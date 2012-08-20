--TEST--
G\Introspection\Repository->getInfos();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;
use G\Introspection\BaseInfo;

$repo = Gir::getDefault();

// repo not loaded? well that's bad mojo
try {
     $repo->getInfo('nothing', 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

$list = $repo->getInfos('GLib');
$total = $repo->getNumInfos('GLib');

var_dump(count($list) == $total);

$correct = 0;
foreach($list as $baseinfo) {
     if($baseinfo instanceof BaseInfo) {
          $correct++;
     } else {
          var_dump($baseinfo);
     }
}

var_dump($correct == $total);

// too few args
try {
     $repo->getInfos();
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// too many args
try {
     $repo->getInfos(1, 1, 1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}

// string or cast to string only arg 1
try {
     $repo->getInfos(array());
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
Namespace nothing is not currently loaded
bool(true)
bool(true)
G\Introspection\Repository::getInfos() expects exactly 1 parameter, 0 given
G\Introspection\Repository::getInfos() expects exactly 1 parameter, 3 given
G\Introspection\Repository::getInfos() expects parameter 1 to be string, array given
= DONE =