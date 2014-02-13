--TEST--
ScreenNav set-get1 data
--FILEEOF--
<?php
require dirname(__FILE__) . '/../../../php/class.screennav.php';
require dirname(__FILE__) . '/../files/set_get.php';

$scr = new ScreenNav(41, 0, 'http://some/url');
ScrNavTestSetGet::set($scr);
ScrNavTestSetGet::get1($scr);

--EXPECT--
array (
  'StartPos' => 0,
  'LimitPos' => 0,
  'PageCnt' => 0,
  'PageNo' => 0,
  'start' => 0,
  'lim' => 0,
)