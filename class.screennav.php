<?php
/*
 * app ScreenNav
 * Печать, навигационной строки для листания экранов,
 * Расчет стартовой точки и лимита для постраничного вывода элементов
 */

 class ScreenNav {
    /**
     * Количество элементов на странице
     */
    private $interval = 20;
    
    /**
     * Максимальный отображаемый отступ
     */
    private $max_tab   = 6;
    
    /**
     * Размер среднего таба. Если 0, то не используется
     */
    private $mid_tab  = 10;
    
    /**
     * Имя класса css для навигационной линии
     */
    private $css_name = 'navline';
    
    /**
     * Строка для обозначения пропуска символов. Например ' ... '
     */
    private  $space   = '<space></space>';
    
    /**
     * Префикс, добавляемый для обозначения номера страниц
     */
    private $prefix   = '?part=';
    
    /**
     * Префикс, добавляемый для обозначения номера страниц
     */
    private $postfix  = '';
    
    /**
      * Номер начального элемента
      */
    private $startPos = 0;
    
    /**
      * Длина списка элементов
      */
    private $limitPos = 0;
    
    /**
      * Количество страниц при разбивке на части
      */
    private $pageCnt = 0;
    
    /**
      * Количество элементов
      */
    private $Count;
    
    /**
      * Номер страницы
      */
    private $pageNo  = 0;
    
    /**
      * Начало пути для текущего набора экранов. Со слешем в конце
      */
    private $curPath = 0;
    
    /**
      * Положение левого индекса
      */
    private $LeftInd = 0;
    
    /**
      * Положение правого индекса
      */
    private $RightInd = 0;
    
    /**
      * Показывать ли количество объектов
      */
    private $_showCount = false;
    
    /**
      * Был ли инициализирован объект (был ли произведен расчет)
      */
    private $inited = false;
    
    
    /*
     * function __construct
     * @param int $pageNo
     * @param int $Count
     * @param string $curPath
     */
    public function __construct($pageNo, $Count, $curPath) {
        $this->pageNo  = $pageNo;
        $this->Count   = $Count;
        $this->curPath = $curPath;
    }
        
    /*
     * Расчет основных параметров
     * function init
     */
    private function init() {
        if($this->inited) {
            return false;
        }
        $this->inited = true;
        
        if($this->interval*$this->pageNo >= $this->Count || $this->pageNo<0) {
            $this->pageNo = 0;
        }
        
        $startPos = $this->interval * $this->pageNo;
        $limitPos = ( ($this->interval*$this->pageNo + $this->interval - $this->Count)<0 )?$this->interval:($this->Count - $this->interval*$this->pageNo);
        
        $pageCnt=($this->Count - $this->Count%$this->interval)/$this->interval;
        if($this->Count%$this->interval>0) $pageCnt++;
        
        $LeftInd  = $this->pageNo - $this->max_tab;
        $RightInd = $this->pageNo + $this->max_tab;
        
        if($this->pageNo < $this->max_tab) {
            # длина правого отствупа
            $RightTab = $this->max_tab + $this->max_tab - $this->pageNo;
            $LeftInd  = 0;
            $RightInd = min($this->pageNo + $RightTab, $pageCnt-1);
        }elseif($pageCnt - 1 - $this->pageNo < $this->max_tab) {
            # длина левого отствупа
            $LeftTab  = $this->max_tab + $this->max_tab - $pageCnt + $this->pageNo;
            $LeftInd  = max(0, $this->pageNo - $LeftTab - 1);
            $RightInd = $pageCnt-1;
        }
        $RightInd = min($RightInd, $pageCnt-1);
        
        $this->startPos = $startPos;
        $this->limitPos = $limitPos;
        $this->pageCnt  = $pageCnt;
        $this->LeftInd  = $LeftInd;
        $this->RightInd = $RightInd;
    }
    
    /*
     * function show
     * @param void
     */
    public function show() {
        
        $this->init();
        
        # Если количество страниц меньше 2, навигационная линия не требуется
        if($this->pageCnt < 2)
            return '';
       
        # Левый край
        $rez =  '';
        if(1==$this->LeftInd) {
            $rez = $this->prnt(0);
        }elseif($this->LeftInd > 1){
            $rez = $this->prnt(0) . $this->space;
            if($this->mid_tab && ( $this->LeftInd > $this->mid_tab + $this->max_tab) ){
                $rez .= $this->prnt($this->LeftInd-$this->mid_tab) . $this->space;
            }
        }
        
        # Середина
        for($i=$this->LeftInd; $i < $this->pageNo; $i++) {
            $rez .= $this->prnt($i);
        }
        $rez .= $this->prnt($this->pageNo,true);
        for($i=$this->pageNo+1; $i <= $this->RightInd; $i++) {
            $rez .= $this->prnt($i);
        }
        
        # Правый край
        if(($this->pageCnt-2)==$this->RightInd) {
            $rez .= $this->prnt($this->pageCnt-1);
        }elseif($this->RightInd < ($this->pageCnt-1)){
            if($this->mid_tab && ( $this->RightInd < $this->pageCnt-1 - $this->mid_tab - $this->max_tab) ){
                $rez .= $this->space . $this->prnt($this->RightInd + $this->mid_tab);
            }
            $rez .= $this->space . $this->prnt($this->pageCnt-1);
        }
        
        return '<div class="'. $this->css_name .'">' .
                $rez .
                ($this->_showCount ? '<b>' . $this->Count . '</b>' : '') .
                '</div>';
    }
    
    /*
     * Печать ссылки для навигационной линии
     * function prnt
     */
    private function prnt($url, $isCur = false) {
        if(0==$url) {
            $capt = 1;
            $url = $this->curPath;
        } else {
            $capt = ++$url;
            $url = $this->curPath . $this->prefix . $url . $this->postfix;
        }
        
        if(!$isCur) {
            return ' <a href="'.$url.'">'.$capt.'</a> ';
        } else {
            return ' <span>'.$capt.'</span> ';
        }
    }
        
    /*
     * function setSpase
     * @param string $space
     */
    public function setSpace($space) {
        $this->space = $space;
    }    
    
    /*
     * function setCssname
     * @param string $css_name
     */
    public function setCssName($css_name) {
        $this->css_name = $css_name;
    }    
    
    /*
     * function setMidTab
     * @param int $mid_tab
     */
    public function setMidTab($mid_tab) {
        $this->mid_tab = $mid_tab;
    }    
    
    /*
     * function setMaxTab
     * @param int $max_tab
     */
    public function setMaxTab($max_tab) {
        $this->max_tab = $max_tab;
    }    
        
    /*
     * function setInterval
     * @param int $interval
     */
    public function setInterval($interval) {
        if($interval <=0 ) return false;
        $this->interval = $interval;
    }
        
    /*
     * function setPrefix
     * @param string $prefix
     */
    public function setPrefix($prefix) {
        $this->prefix = $prefix;
    }
        
    /*
     * function setPostfix
     * @param string $postfix
     */
    public function setPostfix($postfix) {
        $this->postfix = $postfix;
    }
        
    /*
     * function showCount
     * set showCount
     * @param bool $sc
     */
    public function showCount($sc) {
        $this->_showCount = (bool)$sc;
    }
        
    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    public function getStartPos() {
        $this->init();
        return $this->startPos;
    }    
        
    /*
     * Длина списка элементов
     * function getLimitPos
     * @return int
     */
    public function getLimitPos() {
        $this->init();
        return $this->limitPos;
    }    
        
    /*
     * Количество страниц при разбивке на части
     * function getPageCnt
     * @return int
     */
    public function getPageCnt() {
        $this->init();
        return $this->pageCnt;
    }    
        
    /*
     * Номер страницы
     * function getStartPos
     * @return int
     */
    public function getPageNo() {
        $this->init();
        return $this->pageNo;
    }    
        
    /*
     * Определяет и возвращает номер страницы
     * @return string
     */
    static function pageNo($var) {
        return (isset($_GET[$var]))?((int)$_GET[$var]-1):0;
    }
    
}
