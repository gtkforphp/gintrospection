--TEST--
gintrospection phpinfo information
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
$ext = new ReflectionExtension('gintrospection');
$ext->info();
?>
= DONE =
--EXPECTF--
gintrospection

GIntrospection support => enabled
Extension Version => %d.%d.%d%s
= DONE =
