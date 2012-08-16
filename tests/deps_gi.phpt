--TEST--
gi extension dependencies
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
$ext = new ReflectionExtension('gi');
var_dump($ext->getDependencies());
?>
= DONE =
--EXPECT--
array(1) {
  ["g"]=>
  string(8) "Required"
}
= DONE =
