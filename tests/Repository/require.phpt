--TEST--
G\Introspection\Repository->require();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\Repository\LoadFlags as LF;
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

// load it with version and flags
var_dump($repo->require('GObject', '2.0', new LF(LF::LAZY)) instanceof Typelib);

// too few args
try {
     $repo->require();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->require(1, 1, new LF(LF::LAZY), 1);
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

// enum instance only
try {
     $repo->require(1, array(), 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
g-irepository-error-quark:Typelib file for namespace 'nothing' (any version) not found
g-irepository-error-quark:Typelib file for namespace 'GLib', version '0.1.0' not found
bool(true)
bool(true)
G\Introspection\Repository::require() expects at least 1 parameter, 0 given
G\Introspection\Repository::require() expects at most 3 parameters, 4 given
G\Introspection\Repository::require() expects parameter 1 to be string, array given
G\Introspection\Repository::require() expects parameter 2 to be string, array given
Argument 3 passed to G\Introspection\Repository::require() must be an instance of G\Introspection\Repository\LoadFlags, integer given
= DONE =