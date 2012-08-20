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

/* Requires glib for some base types and gobject for type system tools  */
static const zend_module_dep gintrospection_deps[] = {
	ZEND_MOD_REQUIRED("glib")
	ZEND_MOD_REQUIRED("gobject")
	ZEND_MOD_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gintrospection)
{
	PHP_MINIT(gintrospection_Repository)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(gintrospection_Typelib)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(gintrospection_Info)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(gintrospection_Enums)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gintrospection)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "GIntrospection support", "enabled");
	php_info_print_table_row(2, "Extension Version", PHP_GINTROSPECTION_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* {{{ gintrospection_module_entry
 */
zend_module_entry gintrospection_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	gintrospection_deps,
	"gintrospection",
	NULL,
	PHP_MINIT(gintrospection),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(gintrospection),
	PHP_GINTROSPECTION_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GINTROSPECTION
ZEND_GET_MODULE(gintrospection)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
