--TEST--
G\Introspection\Repository\LoadFlags Enum
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository\LoadFlags;

$enum = new LoadFlags(LoadFlags::LAZY);
echo $enum, PHP_EOL;
var_dump($enum instanceof G\Enum);
var_dump($enum);

?>
= DONE =
--EXPECTF--
%d
bool(true)
object(G\Introspection\Repository\LoadFlags)#%d (2) {
  ["__elements"]=>
  array(1) {
    ["LAZY"]=>
    int(1)
  }
  ["__value"]=>
  int(1)
}
= DONE =