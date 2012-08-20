--TEST--
G\Introspection\Typelib->getNamespace();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\Typelib;

$repo = Gir::getDefault();

// load it right with name
$typelib = $repo->require('GLib');

var_dump($typelib instanceof Typelib);

// should test loading it right with version, but don't have a typelib to rely on for that
var_dump($typelib->getNamespace());

// too many args
try {
     $typelib->getNamespace(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
string(4) "GLib"
G\Introspection\Typelib::getNamespace() expects exactly 0 parameters, 1 given
= DONE =