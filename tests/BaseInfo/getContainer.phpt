--TEST--
G\Introspection\BaseInfo->getContainer();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\EnumInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// get the Timer baseinfo
$baseinfo = $repo->findByName('GLib', 'BookmarkFileError');
$valinfo = $baseinfo->getValue(0);

var_dump($valinfo->getContainer() instanceof EnumInfo);

// too many args
try {
     $baseinfo->getContainer(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
G\Introspection\BaseInfo::getContainer() expects exactly 0 parameters, 1 given
= DONE =