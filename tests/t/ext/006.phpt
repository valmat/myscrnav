--TEST--
myScrNav get1 data
--SKIPIF--
<?php if (!extension_loaded("my_Screen_Nav")) print "skip"; ?>
--FILEEOF--
<?php
require dirname(__FILE__) . '/../files/set_get.php';

$scr = new myScrNav(-44, 8456, 'http://some/url');

ScrNavTestSetGet::get1($scr);

--EXPECT--
array (
  'StartPos' => 0,
  'LimitPos' => 20,
  'PageCnt' => 423,
  'PageNo' => 0,
  'start' => 0,
  'lim' => 20,
)