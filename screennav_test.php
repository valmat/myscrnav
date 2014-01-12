<?php
        
    header("Expires: Tue, 1 Jan 2000 00:00:00 GM"); // любая дата из прошлого
    header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); // текущая дата
    header("Cache-Control: no-store, no-cache, must-revalidate");
    header("Pragma: no-cache");
    header('Content-Type: text/html; charset=utf-8');
################################################################################
$memory_get_usage_start = (memory_get_usage()/1024);

function microtime_float(){
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
   }
$time_start = microtime_float();
################################################################################
    $MODE_CPP = true;
    $MODE_CPP = false;
    
    //$cnt = 9876543210;
    $cnt = 9876543210;

    
    if($MODE_CPP) {
        $scr = new myScrNav(myScrNav_pageNoGET('part'), $cnt, 'http://test/phpcpp/screennav_test.php');
    } else {
        require 'class.screennav.php';
        $scr = new ScreenNav(ScreenNav::pageNo('part'), $cnt, 'http://test/phpcpp/screennav_test.php');
    }

    $scr->setInterval(10);

    
?>
<html>
<head>
  <title>Test Screen nav</title>
  <meta http-equiv=Content-Type content="text/html; charset=utf-8"  />
  <style>
    
.navline{
  height:30px;
}
.navline a{
  border-radius:5px;
  -o-border-radius:5px;
  -moz-border-radius:5px;

  -webkit-box-shadow:0 1px 1px rgba(255, 255, 255, 0.4) inset, 0 -2px 2px rgba(0, 0, 0, 0.2) inset, 0 1px 2px #A0A0A0;
  -moz-box-shadow:0 1px 1px rgba(255, 255, 255, 0.4) inset, 0 -2px 2px rgba(0, 0, 0, 0.2) inset, 0 1px 2px #A0A0A0;
  -ms-box-shadow:0 1px 1px rgba(255, 255, 255, 0.4) inset, 0 -2px 2px rgba(0, 0, 0, 0.2) inset, 0 1px 2px #A0A0A0;
  -o-box-shadow:0 1px 1px rgba(255, 255, 255, 0.4) inset, 0 -2px 2px rgba(0, 0, 0, 0.2) inset, 0 1px 2px #A0A0A0;
  box-shadow:0 1px 1px rgba(255, 255, 255, 0.4) inset, 0 -2px 2px rgba(0, 0, 0, 0.2) inset, 0 1px 2px #A0A0A0;
  
 text-shadow: 0 1px 0 #FFF;
}
.navline a:link{
  color: #000;
  background:#FFF;
  border:1px solid #B7B7B7;
}
.navline a:visited{
  color: #752D93;
  background:#FFF;
  border:1px solid #B7B7B7;
}

.navline span, .navline a:active{
  color: #FFEF49; /*AFAFAF*/
  font-weight: bold;
  background:#5399D6;
  border:1px solid #948DFC;
  
  border-radius:5px;
  -o-border-radius:5px;
  -moz-border-radius:5px;
  
  -webkit-box-shadow:1px 1px 2px #073E6B inset;
  -moz-box-shadow:1px 1px 2px #073E6B inset;
  -ms-box-shadow:1px 1px 2px #073E6B inset;
  -o-box-shadow:1px 1px 2px #073E6B inset;
  box-shadow:1px 1px 2px #073E6B inset;
}
.navline span, .navline a, .navline space{
  padding:3px;
  min-width: 30px;
  display:block;
  float:left;
  text-align:center;
  margin-left:5px;
  -moz-border-radius: 7px;
}
.navline space:before{ content: "...";}
.navline space{
  color:#000;
  font-weight:bold;
}
  </style>
  </head>
<body>
<?php
    
    echo $scr->show();
    
    $start = $scr->getStartPos();
    $lim   = $start+$scr->getLimitPos();
    
    for($i = $start; $i<$lim; $i++) {
        //echo '<br>' . $arr[$i];
        echo '<br>' , $i+1;
    }
    
    
    
    
    
    
################################################################################

echo '<br>';
echo '<hr>memory usage: '.(memory_get_usage()/1024-$memory_get_usage_start) .'Kb<br>';
echo '<hr>memory peak_usage: '.(memory_get_peak_usage()/1024-$memory_get_usage_start) .'Kb<br>';

echo '<hr>time: '.( 1000*(microtime_float() - $time_start)*1000 ).' ms<br>';
/**/
?>
</body>
</html>