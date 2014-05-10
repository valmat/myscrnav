<?php
        
    header("Expires: Tue, 1 Jan 2000 00:00:00 GM");
    header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
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
    //$MODE_CPP = false;
    
    $cnt = 5681;
    
    if($MODE_CPP) {
        $scr = new myScrNav(myScrNav::pageNo('part'), $cnt, 'http://test/phpcpp/myScrNav/screennav_test.php');
    } else {
        require 'php/class.screennav.php';
        $scr = new ScreenNav(ScreenNav::pageNo('part'), $cnt, 'http://test/phpcpp/myScrNav/screennav_test.php');
    }

    $scr->setInterval(21);			// Сколько объектов на странице
    $scr->setPrefix('?qwe&part=');		// URL prefix
    $scr->setPostfix('&prm=132');		// URL prefix
    //$scr->setSpace('<space>...</space>');	// Разделитель блоков табов
    //$scr->setCssName('newClassName');		// Имя класса css блока управления постраничным выводом
    $scr->setMidTab(15);			// см. info.png
    $scr->setMaxTab(5);				// см. info.png
    $scr->showCount(true);			// Показывать ли общее количество элементов
    
 
?>
<html>
<head>
  <title>Test Screen nav</title>
  <meta http-equiv=Content-Type content="text/html; charset=utf-8"  />
  <link href="css.css" rel=Stylesheet />
  </head>
<body>
<?php
    
    echo '<hr><pre>';
    var_export(array(
	'StartPos' => $scr->getStartPos(),
	'LimitPos' => $scr->getLimitPos(),
	'PageCnt' => $scr->getPageCnt(),
	'PageNo' => $scr->getPageNo(),
    ));
    echo '</pre><hr>';
    
    
    echo $scr->show();
    
    $start = $scr->getStartPos();
    $lim   = $start+$scr->getLimitPos();
    
    for($i = $start; $i<$lim; $i++) {
        echo '<br>' , $i+1;
    }
    
    //unset($scr);
    
    
################################################################################

echo '<br>';
echo '<hr>time: '.ceil( 1000*(microtime_float() - $time_start)*1000 ).' MicroSec<br>';

echo '<hr>memory usage: '.ceil( (memory_get_usage()/1024-$memory_get_usage_start)*10)/10 .'Kb<br>';
echo '<hr>memory peak_usage: '.ceil( (memory_get_peak_usage()/1024-$memory_get_usage_start)*10)/10 .'Kb<br>';

?>
</body>
</html>