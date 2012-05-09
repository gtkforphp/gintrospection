/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
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
#include "php_gi_private.h"

zend_class_entry *ce_gi_baseinfo;
static zend_object_handlers gi_baseinfo_object_handlers;
static zend_function gi_baseinfo_constructor_wrapper;

/* ----------------------------------------------------------------
    gi\BaseInfo class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(BaseInfo_getName, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

PHP_METHOD(BaseInfo, getName)
{
	const gchar *name;

	PHP_GI_EXCEPTIONS
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	//name = g_base_info_get_name
}


/* ----------------------------------------------------------------
    gi\BaseInfo Object management
------------------------------------------------------------------*/

/* {{{ gi_baseinfo_construction_wrapper
wraps around the constructor to make sure parent::__construct is always called */
static void gi_baseinfo_construction_wrapper(INTERNAL_FUNCTION_PARAMETERS)
{
	zval *this = getThis();
	gi_baseinfo_object *tobj;
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
	if (!EG(exception) && tobj->is_constructed == 0)
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0 TSRMLS_CC,
			"parent::__construct() must be called in %s::__construct()", this_ce->name);
	efree(fci.params);
	zval_ptr_dtor(&retval_ptr);
}
/* }}} */

/* {{{ gi_baseinfo_get_constructor
gets the constructor for the class */
static zend_function *gi_baseinfo_get_constructor(zval *object TSRMLS_DC)
{
	if (Z_OBJCE_P(object) == ce_gi_baseinfo) {
		return zend_get_std_object_handlers()->get_constructor(object TSRMLS_CC);
	} else {
		return &gi_baseinfo_constructor_wrapper;
	}
}
/* }}} */

/* {{{ gi_baseinfo_object_free
unrefs our baseinfo stuff */
static void gi_baseinfo_object_free(void *object TSRMLS_DC)
{
	gi_baseinfo_object *baseinfo_object = (gi_baseinfo_object *)object;

	zend_object_std_dtor(&baseinfo_object->std TSRMLS_CC);

	efree(baseinfo_object);
}
/* }}} */

/* {{{ gi_basinfo_object_create
object that has an internal HANDLE stored */
static zend_object_value gi_baseinfo_object_create(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	gi_baseinfo_object *baseinfo_object;

	baseinfo_object = ecalloc(1, sizeof(gi_baseinfo_object));
	zend_object_std_init((zend_object *) baseinfo_object, ce TSRMLS_CC);
	baseinfo_object->is_constructed = FALSE;

	object_properties_init(&baseinfo_object->std, ce);

	retval.handle = zend_objects_store_put(baseinfo_object,
		(zend_objects_store_dtor_t) zend_objects_destroy_object,
		(zend_objects_free_object_storage_t) gi_baseinfo_object_free,
		NULL TSRMLS_CC);
	retval.handlers = &gi_baseinfo_object_handlers;
	return retval;
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\BaseInfo Definition and registration
------------------------------------------------------------------*/

static const zend_function_entry gi_baseinfo_methods[] = {
	PHP_ME(BaseInfo, getName, BaseInfo_getName, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(BaseInfo)
{
	zend_class_entry ce;

	memcpy(&gi_baseinfo_object_handlers, zend_get_std_object_handlers(),
	sizeof gi_baseinfo_object_handlers);
	gi_baseinfo_object_handlers.get_constructor = gi_baseinfo_get_constructor;

	INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(GI_NAMESPACE, "BaseInfo"), gi_baseinfo_methods);
	ce_gi_baseinfo = zend_register_internal_class(&ce TSRMLS_CC);

	ce_gi_baseinfo->create_object = gi_baseinfo_object_create;

	gi_baseinfo_constructor_wrapper.type = ZEND_INTERNAL_FUNCTION;
	gi_baseinfo_constructor_wrapper.common.function_name = "internal_construction_wrapper";
	gi_baseinfo_constructor_wrapper.common.scope = ce_gi_baseinfo;
	gi_baseinfo_constructor_wrapper.common.fn_flags = ZEND_ACC_PROTECTED;
	gi_baseinfo_constructor_wrapper.common.prototype = NULL;
	gi_baseinfo_constructor_wrapper.common.required_num_args = 0;
	gi_baseinfo_constructor_wrapper.common.arg_info = NULL;
	gi_baseinfo_constructor_wrapper.internal_function.handler = gi_baseinfo_construction_wrapper;
	gi_baseinfo_constructor_wrapper.internal_function.module = EG(current_module);

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
