--TEST--
G\Introspection\EnumInfo->getMethod();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\FunctionInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'DateMonth');
var_dump($baseinfo->getMethod(0) instanceof FunctionInfo);

// not enough args
try {
     $baseinfo->getMethod();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $baseinfo->getMethod(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// must be intable
try {
     $baseinfo->getMethod(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(false)
G\Introspection\EnumInfo::getMethod() expects exactly 1 parameter, 0 given
G\Introspection\EnumInfo::getMethod() expects exactly 1 parameter, 2 given
G\Introspection\EnumInfo::getMethod() expects parameter 1 to be long, array given
= DONE =