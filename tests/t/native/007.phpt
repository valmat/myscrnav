--TEST--
ScreenNav get1 data
--FILEEOF--
<?php
require dirname(__FILE__) . '/../../../php/class.screennav.php';
require dirname(__FILE__) . '/../files/set_get.php';

$scr = new ScreenNav(45282944, 82, 'http://some/url');

ScrNavTestSetGet::get1($scr);

--EXPECT--
array (
  'StartPos' => 0,
  'LimitPos' => 20,
  'PageCnt' => 5,
  'PageNo' => 0,
  'start' => 0,
  'lim' => 20,
)