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

zend_class_entry *ce_gintrospection_vfuncinfo;
zend_class_entry *ce_gintrospection_signalinfo;
zend_class_entry *ce_gintrospection_functioninfo;
zend_class_entry *ce_gintrospection_callableinfo;
zend_class_entry *ce_gintrospection_unioninfo;
zend_class_entry *ce_gintrospection_structinfo;
zend_class_entry *ce_gintrospection_objectinfo;
zend_class_entry *ce_gintrospection_interfaceinfo;
zend_class_entry *ce_gintrospection_enuminfo;
zend_class_entry *ce_gintrospection_regtypeinfo;
zend_class_entry *ce_gintrospection_arginfo;
zend_class_entry *ce_gintrospection_constantinfo;
zend_class_entry *ce_gintrospection_fieldinfo;
zend_class_entry *ce_gintrospection_propertyinfo;
zend_class_entry *ce_gintrospection_typeinfo;
zend_class_entry *ce_gintrospection_baseinfo;
zend_class_entry *ce_gintrospection_valueinfo;

/* {{{ exported function to take a gerror, throw an exception, and clear the error */
zend_class_entry* php_gintrospection_get_info_ce(GIBaseInfo *info)
{
	if(GI_IS_VFUNC_INFO(info)) {
		return ce_gintrospection_vfuncinfo;
	} else if (GI_IS_SIGNAL_INFO(info)) {
		return ce_gintrospection_signalinfo;
	} else if (GI_IS_FUNCTION_INFO(info)) {
		return ce_gintrospection_functioninfo;
	} else if (GI_IS_CALLABLE_INFO(info)) {
		return ce_gintrospection_callableinfo;
	} else if (GI_IS_UNION_INFO(info)) {
		return ce_gintrospection_unioninfo;
	} else if (GI_IS_STRUCT_INFO(info)) {
		return ce_gintrospection_structinfo;
	} else if (GI_IS_OBJECT_INFO(info)) {
		return ce_gintrospection_objectinfo;
	} else if (GI_IS_INTERFACE_INFO(info)) {
		return ce_gintrospection_interfaceinfo;
	} else if (GI_IS_ENUM_INFO(info)) {
		return ce_gintrospection_enuminfo;
	} else if (GI_IS_REGISTERED_TYPE_INFO(info)) {
		return ce_gintrospection_regtypeinfo;
	} else if (GI_IS_ARG_INFO(info)) {
		return ce_gintrospection_arginfo;
	} else if (GI_IS_CONSTANT_INFO(info)) {
		return ce_gintrospection_constantinfo;
	} else if (GI_IS_FIELD_INFO(info)) {
		return ce_gintrospection_fieldinfo;
	} else if (GI_IS_PROPERTY_INFO(info)) {
		return ce_gintrospection_propertyinfo;
	} else if ( GI_IS_TYPE_INFO(info)) {
		return ce_gintrospection_typeinfo;
	}

	return ce_gintrospection_baseinfo;
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\BaseInfo class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(BaseInfo_getAttribute_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(BaseInfo_equal_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_OBJ_INFO(0, info, G\\Introspection\\BaseInfo, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

/* {{{ proto void BaseInfo->__construct()
                 Private constructor placeholder (does nothing) */
PHP_METHOD(BaseInfo, __construct)
{
	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS
}
/* }}} */

/* {{{ proto string G\Introspection\BaseInfo->getType()
                  get enum of type */
PHP_METHOD(BaseInfo, getType)
{

	gintrospection_baseinfo_object *baseinfo_object;
	GIInfoType type;
	const gchar *name;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	type = g_base_info_get_type(baseinfo_object->info);

	object_init_ex(return_value, ce_gintrospection_infotype);
	php_glib_set_enum_value(&return_value, type TSRMLS_CC);
}
/* }}} */

/* {{{ proto string G\Introspection\BaseInfo->getTypeName()
                  string name of the baseinfo type */
PHP_METHOD(BaseInfo, getTypeName)
{

	gintrospection_baseinfo_object *baseinfo_object;
	GIInfoType type;
	const gchar *name;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	type = g_base_info_get_type(baseinfo_object->info);
	name = g_info_type_to_string(type);

	RETURN_STRING(name);
}
/* }}} */

/* {{{ proto string G\Introspection\BaseInfo->getName()
                  get the name of the information */
PHP_METHOD(BaseInfo, getName)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_STRING(g_base_info_get_name(baseinfo_object->info));
}
/* }}} */

/* {{{ proto string G\Introspection\BaseInfo->getNameSpace()
                  get the namespace of the information */
PHP_METHOD(BaseInfo, getNameSpace)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_STRING(g_base_info_get_namespace(baseinfo_object->info));
}
/* }}} */

/* {{{ proto bool G\Introspection\BaseInfo->getDeprecated()
                  is it deprecated */
PHP_METHOD(BaseInfo, isDeprecated)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_BOOL(g_base_info_is_deprecated(baseinfo_object->info));
}
/* }}} */

/* {{{ proto string G\Introspection\BaseInfo->getAttribute(string $name)
                  get a value for a single attribute */
PHP_METHOD(BaseInfo, getAttribute)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gchar *name;
	int name_len;
	const gchar *value;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	value = g_base_info_get_attribute(baseinfo_object->info, name);

	if(value) {
		RETURN_STRING(value);
	}

}
/* }}} */

