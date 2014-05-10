/**
 *  myscrnav.cpp
 *  app myScrNav
 *  
 *  Print the navigation line for turning screens (pagination),
 *  calculation of the start point and limit the output to a pager items.
 *  
 *  This extension is written in a style not familiar to C++ programmers,
 *  but usual for php programmers.
 *  I did it on purpose, to show how easy the program is written in php can be rewritten in php-cpp.
 *
 *  Печать, навигационной строки для листания экранов (pagination),
 *  Расчет стартовой точки и лимита для постраничного вывода элементов
 *
 *  Это расширение написано в стиле не привычном для программистов C++, 
 *  но привычном для программистов php.
 *  Я сделал это нарочно, что бы показать как легко программа, написанная на php, может быть переписана на php-cpp.
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/myscrnav
 */

#include <phpcpp.h>
#include <iostream>

using std::string;

class myScrNavApp : public Php::Base {
private:
    /**
     * The number of items per page
     */
    int interval = 20;
    
    /**
     * Maximum displayed offset
     */
    int max_tab  = 6;
    
    /**
     * The average size offset. If 0 is not used
     */
    int mid_tab  = 10;
    
    /**
     * The css class name for the navigation line
     */
    string css_name = "navline";
    
    /**
     * The string to denote missing symbols. For example ' ... '
     */
    string  space   = "<space></space>";
    
    /**
     * Prefix added to indicate page numbers
     */
    string prefix   = "?part=";
    
    /**
     * Postfix added to indicate page numbers
     */
    string postfix  = "";
    
    /**
      * The number of the first item
      */
    int startPos = 0;
    
    /**
      * The length of the list items on current page
      */
    int limitPos = 0;
    
    /**
      * Number of pagination pages
      */
    int pageCnt  = 0;
    
    /**
      * Number of items
      */
    long int Count;
    
    /**
      * Page number
      */
    int pageNo   = 0;
    
    /**
      * The beginning of the path for the current set of screens. With a slash at the end
      */
    string curPath  = "";
    
    /**
      * The position of the left index
      */
    int LeftInd  = 0;
    
    /**
      * The position of the right index
      */
    int RightInd = 0;
    
    /**
      * Whether to show the number of objects?
      */
    bool _showCount = false;
    
    /**
      * Was initialized, the object (was it calculated)?
      */
    bool _inited    = false;
    
public:
    
    myScrNavApp() {}
        
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
     * The number of the first element
     * function getStartPos
     * @return int
     */
    Php::Value getStartPos() {
    	this->init();
        return this->startPos;
    }    
        
    /*
     * The length of the list elements
     * function getLimitPos
     * @return int
     */
    Php::Value getLimitPos() {
    	this->init();
        return this->limitPos;
    }    
        
    /*
     * Количество страниц при разбивке на части
     * Number of pagination pages
     * function getPageCnt
     * @return int
     */
    Php::Value getPageCnt() {
    	this->init();
        return this->pageCnt;
    }    
        
    /*
     * Get page number
     * function getStartPos
     * @return int
     */
    Php::Value getPageNo() {
    	this->init();
        return this->pageNo;
    }
        
    /*
     * get the number of items per page
     * function getInterval
     * @return int
     */
    Php::Value getInterval() {
    	this->init();
        return this->interval;
    }
        
        
        
