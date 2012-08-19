--TEST--
G\Introspection\StructInfo->getField();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\FieldInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'Date');
var_dump($baseinfo->getField(0) instanceof FieldInfo);

// not enough args
try {
     $baseinfo->getField();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $baseinfo->getField(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// must be intable
try {
     $baseinfo->getField(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
G\Introspection\StructInfo::getField() expects exactly 1 parameter, 0 given
G\Introspection\StructInfo::getField() expects exactly 1 parameter, 2 given
G\Introspection\StructInfo::getField() expects parameter 1 to be long, array given
= DONE =