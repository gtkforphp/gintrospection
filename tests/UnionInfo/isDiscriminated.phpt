--TEST--
G\Introspection\UnionInfo->isDiscriminated();
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

$baseinfo = $repo->findByName('GLib', 'TokenValue');
var_dump($baseinfo->isDiscriminated());

// too many args
try {
     $baseinfo->isDiscriminated(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(false)
G\Introspection\UnionInfo::isDiscriminated() expects exactly 0 parameters, 1 given
= DONE =