--TEST--
G\Introspection\Repository->getNumInfos();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

// repo not loaded? well that's bad mojo
try {
     $repo->getNumInfos('nothing');
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

var_dump($repo->getNumInfos('GLib'));

// too few args
try {
     $repo->getNumInfos();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getNumInfos(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getNumInfos(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECTF--
Namespace nothing is not currently loaded
int(%d)
G\Introspection\Repository::getNumInfos() expects exactly 1 parameter, 0 given
G\Introspection\Repository::getNumInfos() expects exactly 1 parameter, 2 given
G\Introspection\Repository::getNumInfos() expects parameter 1 to be string, array given
= DONE =