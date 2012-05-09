--TEST--
gir phpinfo information
--SKIPIF--
<?php
if(!extension_loaded('gir')) die('skip - GIR extension not available');
?>
--FILE--
<?php
ob_start();
phpinfo(INFO_MODULES);
$data = ob_get_clean();
$data = explode("\n\n", $data);
foreach($data as $key => $info) {
	if ($info === 'gir') {
		break;
	}
}
$data = $data[$key + 1];
var_dump($data);
?>
--EXPECTF--
string(22) "gir support => enabled"
