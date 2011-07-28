/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2011 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Elizabeth M Smith <auroraeosrose@php.net>                    |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <php.h>
#include "php_gir_private.h"
#include <zend_exceptions.h>

#include <ext/spl/spl_exceptions.h>

ZEND_DECLARE_MODULE_GLOBALS(gir)

/* Gir\Repository class information */
static zend_class_entry *ce_gir_repository;

/**
 * FFI calls for methods
 */
void gir_ffi_call(INTERNAL_FUNCTION_PARAMETERS)
{

	zend_function *active_function = EG(current_execute_data)->function_state.function;

	const char *method_name = active_function->common.function_name;
	const char *class_name = NULL;
	const char *value = NULL;
	
	if (active_function->common.scope) {
		class_name = active_function->common.scope->name;
	}

	if (zend_hash_find(GIR_G(method_map), method_name, strlen(method_name) + 1, (void **) &value) == SUCCESS) {
    	php_printf("WTF we found %s\n", value);
    }


	if (class_name) {
		php_printf("Hey! Someone called me! My name is: %s::%s()\n", class_name, method_name);

	} else {
		php_printf("Hey! Someone called me! My name is: %s()\n", method_name);
	}
}

/**
 * Helper Method used to get information for enums to load them into PHP
 */
int static gir_repository_load_enum(const gchar *ns_name, GIEnumInfo *e_info TSRMLS_DC)
{
	int i = 0;
	gint enum_total = 0;
	zend_class_entry ce;
	char *phpname = gir_namespaced_name(ns_name, g_base_info_get_name(e_info), TRUE);

	/* TODO: enum base class? */
	INIT_CLASS_ENTRY_EX(ce, phpname, strlen(phpname), NULL);

	zend_class_entry *target = zend_register_internal_class(&ce TSRMLS_CC);
	target->module = phpext_gir_ptr;

    enum_total = g_enum_info_get_n_values (e_info);
	for(i; i < enum_total; i++) {
		GIValueInfo *current_enum = g_enum_info_get_value(e_info, i);
		gchar * upper_case = g_utf8_strup(g_base_info_get_name(current_enum), -1);

		/* TODO: properly juggle the g_value_info_get_value to a long
           ALSO if it's unsigned it'll overflow so use a string instead! */
		
		zend_declare_class_constant_long(target, upper_case, strlen(upper_case) + 1, (long) g_value_info_get_value(current_enum));

		g_base_info_unref(current_enum);
	}

	return SUCCESS;		
}

/**
 * Helper Method used to get information for structs to load them into PHP
 */
int static gir_repository_load_struct(const gchar *ns_name, GIStructInfo *c_info TSRMLS_DC)
{
	size_t pos = 0;
	gint i = 0;
	gint n = g_struct_info_get_n_methods (c_info);
	zend_function_entry *functions = ecalloc(n + 1, sizeof(zend_function_entry));
	const gchar *object_name = g_base_info_get_name(c_info); // TODO: name should be gir_namespace_class_{class}
	char *phpname = gir_namespaced_name(ns_name, object_name, TRUE);

	/* If the struct has no methods, it is directly translatable to an associative array
       so nothing is done with it */
	if (n < 1) {
		efree(functions);
		php_printf("no methods for struct %s, ignoring\n", phpname);
		return SUCCESS;
	}

	for (i; i < n; i++) {
		GIFunctionInfo *m_info = g_struct_info_get_method  (c_info, i);
		GIFunctionInfoFlags flags = g_function_info_get_flags(m_info);

		if (flags & GI_FUNCTION_IS_METHOD) {
			const gchar *name = g_base_info_get_name(m_info);
			char *store = strdup(name);

			zend_function_entry fe = { name, gir_ffi_call, NULL};
			zend_hash_add(GIR_G(method_map), store, strlen(store) + 1, (void *) store, strlen(store) + 1, NULL);

			functions[pos++] = fe;
		}

		g_base_info_unref(m_info);
	}

	zend_function_entry empty_fe = {NULL, NULL, NULL};
	functions[pos] = empty_fe;

	zend_class_entry ce;

	INIT_CLASS_ENTRY_EX(ce, phpname, strlen(phpname), functions);

	zend_class_entry *target = zend_register_internal_class(&ce TSRMLS_CC);
	target->module = phpext_gir_ptr;

	efree(functions);

	return SUCCESS;		
}

/**
 * Helper Method used to get information for constants to load them into PHP
 */
