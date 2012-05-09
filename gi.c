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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <php.h>
#include <ext/standard/info.h>

#include "php_gi_private.h"

ZEND_DECLARE_MODULE_GLOBALS(gi)

PHP_GINIT_FUNCTION(gi) {
	/* Set things */
}

PHP_GSHUTDOWN_FUNCTION(gi) {
	/* Free things */
}


/* {{{ gi_module_entry
 */
zend_module_entry gi_module_entry = {
	STANDARD_MODULE_HEADER,
	"gi",
	NULL,
	PHP_MINIT(gi),
	PHP_MSHUTDOWN(gi),
	PHP_RINIT(gi),
	PHP_RSHUTDOWN(gi),
	PHP_MINFO(gi),
	PHP_GI_VERSION,
	PHP_MODULE_GLOBALS(gi),
	PHP_GINIT(gi),
	PHP_GSHUTDOWN(gi),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_GI
ZEND_GET_MODULE(gi)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gi)
{
	g_type_init();

	PHP_MINIT(Repository)(INIT_FUNC_ARGS_PASSTHRU);
	PHP_MINIT(BaseInfo)(INIT_FUNC_ARGS_PASSTHRU);
	//PHP_MINIT(enum)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gi)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(gi)
{
	//ALLOC_HASHTABLE(GIR_G(method_map));
	//zend_hash_init(GIR_G(method_map), 0, NULL, NULL, 1);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(gi)
{
	//zend_hash_destroy(GIR_G(method_map));
	//FREE_HASHTABLE(GIR_G(method_map));

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Gobject Introspection support", "enabled");
	php_info_print_table_end();
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
