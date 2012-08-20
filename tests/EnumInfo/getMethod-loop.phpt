--TEST--
G\Introspection\EnumInfo->getMethod(); in loop
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\FunctionInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'DateMonth');

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