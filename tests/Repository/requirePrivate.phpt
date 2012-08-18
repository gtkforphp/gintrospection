--TEST--
G\Introspection\Repository->requirePrivate();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\Repository\LoadFlags as LF;
use G\Introspection\Typelib;
use G\Exception as Ge;

// it'll try private only
$repo = Gir::getDefault();
$path = __DIR__;

// try to require a bad library
try {
     $repo->requirePrivate($path, 'foobar');
} catch (Ge $e) {
    echo $e->getDomain(), ':', $e->getMessage(), PHP_EOL;
}

// try to require a bad version
try {
     $repo->requirePrivate($path, 'GLib', '0.1.0');
} catch (Ge $e) {
    echo $e->getDomain(), ':', $e->getMessage(), PHP_EOL;
}

// try to require a bad path
try {
     $repo->requirePrivate($path, 'GLib', '2.0');
} catch (Ge $e) {
    echo $e->getDomain(), ':', $e->getMessage(), PHP_EOL;
}

// load glib to get a good path
$repo->require('GLib');
$path = dirname($repo->getTypelibPath('GLib'));

// load gobject simply
var_dump($repo->requirePrivate($path, 'GObject') instanceof Typelib);

// load it with version and flags
var_dump($repo->requirePrivate($path, 'Gio', '2.0', new LF(LF::LAZY)) instanceof Typelib);

// too few args
try {
     $repo->requirePrivate();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too few args
try {
     $repo->requirePrivate(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->requirePrivate(1, 1, 1, new LF(LF::LAZY), 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->requirePrivate(array(), 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 2
try {
     $repo->requirePrivate(1, array(), 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 3
try {
     $repo->requirePrivate(1, 1, array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// enum instance only
try {
     $repo->requirePrivate(1, 1, 1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
g-irepository-error-quark:Typelib file for namespace 'foobar' (any version) not found
g-irepository-error-quark:Typelib file for namespace 'GLib', version '0.1.0' not found
g-irepository-error-quark:Typelib file for namespace 'GLib', version '2.0' not found
bool(true)
bool(true)
G\Introspection\Repository::requirePrivate() expects at least 2 parameters, 0 given
G\Introspection\Repository::requirePrivate() expects at least 2 parameters, 1 given
G\Introspection\Repository::requirePrivate() expects at most 4 parameters, 5 given
G\Introspection\Repository::requirePrivate() expects parameter 1 to be string, array given
G\Introspection\Repository::requirePrivate() expects parameter 2 to be string, array given
G\Introspection\Repository::requirePrivate() expects parameter 3 to be string, array given
Argument 4 passed to G\Introspection\Repository::requirePrivate() must be an instance of G\Introspection\Repository\LoadFlags, integer given
= DONE =