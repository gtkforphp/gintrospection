--TEST--
Gir\Repository::getSearchPath
--SKIPIF--
<?php
if(!extension_loaded('gir')) die('skip - GIR extension not available');
?>
--FILE--
<?php
use Gir\Repository;

echo gettype(Repository::getSearchPath());
?>
--EXPECT--
array
