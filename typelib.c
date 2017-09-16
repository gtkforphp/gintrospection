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

#include "php_gintrospection.h"

zend_class_entry *ce_gintrospection_typelib;

/* ----------------------------------------------------------------
    G\Introspection\Typelib class API
------------------------------------------------------------------*/

/* {{{ proto void Typelib->__construct()
                 Private constructor placeholder (does nothing) */
PHP_METHOD(Typelib, __construct)
{
	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS
}
/* }}} */

/* {{{ proto string G\Introspection\Typelib->getNamespace()
                  Gets the namespace of a typelib */
PHP_METHOD(Typelib, getNamespace)
{

	gintrospection_typelib_object *typelib_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	typelib_object = (gintrospection_typelib_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_STRING(g_typelib_get_namespace(typelib_object->typelib));
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\Typelib Object management
------------------------------------------------------------------*/

/* {{{ gintrospection_typelib_object_free */
static void gintrospection_typelib_object_free(void *object TSRMLS_DC)
{
	gintrospection_typelib_object *typelib_object = (gintrospection_typelib_object *)object;

	zend_object_std_dtor(&typelib_object->std TSRMLS_CC);
	typelib_object->typelib = NULL;
	typelib_object->is_constructed = FALSE;

	efree(typelib_object);
}
/* }}} */

/* {{{ gintrospection_typelib_object_create */
static zend_object* gintrospection_typelib_object_create(zend_class_entry *ce TSRMLS_DC)
{
	gintrospection_typelib_object *typelib_object;

	typelib_object = ecalloc(1, sizeof(gintrospection_typelib_object)+
                                sizeof(zend_object_properties_size(ce)));
	zend_object_std_init((zend_object *) typelib_object, ce TSRMLS_CC);
	typelib_object->is_constructed = FALSE;
	typelib_object->typelib = NULL;

	object_properties_init(&typelib_object->std, ce);

	typelib_object->std.handlers = &std_object_handlers;
	return &typelib_object->std;
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\Typelib Definition and registration
------------------------------------------------------------------*/

/* {{{ class methods */
static const zend_function_entry gi_typelib_methods[] = {
	PHP_ME(Typelib, __construct, NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
	PHP_ME(Typelib, getNamespace, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(gintrospection_Typelib)
{
	zend_class_entry ce;
	INIT_NS_CLASS_ENTRY(ce, GINTROSPECTION_NAMESPACE, "Typelib", gi_typelib_methods);
	ce_gintrospection_typelib = zend_register_internal_class(&ce TSRMLS_CC);
	ce_gintrospection_typelib->ce_flags |= ZEND_ACC_FINAL;

	ce_gintrospection_typelib->create_object = gintrospection_typelib_object_create;

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
