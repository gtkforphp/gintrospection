--TEST--
G\Introspection\Repository->require();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\Typelib;
use G\Exception as Ge;

$repo = Gir::getDefault();

// try to require a bad namespace
try {
     $repo->require('nothing');
} catch (Ge $e) {
    echo $e->getDomain(), ':', $e->getMessage(), PHP_EOL;
}

// try to require a bad version
try {
     $repo->require('GLib', '0.1.0');
} catch (Ge $e) {
    echo $e->getDomain(), ':', $e->getMessage(), PHP_EOL;
}

// load it right with name
var_dump($repo->require('GLib') instanceof Typelib);

// should test loading it right with version, but don't have a typelib to rely on for that

// too few args
try {
     $repo->require();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->require(1, 1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->require(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 2
try {
     $repo->require(1, array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
g-irepository-error-quark:Typelib file for namespace 'nothing' (any version) not found
g-irepository-error-quark:Typelib file for namespace 'GLib', version '0.1.0' not found
bool(true)
G\Introspection\Repository::require() expects at least 1 parameter, 0 given
G\Introspection\Repository::require() expects at most 2 parameters, 3 given
G\Introspection\Repository::require() expects parameter 1 to be string, array given
G\Introspection\Repository::require() expects parameter 2 to be string, array given
= DONE =