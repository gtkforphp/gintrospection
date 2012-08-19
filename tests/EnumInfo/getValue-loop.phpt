--TEST--
G\Introspection\EnumInfo->getValue(); in loop
--SKIPIF--
<?php
if(!extension_loaded('gi')) die('skip - GI extension not available');
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\ValueInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'DateMonth');

$total = $baseinfo->getNumValues();

// counter
$found = 0;

for($i = 0; $i < $total; $i++) {
     $valueinfo = $baseinfo->getValue($i);
     if($valueinfo instanceof ValueInfo) {
          $found++;
     }
}

var_dump($found == $total);
?>
= DONE =
--EXPECT--
bool(true)
= DONE =