--TEST--
G\Introspection\UnionInfo->findMethod();
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
var_dump($baseinfo->findMethod('foobar') instanceof FunctionInfo);
var_dump($baseinfo->findMethod('lock') instanceof FunctionInfo);

// not enough args
try {
     $baseinfo->findMethod();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $baseinfo->findMethod(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// must be stringable
try {
     $baseinfo->findMethod(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(false)
bool(true)
G\Introspection\UnionInfo::findMethod() expects exactly 1 parameter, 0 given
G\Introspection\UnionInfo::findMethod() expects exactly 1 parameter, 2 given
G\Introspection\UnionInfo::findMethod() expects parameter 1 to be string, array given
= DONE =