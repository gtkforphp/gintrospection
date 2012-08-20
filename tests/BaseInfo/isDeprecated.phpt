--TEST--
G\Introspection\BaseInfo->isDeprecated();
--SKIPIF--
<?php
include __DIR__ . '/../skipif.inc';
?>
--FILE--
<?php
use G\Introspection\Repository as Gir;

$repo = Gir::getDefault();

// load the repo - we'll do GLib since it SHOULD be around
$repo->require('GLib');

// get the Timer baseinfo
$baseinfo = $repo->findByName('GLib', 'Timer');

var_dump($baseinfo->isDeprecated());

// get a known deprecated symbol
$baseinfo = $repo->findByName('GLib', 'unicode_canonical_decomposition');

var_dump($baseinfo->isDeprecated());

// too many args
try {
     $baseinfo->isDeprecated(1);
} catch (InvalidArgumentException $e) {
    echo $e->getMessage(), PHP_EOL;
}
?>
= DONE =
--EXPECT--
bool(false)
bool(true)
G\Introspection\BaseInfo::isDeprecated() expects exactly 0 parameters, 1 given
= DONE =