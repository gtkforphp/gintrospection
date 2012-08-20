--TEST--
G\Introspection\Repository::getSearchPath();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

Gir::prependSearchPath(__DIR__);
$list = Gir::getSearchPath();

var_dump($list[0] == __DIR__);

// too many args
try {
     Gir::getSearchPath(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
G\Introspection\Repository::getSearchPath() expects exactly 0 parameters, 1 given
= DONE =