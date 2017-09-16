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
#include <php_glib_public.h>

zend_class_entry *ce_gintrospection_repositoryerror;
zend_class_entry *ce_gintrospection_repositoryloadflags;
zend_class_entry *ce_gintrospection_infotype;
zend_class_entry *ce_gintrospection_typetag;

zend_class_entry *ce_gintrospection_vfuncinfoflags;

/* ----------------------------------------------------------------
    All G\Introspection enums Definition and registration
------------------------------------------------------------------*/

PHP_MINIT_FUNCTION(gintrospection_Enums)
{
	zend_class_entry error_ce, lazy_ce, info_ce, tags_ce;
	zend_class_entry flags_ce;

	INIT_NS_CLASS_ENTRY(error_ce, ZEND_NS_NAME(GINTROSPECTION_NAMESPACE, "Repository"), "Error", NULL);
	ce_gintrospection_repositoryerror = zend_register_internal_class_ex(&error_ce, ce_glib_enum);

	REGISTER_ENUM_CONST("TYPELIB_NOT_FOUND", G_IREPOSITORY_ERROR_TYPELIB_NOT_FOUND, ce_gintrospection_repositoryerror);
	REGISTER_ENUM_CONST("NAMESPACE_MISMATCH", G_IREPOSITORY_ERROR_NAMESPACE_MISMATCH, ce_gintrospection_repositoryerror);
	REGISTER_ENUM_CONST("NAMESPACE_VERSION_CONFLICT", G_IREPOSITORY_ERROR_NAMESPACE_VERSION_CONFLICT, ce_gintrospection_repositoryerror);
	REGISTER_ENUM_CONST("LIBRARY_NOT_FOUND", G_IREPOSITORY_ERROR_LIBRARY_NOT_FOUND, ce_gintrospection_repositoryerror);

	INIT_NS_CLASS_ENTRY(lazy_ce, ZEND_NS_NAME(GINTROSPECTION_NAMESPACE, "Repository"), "LoadFlags", NULL);
	ce_gintrospection_repositoryloadflags = zend_register_internal_class_ex(&lazy_ce, ce_glib_enum);

	REGISTER_ENUM_CONST("LAZY", G_IREPOSITORY_LOAD_FLAG_LAZY, ce_gintrospection_repositoryloadflags);

	INIT_NS_CLASS_ENTRY(info_ce, GINTROSPECTION_NAMESPACE, "InfoType", NULL);
	ce_gintrospection_infotype = zend_register_internal_class_ex(&info_ce, ce_glib_enum);

	REGISTER_ENUM_CONST("INVALID", GI_INFO_TYPE_INVALID, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("FUNCTION", GI_INFO_TYPE_FUNCTION, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("CALLBACK", GI_INFO_TYPE_CALLBACK, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("STRUCT", GI_INFO_TYPE_STRUCT, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("BOXED", GI_INFO_TYPE_BOXED, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("ENUM", GI_INFO_TYPE_ENUM, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("FLAGS", GI_INFO_TYPE_FLAGS, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("OBJECT", GI_INFO_TYPE_OBJECT, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("INTERFACE", GI_INFO_TYPE_INTERFACE, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("UNION", GI_INFO_TYPE_UNION, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("VALUE", GI_INFO_TYPE_VALUE, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("SIGNAL", GI_INFO_TYPE_SIGNAL, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("VFUNC", GI_INFO_TYPE_VFUNC, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("CONSTANT", GI_INFO_TYPE_CONSTANT, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("PROPERTY", GI_INFO_TYPE_PROPERTY, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("FIELD", GI_INFO_TYPE_FIELD, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("ARG", GI_INFO_TYPE_ARG, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("TYPE", GI_INFO_TYPE_TYPE, ce_gintrospection_infotype);
	REGISTER_ENUM_CONST("UNRESOLVED", GI_INFO_TYPE_UNRESOLVED, ce_gintrospection_infotype);

	INIT_NS_CLASS_ENTRY(flags_ce, ZEND_NS_NAME(GINTROSPECTION_NAMESPACE, "VFuncInfo"), "Flags", NULL);
	ce_gintrospection_vfuncinfoflags = zend_register_internal_class_ex(&flags_ce, ce_glib_enum);

	REGISTER_ENUM_CONST("MUST_CHAIN_UP", GI_VFUNC_MUST_CHAIN_UP, ce_gintrospection_vfuncinfoflags);
	REGISTER_ENUM_CONST("MUST_OVERRIDE", GI_VFUNC_MUST_OVERRIDE, ce_gintrospection_vfuncinfoflags);
	REGISTER_ENUM_CONST("MUST_NOT_OVERRIDE", GI_VFUNC_MUST_NOT_OVERRIDE, ce_gintrospection_vfuncinfoflags);
	REGISTER_ENUM_CONST("THROWS", GI_VFUNC_THROWS, ce_gintrospection_vfuncinfoflags);

	INIT_NS_CLASS_ENTRY(tags_ce, ZEND_NS_NAME(GINTROSPECTION_NAMESPACE, "TypeInfo"), "Tag", NULL);
	ce_gintrospection_typetag = zend_register_internal_class_ex(&tags_ce, ce_glib_enum);

	REGISTER_ENUM_CONST("VOID", GI_TYPE_TAG_VOID, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("BOOLEAN", GI_TYPE_TAG_BOOLEAN, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("INT8", GI_TYPE_TAG_INT8, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("UINT8", GI_TYPE_TAG_UINT8, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("INT16", GI_TYPE_TAG_INT16, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("UINT16", GI_TYPE_TAG_UINT16, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("INT32", GI_TYPE_TAG_INT32, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("UINT32", GI_TYPE_TAG_UINT32, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("INT64", GI_TYPE_TAG_INT64, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("UINT64", GI_TYPE_TAG_UINT64, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("FLOAT", GI_TYPE_TAG_FLOAT, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("DOUBLE", GI_TYPE_TAG_DOUBLE, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("GTYPE", GI_TYPE_TAG_GTYPE, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("UTF8", GI_TYPE_TAG_UTF8, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("FILENAME", GI_TYPE_TAG_FILENAME, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("ARRAY", GI_TYPE_TAG_ARRAY, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("INTERFACE", GI_TYPE_TAG_INTERFACE, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("GLIST", GI_TYPE_TAG_GLIST, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("GSLIST", GI_TYPE_TAG_GSLIST, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("GHASH", GI_TYPE_TAG_GHASH, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("ERROR", GI_TYPE_TAG_ERROR, ce_gintrospection_typetag);
	REGISTER_ENUM_CONST("UNICHAR", GI_TYPE_TAG_UNICHAR, ce_gintrospection_typetag);

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
