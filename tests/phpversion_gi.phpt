--TEST--
phpversion('gi') value
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
var_dump(phpversion('gi'));
?>
= DONE =
--EXPECTF--
string(%d) "%d.%d.%d%s"
= DONE =