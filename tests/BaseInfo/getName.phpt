--TEST--
G\Introspection\BaseInfo->getName();
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

// get the Timer baseinfo
$baseinfo = $repo->findByName('GLib', 'Timer');

var_dump($baseinfo->getName());

// too many args
try {
     $baseinfo->getName(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
string(5) "Timer"
G\Introspection\BaseInfo::getName() expects exactly 0 parameters, 1 given
= DONE =