--TEST--
gi extension dependencies
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('gintrospection');
var_dump($ext->getDependencies());
?>
= DONE =
--EXPECT--
array(2) {
  ["glib"]=>
  string(8) "Required"
  ["gobject"]=>
  string(8) "Required"
}
= DONE =
