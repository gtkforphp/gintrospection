--TEST--
G\Introspection\ValueInfo->getValue();
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
$baseinfo = $repo->findByName('GLib', 'DateMonth');

$valueinfo = $baseinfo->getValue(9);

var_dump($valueinfo->getValue());

// too many args
try {
     $valueinfo->getValue(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
string(1) "9"
G\Introspection\ValueInfo::getValue() expects exactly 0 parameters, 1 given
= DONE =