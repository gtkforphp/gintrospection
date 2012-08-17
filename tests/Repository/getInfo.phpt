--TEST--
G\Introspection\Repository->getInfo();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\BaseInfo;

$repo = Gir::getDefault();

// repo not loaded? well that's bad mojo
try {
     $repo->getInfo('nothing', 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// index out of bounds?
try {
     $repo->getInfo('GLib', 10000);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

$baseinfo = $repo->getInfo('GLib', 0);

var_dump($baseinfo instanceof BaseInfo);

// too few args
try {
     $repo->getInfo();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too few args
try {
     $repo->getInfo(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getInfo(1, 1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getInfo(array(), 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// int or cast to int only arg 2
try {
     $repo->getInfo(1, array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
Namespace nothing is not currently loaded
Index must be between 0 and 707
bool(true)
G\Introspection\Repository::getInfo() expects exactly 2 parameters, 0 given
G\Introspection\Repository::getInfo() expects exactly 2 parameters, 1 given
G\Introspection\Repository::getInfo() expects exactly 2 parameters, 3 given
G\Introspection\Repository::getInfo() expects parameter 1 to be string, array given
G\Introspection\Repository::getInfo() expects parameter 2 to be long, array given
= DONE =