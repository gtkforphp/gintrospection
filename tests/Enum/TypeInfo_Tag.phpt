--TEST--
G\Introspection\TypeInfo\Tag Enum
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\TypeInfo\Tag;

$enum = new Tag(Tag::VOID);
echo $enum, PHP_EOL;
var_dump($enum instanceof G\Enum);
var_dump($enum);

?>
= DONE =
--EXPECTF--
0
bool(true)
object(G\Introspection\TypeInfo\Tag)#1 (2) {
  ["__elements"]=>
  array(22) {
    ["VOID"]=>
    int(0)
    ["BOOLEAN"]=>
    int(1)
    ["INT8"]=>
    int(2)
    ["UINT8"]=>
    int(3)
    ["INT16"]=>
    int(4)
    ["UINT16"]=>
    int(5)
    ["INT32"]=>
    int(6)
    ["UINT32"]=>
    int(7)
    ["INT64"]=>
    int(8)
    ["UINT64"]=>
    int(9)
    ["FLOAT"]=>
    int(10)
    ["DOUBLE"]=>
    int(11)
    ["GTYPE"]=>
    int(12)
    ["UTF8"]=>
    int(13)
    ["FILENAME"]=>
    int(14)
    ["ARRAY"]=>
    int(15)
    ["INTERFACE"]=>
    int(16)
    ["GLIST"]=>
    int(17)
    ["GSLIST"]=>
    int(18)
    ["GHASH"]=>
    int(19)
    ["ERROR"]=>
    int(20)
    ["UNICHAR"]=>
    int(21)
  }
  ["__value"]=>
  int(0)
}
= DONE =