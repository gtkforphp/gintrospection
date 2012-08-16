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

zend_class_entry *ce_gi_repository;
static zend_object_handlers gi_repository_object_handlers;

/* repository info */
struct _gi_repository_object {
	zend_object std;
	zend_bool is_constructed;
	GIRepository* repo;
};

/* ----------------------------------------------------------------
    G\Introspection\Repository class API
------------------------------------------------------------------*/

ZEND_BEGIN_ARG_INFO(Repository___construct_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getDefault_args, ZEND_SEND_BY_VAL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Repository_isRegistered_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, namespace)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getCPrefix_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_require_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

/* {{{ proto Repository object Repository::getDefault()
 Singleton constructor for process specific default repository */
PHP_METHOD(Repository, getDefault)
{
	gi_repository_object *repository_object;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	object_init_ex(return_value, ce_gi_repository);
	repository_object = (gi_repository_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	repository_object->repo = g_irepository_get_default();
	repository_object->is_constructed = TRUE;
}
/* }}} */

/* {{{ proto void Repository__construct()
Private constructor placeholder (does nothing) */
PHP_METHOD(Repository, __construct)
{
	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GI_RESTORE_ERRORS
}
/* }}} */

PHP_METHOD(Repository, prependSearchPath)
{
	char *path;
	int  path_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len)
			== FAILURE)
	{
		return;
	}

	g_irepository_prepend_search_path(path);
}

PHP_METHOD(Repository, getSearchPath)
{
	gpointer data;
	GSList   *list;
	guint    len, i;

	if (zend_parse_parameters_none() == FAILURE)
		return;

	list = g_irepository_get_search_path();
	len  = g_slist_length(list);

	array_init(return_value);
	for (i = 0; i < len; i++)
	{
		data = g_slist_nth_data(list, i);

		add_next_index_string(return_value, (char *) data, 1);
	}
}

/* {{{ proto void G\Introspection\Repository->isRegistered(string $namespace[, string $version])
                  Allows you to check if a namespace has been registered, and optionally a specific
                  version of a namespace as well */
PHP_METHOD(Repository, isRegistered)
{

	gi_repository_object *repository_object;
	gchar *name, *version = NULL;
	int name_len, version_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len,
				&version, &version_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	RETURN_BOOL(g_irepository_is_registered(repository_object->repo, name, version));
}
/* }}} */

/* {{{ proto void G\Introspection\Repository->getCPrefix(string $namespace)
                  Gets the C namespace of a loaded repository */
PHP_METHOD(Repository, getCPrefix)
{

	gi_repository_object *repository_object;
	gchar *name;
	int name_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	/* This will bomb and segfault!! if we don't check to make sure the typelib is loaded */
	if (0 == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	RETURN_STRING(g_irepository_get_c_prefix(repository_object->repo, name), 1);
}
/* }}} */

/* {{{ proto void G\Introspection\Repository->require(string $namespace, string $version)
                  Tries to load a namespace typelib, returns the typelib object or false */
PHP_METHOD(Repository, require)
{

	gi_repository_object *repository_object;
	gchar *name, *version = NULL;
	int name_len, version_len;
	GITypelib *typelib;
	GError *error = NULL;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &name, &name_len,
				&version, &version_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	typelib = g_irepository_require(repository_object->repo, name, version,
									  G_IREPOSITORY_LOAD_FLAG_LAZY, &error);

	if(typelib) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\Repository Object management
------------------------------------------------------------------*/

/* {{{ gi_baseinfo_object_free */
static void gi_repository_object_free(void *object TSRMLS_DC)
{
	gi_repository_object *repository_object = (gi_repository_object *)object;

	zend_object_std_dtor(&repository_object->std TSRMLS_CC);
	repository_object->repo = NULL;
	repository_object->is_constructed = FALSE;

	efree(repository_object);
}
/* }}} */

/* {{{ gi_repository_object_create */
static zend_object_value gi_repository_object_create(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;
	gi_repository_object *repository_object;

	repository_object = ecalloc(1, sizeof(gi_repository_object));
	zend_object_std_init((zend_object *) repository_object, ce TSRMLS_CC);
	repository_object->is_constructed = FALSE;
	repository_object->repo = NULL;

	object_properties_init(&repository_object->std, ce);

	retval.handle = zend_objects_store_put(repository_object,
		(zend_objects_store_dtor_t) zend_objects_destroy_object,
		(zend_objects_free_object_storage_t) gi_repository_object_free,
		NULL TSRMLS_CC);
	retval.handlers = &gi_repository_object_handlers;
	return retval;
}

/* ----------------------------------------------------------------
    G\Introspection\Repository Definition and registration
------------------------------------------------------------------*/

static const zend_function_entry gi_repository_methods[] = {
	PHP_ME(Repository, __construct, Repository___construct_args, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
	PHP_ME(Repository, getDefault, Repository_getDefault_args, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(Repository, prependSearchPath, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(Repository, getSearchPath,   NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(Repository, isRegistered, Repository_isRegistered_args, ZEND_ACC_PUBLIC )
	PHP_ME(Repository, getCPrefix, Repository_getCPrefix_args, ZEND_ACC_PUBLIC )
	PHP_ME(Repository, require, NULL, ZEND_ACC_PUBLIC )
	ZEND_FE_END
};

PHP_MINIT_FUNCTION(Repository)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, ZEND_NS_NAME(GI_NAMESPACE, "Repository"), gi_repository_methods);
	ce_gi_repository = zend_register_internal_class(&ce TSRMLS_CC);

	ce_gi_repository->create_object = gi_repository_object_create;
	memcpy(&gi_repository_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));

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