/* {{{ proto array G\Introspection\BaseInfo->getAttributes()
                  list of attributes */
PHP_METHOD(BaseInfo, getAttributes)
{

	gintrospection_baseinfo_object *baseinfo_object;
	GIAttributeIter iter = { 0, };
	gchar *name, *value;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	array_init(return_value);
	while (g_base_info_iterate_attributes (baseinfo_object->info, &iter, &name, &value)) {
		add_assoc_string(return_value, name, value);
	}

}
/* }}} */

/* {{{ proto object G\Introspection\BaseInfo->getContainer()
                  gets the container info (or null) for an item */
PHP_METHOD(BaseInfo, getContainer)
{

	gintrospection_baseinfo_object *baseinfo_object;
	GIBaseInfo *info;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	info = g_base_info_get_container(baseinfo_object->info);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, php_gintrospection_get_info_ce(info));
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
	g_base_info_unref(info);
}
/* }}} */

/* {{{ proto object G\Introspection\BaseInfo->getTypelib()
                  gets the typelib for a baseinfo */
PHP_METHOD(BaseInfo, getTypelib)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gintrospection_typelib_object *typelib_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	object_init_ex(return_value, ce_gintrospection_typelib);
	typelib_object = (gintrospection_typelib_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	typelib_object->is_constructed = TRUE;

	typelib_object->typelib = g_base_info_get_typelib(baseinfo_object->info);
	if(!typelib_object->typelib) {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto boolean G\Introspection\BaseInfo->equal(BaseInfo $object)
                  get a value for a single attribute */
PHP_METHOD(BaseInfo, equal)
{

	gintrospection_baseinfo_object *baseinfo_object1;
	gintrospection_baseinfo_object *baseinfo_object2;
	zval *object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &object, ce_gintrospection_baseinfo)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object1 = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	baseinfo_object2 = (gintrospection_baseinfo_object *) zend_object_store_get_object(object TSRMLS_CC);

	RETURN_BOOL(g_base_info_equal(baseinfo_object1->info, baseinfo_object2->info));
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\RegisteredTypeInfo class API
------------------------------------------------------------------*/

/* {{{ proto object G\Introspection\RegisteredTypeInfo->getGTypeName()
                  Obtain the type name of the struct within the GObject type system */
PHP_METHOD(RegisteredTypeInfo, getGTypeName)
{

	gintrospection_baseinfo_object *baseinfo_object;
	const gchar * name;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	name = g_registered_type_info_get_type_name(baseinfo_object->info);

	if (name) {
		RETURN_STRING(name);
	}
}
/* }}} */

/* {{{ proto object G\Introspection\RegisteredTypeInfo->getTypeInit()
                  The type init function is the function which will register
                  the GType within the GObject type system */
PHP_METHOD(RegisteredTypeInfo, getTypeInit)
{

	gintrospection_baseinfo_object *baseinfo_object;
	const gchar * name;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	name = g_registered_type_info_get_type_init(baseinfo_object->info);

	if (name) {
		RETURN_STRING(name);
	}
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\EnumInfo class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(EnumInfo_getValue_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(EnumInfo_getMethod_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

/* {{{ proto int G\Introspection\EnumInfo->getNumValues()
                  Gets the total number of values in the enum */
PHP_METHOD(EnumInfo, getNumValues)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_LONG(g_enum_info_get_n_values(baseinfo_object->info));
}
/* }}} */

/* {{{ proto object G\Introspection\EnumInfo->getValue(string $namespace, int $index)
                 Returns an info object at $index in the repository - index is 0 based
                 so it is number of infos -1 for a range*/
PHP_METHOD(EnumInfo, getValue)
{

	gintrospection_baseinfo_object *baseinfo_object;
	long index;
	gint total;
	GIBaseInfo *info;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	total = g_enum_info_get_n_values(baseinfo_object->info);

	if (total == 0) {
		RETURN_NULL();
	}

	/* our index must be between 0 and maximum number infos */
	if (index < 0 || index > total) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Index must be between 0 and %d", total);
		return;
	}

	info = g_enum_info_get_value(baseinfo_object->info, (gint) index);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_valueinfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto array G\Introspection\EnumInfo->getValues()
                 Returns an array of all enum value infos */
PHP_METHOD(EnumInfo, getValues)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gint total, i;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	total = g_enum_info_get_n_values(baseinfo_object->info);

	array_init(return_value);

	for (i = 0; i < total; i++) {
		gintrospection_baseinfo_object *nested_object;
		zval *zinfo;
		GIBaseInfo *info = NULL;

		info = g_enum_info_get_value(baseinfo_object->info, i);
		/* baseinfo was not loaded right, continue */
		if (NULL == info) {
			continue;
		} else {
			MAKE_STD_ZVAL(zinfo);
			object_init_ex(zinfo, ce_gintrospection_valueinfo);
			nested_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(zinfo TSRMLS_CC);
			nested_object->is_constructed = TRUE;
			nested_object->info = g_base_info_ref(info);
			add_next_index_zval(return_value, zinfo);
		}
	}
}
/* }}} */

/* {{{ proto int G\Introspection\EnumInfo->getNumMethods()
                  Gets the total number of methods in the enum */
PHP_METHOD(EnumInfo, getNumMethods)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_LONG(g_enum_info_get_n_methods(baseinfo_object->info));
}
/* }}} */

/* {{{ proto object G\Introspection\EnumInfo->getMethod(int $index)
                 Returns an info object at $index in the repository - index is 0 based
                 so it is number of infos -1 for a range*/
PHP_METHOD(EnumInfo, getMethod)
{

	gintrospection_baseinfo_object *baseinfo_object;
	long index;
	gint total;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	total = g_enum_info_get_n_methods(baseinfo_object->info);

	if (total == 0) {
		RETURN_NULL();
	}

	/* our index must be between 0 and maximum number infos */
	if (index < 0 || index > total) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Index must be between 0 and %d", total);
		return;
	}

	info = g_enum_info_get_method(baseinfo_object->info, (gint) index);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_functioninfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto array G\Introspection\EnumInfo->getMethods()
                 Returns an array of all method infos */
PHP_METHOD(EnumInfo, getMethods)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gint total, i;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	total = g_enum_info_get_n_methods(baseinfo_object->info);

	array_init(return_value);

	for (i = 0; i < total; i++) {
		gintrospection_baseinfo_object *child_object;
		zval *zinfo;
		GIBaseInfo *info = NULL;

		info = g_enum_info_get_method(baseinfo_object->info, i);
		/* baseinfo was not loaded right, continue */
		if (NULL == info) {
			continue;
		} else {
			MAKE_STD_ZVAL(zinfo);
			object_init_ex(zinfo, ce_gintrospection_functioninfo);
			child_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(zinfo TSRMLS_CC);
			child_object->is_constructed = TRUE;
			child_object->info = g_base_info_ref(info);
			add_next_index_zval(return_value, zinfo);
			g_base_info_unref(info);
		}
	}
}
/* }}} */

/* {{{ proto string G\Introspection\EnumInfo->getStorageType()
                  get enum of type */
PHP_METHOD(EnumInfo, getStorageType)
{

	gintrospection_baseinfo_object *baseinfo_object;
	GITypeTag type;
	const gchar *name;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	type = g_enum_info_get_storage_type(baseinfo_object->info);

	object_init_ex(return_value, ce_gintrospection_typetag);
	php_glib_set_enum_value(&return_value, type TSRMLS_CC);
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\ValueInfo class API
------------------------------------------------------------------*/

/* {{{ proto string G\Introspection\ValueInfo->getValue()
                  this is a gint64 (eww) so we push it into
                  a string.  Can later be juggled if that
                  is desired but user takes reposibility for overflows */
PHP_METHOD(ValueInfo, getValue)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gchar *value;
	gint64 item;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	item = g_value_info_get_value(baseinfo_object->info);

	value = g_strdup_printf("%"G_GINT64_FORMAT, item);
	RETVAL_STRING(value);
	g_free(value);
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\StructInfo class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(StructInfo_getField_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(StructInfo_getMethod_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(StructInfo_findMethod_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

/* {{{ proto int G\Introspection\StructInfo->getNumFields()
                  Gets the total number of fields attached to the struct */
PHP_METHOD(StructInfo, getNumFields)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_LONG(g_struct_info_get_n_fields(baseinfo_object->info));
}
/* }}} */

/* {{{ proto object G\Introspection\StructInfo->getField(int $index)
                 Returns an info object at $index in the repository - index is 0 based
                 so it is number of infos -1 for a range */
PHP_METHOD(StructInfo, getField)
{

	gintrospection_baseinfo_object *baseinfo_object;
	long index;
	gint total;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	total = g_struct_info_get_n_fields(baseinfo_object->info);

	if (total == 0) {
		RETURN_NULL();
	}

	/* our index must be between 0 and maximum number infos */
	if (index < 0 || index > total) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Index must be between 0 and %d", total);
		return;
	}

	info = g_struct_info_get_field(baseinfo_object->info, (gint) index);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_fieldinfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto array G\Introspection\StructInfo->getFields()
                 Returns an array of all method infos */
PHP_METHOD(StructInfo, getFields)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gint total, i;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	total = g_struct_info_get_n_fields(baseinfo_object->info);

	array_init(return_value);

	for (i = 0; i < total; i++) {
		gintrospection_baseinfo_object *child_object;
		zval *zinfo;
		GIBaseInfo *info = NULL;

		info = g_struct_info_get_field(baseinfo_object->info, i);
		/* baseinfo was not loaded right, continue */
		if (NULL == info) {
			continue;
		} else {
			MAKE_STD_ZVAL(zinfo);
			object_init_ex(zinfo, ce_gintrospection_fieldinfo);
			child_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(zinfo TSRMLS_CC);
			child_object->is_constructed = TRUE;
			child_object->info = g_base_info_ref(info);
			add_next_index_zval(return_value, zinfo);
			g_base_info_unref(info);
		}
	}
}
/* }}} */

/* {{{ proto int G\Introspection\StructInfo->getNumMethods()
                  Gets the total number of methods attached to the struct */
PHP_METHOD(StructInfo, getNumMethods)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_LONG(g_struct_info_get_n_methods(baseinfo_object->info));
}
/* }}} */

/* {{{ proto object G\Introspection\StructInfo->getMethod(int $index)
                 Returns an info object at $index in the repository - index is 0 based
                 so it is number of infos -1 for a range*/
PHP_METHOD(StructInfo, getMethod)
{

	gintrospection_baseinfo_object *baseinfo_object;
	long index;
	gint total;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	total = g_struct_info_get_n_methods(baseinfo_object->info);

	if (total == 0) {
		RETURN_NULL();
	}

	/* our index must be between 0 and maximum number infos */
	if (index < 0 || index > total) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Index must be between 0 and %d", total);
		return;
	}

	info = g_struct_info_get_method(baseinfo_object->info, (gint) index);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_functioninfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto array G\Introspection\Structnfo->getMethods()
                 Returns an array of all method infos */
PHP_METHOD(StructInfo, getMethods)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gint total, i;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	total = g_struct_info_get_n_methods(baseinfo_object->info);

	array_init(return_value);

	for (i = 0; i < total; i++) {
		gintrospection_baseinfo_object *child_object;
		zval *zinfo;
		GIBaseInfo *info = NULL;

		info = g_struct_info_get_method(baseinfo_object->info, i);
		/* baseinfo was not loaded right, continue */
		if (NULL == info) {
			continue;
		} else {
			MAKE_STD_ZVAL(zinfo);
			object_init_ex(zinfo, ce_gintrospection_functioninfo);
			child_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(zinfo TSRMLS_CC);
			child_object->is_constructed = TRUE;
			child_object->info = g_base_info_ref(info);
			add_next_index_zval(return_value, zinfo);
			g_base_info_unref(info);
		}
	}
}
/* }}} */

/* {{{ proto object G\Introspection\StructInfo->findMethod(string $name)
                 Returns method with $name from struct (or null) */
PHP_METHOD(StructInfo, findMethod)
{

	gintrospection_baseinfo_object *baseinfo_object;
	char* name;
	int name_len;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	info = g_struct_info_find_method(baseinfo_object->info, name);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_functioninfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto string G\Introspection\StructInfo->getSize()
                  again, because of possible overflows, we're shoving
                  a gsize into a string */
PHP_METHOD(StructInfo, getSize)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gchar *value;
	gsize item;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	item = g_struct_info_get_size(baseinfo_object->info);

	value = g_strdup_printf("%"G_GSIZE_FORMAT, item);
	RETVAL_STRING(value);
	g_free(value);
}
/* }}} */

/* {{{ proto string G\Introspection\StructInfo->getAlignment()
                  again, because of possible overflows, we're shoving
                  a gsize into a string */
PHP_METHOD(StructInfo, getAlignment)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gchar *value;
	gsize item;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	item = g_struct_info_get_alignment(baseinfo_object->info);

	value = g_strdup_printf("%"G_GSIZE_FORMAT, item);
	RETVAL_STRING(value);
	g_free(value);
}
/* }}} */

