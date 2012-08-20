--TEST--
G\Introspection\EnumInfo->getValue();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\ValueInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'DateMonth');
var_dump($baseinfo->getValue(0) instanceof ValueInfo);

// not enough args
try {
     $baseinfo->getValue();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $baseinfo->getValue(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// must be intable
try {
     $baseinfo->getValue(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
G\Introspection\EnumInfo::getValue() expects exactly 1 parameter, 0 given
G\Introspection\EnumInfo::getValue() expects exactly 1 parameter, 2 given
G\Introspection\EnumInfo::getValue() expects parameter 1 to be long, array given
= DONE =