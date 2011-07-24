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

/* Repository API */

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
	PHP_ME(Repository, import, 0, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(repository)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(GIR_NAMESPACE, "Repository"), ext_class_methods);
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
