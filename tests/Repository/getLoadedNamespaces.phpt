--TEST--
G\Introspection\Repository->getLoadedNamespaces();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

var_dump($repo->getLoadedNamespaces());

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

var_dump($repo->getLoadedNamespaces());

// too many args
try {
     $repo->getLoadedNamespaces(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
array(0) {
}
array(1) {
  [0]=>
  string(4) "GLib"
}
G\Introspection\Repository::getLoadedNamespaces() expects exactly 0 parameters, 1 given
= DONE =