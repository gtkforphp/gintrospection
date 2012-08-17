--TEST--
G\Introspection\Repository->getSharedLibrary();
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
     $repo->getSharedLibrary('nothing');
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

var_dump($repo->getSharedLibrary('GLib'));

// too few args
try {
     $repo->getSharedLibrary();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getSharedLibrary(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getSharedLibrary(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECTF--
Namespace nothing is not currently loaded
string(%s) "%sglib%s"
G\Introspection\Repository::getSharedLibrary() expects exactly 1 parameter, 0 given
G\Introspection\Repository::getSharedLibrary() expects exactly 1 parameter, 2 given
G\Introspection\Repository::getSharedLibrary() expects parameter 1 to be string, array given
= DONE =