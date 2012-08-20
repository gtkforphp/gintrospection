--TEST--
G\Introspection\BaseInfo->getType();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\InfoTYpe as Type;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// get the Timer baseinfo
$baseinfo = $repo->findByName('GLib', 'Timer');

$enum = $baseinfo->getType();

var_dump($enum instanceof Type);

echo $enum, ' ', $enum->getName(), PHP_EOL;

// too many args
try {
     $baseinfo->getType(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
3 STRUCT
G\Introspection\BaseInfo::getType() expects exactly 0 parameters, 1 given
= DONE =