--TEST--
G\Introspection\Repository\Error Enum
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository\Error;

$enum = new Error(Error::TYPELIB_NOT_FOUND);
echo $enum, PHP_EOL;
var_dump($enum instanceof G\Enum);
var_dump($enum);

?>
= DONE =
--EXPECTF--
%d
bool(true)
object(G\Introspection\Repository\Error)#%d (2) {
  ["__elements"]=>
  array(4) {
    ["TYPELIB_NOT_FOUND"]=>
    int(0)
    ["NAMESPACE_MISMATCH"]=>
    int(1)
    ["NAMESPACE_VERSION_CONFLICT"]=>
    int(2)
    ["LIBRARY_NOT_FOUND"]=>
    int(3)
  }
  ["__value"]=>
  int(0)
}
= DONE =