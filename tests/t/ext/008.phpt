--TEST--
myScrNav set-get1 data
--SKIPIF--
<?php if (!extension_loaded("my_Screen_Nav")) print "skip"; ?>
--FILEEOF--
<?php
require dirname(__FILE__) . '/../../include/set_get.php';

$scr = new myScrNav(41, 0, 'http://some/url');
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