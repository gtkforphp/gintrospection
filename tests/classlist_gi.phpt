--TEST--
gi class listing
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
$ext = new ReflectionExtension('gi');
var_dump($ext->getClassNames());
?>
= DONE =
--EXPECT--
array(22) {
  [0]=>
  string(26) "G\Introspection\Repository"
  [1]=>
  string(23) "G\Introspection\Typelib"
  [2]=>
  string(24) "G\Introspection\BaseInfo"
  [3]=>
  string(28) "G\Introspection\CallableInfo"
  [4]=>
  string(28) "G\Introspection\FunctionInfo"
  [5]=>
  string(26) "G\Introspection\SignalInfo"
  [6]=>
  string(25) "G\Introspection\VFuncInfo"
  [7]=>
  string(27) "G\Introspection\RegTypeInfo"
  [8]=>
  string(24) "G\Introspection\EnumInfo"
  [9]=>
  string(25) "G\Introspection\UnionInfo"
  [10]=>
  string(26) "G\Introspection\StructInfo"
  [11]=>
  string(26) "G\Introspection\ObjectInfo"
  [12]=>
  string(29) "G\Introspection\InterfaceInfo"
  [13]=>
  string(23) "G\Introspection\ArgInfo"
  [14]=>
  string(28) "G\Introspection\ConstantInfo"
  [15]=>
  string(25) "G\Introspection\FieldInfo"
  [16]=>
  string(28) "G\Introspection\PropertyInfo"
  [17]=>
  string(24) "G\Introspection\TypeInfo"
  [18]=>
  string(32) "G\Introspection\Repository\Error"
  [19]=>
  string(36) "G\Introspection\Repository\LoadFlags"
  [20]=>
  string(24) "G\Introspection\InfoType"
  [21]=>
  string(31) "G\Introspection\VFuncInfo\Flags"
}
= DONE =