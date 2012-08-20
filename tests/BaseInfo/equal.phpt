--TEST--
G\Introspection\BaseInfo->equal();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\InfoTYpe as Type;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// get the Timer baseinfo
$baseinfo1 = $repo->findByName('GLib', 'Timer');

// get another timer baseinfo
$baseinfo2 = $repo->findByName('GLib', 'Timer');

var_dump($baseinfo1 == $baseinfo2);
var_dump($baseinfo1->equal($baseinfo2));

// get a different baseinfo
$baseinfo2 = $repo->findByName('GLib', 'DestroyNotify');

var_dump($baseinfo1 == $baseinfo2);
var_dump($baseinfo1->equal($baseinfo2));

// not enough args
try {
     $baseinfo1->equal();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $baseinfo1->equal($baseinfo2, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// wrong arg type
try {
     $baseinfo1->equal(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
bool(true)
bool(false)
bool(false)
G\Introspection\BaseInfo::equal() expects exactly 1 parameter, 0 given
G\Introspection\BaseInfo::equal() expects exactly 1 parameter, 2 given
Argument 1 passed to G\Introspection\BaseInfo::equal() must be an instance of G\Introspection\BaseInfo, integer given
= DONE =