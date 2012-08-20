--TEST--
G\Introspection\UnionInfo->getField(); in loop
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\FieldInfo;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// has more then one count
$baseinfo = $repo->findByName('GLib', 'Mutex');

$total = $baseinfo->getNumFields();

// counter
$found = 0;

for($i = 0; $i < $total; $i++) {
     $valueinfo = $baseinfo->getField($i);
     if($valueinfo instanceof FieldInfo) {
          $found++;
     }
}

var_dump($found == $total);
?>
= DONE =
--EXPECT--
bool(true)
= DONE =