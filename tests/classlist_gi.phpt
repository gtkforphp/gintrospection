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
array(3) {
  [0]=>
  string(26) "G\Introspection\Repository"
  [1]=>
  string(23) "G\Introspection\Typelib"
  [2]=>
  string(24) "G\Introspection\BaseInfo"
}
= DONE =