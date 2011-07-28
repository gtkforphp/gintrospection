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

/**
 * Helpers for sticking items into the Gir namespace
 */
char* gir_namespaced_name(const char *ns_name, const char *name, zend_bool persistent)
{
	char *phpname = pemalloc(4 + strlen(ns_name) + strlen(name) + 2, persistent);
	sprintf(phpname, "Gir\\%s\\%s", ns_name, name);

	return phpname;
}

/**
 * Helpers for sticking items into the Gir namespace
 */
char* gir_enum_constant_name(const char *ns_name, const char *constant, const char *name, zend_bool persistent)
{
	char *phpname = pemalloc(4 + strlen(ns_name) + strlen(constant) + strlen(name) + 2, persistent);
	sprintf(phpname, "Gir\\%s\\%s\\%s", ns_name, name, constant);

	return phpname;
}

/**
 * Helpers for dealing with GIArgument structs
 */
int gir_types_giargument_to_zval(GITypeInfo *type_info, GIArgument *src, zval *value TSRMLS_DC)
{
	char * buffer;
	int len;
	GITypeTag type_tag = g_type_info_get_tag(type_info);

	switch (type_tag) {
		/* Basic types */
		case GI_TYPE_TAG_VOID:
			ZVAL_NULL(value);
		break;
		case GI_TYPE_TAG_BOOLEAN:
			ZVAL_BOOL(value, src->v_boolean);
		break;
		case GI_TYPE_TAG_INT8:
			ZVAL_LONG(value, src->v_int8);
		break;
		case GI_TYPE_TAG_UINT8:
			ZVAL_LONG(value, src->v_uint8);
		break;
		case GI_TYPE_TAG_INT16:
			ZVAL_LONG(value, src->v_int16);
		break;
		case GI_TYPE_TAG_UINT16:
			ZVAL_LONG(value, src->v_uint16);
		break;

		/* TODO: check limits for these and do them as strings if they overflow */
		case GI_TYPE_TAG_INT32:
			ZVAL_LONG(value, src->v_int32);
		break;
		case GI_TYPE_TAG_UINT32:
			ZVAL_LONG(value, src->v_uint32);
		break;
		case GI_TYPE_TAG_INT64:
			ZVAL_LONG(value, src->v_int64);
		break;
		case GI_TYPE_TAG_UINT64:
			ZVAL_LONG(value, src->v_uint64);
		break;

		/* TODO: limits for floats as well */
		case GI_TYPE_TAG_FLOAT:
			ZVAL_DOUBLE(value, src->v_float);
		break;
		case GI_TYPE_TAG_DOUBLE:
			ZVAL_DOUBLE(value, src->v_double);
		break;

		/* String Types - Still basic types */
		case GI_TYPE_TAG_UTF8:
			ZVAL_STRING(value, src->v_pointer, 1);
		break;
		case GI_TYPE_TAG_UNICHAR:
			buffer = ecalloc(6, sizeof(char));
			len = g_unichar_to_utf8(src->v_uint32, buffer);

			ZVAL_STRINGL(value, buffer, len, 0);
		break;

		/* Bail */
		default:
			ZVAL_NULL(value);
			return FAILURE;
	}
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
