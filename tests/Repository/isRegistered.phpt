--TEST--
G\Introspection\Repository->isRegistered();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

var_dump($repo->isRegistered('nothing'));
var_dump($repo->isRegistered('nothing', 'whatever'));

// too few args
try {
     $repo->isRegistered();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->isRegistered(1, 1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->isRegistered(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 2
try {
     $repo->isRegistered(1, array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(false)
bool(false)
G\Introspection\Repository::isRegistered() expects at least 1 parameter, 0 given
G\Introspection\Repository::isRegistered() expects at most 2 parameters, 3 given
G\Introspection\Repository::isRegistered() expects parameter 1 to be string, array given
G\Introspection\Repository::isRegistered() expects parameter 2 to be string, array given
= DONE =