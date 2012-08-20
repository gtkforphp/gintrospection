--TEST--
G\Introspection\StructInfo->getAlignment();
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
var_dump($baseinfo->getAlignment());

$baseinfo = $repo->findByName('GLib', 'Date');
var_dump($baseinfo->getAlignment());

// too many args
try {
     $baseinfo->getAlignment(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
string(1) "1"
string(1) "4"
G\Introspection\StructInfo::getAlignment() expects exactly 0 parameters, 1 given
= DONE =