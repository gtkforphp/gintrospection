--TEST--
G\Introspection\InfoType Enum
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\InfoType;

$enum = new InfoType(InfoType::INVALID);
echo $enum, PHP_EOL;
var_dump($enum instanceof G\Enum);
var_dump($enum);

?>
= DONE =
--EXPECTF--
0
bool(true)
object(G\Introspection\InfoType)#%d (2) {
  ["__elements"]=>
  array(19) {
    ["INVALID"]=>
    int(0)
    ["FUNCTION"]=>
    int(1)
    ["CALLBACK"]=>
    int(2)
    ["STRUCT"]=>
    int(3)
    ["BOXED"]=>
    int(4)
    ["ENUM"]=>
    int(5)
    ["FLAGS"]=>
    int(6)
    ["OBJECT"]=>
    int(7)
    ["INTERFACE"]=>
    int(8)
    ["UNION"]=>
    int(11)
    ["VALUE"]=>
    int(12)
    ["SIGNAL"]=>
    int(13)
    ["VFUNC"]=>
    int(14)
    ["CONSTANT"]=>
    int(9)
    ["PROPERTY"]=>
    int(15)
    ["FIELD"]=>
    int(16)
    ["ARG"]=>
    int(17)
    ["TYPE"]=>
    int(18)
    ["UNRESOLVED"]=>
    int(19)
  }
  ["__value"]=>
  int(0)
}
= DONE =