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

/* Gir\Repository class information */
static zend_object_handlers gir_object_handlers;
static zend_class_entry *ce_gir_repository;
static zend_function gir_construct_wrapper;

/* Make repository extendable properly */
static zend_object_value ce_create_gir_repository_object(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value 		zov;
    gir_repository_object   *obj;
 
    obj = emalloc(sizeof *obj);
    zend_object_std_init((zend_object *) obj, class_type TSRMLS_CC);
    obj->constructed = 0;
	obj->gir = NULL;
 
#if PHP_VERSION_ID < 50399
    zend_hash_copy(obj->std.properties, &(class_type->default_properties),
        (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval*));
#else
    object_properties_init(&obj->std, class_type);
#endif
 
    zov.handle = zend_objects_store_put(obj,
        (zend_objects_store_dtor_t) zend_objects_destroy_object,
        (zend_objects_free_object_storage_t) zend_objects_free_object_storage,
        NULL TSRMLS_CC);
    zov.handlers = &gir_object_handlers;
    return zov;
}

static zend_function *gir_get_constructor(zval *object TSRMLS_DC)
{
    if (Z_OBJCE_P(object) == ce_gir_repository)
        return zend_get_std_object_handlers()->
            get_constructor(object TSRMLS_CC);
    else
        return &gir_construct_wrapper;
}

static void construction_wrapper(INTERNAL_FUNCTION_PARAMETERS) {
    zval *this = getThis();
    gir_repository_object *obj;
    zend_class_entry *this_ce;
    zend_function *zf;
    zend_fcall_info fci = {0};
    zend_fcall_info_cache fci_cache = {0};
    zval *retval_ptr = NULL;
    unsigned i;
 
    obj = zend_object_store_get_object(this TSRMLS_CC);
    zf = zend_get_std_object_handlers()->get_constructor(this TSRMLS_CC);
    this_ce = Z_OBJCE_P(this);
 
    fci.size = sizeof(fci);
    fci.function_table = &this_ce->function_table;
    fci.object_ptr = this;
    /* fci.function_name = ; not necessary to bother */
    fci.retval_ptr_ptr = &retval_ptr;
    fci.param_count = ZEND_NUM_ARGS();
    fci.params = emalloc(fci.param_count * sizeof *fci.params);
    /* Or use _zend_get_parameters_array_ex instead of loop: */
    for (i = 0; i < fci.param_count; i++) {
        fci.params[i] = (zval **) (zend_vm_stack_top(TSRMLS_C) - 1 -
            (fci.param_count - i));
    }
    fci.object_ptr = this;
    fci.no_separation = 0;
 
    fci_cache.initialized = 1;
    fci_cache.called_scope = EG(current_execute_data)->called_scope;
    fci_cache.calling_scope = EG(current_execute_data)->current_scope;
    fci_cache.function_handler = zf;
    fci_cache.object_ptr = this;
 
    zend_call_function(&fci, &fci_cache TSRMLS_CC);
    if (!EG(exception) && obj->constructed == 0)
        zend_throw_exception(NULL, "parent::__construct() must be called in "
            "the constructor.", 0 TSRMLS_CC);
    efree(fci.params);
    zval_ptr_dtor(&retval_ptr);
}

/* Repository API */
PHP_METHOD(Repository, __construct)
{
    gir_repository_object *obj = zend_object_store_get_object(getThis() TSRMLS_CC);

    obj->constructed = (zend_bool) 1;
	obj->gir = g_irepository_get_default();
}

PHP_METHOD(Repository, import)
{
	/* parameter parsing */
	char *name = NULL, *version = NULL;
	int name_len = 0, version_len = 0;

	/* Typelib loading */
	GError *error = NULL;
	GITypelib *type_lib = NULL;

	/* Number of metadata in typelib */
	gint metadata_count = 0, i = 0;

	/* Our object struct with repo */
	gir_repository_object *obj = zend_object_store_get_object(getThis() TSRMLS_CC);	

	/* namespace to put in and optional version */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len, &version, &version_len) == FAILURE) {
		return;
	}

	/* Check and see if the ns is registered,
       we use this instead of require straight off so we can skip all loading into PHP */
	if (g_irepository_is_registered(obj->gir, name, version)) {
		RETURN_TRUE;
	}

	/* Otherwise let's try to load this in */
	type_lib = g_irepository_require(obj->gir, name, version, 0, &error);

	if (error) {
		zend_throw_exception_ex(spl_ce_OutOfBoundsException, error->code TSRMLS_CC, "Failed to load \"%s\" namespace: %s", name, error->message);
		g_error_free(error);
		return;
	}

	/* Walk the repository and register stuff into PHP */
	metadata_count = g_irepository_get_n_infos(obj->gir, name);
	for (i; i < metadata_count; i++) {
		GIBaseInfo *b_info = g_irepository_get_info(obj->gir, name, i);
		GIInfoType info_type = g_base_info_get_type(b_info);

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
				php_printf("-> struct %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_FUNCTION:
				//gobject_girepository_load_function(b_info TSRMLS_CC);
			break;

			case GI_INFO_TYPE_ENUM:
				php_printf("-> enumeration %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_BOXED:
				php_printf("-> boxed %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_FLAGS:
				php_printf("-> flags %s\n", g_base_info_get_name(b_info));
			break;

			case GI_INFO_TYPE_CONSTANT:
				//gir_repository_load_constant(ns_name, (GIConstantInfo *) b_info TSRMLS_CC);
				php_printf("-> constant %s\n", g_base_info_get_name(b_info));
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
static const zend_function_entry ext_class_methods[] = {
    PHP_ME(Repository, __construct, 0, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(Repository, import, 0, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(repository)
{
    zend_class_entry ce;
 
    memcpy(&gir_object_handlers, zend_get_std_object_handlers(),
        sizeof gir_object_handlers);
    gir_object_handlers.get_constructor = gir_get_constructor;
    gir_object_handlers.clone_obj       = NULL;
 
    INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(GIR_NAMESPACE, "Repository"), ext_class_methods);
    ce_gir_repository = zend_register_internal_class(&ce TSRMLS_CC);
    ce_gir_repository->create_object = ce_create_gir_repository_object;
 
    gir_construct_wrapper.type = ZEND_INTERNAL_FUNCTION;
    gir_construct_wrapper.common.function_name = "__construct";
    gir_construct_wrapper.common.scope = ce_gir_repository;
    gir_construct_wrapper.common.fn_flags = ZEND_ACC_PROTECTED;
    gir_construct_wrapper.common.prototype = NULL;
    gir_construct_wrapper.common.required_num_args = 0;
    gir_construct_wrapper.common.arg_info = NULL;
#if PHP_VERSION_ID < 50399 
    /* moved to common.fn_flags with rev 303381 */
    gir_construct_wrapper.common.pass_rest_by_reference = 0;
    gir_construct_wrapper.common.return_reference = 0;
#endif
    gir_construct_wrapper.internal_function.handler = construction_wrapper;
    gir_construct_wrapper.internal_function.module = EG(current_module);
 
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
