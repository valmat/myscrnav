/**
 *  myscrnav.cpp
 *  app myScrNav
 *  Печать, навигационной строки для листания экранов (pageinator),
 *  Расчет стартовой точки и лимита для постраничного вывода элементов
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/myscrnav
 */

#include <phpcpp.h>

using namespace std;

class myScrNavApp : public Php::Base {
private:
    /**
     * Количество элементов на странице
     */
    int interval;
    
    /**
     * Максимальный отображаемый отступ
     */
    int max_tab;
    
    /**
     * Размер среднего таба. Если 0, то не используется
     */
    int mid_tab;
    
    /**
     * Имя класса css для навигационной линии
     */
    string css_name;
    
    /**
     * Строка для обозначения пропуска символов. Например ' ... '
     */
    string  space;
    
    /**
     * Префикс, добавляемый для обозначения номера страниц
     */
    string prefix;
    
    /**
     * Префикс, добавляемый для обозначения номера страниц
     */
    string postfix;
    
    /**
      * Номер начального элемента
      */
    int startPos;
    
    /**
      * Длина списка элементов
      */
    int limitPos;
    
    /**
      * Количество страниц при разбивке на части
      */
    int pageCnt;
    
    /**
      * Количество элементов
      */
    long int Count;
    
    /**
      * Номер страницы
      */
    int pageNo;
    
    /**
      * Начало пути для текущего набора экранов. Со слешем в конце
      */
    string curPath;
    
    /**
      * Положение левого индекса
      */
    int LeftInd;
    
    /**
      * Положение правого индекса
      */
    int RightInd;
    
    /**
      * Показывать ли количество объектов
      */
    bool _showCount;
    
    /**
      * Был ли инициализирован объект (был ли произведен расчет)
      */
    bool _inited;
    
public:
    
    myScrNavApp() {
        // int
        this->interval = 20;
        this->max_tab  = 6;
        this->mid_tab  = 10;
        this->startPos = 0;
        this->limitPos = 0;
        this->pageCnt  = 0;
        this->pageNo   = 0;
        this->LeftInd  = 0;
        this->RightInd = 0;
        
        // string
        this->css_name = "navline";
        this->space    = "<space></space>";
        this->prefix   = "?part=";
        this->postfix  = "";
        this->curPath  = "";

        // bool
        this->_showCount = false;
        this->_inited    = false;
    }
        
    /*
     * function __construct
     * @param int $pageNo
     * @param int $Count
     * @param string $curPath
     */
    virtual void __construct(Php::Parameters &params) {
        if (params.size() != 3) {
            throw Php::Exception("Requires 3 parameters");
            this->pageNo  = 0;
            this->Count   = 0;
            this->curPath = "";
            return;
        }
        this->pageNo  = params[0].numericValue();
        this->Count   = params[1].numericValue();
        this->curPath = params[2].stringValue();
    }
        
    virtual ~myScrNavApp() {}
    virtual void __destruct() {}
    
    // SETERS
    /*
     * function setSpace
     * @param string $space
     */
    void setSpace(Php::Parameters &params) {
        _set_param(params, this->space);
    }    
    
    /*
     * function setCssName
     * @param string $css_name
     */
    void setCssName(Php::Parameters &params) {
        _set_param(params, this->css_name);
    }    
    
    /*
     * function setMidTab
     * @param int $mid_tab
     */
    void setMidTab(Php::Parameters &params) {
        _set_param(params, this->mid_tab);
    }    
    
    /*
     * function setMaxTab
     * @param int $max_tab
     */
    void setMaxTab(Php::Parameters &params) {
        _set_param(params, this->max_tab);
    }    
        
    /*
     * function setInterval
     * @param int $interval
     */
    void setInterval(Php::Parameters &params) {
        if (params.size() == 0 || (int)params[0] <= 0) {
            return;
        }
        this->interval = params[0];
    }
        
    /*
     * function setPrefix
     * @param string $prefix
     */
    void setPrefix(Php::Parameters &params) {
        _set_param(params, this->prefix);
    }
        
    /*
     * function setPostfix
     * @param string $postfix
     */
    void setPostfix(Php::Parameters &params) {
        _set_param(params, this->postfix);
    }

    /*
     * function showCount
     * set showCount
     * @param bool $sc
     */
    void showCount(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->_showCount = (bool)params[0];
    }
        
