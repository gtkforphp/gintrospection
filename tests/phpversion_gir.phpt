--TEST--
phpversion('gir') value
--SKIPIF--
<?php
if(!extension_loaded('gir')) die('skip - GIR extension not available');
?>
--FILE--
<?php
var_dump(phpversion('gir'));
?>
--EXPECTF--
string(%d) "%d.%d.%d%s"
