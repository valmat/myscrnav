--TEST--
myScrNav_pageNoGET()
--DESCRIPTION--
This test check myScrNav_pageNoGET('part') [part=0]
--SKIPIF--
<?php if (!extension_loaded("my_Screen_Nav")) print "skip"; ?>
--GET--
part=0
--FILE--
<?php
/*
if (defined('HHVM_VERSION')) {
    echo "HHVM is working\n";
} else {
    echo "HHVM is not working\n";
}
*/
echo var_dump(myScrNav_pageNoGET('part')) .PHP_EOL;
--EXPECT--
int(0)