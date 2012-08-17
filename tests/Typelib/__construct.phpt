--TEST--
G\Introspection\Typelib->__construct();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Typelib;

// constructor is private and instantiation will fail
$typelib = new Typelib();

?>
= DONE =
--EXPECTF--
Fatal error: Call to private G\Introspection\Typelib::__construct() from invalid context in %s on line %d
