--TEST--
G\Introspection\StructInfo->getMethod(); in loop
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\FunctionInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'Mutex');

$total = $baseinfo->getNumMethods();

// counter
$found = 0;

for($i = 0; $i < $total; $i++) {
     $valueinfo = $baseinfo->getMethod($i);
     if($valueinfo instanceof FunctionInfo) {
          $found++;
     }
}

var_dump($found == $total);
?>
= DONE =
--EXPECT--
bool(true)
= DONE =