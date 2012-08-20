--TEST--
G\Introspection\UnionInfo->getSize();
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

$baseinfo = $repo->findByName('GLib', 'TokenValue');
var_dump($baseinfo->getSize());

$baseinfo = $repo->findByName('GLib', 'Mutex');
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
string(1) "8"
string(1) "8"
G\Introspection\UnionInfo::getSize() expects exactly 0 parameters, 1 given
= DONE =