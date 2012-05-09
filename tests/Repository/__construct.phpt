--TEST--
G\Introspection\Repository->__construct();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

// constructor is private and instantiation will fail
$repo = new Gir();


?>
--EXPECTF--
Fatal error: Call to private G\Introspection\Repository::__construct() from invalid context in %s on line %d
