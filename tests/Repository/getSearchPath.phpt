--TEST--
G\Introspection\Repository::getSearchPath
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository;

echo gettype(Repository::getSearchPath());
?>
--EXPECT--
array
