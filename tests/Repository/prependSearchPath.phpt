--TEST--
G\Introspection\Repository::prependSearchPath();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

var_dump(Gir::prependSearchPath(__DIR__));
$list = Gir::getSearchPath();

var_dump($list[0] == __DIR__);

// too few args
try {
     Gir::prependSearchPath();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     Gir::prependSearchPath(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     Gir::prependSearchPath(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

?>
= DONE =
--EXPECT--
NULL
bool(true)
G\Introspection\Repository::prependSearchPath() expects exactly 1 parameter, 0 given
G\Introspection\Repository::prependSearchPath() expects exactly 1 parameter, 2 given
G\Introspection\Repository::prependSearchPath() expects parameter 1 to be string, array given
= DONE =