--TEST--
G\Introspection\Repository->__construct();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

class MyRepo extends Gir {}

// constructor is private and instantiation will fail
$repo = new MyRepo();

?>
= DONE =
--EXPECTF--
Fatal error: Call to private G\Introspection\Repository::__construct() from invalid context in %s on line %d
