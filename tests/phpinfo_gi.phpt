--TEST--
gi phpinfo information
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
ob_start();
phpinfo(INFO_MODULES);
$data = ob_get_clean();
$data = explode("\n\n", $data);
foreach($data as $key => $info) {
	if ($info === 'gi') {
		break;
	}
}
$data = $data[$key + 1];
var_dump($data);
?>
--EXPECTF--
string(40) "Gobject Introspection support => enabled"
