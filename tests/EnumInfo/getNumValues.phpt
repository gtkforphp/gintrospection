--TEST--
G\Introspection\EnumInfo->getNumValues();
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

// has more then one count
$baseinfo = $repo->findByName('GLib', 'DateMonth');
var_dump($baseinfo->getNumValues());

// too many args
try {
     $baseinfo->getNumValues(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
int(13)
G\Introspection\EnumInfo::getNumValues() expects exactly 0 parameters, 1 given
= DONE =