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
#include <ext/standard/info.h>

#include "php_gir_private.h"

ZEND_DECLARE_MODULE_GLOBALS(gir)

PHP_GINIT_FUNCTION(gir) {
	/* Set things */
}

PHP_GSHUTDOWN_FUNCTION(gir) {
	/* Free things */	
}


/* {{{ gobject_module_entry
 */
zend_module_entry gir_module_entry = {
	STANDARD_MODULE_HEADER,
	"gir",
	NULL,
	PHP_MINIT(gir),
	PHP_MSHUTDOWN(gir),
	PHP_RINIT(gir),
	PHP_RSHUTDOWN(gir),
	PHP_MINFO(gir),
	PHP_GIR_VERSION,
	PHP_MODULE_GLOBALS(gir),
	PHP_GINIT(gir),
	PHP_GSHUTDOWN(gir),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_GIR
ZEND_GET_MODULE(gir)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(gir)
{
	g_type_init();

	PHP_MINIT(repository)(INIT_FUNC_ARGS_PASSTHRU);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(gir)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(gir)
{
	ALLOC_HASHTABLE(GIR_G(method_map));
	zend_hash_init(GIR_G(method_map), 0, NULL, NULL, 1);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(gir)
{
	zend_hash_destroy(GIR_G(method_map));
	FREE_HASHTABLE(GIR_G(method_map));

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(gir)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "gir support", "enabled");
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
