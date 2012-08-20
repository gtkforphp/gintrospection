--TEST--
G\Introspection\UnionInfo->getMethod();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\FunctionInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'Mutex');
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
bool(true)
G\Introspection\UnionInfo::getMethod() expects exactly 1 parameter, 0 given
G\Introspection\UnionInfo::getMethod() expects exactly 1 parameter, 2 given
G\Introspection\UnionInfo::getMethod() expects parameter 1 to be long, array given
= DONE =