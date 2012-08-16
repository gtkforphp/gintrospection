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

/* Requires the G system tools for unicode/string classes, gerror handling
   enums and more */
static const zend_module_dep gi_deps[] = {
	ZEND_MOD_REQUIRED("g")
	ZEND_MOD_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gi)
{
	g_type_init();

	PHP_MINIT(Repository)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(Typelib)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(BaseInfo)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Gobject Introspection support", "enabled");
	php_info_print_table_row(2, "Extension Version", PHP_GI_VERSION);
	php_info_print_table_end();
}
/* }}} */

/* {{{ gi_module_entry
 */
zend_module_entry gi_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	gi_deps,
	"gi",
	NULL,
	PHP_MINIT(gi),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(gi),
	PHP_GI_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GI
ZEND_GET_MODULE(gi)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
