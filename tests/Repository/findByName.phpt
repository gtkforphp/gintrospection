--TEST--
G\Introspection\Repository->findByName();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\BaseInfo;

$repo = Gir::getDefault();

// repo not loaded? well that's bad mojo
try {
     $repo->findByName('nothing', 'much');
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

$baseinfo = $repo->findByName('GLib', 'Timer');

var_dump($baseinfo instanceof BaseInfo);
var_dump(get_class($baseinfo));

$baseinfo = $repo->findByName('GLib', 'foobar');

var_dump($baseinfo);

// too few args
try {
     $repo->findByName();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too few args
try {
     $repo->findByName(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->findByName(1, 1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->findByName(array(), 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 2
try {
     $repo->findByName(1, array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
Namespace nothing is not currently loaded
bool(true)
string(26) "G\Introspection\StructInfo"
NULL
G\Introspection\Repository::findByName() expects exactly 2 parameters, 0 given
G\Introspection\Repository::findByName() expects exactly 2 parameters, 1 given
G\Introspection\Repository::findByName() expects exactly 2 parameters, 3 given
G\Introspection\Repository::findByName() expects parameter 1 to be string, array given
G\Introspection\Repository::findByName() expects parameter 2 to be string, array given
= DONE =