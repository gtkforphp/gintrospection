--TEST--
gi phpinfo information
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
$ext = new ReflectionExtension('gi');
$ext->info();
?>
= DONE =
--EXPECTF--
gi

Gobject Introspection support => enabled
Extension Version => %d.%d.%d%s
= DONE =
