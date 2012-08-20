--TEST--
G\Introspection\StructInfo->getSize();
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

$baseinfo = $repo->findByName('GLib', 'Timer');
var_dump($baseinfo->getSize());

$baseinfo = $repo->findByName('GLib', 'Date');
var_dump($baseinfo->getSize());

// too many args
try {
     $baseinfo->getSize(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
string(1) "0"
string(2) "24"
G\Introspection\StructInfo::getSize() expects exactly 0 parameters, 1 given
= DONE =