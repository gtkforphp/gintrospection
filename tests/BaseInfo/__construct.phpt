--TEST--
G\Introspection\BaseInfo->__construct();
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\BaseInfo;

// constructor is private and instantiation will fail
$info = new BaseInfo();

?>
= DONE =
--EXPECTF--
Fatal error: Call to private G\Introspection\BaseInfo::__construct() from invalid context in %s on line %d