    // GETERS
    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    Php::Value getStartPos() {
    	this->init();
        return this->startPos;
    }    
        
    /*
     * Длина списка элементов
     * function getLimitPos
     * @return int
     */
    Php::Value getLimitPos() {
    	this->init();
        return this->limitPos;
    }    
        
    /*
     * Количество страниц при разбивке на части
     * function getPageCnt
     * @return int
     */
    Php::Value getPageCnt() {
    	this->init();
        return this->pageCnt;
    }    
        
    /*
     * Номер страницы
     * function getStartPos
     * @return int
     */
    Php::Value getPageNo() {
    	this->init();
        return this->pageNo;
    }
        
    /*
     * Номер страницы
     * function getInterval
     * @return int
     */
    Php::Value getInterval() {
    	this->init();
        return this->interval;
    }
        
        
        
    /*
     * function show
     * @param void
     */
    Php::Value show() {
        
        this->init();
        
        string rez;
        int i;
        
        // Если количество страниц меньше 2, навигационная линия не требуется
        if(this->pageCnt < 2)
            return "";
       
        // Левый край
        rez =  "";
        if(1==this->LeftInd) {
            rez = this->prnt(0);
        }else if(this->LeftInd > 1){
            rez = this->prnt(0) + this->space;
            if(this->mid_tab && ( this->LeftInd > this->mid_tab + this->max_tab) ){
                rez += this->prnt(this->LeftInd-this->mid_tab) + this->space;
            }
        }
        
        // Середина
        for(i=this->LeftInd; i < this->pageNo; i++) {
            rez += this->prnt(i);
        }
        rez += this->prnt(this->pageNo,true);
        for(i=this->pageNo+1; i <= this->RightInd; i++) {
            rez += this->prnt(i);
        }
        
        // Правый край
        if((this->pageCnt-2)==this->RightInd) {
            rez += this->prnt(this->pageCnt-1);
        }else if(this->RightInd < (this->pageCnt-1)) {
            if(this->mid_tab && ( this->RightInd < this->pageCnt-1 - this->mid_tab - this->max_tab) ){
                rez += this->space + this->prnt(this->RightInd + this->mid_tab);
            }
            rez += this->space + this->prnt(this->pageCnt-1);
        }
        

        return this->_showCount ? (
        			"<div class=\"" + this->css_name + "\">" + 
        			rez + 
        			"<b>" + std::to_string(this->Count) + "</b>" +
        			"</div>"
	        	) : (
	        		"<div class=\"" + this->css_name + "\">" + rez + "</div>"
	        	);
    }
        
        
private:
        
    /*
     * Расчет основных параметров
     * function init
     */
    void init() {
        if(this->_inited) {
            return;
        }
        this->_inited = true;

        if(this->interval*this->pageNo >= this->Count || this->pageNo < 0) {
            this->pageNo = 0;
        }
        
        int startPos = this->interval * this->pageNo;
        int limitPos = ( (this->interval*this->pageNo + this->interval - this->Count)<0 )?this->interval:(this->Count - this->interval*this->pageNo);
        
        int pageCnt = (this->Count - this->Count%this->interval)/this->interval;
        if(this->Count%this->interval>0) pageCnt++;
        
        int LeftInd  = this->pageNo - this->max_tab;
        int RightInd = this->pageNo + this->max_tab;
        
        if(this->pageNo < this->max_tab) {
            // длина правого отствупа
            int RightTab = this->max_tab + this->max_tab - this->pageNo;
            LeftInd  = 0;
            RightInd = std::min(this->pageNo + RightTab, pageCnt-1);
        }else if(pageCnt - 1 - this->pageNo < this->max_tab) {
            // длина левого отствупа
            int LeftTab  = this->max_tab + this->max_tab - pageCnt + this->pageNo;
            LeftInd  = std::max(0, this->pageNo - LeftTab - 1);
            RightInd = pageCnt-1;
        }
        RightInd = std::min(RightInd, pageCnt-1);
        
        this->startPos = startPos;
        this->limitPos = limitPos;
        this->pageCnt  = pageCnt;
        this->LeftInd  = LeftInd;
        this->RightInd = RightInd;
    }
        