    /*
     * Returns html code of the navigation line
     * function show
     * @param void
     */
    Php::Value show() {
        
        this->init();
        
        string rez;
        int i;
        
        // If the number of pages is less than 2, the navigation line is not required
        if(this->pageCnt < 2)
            return "";
       
        // The left edge
        rez =  "";
        if(1==this->LeftInd) {
            rez = this->prnt(0);
        }else if(this->LeftInd > 1){
            rez = this->prnt(0) + this->space;
            if(this->mid_tab && ( this->LeftInd > this->mid_tab + this->max_tab) ){
                rez += this->prnt(this->LeftInd-this->mid_tab) + this->space;
            }
        }
        
        // Mid
        for(i=this->LeftInd; i < this->pageNo; i++) {
            rez += this->prnt(i);
        }
        rez += this->prnt(this->pageNo,true);
        for(i=this->pageNo+1; i <= this->RightInd; i++) {
            rez += this->prnt(i);
        }
        
        // The right edge
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
     * Calculation of the main parameters
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
            // the length of the right indentation
            int RightTab = this->max_tab + this->max_tab - this->pageNo;
            LeftInd  = 0;
            RightInd = std::min(this->pageNo + RightTab, pageCnt-1);
        }else if(pageCnt - 1 - this->pageNo < this->max_tab) {
            // the length of the left otstupat
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
     * Print the html-links for the navigation line
     * Helper function prnt
     * @param int iUrl     integer url
     * @param bool isCur   integer caption
     * @return std::string html-link
     */
    string prnt(int iUrl, bool isCur = false) {
        string link;
        // integer caption
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
     * Helper function _set_param
     * default string seter
     */
    void _set_param(const Php::Parameters &params, string &var) {
        if (params.size() == 0) {
            return;
        }
        var = params[0].stringValue();
    }

    /*
     * Helper function _set_param
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
 * Defines and returns the page number
 * @param string
 * @return string
 */
Php::Value GETpageNom(Php::Parameters &params) {
    if (params.size() == 0) {
        return 0;
    }
    auto var   = params[0].stringValue();
    //if ( Php::empty(Php::GET[var]) ) {
    //    return 0;
    //}

    //auto get   = Php::GET[var].numericValue(); --->  it seems it's still not working and requires debugging
                                                //     We'll go the other way:
    Php::Value G = Php::GLOBALS["_GET"][var];
    auto get   = G.numericValue();
    
    //long int rez = std::strtol( get.c_str(), nullptr, 10 );
    // (isset($_GET[var]))?((int)$_GET[var]-1):0;
    //return rez ? (rez-1) : 0;
    return get ? (get-1) : 0;
    
}



        
// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("my_Screen_Nav","1.2");
                
        /*
         *   Add our C++ class myScrNavApp in our expansion.
         *   In php it will be named `myScrNav`
         */
        Php::Class<myScrNavApp> customClass("myScrNav");

        /*
         *   add methods to `myScrNav`
         */
        customClass.method("__construct", &myScrNavApp::__construct, {
            Php::ByVal("pageNo",  Php::Type::Numeric),
            Php::ByVal("Count",   Php::Type::Numeric),
            Php::ByVal("curPath", Php::Type::String)
        });
        
        customClass.method("show", &myScrNavApp::show);
        
        //GETERS
        customClass.method("getStartPos", &myScrNavApp::getStartPos);
        customClass.method("getLimitPos", &myScrNavApp::getLimitPos);
        customClass.method("getPageCnt",  &myScrNavApp::getPageCnt);
        customClass.method("getPageNo",   &myScrNavApp::getPageNo);
        
        customClass.method("getInterval", &myScrNavApp::getInterval);
        
        
        // SETERS
        customClass.method("setSpace", &myScrNavApp::setSpace, {
            Php::ByVal("space", Php::Type::String)
        });
        customClass.method("setCssName", &myScrNavApp::setCssName, {
            Php::ByVal("css_name", Php::Type::String)
        });
        customClass.method("setPrefix", &myScrNavApp::setPrefix, {
            Php::ByVal("prefix", Php::Type::String)
        });
        customClass.method("setPostfix", &myScrNavApp::setPostfix, {
            Php::ByVal("postfix", Php::Type::String)
        });
        customClass.method("setMidTab", &myScrNavApp::setMidTab, {
            Php::ByVal("mid_tab", Php::Type::Numeric)
        });
        customClass.method("setMaxTab", &myScrNavApp::setMaxTab, {
            Php::ByVal("max_tab", Php::Type::Numeric)
        });
        customClass.method("setInterval", &myScrNavApp::setInterval, {
            Php::ByVal("interval", Php::Type::Numeric)
        });
        customClass.method("showCount", &myScrNavApp::showCount, {
            Php::ByVal("sc", Php::Type::Bool)
        });

        // add the class to the extension
        extension.add(customClass);
        /*
         *   The end of the class `myScrNav` definition
         */

        // pseudo-static function
        extension.add("myScrNav_pageNoGET", GETpageNom, {
            Php::ByVal("var", Php::Type::String)
        });
                
        // return the extension module
        return extension;
    }
}
