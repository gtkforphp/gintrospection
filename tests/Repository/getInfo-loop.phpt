--TEST--
G\Introspection\Repository->getInfo(); in loop
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\BaseInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// get our total
$total = $repo->getNumInfos('GLib');

// counter
$found = 0;

for($i = 0; $i < $total; $i++) {
     $baseinfo = $repo->getInfo('GLib', 0);
     if($baseinfo instanceof BaseInfo) {
          $found++;
     }
}

var_dump($found == $total);
?>
= DONE =
--EXPECT--
bool(true)
= DONE =