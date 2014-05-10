--TEST--
myScrNav_pageNoGET()
--DESCRIPTION--
This test check myScrNav_pageNoGET('part') [part=5]
--SKIPIF--
<?php if (!extension_loaded("my_Screen_Nav")) print "skip"; ?>
--FILE--
<?php
$_GET['part']=5;
echo var_dump(myScrNav::pageNo('part')) .PHP_EOL;
--EXPECT--
int(4)