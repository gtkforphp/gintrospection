TODO
===

 1. repository.c - g_irepository_load_typelib - can't really do this until I can create typelibs
 1. repository.c - g_irepository_get_option_group - can't do this until the glib/gobject deps are done
 1. repository.c - g_irepository_find_by_gtype  - need gtype stuff from glib

 1. typelib.c - g_typelib_new_from_memory - need glib
 1. typelib.c - g_typelib_new_from_const_memory - need glib
 1. typelib.c - g_typelib_new_from_mapped_file - need glib and gio
 1. typelib.c - g_typelib_symbol - need glib

 1. info.c - (baseinfo) g_base_info_get_attribute - is done but test is xfail until I find a known attribute to test with
 1. info.c - (baseinfo) g_base_info_iterate_attributes - is done but test is xfail until I find a known attribute to test with
 1. info.c - (baseinfo) g_base_info_get_container - is done but test is xfail until I find a known item with a container

IGNORED
===
 1. G_IREPOSITORY_ERROR (g_irepository_error_quark()) - managed by GError stuff
 1. g_typelib_free - managed by object destruction
 1. GIAttributeIter - attributes exposed as PHP array, no need for this
 1. g_base_info_ref - handled in repository methods that retrieve infos
 1. g_base_info_unref - handled in object destruction

NOTES
===
Currently we have a chicken and egg issue going on with the extension here - it is going to need to dep
on both glib (for basic types wrappers) and gobject (for object stuff) extensions at some point when we're
ready to do the importing.  For now the focus is on getting all the introspection stuff working so the
generator can be created. After the generator works the dep tree will be glib <- gobject <- gintrospection.
Yes that means some importing and renaming and moving GError stuff to use glib stuff
(which will be namespace G)

need to rename this extension to gintrospection (the module) - will leave the namespace/etc as is
possibly add an "importNamespace" to do class_alias help

baseinfo might be good to get some built in mangling? we might wait for import to do that
getName - getCName(as is) getMangledName(to camelcase) getFullName(full namespaced path?)