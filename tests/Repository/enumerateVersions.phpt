--TEST--
G\Introspection\Repository->enumerateVersions();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

// this can be different machine to machine, so we'll verify just a few things
$versions = $repo->enumerateVersions('GLib');

// we have an array with at least one element, and 2.0 defs are available
var_dump(is_array($versions));
var_dump(isset($versions[0]));
var_dump(in_array('2.0', $versions));

// too few args
try {
     $repo->enumerateVersions();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->enumerateVersions(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->enumerateVersions(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
bool(true)
bool(true)
G\Introspection\Repository::enumerateVersions() expects exactly 1 parameter, 0 given
G\Introspection\Repository::enumerateVersions() expects exactly 1 parameter, 2 given
G\Introspection\Repository::enumerateVersions() expects parameter 1 to be string, array given
= DONE =