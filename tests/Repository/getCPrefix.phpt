--TEST--
G\Introspection\Repository->getCPrefix();
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
     $repo->getCPrefix('nothing');
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

var_dump($repo->getCPrefix('GLib'));

// too few args
try {
     $repo->getCPrefix();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getCPrefix(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getCPrefix(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
Namespace nothing is not currently loaded
string(1) "G"
G\Introspection\Repository::getCPrefix() expects exactly 1 parameter, 0 given
G\Introspection\Repository::getCPrefix() expects exactly 1 parameter, 2 given
G\Introspection\Repository::getCPrefix() expects parameter 1 to be string, array given
= DONE =