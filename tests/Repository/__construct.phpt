--TEST--
G\Introspection\Repository->__construct();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

// constructor is private and instantiation will fail
$repo = new Gir();

?>
= DONE =
--EXPECTF--
Fatal error: Call to private G\Introspection\Repository::__construct() from invalid context in %s on line %d
