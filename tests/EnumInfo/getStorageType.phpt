--TEST--
G\Introspection\EnumInfo->getStorageType();
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

// has more then one count
$baseinfo = $repo->findByName('GLib', 'ConvertError');

$enum = $baseinfo->getStorageType();

var_dump($enum instanceof Type);

echo $enum, ' ', $enum->getName(), PHP_EOL;

// too many args
try {
     $baseinfo->getStorageType(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(false)
7 UINT32
G\Introspection\EnumInfo::getStorageType() expects exactly 0 parameters, 1 given
= DONE =