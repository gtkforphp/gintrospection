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

$list = $repo->getInfos('GLib');
foreach($list as $info) {
     $attr = $info->getAttributes();
     var_dump($attr);
}
// get the Timer baseinfo
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
bool(false)
bool(true)
G\Introspection\BaseInfo::isDeprecated() expects exactly 0 parameters, 1 given
= DONE =