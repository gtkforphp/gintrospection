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

ZEND_BEGIN_ARG_INFO_EX(Repository_prependSearchPath_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Repository_isRegistered_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, namespace)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_findByName_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Repository_require_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, namespace)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Repository_requirePrivate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, namespace)
	ZEND_ARG_INFO(0, version)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getDependencies_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getNumInfos_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getInfo_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
	ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getAllInfos_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getTypelibPath_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getSharedLibrary_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getVersion_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_getCPrefix_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_dump_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, files)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(Repository_enumerateVersions_args, ZEND_SEND_BY_VAL)
	ZEND_ARG_INFO(0, namespace)
ZEND_END_ARG_INFO()

/* {{{ proto void Repository->__construct()
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

/* {{{ proto object Repository::getDefault()
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


/* {{{ proto void Repository::prependSearchPath()
                  adds a search path for all repositories to fine .typelibs */
PHP_METHOD(Repository, prependSearchPath)
{
	char *path;
	int  path_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	g_irepository_prepend_search_path(path);
}
/* }}} */

/* {{{ proto array Repository::getSearchPath()
                  adds a search path for all repositories to fine .typelibs */
PHP_METHOD(Repository, getSearchPath)
{
	gpointer data;
	GSList   *list;
	guint    len, i;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	list = g_irepository_get_search_path();
	len  = g_slist_length(list);

	array_init(return_value);
	for (i = 0; i < len; i++)
	{
		data = g_slist_nth_data(list, i);

		add_next_index_string(return_value, (char *) data, 1);
	}
}
/* }}} */

/* {{{ proto bool G\Introspection\Repository->isRegistered(string $namespace[, string $version])
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

/* {{{ proto bool G\Introspection\Repository->findByName(string $namespace, string $name)
                 Searches for a particular entry in a namespace and returns a baseinfo object */
PHP_METHOD(Repository, findByName)
{

	gi_repository_object *repository_object;
	gi_baseinfo_object *baseinfo_object;
	gchar *name, *find;
	int name_len, find_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &name, &name_len,
				&find, &find_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	/* This will bomb and segfault!! if we don't check to make sure the typelib is loaded */
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	object_init_ex(return_value, ce_gi_baseinfo);
	baseinfo_object = (gi_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_irepository_find_by_name(repository_object->repo, name, find);

	if (NULL == baseinfo_object->info) {
		RETURN_NULL();
	}
}
/* }}} */

/* {{{ proto object G\Introspection\Repository->require(string $namespace[, string $version])
                  Tries to load a namespace typelib, returns the typelib object or false */
PHP_METHOD(Repository, require)
{

	gi_repository_object *repository_object;
	gi_typelib_object *typelib_object;
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

	object_init_ex(return_value, ce_gi_typelib);

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	typelib_object = (gi_typelib_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	typelib_object->is_constructed = TRUE;

	typelib_object->typelib = g_irepository_require(repository_object->repo, name, version,
									G_IREPOSITORY_LOAD_FLAG_LAZY, &error);

	if (php_g_handle_gerror(&error TSRMLS_CC)) {
		RETURN_FALSE;
	}

	if(!typelib_object->typelib) {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto object G\Introspection\Repository->requirePrivate(string $path, string $namespace[, string $version])
                  Tries to load a namespace typelib, returns the typelib object or false
                  will look in private path for typelib */
PHP_METHOD(Repository, requirePrivate)
{

	gi_repository_object *repository_object;
	gi_typelib_object *typelib_object;
	gchar *name, *path, *version = NULL;
	int name_len, path_len, version_len;
	GITypelib *typelib;
	GError *error = NULL;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|s", &path, &path_len,
				&name, &name_len, &version, &version_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	object_init_ex(return_value, ce_gi_typelib);

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);
	typelib_object = (gi_typelib_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	typelib_object->is_constructed = TRUE;

	typelib_object->typelib = g_irepository_require_private(repository_object->repo, path, name, version,
									G_IREPOSITORY_LOAD_FLAG_LAZY, &error);

	if (php_g_handle_gerror(&error TSRMLS_CC)) {
		RETURN_FALSE;
	}

	if(!typelib_object->typelib) {
		RETURN_FALSE;
	}
}
/* }}} */

/* {{{ proto array G\Introspection\Repository->getDependencies(string $namespace)
                  get all namespace-version deps for a namespace */
PHP_METHOD(Repository, getDependencies)
{

	gi_repository_object *repository_object;
	gchar **dependencies;
	gssize i;
	gchar *name;
	int name_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	/* This will bomb and segfault!! if we don't check to make sure the typelib is loaded */
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	dependencies = g_irepository_get_dependencies(repository_object->repo, name);

	array_init(return_value);

	if (NULL != dependencies) {
		for (i = 0; dependencies[i] != NULL; i++) {
			add_next_index_string(return_value, dependencies[i], 1);
			g_free(dependencies[i]);
		}
	
		g_free(dependencies);
	}
}
/* }}} */

/* {{{ proto array G\Introspection\Repository->getLoadedNamespaces()
                  get the loaded namespaces in the repo */
PHP_METHOD(Repository, getLoadedNamespaces)
{

	gi_repository_object *repository_object;
	gchar **namespaces;
	gssize i;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters_none()) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	namespaces = g_irepository_get_loaded_namespaces(repository_object->repo);

	array_init(return_value);
	for (i = 0; namespaces[i] != NULL; i++) {
		add_next_index_string(return_value, namespaces[i], 1);
		g_free(namespaces[i]);
	}

	g_free(namespaces);
}
/* }}} */

/* {{{ proto int G\Introspection\Repository->getNumInfos(string $namespace)
                  Gets the total number of infos in the namespace */
PHP_METHOD(Repository, getNumInfos)
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
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	RETURN_LONG(g_irepository_get_n_infos(repository_object->repo, name));
}
/* }}} */

/* {{{ proto object G\Introspection\Repository->getInfo(string $namespace, int $index)
                 Returns an info object at $index in the repository - index is 0 based
                 so it is number of infos -1 for a range*/
PHP_METHOD(Repository, getInfo)
{

	gi_repository_object *repository_object;
	gi_baseinfo_object *baseinfo_object;
	long index;
	gchar *name;
	gint total;
	int name_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &name, &name_len,
				&index)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	/* This will bomb and segfault!! if we don't check to make sure the typelib is loaded */
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	total = g_irepository_get_n_infos(repository_object->repo, name);

	/* our index must be between 0 and maximum number infos */
	if (index < 0 || index > total) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Index must be between 0 and %d", total);
		return;
	}

	object_init_ex(return_value, ce_gi_baseinfo);
	baseinfo_object = (gi_baseinfo_object *)zend_object_store_get_object(return_value TSRMLS_CC);
	baseinfo_object->is_constructed = TRUE;
	baseinfo_object->info = g_irepository_get_info(repository_object->repo, name, (gint) index);

	if (NULL == baseinfo_object->info) {
		RETURN_NULL();
	}
}
/* }}} */