/* {{{ proto bool G\Introspection\StructInfo->isGTypeStruct()
                  is this a special gtype struct */
PHP_METHOD(StructInfo, isGTypeStruct)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_BOOL(g_struct_info_is_gtype_struct(baseinfo_object->info));
}
/* }}} */

/* {{{ proto bool G\Introspection\StructInfo->isForeign() */
PHP_METHOD(StructInfo, isForeign)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_BOOL(g_struct_info_is_foreign(baseinfo_object->info));
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\UnionInfo class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(UnionInfo_getField_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(UnionInfo_getMethod_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(UnionInfo_getDiscriminator_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(UnionInfo_findMethod_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

/* {{{ proto int G\Introspection\UnionInfo->getNumFields()
                  Gets the total number of fields attached to the struct */
PHP_METHOD(UnionInfo, getNumFields)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_LONG(g_union_info_get_n_fields(baseinfo_object->info));
}
/* }}} */

/* {{{ proto object G\Introspection\UnionInfo->getField(int $index)
                 Returns an info object at $index in the repository - index is 0 based
                 so it is number of infos -1 for a range */
PHP_METHOD(UnionInfo, getField)
{

	gintrospection_baseinfo_object *baseinfo_object;
	long index;
	gint total;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	total = g_union_info_get_n_fields(baseinfo_object->info);

	if (total == 0) {
		RETURN_NULL();
	}

	/* our index must be between 0 and maximum number infos */
	if (index < 0 || index > total) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Index must be between 0 and %d", total);
		return;
	}

	info = g_union_info_get_field(baseinfo_object->info, (gint) index);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_fieldinfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto array G\Introspection\UnionInfo->getFields()
                 Returns an array of all method infos */
PHP_METHOD(UnionInfo, getFields)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gint total, i;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	total = g_union_info_get_n_fields(baseinfo_object->info);

	array_init(return_value);

	for (i = 0; i < total; i++) {
		gintrospection_baseinfo_object *child_object;
		zval *zinfo;
		GIBaseInfo *info = NULL;

		info = g_union_info_get_field(baseinfo_object->info, i);
		/* baseinfo was not loaded right, continue */
		if (NULL == info) {
			continue;
		} else {
			MAKE_STD_ZVAL(zinfo);
			object_init_ex(zinfo, ce_gintrospection_fieldinfo);
			child_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(zinfo TSRMLS_CC);
			child_object->is_constructed = TRUE;
			child_object->info = g_base_info_ref(info);
			add_next_index_zval(return_value, zinfo);
			g_base_info_unref(info);
		}
	}
}
/* }}} */

/* {{{ proto int G\Introspection\UnionInfo->getNumMethods()
                  Gets the total number of methods attached to the struct */
PHP_METHOD(UnionInfo, getNumMethods)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_LONG(g_union_info_get_n_methods(baseinfo_object->info));
}
/* }}} */

/* {{{ proto object G\Introspection\UnionInfo->getMethod(int $index)
                 Returns an info object at $index in the repository - index is 0 based
                 so it is number of infos -1 for a range*/
PHP_METHOD(UnionInfo, getMethod)
{

	gintrospection_baseinfo_object *baseinfo_object;
	long index;
	gint total;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	total = g_union_info_get_n_methods(baseinfo_object->info);

	if (total == 0) {
		RETURN_NULL();
	}

	/* our index must be between 0 and maximum number infos */
	if (index < 0 || index > total) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Index must be between 0 and %d", total);
		return;
	}

	info = g_union_info_get_method(baseinfo_object->info, (gint) index);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_functioninfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto array G\Introspection\UnionInfo->getMethods()
                 Returns an array of all method infos */
PHP_METHOD(UnionInfo, getMethods)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gint total, i;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	total = g_union_info_get_n_methods(baseinfo_object->info);

	array_init(return_value);

	for (i = 0; i < total; i++) {
		gintrospection_baseinfo_object *child_object;
		zval *zinfo;
		GIBaseInfo *info = NULL;

		info = g_union_info_get_method(baseinfo_object->info, i);
		/* baseinfo was not loaded right, continue */
		if (NULL == info) {
			continue;
		} else {
			MAKE_STD_ZVAL(zinfo);
			object_init_ex(zinfo, ce_gintrospection_functioninfo);
			child_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(zinfo TSRMLS_CC);
			child_object->is_constructed = TRUE;
			child_object->info = g_base_info_ref(info);
			add_next_index_zval(return_value, zinfo);
			g_base_info_unref(info);
		}
	}
}
/* }}} */

