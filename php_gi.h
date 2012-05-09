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

#ifndef PHP_GI_EXT_H
#define PHP_GIREXT_H

#define PHP_GI_VERSION "0.1.0-dev"
#define GI_NAMESPACE ZEND_NS_NAME("G", "Introspection")

extern zend_module_entry gi_module_entry;
#define phpext_gi_ptr &gi_module_entry

#ifdef PHP_WIN32
# define PHP_GI_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_GI_API __attribute__ ((visibility("default")))
#else
# define PHP_GI
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

/* Globals */
ZEND_BEGIN_MODULE_GLOBALS(gi)
	HashTable *method_map;
ZEND_END_MODULE_GLOBALS(gi)

#ifdef ZTS
# define GI_G(v) TSRMG(gi_globals_id, zend_gi_globals *, v)
#else
# define GI_G(v) (gi_globals.v)
#endif

ZEND_EXTERN_MODULE_GLOBALS(gi)

#include <girepository.h>
#include <girffi.h>

#endif /* PHP_GI_EXT_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
