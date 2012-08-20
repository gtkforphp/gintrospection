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

#ifndef PHP_GINTROSPECTION_PUBLIC_EXT_H
#define PHP_GINTROSPECTION_PUBLIC_EXT_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

#include <php.h>

#ifdef PHP_WIN32
#  ifdef gintrospection_EXPORTS
#    define PHP_GINTROSPECTION_API __declspec(dllexport)
#  elif defined(COMPILE_DL_GINTROSPECTION)
#    define PHP_GINTROSPECTION_API __declspec(dllimport)
#  else
#    define PHP_GINTROSPECTION_API /* nothing special */
#  endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#  define PHP_GINTROSPECTION_API __attribute__ ((visibility("default")))
#else
#  define PHP_GINTROSPECTION_API
#endif

#define PHP_GINTROSPECTION_VERSION "0.1.0-dev"
#define GINTROSPECTION_NAMESPACE ZEND_NS_NAME("G", "Introspection")

typedef struct _gintrospection_repository_object gintrospection_repository_object;
typedef struct _gintrospection_baseinfo_object gintrospection_baseinfo_object;
typedef struct _gintrospection_typelib_object gintrospection_typelib_object;

extern zend_class_entry *ce_gintrospection_repository;
extern zend_class_entry *ce_gintrospection_typelib;

extern zend_class_entry *ce_gintrospection_vfuncinfo;
extern zend_class_entry *ce_gintrospection_signalinfo;
extern zend_class_entry *ce_gintrospection_functioninfo;
extern zend_class_entry *ce_gintrospection_callableinfo;
extern zend_class_entry *ce_gintrospection_unioninfo;
extern zend_class_entry *ce_gintrospection_structinfo;
extern zend_class_entry *ce_gintrospection_objectinfo;
extern zend_class_entry *ce_gintrospection_interfaceinfo;
extern zend_class_entry *ce_gintrospection_enuminfo;
extern zend_class_entry *ce_gintrospection_regtypeinfo;
extern zend_class_entry *ce_gintrospection_arginfo;
extern zend_class_entry *ce_gintrospection_constantinfo;
extern zend_class_entry *ce_gintrospection_fieldinfo;
extern zend_class_entry *ce_gintrospection_propertyinfo;
extern zend_class_entry *ce_gintrospection_typeinfo;
extern zend_class_entry *ce_gintrospection_baseinfo;

extern zend_class_entry *ce_gintrospection_repositoryloadflags;
extern zend_class_entry *ce_gintrospection_infotype;
extern zend_class_entry *ce_gintrospection_typetag;

#endif /* PHP_GINTROSPECTION_PUBLIC_EXT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
