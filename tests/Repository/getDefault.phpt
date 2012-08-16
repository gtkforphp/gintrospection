--TEST--
G\Introspection\Repository::getDefault();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();
var_dump($repo instanceof Gir);

try {
     $repo = Gir::getDefault(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

?>
= DONE =
--EXPECT--
bool(true)
G\Introspection\Repository::getDefault() expects exactly 0 parameters, 1 given
= DONE =