/* {{{ proto bool G\Introspection\UnionInfo->isDiscriminated()
                  Return true if this union contains discriminator field */
PHP_METHOD(UnionInfo, isDiscriminated)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_BOOL(g_union_info_is_discriminated(baseinfo_object->info));
}
/* }}} */

/* {{{ proto long G\Introspection\UnionInfo->getDiscriminatorOffset() */
PHP_METHOD(UnionInfo, getDiscriminatorOffset)
{

	gintrospection_baseinfo_object *baseinfo_object;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_LONG(g_union_info_get_discriminator_offset(baseinfo_object->info));
}
/* }}} */

/* {{{ proto object G\Introspection\UnionInfo->getDiscriminatorType()
                 Obtain the type information of the union discriminator */
PHP_METHOD(UnionInfo, getDiscriminatorType)
{

	gintrospection_baseinfo_object *baseinfo_object;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	if (FALSE == g_union_info_is_discriminated(baseinfo_object->info)) {
		RETURN_NULL();
	}

	info = g_union_info_get_discriminator_type(baseinfo_object->info);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_typeinfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto object G\Introspection\UnionInfo->getDiscriminator()
                 Obtain the type information of the union discriminator */
PHP_METHOD(UnionInfo, getDiscriminator)
{

	gintrospection_baseinfo_object *baseinfo_object;
	long index;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	info = g_union_info_get_discriminator(baseinfo_object->info, index);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_constantinfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto object G\Introspection\UnionInfo->findMethod(string $name)
                 Returns method with $name from struct (or null) */
PHP_METHOD(UnionInfo, findMethod)
{

	gintrospection_baseinfo_object *baseinfo_object;
	char* name;
	int name_len;
	GIBaseInfo *info = NULL;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	info = g_union_info_find_method(baseinfo_object->info, name);

	if (NULL == info) {
		RETURN_NULL();
	}

	object_init_ex(return_value, ce_gintrospection_functioninfo);
	baseinfo_object = (gintrospection_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_base_info_ref(info);
}
/* }}} */

/* {{{ proto string G\Introspection\UnionInfo->getSize()
                  again, because of possible overflows, we're shoving
                  a gsize into a string */
PHP_METHOD(UnionInfo, getSize)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gchar *value;
	gsize item;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	item = g_union_info_get_size(baseinfo_object->info);

	value = g_strdup_printf("%"G_GSIZE_FORMAT, item);
	RETVAL_STRING(value);
	g_free(value);
}
/* }}} */

/* {{{ proto string G\Introspection\UnionInfo->getAlignment()
                  again, because of possible overflows, we're shoving
                  a gsize into a string */
PHP_METHOD(UnionInfo, getAlignment)
{

	gintrospection_baseinfo_object *baseinfo_object;
	gchar *value;
	gsize item;

	PHP_GINTROSPECTION_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GINTROSPECTION_RESTORE_ERRORS

	baseinfo_object = (gintrospection_baseinfo_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	item = g_union_info_get_alignment(baseinfo_object->info);

	value = g_strdup_printf("%"G_GSIZE_FORMAT, item);
	RETVAL_STRING(value);
	g_free(value);
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\BaseInfo Object management
------------------------------------------------------------------*/

/* {{{ gintrospection_baseinfo_object_free */
static void gintrospection_baseinfo_object_free(void *object TSRMLS_DC)
{
	gintrospection_baseinfo_object *baseinfo_object = (gintrospection_baseinfo_object *)object;

	zend_object_std_dtor(&baseinfo_object->std TSRMLS_CC);
	baseinfo_object->is_constructed = FALSE;
	if (NULL != baseinfo_object->info) {
		g_base_info_unref(baseinfo_object->info);
		baseinfo_object->info = NULL;
	}

	efree(baseinfo_object);
}
/* }}} */

/* {{{ gintrospection_baseinfo_object_create */
static zend_object* gintrospection_baseinfo_object_create(zend_class_entry *ce TSRMLS_DC)
{
	gintrospection_baseinfo_object *baseinfo_object;

	baseinfo_object = ecalloc(1, sizeof(gintrospection_baseinfo_object)+
                                 sizeof(zend_object_properties_size(ce)));
	zend_object_std_init((zend_object *) baseinfo_object, ce TSRMLS_CC);
	baseinfo_object->is_constructed = FALSE;
	baseinfo_object->info = NULL;

	object_properties_init(&baseinfo_object->std, ce);


    baseinfo_object->std.handlers = &std_object_handlers;
    return &baseinfo_object->std;
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\BaseInfo Definition and registration
------------------------------------------------------------------*/

/* {{{ baseinfo methods */
static const zend_function_entry gi_baseinfo_methods[] = {
	PHP_ME(BaseInfo, __construct, NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
	PHP_ME(BaseInfo, getType, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, getTypeName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, getNameSpace, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, isDeprecated, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, getAttribute, BaseInfo_getAttribute_args, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, getAttributes, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, getContainer, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, getTypelib, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(BaseInfo, equal, BaseInfo_equal_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ class methods */
static const zend_function_entry gi_vfuncinfo_methods[] = {
	//PHP_ME(BaseInfo, getTypeName, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(BaseInfo, getName, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(VFuncInfo, getNameSpace, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(VFuncInfo, getOffset, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(VFuncInfo, getSignal, NULL, ZEND_ACC_PUBLIC)
	//PHP_ME(VFuncInfo, getInvoker, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ class methods */
static const zend_function_entry gi_regtypeinfo_methods[] = {
	PHP_ME(RegisteredTypeInfo, getGTypeName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(RegisteredTypeInfo, getTypeInit, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ class methods */
static const zend_function_entry gi_enuminfo_methods[] = {
	PHP_ME(EnumInfo, getNumValues, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(EnumInfo, getValue, EnumInfo_getValue_args, ZEND_ACC_PUBLIC)
	PHP_ME(EnumInfo, getValues, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(EnumInfo, getNumMethods, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(EnumInfo, getMethod, EnumInfo_getMethod_args, ZEND_ACC_PUBLIC)
	PHP_ME(EnumInfo, getMethods, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(EnumInfo, getStorageType, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ class methods */
static const zend_function_entry gi_valueinfo_methods[] = {
	PHP_ME(ValueInfo, getValue, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ class methods */
static const zend_function_entry gi_structinfo_methods[] = {
	PHP_ME(StructInfo, getNumFields, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, getField, StructInfo_getField_args, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, getFields, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, getNumMethods, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, getMethod, StructInfo_getMethod_args, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, getMethods, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, findMethod, StructInfo_findMethod_args, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, getSize, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, getAlignment, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, isGTypeStruct, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(StructInfo, isForeign, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ class methods */
static const zend_function_entry gi_unioninfo_methods[] = {
	PHP_ME(UnionInfo, getNumFields, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getField, UnionInfo_getField_args, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getFields, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getNumMethods, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getMethod, UnionInfo_getMethod_args, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getMethods, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, isDiscriminated, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getDiscriminatorOffset, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getDiscriminatorType, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getDiscriminator, UnionInfo_getDiscriminator_args, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, findMethod, UnionInfo_findMethod_args, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getSize, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(UnionInfo, getAlignment, NULL, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(gintrospection_Info)
{
	zend_class_entry base_ce, callable_ce, function_ce, signal_ce, vfunc_ce, regtype_ce, enum_ce;
	zend_class_entry value_ce, property_ce, field_ce;
	zend_class_entry union_ce, struct_ce, object_ce, interface_ce, arginfo_ce, constant_ce, type_ce;

	INIT_NS_CLASS_ENTRY(base_ce, GINTROSPECTION_NAMESPACE, "BaseInfo", gi_baseinfo_methods);
	ce_gintrospection_baseinfo = zend_register_internal_class(&base_ce TSRMLS_CC);
	ce_gintrospection_baseinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(callable_ce, GINTROSPECTION_NAMESPACE, "CallableInfo", NULL);
	ce_gintrospection_callableinfo = zend_register_internal_class_ex(&callable_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_callableinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(function_ce, GINTROSPECTION_NAMESPACE, "FunctionInfo", NULL);
	ce_gintrospection_functioninfo = zend_register_internal_class_ex(&function_ce, ce_gintrospection_callableinfo);
	ce_gintrospection_functioninfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(signal_ce, GINTROSPECTION_NAMESPACE, "SignalInfo", NULL);
	ce_gintrospection_signalinfo = zend_register_internal_class_ex(&signal_ce, ce_gintrospection_callableinfo);
	ce_gintrospection_signalinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(vfunc_ce, GINTROSPECTION_NAMESPACE, "VFuncInfo", NULL);
	ce_gintrospection_vfuncinfo = zend_register_internal_class_ex(&vfunc_ce, ce_gintrospection_callableinfo);
	ce_gintrospection_vfuncinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(regtype_ce, GINTROSPECTION_NAMESPACE, "RegisteredTypeInfo", gi_regtypeinfo_methods);
	ce_gintrospection_regtypeinfo = zend_register_internal_class_ex(&regtype_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_regtypeinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(enum_ce, GINTROSPECTION_NAMESPACE, "EnumInfo", gi_enuminfo_methods);
	ce_gintrospection_enuminfo = zend_register_internal_class_ex(&enum_ce, ce_gintrospection_regtypeinfo);
	ce_gintrospection_enuminfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(union_ce, GINTROSPECTION_NAMESPACE, "UnionInfo", gi_unioninfo_methods);
	ce_gintrospection_unioninfo = zend_register_internal_class_ex(&union_ce, ce_gintrospection_regtypeinfo);
	ce_gintrospection_unioninfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(struct_ce, GINTROSPECTION_NAMESPACE, "StructInfo", gi_structinfo_methods);
	ce_gintrospection_structinfo = zend_register_internal_class_ex(&struct_ce, ce_gintrospection_regtypeinfo);
	ce_gintrospection_structinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(object_ce, GINTROSPECTION_NAMESPACE, "ObjectInfo", NULL);
	ce_gintrospection_objectinfo = zend_register_internal_class_ex(&object_ce, ce_gintrospection_regtypeinfo);
	ce_gintrospection_objectinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(interface_ce, GINTROSPECTION_NAMESPACE, "InterfaceInfo", NULL);
	ce_gintrospection_interfaceinfo = zend_register_internal_class_ex(&interface_ce, ce_gintrospection_regtypeinfo);
	ce_gintrospection_interfaceinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(arginfo_ce, GINTROSPECTION_NAMESPACE, "ArgInfo", NULL);
	ce_gintrospection_arginfo = zend_register_internal_class_ex(&arginfo_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_arginfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(constant_ce, GINTROSPECTION_NAMESPACE, "ConstantInfo", NULL);
	ce_gintrospection_constantinfo = zend_register_internal_class_ex(&constant_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_constantinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(field_ce, GINTROSPECTION_NAMESPACE, "FieldInfo", NULL);
	ce_gintrospection_fieldinfo = zend_register_internal_class_ex(&field_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_fieldinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(property_ce, GINTROSPECTION_NAMESPACE, "PropertyInfo", NULL);
	ce_gintrospection_propertyinfo = zend_register_internal_class_ex(&property_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_propertyinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(type_ce, GINTROSPECTION_NAMESPACE, "TypeInfo", NULL);
	ce_gintrospection_typeinfo = zend_register_internal_class_ex(&type_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_typeinfo->create_object = gintrospection_baseinfo_object_create;

	INIT_NS_CLASS_ENTRY(value_ce, GINTROSPECTION_NAMESPACE, "ValueInfo", gi_valueinfo_methods);
	ce_gintrospection_valueinfo = zend_register_internal_class_ex(&value_ce, ce_gintrospection_baseinfo);
	ce_gintrospection_valueinfo->create_object = gintrospection_baseinfo_object_create;

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
