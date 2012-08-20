--TEST--
G\Introspection\Repository->getVersion();
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
     $repo->getVersion('nothing');
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

var_dump($repo->getVersion('GLib'));

// too few args
try {
     $repo->getVersion();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getVersion(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getVersion(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
Namespace nothing is not currently loaded
string(3) "2.0"
G\Introspection\Repository::getVersion() expects exactly 1 parameter, 0 given
G\Introspection\Repository::getVersion() expects exactly 1 parameter, 2 given
G\Introspection\Repository::getVersion() expects parameter 1 to be string, array given
= DONE =