    /*
     * Печать ссылки для навигационной линии
     * function prnt
     */
    string prnt(int iUrl, bool isCur = false) {
        string link;
        int iCapt;
        if(0 == iUrl) {
            iCapt = 1;
            link = this->curPath;
        } else {
            iCapt = ++iUrl;
            link = this->curPath + this->prefix + std::to_string(iUrl) + this->postfix;
        }
        
        if(!isCur) {
            return " <a href=\"" + link + "\">" + std::to_string(iCapt) + "</a> ";
        } else {
            return " <span>" + std::to_string(iCapt) + "</span> ";
        }
    }

    /*
     * function _set_param
     * default string seter
     */
    void _set_param(const Php::Parameters &params, string &var) {
        if (params.size() == 0) {
            return;
        }
        var = params[0].stringValue();
    }

    /*
     * function _set_param
     * default int seter
     */
    void _set_param(const Php::Parameters &params, int &var) {
        if (params.size() == 0 || (int)params[0] < 0) {
            return;
        }
        var = params[0].numericValue();
    }

};

        
/*
 * Определяет и возвращает номер страницы
 * @param string
 * @return string
 */
Php::Value GETpageNom(Php::Parameters &params) {
    if (params.size() == 0) {
        return 0;
    }
    string var   = params[0].stringValue();
    string get   = Php::globals["_GET"][var];
    long int rez = std::strtol( get.c_str(), nullptr, 10 );
    // (isset($_GET[var]))?((int)$_GET[var]-1):0;
    return rez ? (rez-1) : 0;
}

// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("my_Screen_Nav","1.0");
        
        // add the custom class ot the extension
        extension.add("myScrNav", Php::Class<myScrNavApp>({
                Php::Public("__construct", Php::Method<myScrNavApp>(&myScrNavApp::__construct), {
                    Php::ByVal("pageNo",  Php::numericType),
                    Php::ByVal("Count",   Php::numericType),
                    Php::ByVal("curPath", Php::stringType)
                }),
                
                Php::Public("show", Php::Method<myScrNavApp>(&myScrNavApp::show)),
                
                //GETERS
                Php::Public("getStartPos", Php::Method<myScrNavApp>(&myScrNavApp::getStartPos)),
                Php::Public("getLimitPos", Php::Method<myScrNavApp>(&myScrNavApp::getLimitPos)),
                Php::Public("getPageCnt",  Php::Method<myScrNavApp>(&myScrNavApp::getPageCnt)),
                Php::Public("getPageNo", Php::Method<myScrNavApp>(&myScrNavApp::getPageNo)),
                
                Php::Protected("getInterval", Php::Method<myScrNavApp>(&myScrNavApp::getInterval),{}),
                
                
                // SETERS
                Php::Public("setSpace", Php::Method<myScrNavApp>(&myScrNavApp::setSpace), {
                    Php::ByVal("space", Php::stringType)
                }),
                Php::Public("setCssName", Php::Method<myScrNavApp>(&myScrNavApp::setCssName), {
                    Php::ByVal("css_name", Php::stringType)
                }),
                Php::Public("setPrefix", Php::Method<myScrNavApp>(&myScrNavApp::setPrefix), {
                    Php::ByVal("prefix", Php::stringType)
                }),
                Php::Public("setPostfix", Php::Method<myScrNavApp>(&myScrNavApp::setPostfix), {
                    Php::ByVal("postfix", Php::stringType)
                }),
                Php::Public("setMidTab", Php::Method<myScrNavApp>(&myScrNavApp::setMidTab), {
                    Php::ByVal("mid_tab", Php::numericType)
                }),
                Php::Public("setMaxTab", Php::Method<myScrNavApp>(&myScrNavApp::setMaxTab), {
                    Php::ByVal("max_tab", Php::numericType)
                }),
                Php::Public("setInterval", Php::Method<myScrNavApp>(&myScrNavApp::setInterval), {
                    Php::ByVal("interval", Php::numericType)
                }),
                Php::Public("showCount", Php::Method<myScrNavApp>(&myScrNavApp::showCount), {
                    Php::ByVal("sc", Php::boolType)
                })
                
                
            }));
                
                
            extension.add("myScrNav_pageNoGET", GETpageNom, {
                Php::ByVal("var", Php::stringType)
            });
                
                
        // return the extension module
        return extension.module();
    }
}
