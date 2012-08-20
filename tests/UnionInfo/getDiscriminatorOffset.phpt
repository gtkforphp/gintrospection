--TEST--
G\Introspection\UnionInfo->getDiscriminatorOffset();
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
var_dump($baseinfo->getDiscriminatorOffset());

// too many args
try {
     $baseinfo->getDiscriminatorOffset(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
int(0)
G\Introspection\UnionInfo::getDiscriminatorOffset() expects exactly 0 parameters, 1 given
= DONE =