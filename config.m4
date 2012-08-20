PHP_ARG_WITH(gintrospection, Gobject Introspection Support,
[  --with-gintrospection        Enable gintrospection support], yes)

if test "$PHP_GINTROSPECTION" != "no"; then

	export OLD_CPPFLAGS="$CPPFLAGS"
	export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_GINTROSPECTION"

	AC_MSG_CHECKING(PHP version)
	AC_TRY_COMPILE([#include <php_version.h>], [
	#if PHP_VERSION_ID < 50400
	#error this extension requires at least PHP version 5.4.0
	#endif
	],
 	[AC_MSG_RESULT(ok)],
	[AC_MSG_ERROR([need at least PHP 5.4.0])])

	export CPPFLAGS="$OLD_CPPFLAGS"

	PHP_SUBST(GINTROSPECTION_SHARED_LIBADD)
	AC_DEFINE(HAVE_GINTROSPECTION, 1, [ ])

	PHP_NEW_EXTENSION(gintrospection, php_gintrospection.c repository.c typelib.c enum.c info.c, $ext_shared)

	EXT_GINTROSPECTION_HEADERS="php_gintrospection_public.h"

	ifdef([PHP_INSTALL_HEADERS], [
		PHP_INSTALL_HEADERS(ext/gintrospection, $EXT_GINTROSPECTION_HEADERS)
	])

	PHP_ADD_EXTENSION_DEP(gintrospection, gobject)
	PHP_ADD_EXTENSION_DEP(gintrospection, glib)

	AC_MSG_CHECKING(for glib gtkforphp extension)
	if test -f "$phpincludedir/ext/glib/php_glib_public.h"; then
		PHP_ADD_INCLUDE($phpincludedir/ext/glib)
		AC_MSG_RESULT(yes)

		AC_MSG_CHECKING(for gobject gtkforphp extension)
		if test -f "$phpincludedir/ext/gobject/php_gobject_public.h"; then
			PHP_ADD_INCLUDE($phpincludedir/ext/glib)
			AC_MSG_RESULT(yes)
		else
			AC_MSG_RESULT(no)
			AC_MSG_ERROR(gobject gtkforphp extension not found.)
		fi
	else
		AC_MSG_RESULT(no)
		AC_MSG_ERROR(glib gtkforphp extension not found.)
	fi

	AC_MSG_CHECKING(for pkg-config)

	if test ! -f "$PKG_CONFIG"; then
		PKG_CONFIG=`which pkg-config`
	fi

	if test -f "$PKG_CONFIG"; then
		AC_MSG_RESULT(found)
		AC_MSG_CHECKING(for gintrospection)

		if $PKG_CONFIG --exists gobject-introspection-1.0; then
			gir_version_full=`$PKG_CONFIG --modversion gobject-introspection-1.0`
			AC_MSG_RESULT([found $gir_version_full])
			GINTROSPECTION_LIBS="$LDFLAGS `$PKG_CONFIG --libs gobject-introspection-1.0`"
			GINTROSPECTION_INCS="$CFLAGS `$PKG_CONFIG --cflags-only-I gobject-introspection-1.0`"
			PHP_EVAL_INCLINE($GINTROSPECTION_INCS)
			PHP_EVAL_LIBLINE($GINTROSPECTION_LIBS, GINTROSPECTION_SHARED_LIBADD)
			AC_DEFINE(HAVE_GINTROSEPCTION, 1, [whether gintrospection library exists in the system])
		else
			AC_MSG_RESULT(not found)
			AC_MSG_ERROR(Ooops ! no gobject introspection library - libgintrospection - detected in the system)
		fi
	else
		AC_MSG_RESULT(not found)
		AC_MSG_ERROR(Ooops ! no pkg-config found .... )
	fi
fi