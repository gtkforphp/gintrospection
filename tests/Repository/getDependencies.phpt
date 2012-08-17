--TEST--
G\Introspection\Repository->getDependencies();
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
     $repo->getDependencies('nothing');
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

var_dump($repo->getDependencies('GLib'));

// too few args
try {
     $repo->getDependencies();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getDependencies(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getDependencies(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
Namespace nothing is not currently loaded
array(0) {
}
G\Introspection\Repository::getDependencies() expects exactly 1 parameter, 0 given
G\Introspection\Repository::getDependencies() expects exactly 1 parameter, 2 given
G\Introspection\Repository::getDependencies() expects parameter 1 to be string, array given
= DONE =