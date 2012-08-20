--TEST--
G\Introspection\EnumInfo->getValues();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
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

$list = $baseinfo->getValues();
$total = $baseinfo->getNumValues();

var_dump(count($list) == $total);

$correct = 0;
foreach($list as $info) {
     if($info instanceof ValueInfo) {
          $correct++;
     } else {
          var_dump($info);
     }
}

var_dump($correct == $total);

// too many args
try {
     $baseinfo->getValues(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(true)
bool(true)
G\Introspection\EnumInfo::getValues() expects exactly 0 parameters, 1 given
= DONE =