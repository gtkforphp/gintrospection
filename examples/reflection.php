<?php
use Gir\Repository;

Repository::importNamespace('GLib');

Reflection::export (new ReflectionExtension('gir'));
