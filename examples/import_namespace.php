<?php
use Gir\Repository;

Repository::importNamespace('GLib');

$class = new Gir\Glib\Timer;

var_dump($class);

$class->start();