int static gir_repository_load_constant(const gchar *ns_name, GIConstantInfo *c_info TSRMLS_DC)
{
	GIArgument giargument;
	gint size;
	zval *value;
	char *phpname = gir_namespaced_name(ns_name, g_base_info_get_name(c_info), TRUE);

    if (g_constant_info_get_value (c_info, &giargument) < 0) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "Could not get Constant Value");
        return FAILURE;
    }

	zend_constant *const_struct = emalloc(sizeof(zend_constant));
	const_struct->flags = CONST_CS;
	const_struct->name = phpname;
	const_struct->name_len = strlen(phpname) + 1;
	const_struct->module_number = phpext_gir_ptr.module_number;

	if (FAILURE ==	gir_types_giargument_to_zval((GITypeInfo *)g_constant_info_get_type(c_info), &giargument, &const_struct->value TSRMLS_CC)) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0 TSRMLS_CC, "Could not translate Constant Value");
		efree(const_struct);
        return FAILURE;
	}
	zend_register_constant(const_struct TSRMLS_CC);
	efree(const_struct);

	return SUCCESS;		
}

/* Repository API */

PHP_METHOD(Repository, importNamespace)
{
	/* parameter parsing */
	char *name = NULL, *version = NULL;
	int name_len = 0, version_len = 0;

	/* Typelib loading */
	GError *error = NULL;
	GITypelib *type_lib = NULL;

	/* Number of metadata in typelib */
	gint metadata_count = 0, i = 0;

	/* GIR repository */
	GIRepository *gir = g_irepository_get_default();

	/* namespace to put in and optional version */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len, &version, &version_len) == FAILURE) {
		return;
	}

	/* This needs to be replaced with a hashtable lookup for what has been imported
       to see if the namespace has been loaded  
	if (g_irepository_is_registered(obj->gir, name, version)) {
		RETURN_TRUE;
	} */

	/* Always do the require, according to the docs it's just as fast as calling an is_registered check
       beforehand, so we'll just always make sure the namespace tries to load */
	type_lib = g_irepository_require(gir, name, version, 0, &error);

	if (error) {
		zend_throw_exception_ex(spl_ce_OutOfBoundsException, error->code TSRMLS_CC, "Could not find \"%s\" namespace to load: %s", name, error->message);
		g_error_free(error);
		return;
	}

	/* Walk the repository and register everything into PHP
       TODO: we need to check for dependencies of a library
             and load those FIRST */
	metadata_count = g_irepository_get_n_infos(gir, name);
	for (i; i < metadata_count; i++) {
		GIBaseInfo *b_info = g_irepository_get_info(gir, name, i);
		GIInfoType info_type = g_base_info_get_type(b_info);
		const gchar *ns_name = g_base_info_get_namespace(b_info);

		switch (info_type) {
			case GI_INFO_TYPE_INTERFACE:
				php_printf("-> interface %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_OBJECT:
				//gobject_girepository_load_class(b_info TSRMLS_CC);
				php_printf("-> object %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_TYPE:
				php_printf("-> type %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_STRUCT:
				gir_repository_load_struct(ns_name, (GIStructInfo *) b_info TSRMLS_CC);
			break;

			case GI_INFO_TYPE_FUNCTION:
				//gobject_girepository_load_function(b_info TSRMLS_CC);
			break;

			case GI_INFO_TYPE_FLAGS:
			case GI_INFO_TYPE_ENUM:
				gir_repository_load_enum(ns_name, (GIEnumInfo *)b_info TSRMLS_CC);
			break;

			case GI_INFO_TYPE_BOXED:
				php_printf("-> boxed %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_CONSTANT:
				gir_repository_load_constant(ns_name, (GIConstantInfo *) b_info TSRMLS_CC);
			break;

			case GI_INFO_TYPE_CALLBACK:
				php_printf("-> callback %s\n", g_base_info_get_name(b_info));
			break;

			default:
				php_printf("-> ??? %s\n", g_base_info_get_name(b_info));
			break;
		}
		g_base_info_unref(b_info);
	}

	RETURN_TRUE;
}

/* Register Object */
static const zend_function_entry gir_repository_methods[] = {
	PHP_ME(Repository, importNamespace, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(repository)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(GIR_NAMESPACE, "Repository"), gir_repository_methods);
    ce_gir_repository = zend_register_internal_class(&ce TSRMLS_CC);

    return SUCCESS;
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
