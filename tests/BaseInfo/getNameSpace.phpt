--TEST--
G\Introspection\BaseInfo->getNameSpace();
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

var_dump($baseinfo->getNameSpace());

// too many args
try {
     $baseinfo->getNameSpace(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
string(4) "GLib"
G\Introspection\BaseInfo::getNameSpace() expects exactly 0 parameters, 1 given
= DONE =