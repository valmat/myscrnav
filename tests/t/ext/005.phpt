--TEST--
myScrNav set1-get data
--SKIPIF--
<?php if (!extension_loaded("my_Screen_Nav")) print "skip"; ?>
--FILEEOF--
<?php
require dirname(__FILE__) . '/../../include/set_get.php';

$scr = new myScrNav(44, 8456, 'http://some/url');

ScrNavTestSetGet::set1($scr);
ScrNavTestSetGet::get($scr);

--EXPECT--
array (
  'StartPos' => 924,
  'LimitPos' => 21,
  'PageCnt' => 403,
  'PageNo' => 44,
  'start' => 924,
  'lim' => 945,
)<div class="newClassName"> <a href="http://some/url">1</a> <space>...</space> <a href="http://some/url?qwe&part=25&prm=132">25</a> <space>...</space> <a href="http://some/url?qwe&part=40&prm=132">40</a>  <a href="http://some/url?qwe&part=41&prm=132">41</a>  <a href="http://some/url?qwe&part=42&prm=132">42</a>  <a href="http://some/url?qwe&part=43&prm=132">43</a>  <a href="http://some/url?qwe&part=44&prm=132">44</a>  <span>45</span>  <a href="http://some/url?qwe&part=46&prm=132">46</a>  <a href="http://some/url?qwe&part=47&prm=132">47</a>  <a href="http://some/url?qwe&part=48&prm=132">48</a>  <a href="http://some/url?qwe&part=49&prm=132">49</a>  <a href="http://some/url?qwe&part=50&prm=132">50</a> <space>...</space> <a href="http://some/url?qwe&part=65&prm=132">65</a> <space>...</space> <a href="http://some/url?qwe&part=403&prm=132">403</a> </div>