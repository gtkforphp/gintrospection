--TEST--
G\Introspection\VFuncInfo\Flags Enum
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\VFuncInfo\Flags;

$enum = new Flags(Flags::THROWS);
echo $enum, PHP_EOL;
var_dump($enum instanceof G\Enum);
var_dump($enum);

?>
= DONE =
--EXPECTF--
%d
bool(true)
object(G\Introspection\VFuncInfo\Flags)#%d (2) {
  ["__elements"]=>
  array(4) {
    ["MUST_CHAIN_UP"]=>
    int(1)
    ["MUST_OVERRIDE"]=>
    int(2)
    ["MUST_NOT_OVERRIDE"]=>
    int(4)
    ["THROWS"]=>
    int(8)
  }
  ["__value"]=>
  int(8)
}
= DONE =