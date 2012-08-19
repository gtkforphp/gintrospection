<?php
use G\Introspection\Repository as Repo;
use G\Introspection\EnumInfo;
use G\Introspection\StructInfo;
use G\Introspection\UnionInfo;

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
	} elseif (($info instanceof StructInfo) ||
			 ($info instanceof UnionInfo)){
		echo 'class ', $info->getName(), ' {', PHP_EOL;
		$fields = $info->getFields();
		foreach($fields as $field) {
			echo 'public $', $field->getName(), ';', PHP_EOL;
		}
		echo PHP_EOL;
		$methods = $info->getMethods();
		foreach($methods as $method) {
			echo 'public function ', $method->getName(), '(){}', PHP_EOL;
		}
		echo '}', PHP_EOL, PHP_EOL;
	}
}