--TEST--
ScreenNav get data
--FILEEOF--
<?php
require dirname(__FILE__) . '/../../../php/class.screennav.php';
require dirname(__FILE__) . '/../../include/set_get.php';

$scr = new ScreenNav(5, 8456, 'http://some/url');

ScrNavTestSetGet::get($scr);

--EXPECT--
array (
  'StartPos' => 100,
  'LimitPos' => 20,
  'PageCnt' => 423,
  'PageNo' => 5,
  'start' => 100,
  'lim' => 120,
)<div class="navline"> <a href="http://some/url">1</a>  <a href="http://some/url?part=2">2</a>  <a href="http://some/url?part=3">3</a>  <a href="http://some/url?part=4">4</a>  <a href="http://some/url?part=5">5</a>  <span>6</span>  <a href="http://some/url?part=7">7</a>  <a href="http://some/url?part=8">8</a>  <a href="http://some/url?part=9">9</a>  <a href="http://some/url?part=10">10</a>  <a href="http://some/url?part=11">11</a>  <a href="http://some/url?part=12">12</a>  <a href="http://some/url?part=13">13</a> <space></space> <a href="http://some/url?part=23">23</a> <space></space> <a href="http://some/url?part=423">423</a> </div>