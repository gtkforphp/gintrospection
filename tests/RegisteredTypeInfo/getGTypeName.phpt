--TEST--
G\Introspection\RegisteredTypeInfo->getGTypeName();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// get the Timer baseinfo - has a null gtypename
$baseinfo = $repo->findByName('GLib', 'Timer');
var_dump($baseinfo->getTypeInit());

// typevariant has an init function
$baseinfo = $repo->findByName('GLib', 'VariantType');
var_dump($baseinfo->getGTypeName());

// too many args
try {
     $baseinfo->getGTypeName(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
NULL
string(12) "GVariantType"
G\Introspection\RegisteredTypeInfo::getGTypeName() expects exactly 0 parameters, 1 given
= DONE =