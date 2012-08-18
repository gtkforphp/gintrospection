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
#include <php_g_public.h>

zend_class_entry *ce_gi_repositoryerror;
zend_class_entry *ce_gi_repositoryloadflags;
zend_class_entry *ce_gi_infotype;

zend_class_entry *ce_gi_vfuncinfoflags;

/* ----------------------------------------------------------------
    All G\Introspection enums Definition and registration
------------------------------------------------------------------*/

PHP_MINIT_FUNCTION(gi_Enums)
{
	zend_class_entry error_ce, lazy_ce, info_ce;
	zend_class_entry flags_ce;

	INIT_NS_CLASS_ENTRY(error_ce, ZEND_NS_NAME(GI_NAMESPACE, "Repository"), "Error", NULL);
	ce_gi_repositoryerror = zend_register_internal_class_ex(&error_ce, ce_g_enum, NULL TSRMLS_CC);

	REGISTER_ENUM_CONST("TYPELIB_NOT_FOUND", G_IREPOSITORY_ERROR_TYPELIB_NOT_FOUND, ce_gi_repositoryerror);
	REGISTER_ENUM_CONST("NAMESPACE_MISMATCH", G_IREPOSITORY_ERROR_NAMESPACE_MISMATCH, ce_gi_repositoryerror);
	REGISTER_ENUM_CONST("NAMESPACE_VERSION_CONFLICT", G_IREPOSITORY_ERROR_NAMESPACE_VERSION_CONFLICT, ce_gi_repositoryerror);
	REGISTER_ENUM_CONST("LIBRARY_NOT_FOUND", G_IREPOSITORY_ERROR_LIBRARY_NOT_FOUND, ce_gi_repositoryerror);

	INIT_NS_CLASS_ENTRY(lazy_ce, ZEND_NS_NAME(GI_NAMESPACE, "Repository"), "LoadFlags", NULL);
	ce_gi_repositoryloadflags = zend_register_internal_class_ex(&lazy_ce, ce_g_enum, NULL TSRMLS_CC);

	REGISTER_ENUM_CONST("LAZY", G_IREPOSITORY_LOAD_FLAG_LAZY, ce_gi_repositoryloadflags);

	INIT_NS_CLASS_ENTRY(info_ce, GI_NAMESPACE, "InfoType", NULL);
	ce_gi_infotype = zend_register_internal_class_ex(&info_ce, ce_g_enum, NULL TSRMLS_CC);

	REGISTER_ENUM_CONST("INVALID", GI_INFO_TYPE_INVALID, ce_gi_infotype);
	REGISTER_ENUM_CONST("FUNCTION", GI_INFO_TYPE_FUNCTION, ce_gi_infotype);
	REGISTER_ENUM_CONST("CALLBACK", GI_INFO_TYPE_CALLBACK, ce_gi_infotype);
	REGISTER_ENUM_CONST("STRUCT", GI_INFO_TYPE_STRUCT, ce_gi_infotype);
	REGISTER_ENUM_CONST("BOXED", GI_INFO_TYPE_BOXED, ce_gi_infotype);
	REGISTER_ENUM_CONST("ENUM", GI_INFO_TYPE_ENUM, ce_gi_infotype);
	REGISTER_ENUM_CONST("FLAGS", GI_INFO_TYPE_FLAGS, ce_gi_infotype);
	REGISTER_ENUM_CONST("OBJECT", GI_INFO_TYPE_OBJECT, ce_gi_infotype);
	REGISTER_ENUM_CONST("INTERFACE", GI_INFO_TYPE_INTERFACE, ce_gi_infotype);
	REGISTER_ENUM_CONST("UNION", GI_INFO_TYPE_UNION, ce_gi_infotype);
	REGISTER_ENUM_CONST("VALUE", GI_INFO_TYPE_VALUE, ce_gi_infotype);
	REGISTER_ENUM_CONST("SIGNAL", GI_INFO_TYPE_SIGNAL, ce_gi_infotype);
	REGISTER_ENUM_CONST("VFUNC", GI_INFO_TYPE_VFUNC, ce_gi_infotype);
	REGISTER_ENUM_CONST("CONSTANT", GI_INFO_TYPE_CONSTANT, ce_gi_infotype);
	REGISTER_ENUM_CONST("PROPERTY", GI_INFO_TYPE_PROPERTY, ce_gi_infotype);
	REGISTER_ENUM_CONST("FIELD", GI_INFO_TYPE_FIELD, ce_gi_infotype);
	REGISTER_ENUM_CONST("ARG", GI_INFO_TYPE_ARG, ce_gi_infotype);
	REGISTER_ENUM_CONST("TYPE", GI_INFO_TYPE_TYPE, ce_gi_infotype);
	REGISTER_ENUM_CONST("UNRESOLVED", GI_INFO_TYPE_UNRESOLVED, ce_gi_infotype);

	INIT_NS_CLASS_ENTRY(flags_ce, ZEND_NS_NAME(GI_NAMESPACE, "VFuncInfo"), "Flags", NULL);
	ce_gi_vfuncinfoflags = zend_register_internal_class_ex(&flags_ce, ce_g_enum, NULL TSRMLS_CC);

	REGISTER_ENUM_CONST("MUST_CHAIN_UP", GI_VFUNC_MUST_CHAIN_UP, ce_gi_vfuncinfoflags);
	REGISTER_ENUM_CONST("MUST_OVERRIDE", GI_VFUNC_MUST_OVERRIDE, ce_gi_vfuncinfoflags);
	REGISTER_ENUM_CONST("MUST_NOT_OVERRIDE", GI_VFUNC_MUST_NOT_OVERRIDE, ce_gi_vfuncinfoflags);
	REGISTER_ENUM_CONST("THROWS", GI_VFUNC_THROWS, ce_gi_vfuncinfoflags);

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
