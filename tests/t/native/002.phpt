--TEST--
ScreenNav::pageNo()
--DESCRIPTION--
This test check ScreenNav::pageNo('part') [part=5]
--GET--
part=5
--FILE--
<?php
require '../../../php/class.screennav.php';
echo var_dump(ScreenNav::pageNo('part')) .PHP_EOL;
--EXPECT--
int(4)