/* {{{ proto array G\Introspection\Repository->getAllInfos(string $namespace)
                 Returns an array of all info objects for the namespace
                 WARNING: this might be LARGE */
PHP_METHOD(Repository, getAllInfos)
{

	gi_repository_object *repository_object;
	gint total, i;
	gchar *name;
	int name_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	/* This will bomb and segfault!! if we don't check to make sure the typelib is loaded */
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	total = g_irepository_get_n_infos(repository_object->repo, name);

	array_init(return_value);

	for (i = 0; i < total; i++) {
		gi_baseinfo_object *baseinfo_object;
		zval *info;

		MAKE_STD_ZVAL(info);
		object_init_ex(info, ce_gi_baseinfo);
		baseinfo_object = (gi_baseinfo_object *)zend_object_store_get_object(info TSRMLS_CC);
		baseinfo_object->is_constructed = TRUE;
		baseinfo_object->info = g_irepository_get_info(repository_object->repo, name, i);

		/* baseinfo was not loaded right, destruct and continue */
		if (NULL == baseinfo_object->info) {
			// destroy here
		} else {
			 add_next_index_zval(return_value, info);
		}
	}
}
/* }}} */

/* {{{ proto string G\Introspection\Repository->getTypelibPath(string $namespace)
                  Gets the typelib path of a loaded repository */
PHP_METHOD(Repository, getTypelibPath)
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
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	RETURN_STRING(g_irepository_get_typelib_path(repository_object->repo, name), 1);
}
/* }}} */

/* {{{ proto string G\Introspection\Repository->getSharedLibrary(string $namespace)
                  path to the shared C library associated with the given namespace
                  may be comma separated */
