<?php
use G\Introspection\Repository as Repo;
use G\Introspection\EnumInfo;

$repo = Repo::getDefault();

$repo->require('GLib');

$list = $repo->getInfos('GLib');

// write out our enums
foreach($list as $info) {
	if($info instanceof EnumInfo) {
		echo 'enum ', $info->getName(), ' {', PHP_EOL;
		$values = $info->getValues();
		foreach($values as $item) {
			echo '	', $item->getName(), ' = ', $item->getValue(), ',', PHP_EOL;
		}
		echo '};', PHP_EOL, PHP_EOL;
	}
}