--TEST--
ScreenNav::pageNo()
--DESCRIPTION--
This test check ScreenNav::pageNo('part') [part=0]
--GET--
part=0
--FILE--
<?php
require '../../../php/class.screennav.php';
echo var_dump(ScreenNav::pageNo('part')) .PHP_EOL;
--EXPECT--
int(0)