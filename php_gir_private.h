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

#ifndef PHP_GIR_PRIVATE_EXT_H
#define PHP_GIR_PRIVATE_EXT_H

#include "php_gir.h"

/* Lifecycle - Extension */
PHP_MINIT_FUNCTION(gir);
PHP_MSHUTDOWN_FUNCTION(gir);
PHP_RINIT_FUNCTION(gir);
PHP_RSHUTDOWN_FUNCTION(gir);
PHP_MINFO_FUNCTION(gir);

/* Class lifecycle */
PHP_MINIT_FUNCTION(repository);

/* Internal C API */
char* gir_namespaced_name(const char *ns_name, const char *name, zend_bool persistent);

#endif	/* PHP_GIR_PRIVATE_EXT_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
