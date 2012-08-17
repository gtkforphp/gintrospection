--TEST--
G\Introspection\Repository->getTypelibPath();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

// repo not loaded? well that's bad mojo
try {
     $repo->getTypelibPath('nothing');
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

var_dump($repo->getTypelibPath('GLib'));

// too few args
try {
     $repo->getTypelibPath();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getTypelibPath(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getTypelibPath(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECTF--
Namespace nothing is not currently loaded
string(%d) "%sGLib-%s.typelib"
G\Introspection\Repository::getTypelibPath() expects exactly 1 parameter, 0 given
G\Introspection\Repository::getTypelibPath() expects exactly 1 parameter, 2 given
G\Introspection\Repository::getTypelibPath() expects parameter 1 to be string, array given
= DONE =