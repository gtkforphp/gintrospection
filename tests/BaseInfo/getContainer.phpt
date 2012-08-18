--TEST--
G\Introspection\BaseInfo->getContainer();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\InfoTYpe as Type;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// get the Timer baseinfo
$baseinfo = $repo->findByName('GLib', 'Timer');

var_dump($baseinfo->getContainer());

// TODO HERE _ find a baseinfo to grab with a container

// too many args
try {
     $baseinfo->getContainer(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
NULL
some object here
G\Introspection\BaseInfo::getContainer() expects exactly 0 parameters, 1 given
= DONE =
--XFAIL--
Need to find an info in a typelib with container to test this on