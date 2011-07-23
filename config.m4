dnl
dnl $Id$
dnl

PHP_ARG_WITH(gir, Gobject Introspection Library Support,
[  --with-gir             Enable gir support], yes)

if test "$PHP_GIR" != "no"; then
	export OLD_CPPFLAGS="$CPPFLAGS"
	export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_GIR"
	
	AC_MSG_CHECKING(PHP version)
	AC_TRY_COMPILE([#include <php_version.h>], [
	#if PHP_VERSION_ID < 50300
	#error this extension requires at least PHP version 5.3.0
	#endif
	],
 	[AC_MSG_RESULT(ok)],
	[AC_MSG_ERROR([need at least PHP 5.3.0])])
	
	export CPPFLAGS="$OLD_CPPFLAGS"

  PHP_SUBST(GIR_SHARED_LIBADD)
  AC_DEFINE(HAVE_GIR, 1, [ ])

  PHP_NEW_EXTENSION(gir, gir.c, $ext_shared)
  
  EXT_GIR_HEADERS="php_gir.h"

  ifdef([PHP_INSTALL_HEADERS], [
    PHP_INSTALL_HEADERS(ext/gir, $EXT_GIR_HEADERS)
  ])

  AC_MSG_CHECKING(for pkg-config)

  if test ! -f "$PKG_CONFIG"; then
    PKG_CONFIG=`which pkg-config`
  fi

  if test -f "$PKG_CONFIG"; then
    AC_MSG_RESULT(found)
    AC_MSG_CHECKING(for gir)
    
    if $PKG_CONFIG --exists gobject-introspection-1.0; then
        gir_version_full=`$PKG_CONFIG --modversion gobject-introspection-1.0`
        AC_MSG_RESULT([found $gobject_version_full])
        GIR_LIBS="$LDFLAGS `$PKG_CONFIG --libs gobject-introspection-1.0`"
        GIR_INCS="$CFLAGS `$PKG_CONFIG --cflags-only-I gobject-introspection-1.0`"
        PHP_EVAL_INCLINE($GIR_INCS)
        PHP_EVAL_LIBLINE($GIR_LIBS, GIR_SHARED_LIBADD)
        AC_DEFINE(HAVE_GIR, 1, [whether gir exists in the system])
    else
        AC_MSG_RESULT(not found)
        AC_MSG_ERROR(Ooops ! no gobject introspection - gir detected in the system)
    fi
  else
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR(Ooops ! no pkg-config found .... )
  fi
fi

