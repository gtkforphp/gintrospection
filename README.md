Gi
=============
The gtkforphp gi extension provides languages bindings for the Gobject Introspection (gi) library.
Documentation and information about the GI library can be found at http://developer.gnome.org/gi/stable/

The bindings provide twofold functionality - the ability to read and iterate over information in a
typelib, and the ability to import libraries directly into PHP as "faux" modules.

You can send comments, patches, questions [here on github](https://github.com/gtkforphp/gi/issues)

This is still an experimental extension.

Installing/Configuring
======================

This extension requires the gobject introspection library development files.  You can build the package
manually or use your system's package manager.  For example on ubuntu use

<pre>
apt-get install libgirepository-1.0-dev
</pre>

Then you can use phpize to install the extension against your current PHP install

<pre>
phpize
./configure
make && make test && make install
</pre>

If you want to use a non-standard location for your PHP use
<pre>
/path/to/phpize
./configure --with-php-config=/path/to/php-config
make && make test && make install
</pre>

`make install` copies `gi.so` to the right location, but you still need to enable the module
in your php.ini file.  Although the extension can be used with a webserver, it's recommended
you only use this with a cli PHP install.