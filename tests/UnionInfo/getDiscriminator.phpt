--TEST--
G\Introspection\UnionInfo->getDiscriminator();
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
var_dump($baseinfo->getDiscriminator(1));

// too few args
try {
     $baseinfo->getDiscriminator();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $baseinfo->getDiscriminator(1,1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// arg must be intable
try {
     $baseinfo->getDiscriminator(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
NULL
G\Introspection\UnionInfo::getDiscriminator() expects exactly 1 parameter, 0 given
G\Introspection\UnionInfo::getDiscriminator() expects exactly 1 parameter, 2 given
G\Introspection\UnionInfo::getDiscriminator() expects parameter 1 to be long, array given
= DONE =