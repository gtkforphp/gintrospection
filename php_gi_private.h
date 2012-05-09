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

#ifndef PHP_GI_PRIVATE_EXT_H
#define PHP_GI_PRIVATE_EXT_H

#include "php_gi.h"
#include <zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

/* Lifecycle - Extension */
PHP_MINIT_FUNCTION(gi);
PHP_MSHUTDOWN_FUNCTION(gi);
PHP_RINIT_FUNCTION(gi);
PHP_RSHUTDOWN_FUNCTION(gi);
PHP_MINFO_FUNCTION(gi);

/* Class lifecycle */
PHP_MINIT_FUNCTION(repository);

#define PHP_GI_EXCEPTIONS \
	zend_error_handling error_handling; \
	zend_replace_error_handling(EH_THROW, spl_ce_InvalidArgumentException, &error_handling TSRMLS_CC);

#define PHP_GI_RESTORE_ERRORS \
	zend_restore_error_handling(&error_handling TSRMLS_CC);

/* Internal C API */
char* gi_namespaced_name(const char *ns_name, const char *name, zend_bool persistent);

/* repository info */
typedef struct _gi_repository_object {
	zend_object std;
	zend_bool is_constructed;
	GIRepository* repo;
} gi_repository_object;

/* baseinfo object */
typedef struct _gi_baseinfo_object {
	zend_object std;
	zend_bool is_constructed;
} gi_baseinfo_object;

#endif /* PHP_GI_PRIVATE_EXT_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */