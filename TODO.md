TODO
===

 1. repository.c - g_irepository_load_typelib - can't really do this until I can create typelibs
 1. repository.c - g_irepository_get_option_group - can't do this until the glib/gobject deps are done
 1. repository.c - GIRepositoryError - need enums for this
 1. repository.c - GIRepositoryLoadFlags - need enums for this, will also need to add flags option to
                   require, requirePrivate, and loadTypelib (when it's done)
 1. repository.c - g_irepository_find_by_gtype  - need gtype stuff from glib

 1. typelib.c - g_typelib_new_from_memory - need glib
 1. typelib.c - g_typelib_new_from_const_memory - need glib
 1. typelib.c - g_typelib_new_from_mapped_file - need glib and gio
 1. typelib.c - g_typelib_symbol - need glib

Currently we have a chicken and egg issue going on with the extension here - it is going to need to dep
on both glib (for basic types wrappers) and gobject (for object stuff) extensions at some point when we're
ready to do the importing.  For now the focus is on getting all the introspection stuff working so the
generator can be created. After the generator works the dep tree will be glib <- gobject <- gintrospection.
Yes that means some importing and renaming and moving GError stuff to use glib stuff (which will be namespace G)

IGNORED:
G_IREPOSITORY_ERROR (g_irepository_error_quark()) - managed by GError stuff
g_typelib_free - managed by object destruction