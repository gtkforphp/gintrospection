--TEST--
G\Introspection\UnionInfo->getNumFields();
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

$baseinfo = $repo->findByName('GLib', 'Mutex');
var_dump($baseinfo->getNumFields());

// too many args
try {
     $baseinfo->getNumFields(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
int(2)
G\Introspection\UnionInfo::getNumFields() expects exactly 0 parameters, 1 given
= DONE =