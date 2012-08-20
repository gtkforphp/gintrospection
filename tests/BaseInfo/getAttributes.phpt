--TEST--
G\Introspection\BaseInfo->getAttributes();
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

// no attributes
$baseinfo = $repo->findByName('GLib', 'Timer');
var_dump($baseinfo->getAttributes());

// too many args
try {
     $baseinfo->getAttributes(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
array(0) {
}
G\Introspection\BaseInfo::getAttributes() expects exactly 0 parameters, 1 given
= DONE =