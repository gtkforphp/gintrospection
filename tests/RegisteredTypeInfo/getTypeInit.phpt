--TEST--
G\Introspection\RegisteredTypeInfo->getTypeInit();
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

// get the Timer baseinfo - has a null gettypeinit
$baseinfo = $repo->findByName('GLib', 'Timer');
var_dump($baseinfo->getTypeInit());

// typevariant has an init function
$baseinfo = $repo->findByName('GLib', 'VariantType');
var_dump($baseinfo->getTypeInit());

// too many args
try {
     $baseinfo->getTypeInit(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
NULL
string(24) "g_variant_type_get_gtype"
G\Introspection\RegisteredTypeInfo::getTypeInit() expects exactly 0 parameters, 1 given
= DONE =