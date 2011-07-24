--TEST--
Gir\Repository->__construct
--SKIPIF--
<?php
if(!extension_loaded('gir')) die('skip - GIR extension not available');
?>
--FILE--
<?php
class Foo extends TestClass {
     public function __construct() {
	}
}
//$class = new TestClass;
//$class = new Foo;


?>
--EXPECTF--
