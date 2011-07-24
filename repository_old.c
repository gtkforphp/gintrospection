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

/* Gir\Repository class */
static zend_object_handlers object_handlers;
static zend_class_entry *ce_ptr;
static zend_function constr_wrapper_fun;

typedef struct test_object {
    zend_object std;
    zend_bool constructed;
	GIRepository *gir;
} test_object;

/**
 * These are a series of helper functions used for translating typelib info and registering them into PHP proper
 */
zend_bool static gir_giarg_to_zval(GITypeInfo *type_info, GIArgument *src, zval *return_value TSRMLS_DC)
{
	GITypeTag type_tag = g_type_info_get_tag(type_info);

	switch (type_tag) {
		case GI_TYPE_TAG_UTF8:
			ZVAL_STRING(return_value, src->v_pointer, 1);
		break;

		default:
			php_error(E_WARNING, "Conversion of this type is not implemented");
			ZVAL_NULL(return_value);
			return FALSE;
		break;
	}

	return TRUE;
}

char* generate_namespaced_name(const char *ns_name, const char *name, zend_bool persistent)
{
	char *phpname = pemalloc(4 + strlen(ns_name) + strlen(name) + 2, persistent);
	sprintf(phpname, "Gir\\%s\\%s", ns_name, name);

	return phpname;
}

void static gir_repository_load_constant(GIConstantInfo *c_info TSRMLS_DC)
{
	GIArgument value;
	gint size = g_constant_info_get_value(c_info, &value);
	GITypeInfo *t_info = g_constant_info_get_type(c_info);

	char *phpname = generate_namespaced_name(g_base_info_get_namespace(c_info), g_base_info_get_name(c_info), TRUE);

	zend_constant *const_struct = emalloc(sizeof(zend_constant));
	const_struct->flags = CONST_CS;
	const_struct->name = phpname;
	const_struct->name_len = strlen(phpname) + 1;
	const_struct->module_number = 0;

	if (FALSE == gir_giarg_to_zval(t_info, &value, &const_struct->value TSRMLS_CC)) {
		// error
		efree(const_struct);
		return;
	}

	zend_register_constant(const_struct TSRMLS_CC);
	efree(const_struct);
}


static zend_object_value ce_create_object(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value zov;
    test_object       *tobj;
 
    tobj = emalloc(sizeof *tobj);
    zend_object_std_init((zend_object *) tobj, class_type TSRMLS_CC);
    tobj->constructed = 0;
 
#if PHP_VERSION_ID < 50399
    zend_hash_copy(tobj->std.properties, &(class_type->default_properties),
        (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval*));
#else
    object_properties_init(&tobj->std, class_type);
#endif
 
    zov.handle = zend_objects_store_put(tobj,
        (zend_objects_store_dtor_t) zend_objects_destroy_object,
        (zend_objects_free_object_storage_t) zend_objects_free_object_storage,
        NULL TSRMLS_CC);
    zov.handlers = &object_handlers;
    return zov;
}

PHP_METHOD(Repository, __construct)
{
    zval *this = getThis();
 
    test_object *tobj = zend_object_store_get_object(this TSRMLS_CC);
    assert(tobj != NULL);

    tobj->constructed = (zend_bool) 1;
	tobj->gir = g_irepository_get_default();
 
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


	zval *this = getThis();
	test_object *tobj = zend_object_store_get_object(this TSRMLS_CC);

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len, &version, &version_len) == FAILURE) {
		return;
	}

	/* Check and see if the ns is registered,
       we use this instead of require straight off so we can skip all loading into PHP */
	if (g_irepository_is_registered(tobj->gir, name, version)) {
		RETURN_TRUE;
	}

	/* Otherwise let's try to load this in */
	type_lib = g_irepository_require(tobj->gir, name, version, 0, &error);

	if (error) {
		zend_throw_exception_ex(spl_ce_OutOfBoundsException, error->code TSRMLS_CC, "Failed to load \"%s\" namespace: %s", name, error->message);
		g_error_free(error);
		return;
	}

	/* Walk the repository and register stuff into PHP */
	metadata_count = g_irepository_get_n_infos(tobj->gir, name);
	for (i; i < metadata_count; i++) {
		GIBaseInfo *b_info = g_irepository_get_info(tobj->gir, name, i);
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
				gir_repository_load_constant(ns_name, (GIConstantInfo *) b_info TSRMLS_CC);
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

static zend_function *get_constructor(zval *object TSRMLS_DC)
{
    /* Could always return constr_wrapper_fun, but it's uncessary to call the
     * wrapper if instantiating the superclass */
    if (Z_OBJCE_P(object) == ce_ptr)
        return zend_get_std_object_handlers()->
            get_constructor(object TSRMLS_CC);
    else
        return &constr_wrapper_fun;
}

static void construction_wrapper(INTERNAL_FUNCTION_PARAMETERS) {
    zval *this = getThis();
    test_object *tobj;
    zend_class_entry *this_ce;
    zend_function *zf;
    zend_fcall_info fci = {0};
    zend_fcall_info_cache fci_cache = {0};
    zval *retval_ptr = NULL;
    unsigned i;
 
    tobj = zend_object_store_get_object(this TSRMLS_CC);
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
    if (!EG(exception) && tobj->constructed == 0)
        zend_throw_exception(NULL, "parent::__construct() must be called in "
            "the constructor.", 0 TSRMLS_CC);
    efree(fci.params);
    zval_ptr_dtor(&retval_ptr);
}
static const zend_function_entry ext_class_methods[] = {
    PHP_ME(Repository, __construct, 0, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(Repository, import, 0, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(repository)
{
    zend_class_entry ce;
 
    memcpy(&object_handlers, zend_get_std_object_handlers(),
        sizeof object_handlers);
    object_handlers.get_constructor = get_constructor;
    object_handlers.clone_obj       = NULL;
 
    INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(GIR_NAMESPACE, "Repository"), ext_class_methods);
    ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
    ce_ptr->create_object = ce_create_object;
 
    constr_wrapper_fun.type = ZEND_INTERNAL_FUNCTION;
    constr_wrapper_fun.common.function_name = "__construct";
    constr_wrapper_fun.common.scope = ce_ptr;
    constr_wrapper_fun.common.fn_flags = ZEND_ACC_PROTECTED;
    constr_wrapper_fun.common.prototype = NULL;
    constr_wrapper_fun.common.required_num_args = 0;
    constr_wrapper_fun.common.arg_info = NULL;
#if PHP_VERSION_ID < 50399 
    /* moved to common.fn_flags with rev 303381 */
    constr_wrapper_fun.common.pass_rest_by_reference = 0;
    constr_wrapper_fun.common.return_reference = 0;
#endif
    constr_wrapper_fun.internal_function.handler = construction_wrapper;
    constr_wrapper_fun.internal_function.module = EG(current_module);
 
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
