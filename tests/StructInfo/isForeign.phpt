--TEST--
G\Introspection\StructInfo->isForeign();
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

// get the Timer baseinfo
$baseinfo = $repo->findByName('GLib', 'Timer');

var_dump($baseinfo->isForeign());

// too many args
try {
     $baseinfo->isForeign(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(false)
G\Introspection\StructInfo::isForeign() expects exactly 0 parameters, 1 given
= DONE =