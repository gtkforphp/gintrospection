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

#ifndef PHP_GI_PUBLIC_EXT_H
#define PHP_GI_PUBLIC_EXT_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

#include <php.h>

#ifdef PHP_WIN32
#  ifdef GI_EXPORTS
#    define PHP_GI_API __declspec(dllexport)
#  elif defined(COMPILE_DL_G)
#    define PHP_GI_API __declspec(dllimport)
#  else
#    define PHP_GI_API /* nothing special */
#  endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#  define PHP_GI_API __attribute__ ((visibility("default")))
#else
#  define PHP_GI_API
#endif

#define PHP_GI_VERSION "0.1.0-dev"
#define GI_NAMESPACE ZEND_NS_NAME("G", "Introspection")

typedef struct _gi_repository_object gi_repository_object;
typedef struct _gi_baseinfo_object gi_baseinfo_object;

PHP_GI_API zend_class_entry *ce_gi_repository;
PHP_GI_API zend_class_entry *ce_gi_typelib;
PHP_GI_API zend_class_entry *ce_gi_baseinfo;

#endif /* PHP_GI_PUBLIC_EXT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
