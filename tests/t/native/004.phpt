--TEST--
ScreenNav set-get data
--FILEEOF--
<?php
require dirname(__FILE__) . '/../../../php/class.screennav.php';
require dirname(__FILE__) . '/../files/set_get.php';

$scr = new ScreenNav(5, 8456, 'http://some/url');

ScrNavTestSetGet::set($scr);
ScrNavTestSetGet::get($scr);

--EXPECT--
array (
  'StartPos' => 105,
  'LimitPos' => 21,
  'PageCnt' => 403,
  'PageNo' => 5,
  'start' => 105,
  'lim' => 126,
)<div class="navline"> <a href="http://some/url">1</a>  <a href="http://some/url?qwe&part=2&prm=132">2</a>  <a href="http://some/url?qwe&part=3&prm=132">3</a>  <a href="http://some/url?qwe&part=4&prm=132">4</a>  <a href="http://some/url?qwe&part=5&prm=132">5</a>  <span>6</span>  <a href="http://some/url?qwe&part=7&prm=132">7</a>  <a href="http://some/url?qwe&part=8&prm=132">8</a>  <a href="http://some/url?qwe&part=9&prm=132">9</a>  <a href="http://some/url?qwe&part=10&prm=132">10</a>  <a href="http://some/url?qwe&part=11&prm=132">11</a> <space></space> <a href="http://some/url?qwe&part=26&prm=132">26</a> <space></space> <a href="http://some/url?qwe&part=403&prm=132">403</a> <b>8456</b></div>