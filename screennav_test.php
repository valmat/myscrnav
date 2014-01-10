<?php
        
    header("Expires: Tue, 1 Jan 2000 00:00:00 GM"); // любая дата из прошлого
    header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); // текущая дата
    header("Cache-Control: no-store, no-cache, must-revalidate");
    header("Pragma: no-cache");
    header('Content-Type: text/html; charset=utf-8');
    
    
    $cnt = 55654;
    $arr = array();
    for($i = 0; $i<$cnt; $i++) {
        //$arr[] = mt_rand(1,5000);
        $arr[] = $i+1;
    }

################################################################################
$memory_get_usage_start = (memory_get_usage()/1024);

function microtime_float(){
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
   }
$time_start = microtime_float();
################################################################################
    
    
    $a = new myScrNav(1,2,"Hellow my world");
    
    $a->getStartPos();
    $a->getLimitPos();
    $a->getPageCnt();
    $a->getStartPos();
    //$a->getInterval();



    
    $a->setInterval(156);
    
    echo $a->getInterval();
    echo $a->getPageNo();
    
    /*
    require 'class.screennav.php';
    
    $scr = new ScreenNav(ScreenNav::pageNo('part'), $cnt, 'http://test/phpcpp/screennav_test.php');
    
    
    var_export($scr);
    
    echo $scr->show();
    
    $start = $scr->getStartPos();
    $lim   = $start+$scr->getLimitPos();
    
    for($i = $start; $i<$lim; $i++) {
        echo '<br>' . $arr[$i];
    }
    */
    
    
    
    
    
    
################################################################################

echo '<br>';
echo '<hr>memory usage: '.(memory_get_usage()/1024-$memory_get_usage_start) .'Kb<br>';
echo '<hr>memory peak_usage: '.(memory_get_peak_usage()/1024-$memory_get_usage_start) .'Kb<br>';

echo '<hr>time: '.( 1000*(microtime_float() - $time_start)*1000 ).' ms<br>';
/**/
