--TEST--
Gir\Repository->import
--SKIPIF--
<?php
if(!extension_loaded('gir')) die('skip - GIR extension not available');
?>
--FILE--
<?php
use Gir\Repository;

$repo = new Repository;
$repo->import('GObject');
//Reflection::export (new ReflectionExtension('gir'));
?>
--EXPECTF--
