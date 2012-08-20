--TEST--
phpversion('gintrospection') value
--SKIPIF--
<?php
include __DIR__ . '/skipif.inc';
?>
--FILE--
<?php
var_dump(phpversion('gintrospection'));
?>
= DONE =
--EXPECTF--
string(%d) "%d.%d.%d%s"
= DONE =