PHP_METHOD(Repository, getSharedLibrary)
{

	gi_repository_object *repository_object;
	gchar *name;
	const gchar *path = NULL;
	int name_len;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	/* This will bomb and segfault!! if we don't check to make sure the typelib is loaded */
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	path = g_irepository_get_shared_library(repository_object->repo, name);

	if(NULL == path) {
		RETURN_NULL();
	} else {
		RETURN_STRING(path, 1);
	}
}
/* }}} */

/* {{{ proto string G\Introspection\Repository->getVersion(string $namespace)
                  Gets the version of a loaded repository */
PHP_METHOD(Repository, getVersion)
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
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	RETURN_STRING(g_irepository_get_version(repository_object->repo, name), 1);
}
/* }}} */

/* {{{ proto string G\Introspection\Repository->getCPrefix(string $namespace)
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
	if (FALSE == g_irepository_is_registered(repository_object->repo, name, NULL)) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC,
								"Namespace %s is not currently loaded", name);
		return;
	}

	RETURN_STRING(g_irepository_get_c_prefix(repository_object->repo, name), 1);
}
/* }}} */

/* {{{ proto void G\Introspection\Repository::dump(string $files)
                   Argument specified is a comma-separated pair of filenames;
                   i.e. of the form "input.txt,output.xml".
                   The input file should be a UTF-8 Unix-line-ending text file,
                   with each line containing the name of a GType _get_type function.
                   The output file should already exist, but be empty. This function
                   will overwrite its contents. */
PHP_METHOD(Repository, dump)
{

	gchar *files;
	int files_len;
	gboolean worked = FALSE;
	GError *error = NULL;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &files, &files_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	worked = g_irepository_dump(files, &error);

	if (php_g_handle_gerror(&error TSRMLS_CC)) {
		RETURN_FALSE;
	}

	RETURN_BOOL(worked);
}
/* }}} */

/* {{{ proto array G\Introspection\Repository->enumerateVersions(string $namespace)
                  Options a list of loaded and available versions for a namespace */
PHP_METHOD(Repository, enumerateVersions)
{

	gi_repository_object *repository_object;
	gchar *name;
	int name_len;
	GList *versions, *item;

	PHP_GI_EXCEPTIONS
	if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
		return;
	}
	PHP_GI_RESTORE_ERRORS

	repository_object = (gi_repository_object *) zend_object_store_get_object(getThis() TSRMLS_CC);

	versions = g_irepository_enumerate_versions(repository_object->repo, name);

	array_init(return_value);

	for (item = versions; item; item = item->next) {
		add_next_index_string(return_value, item->data, 1);
	}

	g_list_free(versions);
}
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\Repository Object management
------------------------------------------------------------------*/

/* {{{ gi_repository_object_free */
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
/* }}} */

/* ----------------------------------------------------------------
    G\Introspection\Repository Definition and registration
------------------------------------------------------------------*/

/* {{{ class methods */
static const zend_function_entry gi_repository_methods[] = {
	PHP_ME(Repository, __construct, NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
	PHP_ME(Repository, getDefault, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(Repository, prependSearchPath, Repository_prependSearchPath_args, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(Repository, getSearchPath,   NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(Repository, isRegistered, Repository_isRegistered_args, ZEND_ACC_PUBLIC )
	PHP_ME(Repository, findByName, Repository_findByName_args, ZEND_ACC_PUBLIC )
	PHP_ME(Repository, require, Repository_require_args, ZEND_ACC_PUBLIC )
	PHP_ME(Repository, requirePrivate, Repository_requirePrivate_args, ZEND_ACC_PUBLIC )
	PHP_ME(Repository, getDependencies, Repository_getDependencies_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getLoadedNamespaces, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getNumInfos, Repository_getNumInfos_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getInfo, Repository_getInfo_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getAllInfos, Repository_getAllInfos_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getTypelibPath, Repository_getTypelibPath_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getSharedLibrary, Repository_getSharedLibrary_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getVersion, Repository_getVersion_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, getCPrefix, Repository_getCPrefix_args, ZEND_ACC_PUBLIC)
	PHP_ME(Repository, dump, Repository_dump_args, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(Repository, enumerateVersions, Repository_enumerateVersions_args, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(Repository)
{
	zend_class_entry ce;
	INIT_NS_CLASS_ENTRY(ce, GI_NAMESPACE, "Repository", gi_repository_methods);
	ce_gi_repository = zend_register_internal_class(&ce TSRMLS_CC);
	ce_gi_repository->ce_flags |= ZEND_ACC_FINAL;

	ce_gi_repository->create_object = gi_repository_object_create;
	memcpy(&gi_repository_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));

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
