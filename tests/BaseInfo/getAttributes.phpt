--TEST--
G\Introspection\BaseInfo->getAttributes();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// no attributes
$baseinfo = $repo->findByName('GLib', 'Timer');
var_dump($baseinfo->getAttributes());

// TODO: find one with real attributes to test!
$baseinfo = $repo->findByName('GLib', 'Timer');
var_dump($baseinfo->getAttributes());

// too many args
try {
     $baseinfo->getAttributes(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
array(0) {
}

array(1) {
  ["realattribute"]=>
  string(13) "someattribute"
}
G\Introspection\BaseInfo::getAttributes() expects exactly 0 parameters, 1 given
= DONE =
--XFAIL--
Need to find an info in a typelib with attributes to actually test this