--TEST--
G\Introspection\Repository->__construct();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

class MyRepo extends Gir {}

// constructor is private and instantiation will fail
$repo = new MyRepo();


?>
--EXPECTF--
Fatal error: Call to private G\Introspection\Repository::__construct() from invalid context in %s on line %d
