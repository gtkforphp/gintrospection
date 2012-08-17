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

#include "php_gi.h"

zend_class_entry *ce_gi_baseinfo;

/* ----------------------------------------------------------------
    G\Introspection\BaseInfo class API
------------------------------------------------------------------*/

/* {{{ proto void BaseInfo->__construct()
                 Private constructor placeholder (does nothing) */
PHP_METHOD(BaseInfo, __construct)
{
	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GI_RESTORE_ERRORS
}
/* }}} */


/* ----------------------------------------------------------------
    G\Introspection\BaseInfo Object management
------------------------------------------------------------------*/

/* {{{ gi_baseinfo_object_free */
static void gi_baseinfo_object_free(void *object TSRMLS_DC)
{
	gi_baseinfo_object *baseinfo_object = (gi_baseinfo_object *)object;

	zend_object_std_dtor(&baseinfo_object->std TSRMLS_CC);
	baseinfo_object->is_constructed = FALSE;
	if (NULL != baseinfo_object->info) {
		g_base_info_unref(baseinfo_object->info);
		baseinfo_object->info = NULL;
	}

	efree(baseinfo_object);
}
/* }}} */

/* {{{ gi_baseinfo_object_create */
static zend_object_value gi_baseinfo_object_create(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	gi_baseinfo_object *baseinfo_object;

	baseinfo_object = ecalloc(1, sizeof(gi_baseinfo_object));
	zend_object_std_init((zend_object *) baseinfo_object, ce TSRMLS_CC);
	baseinfo_object->is_constructed = FALSE;
	baseinfo_object->info = NULL;

	object_properties_init(&baseinfo_object->std, ce);

	retval.handle = zend_objects_store_put(baseinfo_object,
		(zend_objects_store_dtor_t) zend_objects_destroy_object,
		(zend_objects_free_object_storage_t) gi_baseinfo_object_free,
		NULL TSRMLS_CC);
	retval.handlers = &std_object_handlers;
	return retval;
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\BaseInfo Definition and registration
------------------------------------------------------------------*/

/* {{{ class methods */
static const zend_function_entry gi_baseinfo_methods[] = {
	PHP_ME(BaseInfo, __construct, NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(BaseInfo)
{
	zend_class_entry ce;
	INIT_NS_CLASS_ENTRY(ce, GI_NAMESPACE, "BaseInfo", gi_baseinfo_methods);
	ce_gi_baseinfo = zend_register_internal_class(&ce TSRMLS_CC);
	ce_gi_baseinfo->ce_flags |= ZEND_ACC_FINAL;

	ce_gi_baseinfo->create_object = gi_baseinfo_object_create;

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
