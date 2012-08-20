--TEST--
G\Introspection\BaseInfo->getAttribute();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// TODO: find one with real attributes
$baseinfo = $repo->findByName('GLib', 'Timer');

// no attribute
var_dump($baseinfo->getAttribute('fail'));

// too few args
try {
     $baseinfo->getAttribute();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $baseinfo->getAttribute(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// arg 1 must be stringable
try {
     $baseinfo->getAttribute(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
NULL
G\Introspection\BaseInfo::getAttribute() expects exactly 1 parameter, 0 given
G\Introspection\BaseInfo::getAttribute() expects exactly 1 parameter, 2 given
G\Introspection\BaseInfo::getAttribute() expects parameter 1 to be string, array given
= DONE =