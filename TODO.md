TODO
===

 1. repository.c - Typelib loading - can't really do this until I can create typelibs
 1. repository.c - get_option_group - not sure how I'm going to handle this, should REALLY be in the glib extension
                   perhaps after I get this extension and the gig generator done, g/ should die in favor of the
                   glib extension (as G/ namespace) - will think on this  If I do this means you have to use
                   the static glib....the other option is to move the group option stuff into G (with
                   perhaps leaving the rest out?)