--TEST--
G\Introspection\Repository::dump();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Exception as Ge;

// file 1 doesn't exist
try {
     Gir::dump('foo.txt,foo.xml');
} catch (Ge $e) {
    echo $e->getDomain(), ':', $e->getMessage(), PHP_EOL;
}

var_dump(Gir::dump(__DIR__ .'/dump.txt,' . __DIR__ . '/dump.xml'));

// too few args
try {
     Gir::dump();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     Gir::dump(1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     Gir::dump(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

?>
= DONE =
--EXPECT--
g-io-error-quark:Error opening file: No such file or directory
bool(true)
G\Introspection\Repository::dump() expects exactly 1 parameter, 0 given
G\Introspection\Repository::dump() expects exactly 1 parameter, 2 given
G\Introspection\Repository::dump() expects parameter 1 to be string, array given
= DONE =