/**
 *  myscrnav.cpp
 *  app myScrNav
 *  Печать, навигационной строки для листания экранов,
 *  Расчет стартовой точки и лимита для постраничного вывода элементов
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat
 */


/**
 *  Default Cpp libraries
 */
 
#include <string>
#include <iostream>

//#include <typeinfo>

/**
 *  Our own library.
 */
#include <phpcpp.h>

/**
 *  Namespace to use
 */
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
    int Count;
    
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
    
public:
    
    myScrNavApp(/*Php::Parameters &params*/) {
        // int
        interval = 20;
        max_tab  = 6;
        mid_tab  = 10;
        startPos = 0;
        limitPos = 0;
        pageCnt  = 0;
        pageNo   = 0;
        LeftInd  = 0;
        RightInd = 0;
        
        // string
        css_name = "navline";
        space    = "<space></space>";
        prefix   = "?part=";
        postfix  = "&prm=132";
        //curPath  = new string("");
        curPath  = "";
        
        
        std::cout << "myScrNavApp::myScrNavApp" << std::endl;
        std::cout << css_name << std::endl;
    }
        
    /*
     * function __construct
     * @param int $pageNo
     * @param int $Count
     * @param string $curPath
     */
    virtual void __construct(Php::Parameters &params) {
        
        cout << "myScrNavApp::__construct" << endl;
        
        if (params.size() != 3) {
            throw Php::Exception("Requires 3 parameters");
            this->pageNo  = 0;
            this->Count   = 0;
            this->curPath = "";
            return;
        }
        this->pageNo  = params[0];
        this->Count   = params[1];
        this->curPath = (new Php::Value(params[2]))->stringValue();
    }
        
    ~myScrNavApp() {
        std::cout << "myScrNavApp::~myScrNavApp" << std::endl;
        //string output = env.call("strtoupper","test in lowercase");
        //cout << "output: " << output << endl;
    }
        
    void myMethod(Php::Parameters &params) {
        std::cout << "myMethod is called." << std::endl;
        //std::cout << "_x: " << _x << std::endl;
        //_x = params[0];
        //std::cout << "New _x=" << _x << std::endl;
    }
    
    virtual void __destruct() {}
    
    // SETERS
    /*
     * function setSpace
     * @param string $space
     */
    void setSpace(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->space = (new Php::Value(params[0]))->stringValue();
    }    
    
    /*
     * function setCssName
     * @param string $css_name
     */
    void setCssName(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->css_name = (new Php::Value(params[0]))->stringValue();
    }    
    
    /*
     * function setMidTab
     * @param int $mid_tab
     */
    void setMidTab(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->mid_tab = params[0];
    }    
    
    /*
     * function setMaxTab
     * @param int $max_tab
     */
    void setMaxTab(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->max_tab = params[0];
    }    
        
    /*
     * function setInterval
     * @param int $interval
     */
    void setInterval(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->interval = params[0];
    }
        
    /*
     * function setPrefix
     * @param string $prefix
     */
    void setPrefix(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->prefix = (new Php::Value(params[0]))->stringValue();
    }
        
    /*
     * function setPostfix
     * @param string $postfix
     */
    void setPostfix(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        this->postfix = (new Php::Value(params[0]))->stringValue();
    }
        
    // GETERS
    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    Php::Value getStartPos() {
        return this->startPos;
    }    
        
    /*
     * Длина списка элементов
     * function getLimitPos
     * @return int
     */
    Php::Value getLimitPos() {
        return this->limitPos;
    }    
        
    /*
     * Количество страниц при разбивке на части
     * function getPageCnt
     * @return int
     */
    Php::Value getPageCnt() {
        return this->pageCnt;
    }    
        
    /*
     * Номер страницы
     * function getStartPos
     * @return int
     */
    Php::Value getPageNo() {
        return this->pageNo;
    }
    
    
    
        
    /*
     * Номер страницы
     * function getInterval
     * @return int
     */
    Php::Value getInterval() {
        return this->interval;
    }
    

};


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
                Php::Public("myMethod", Php::Method<myScrNavApp>(&myScrNavApp::myMethod), {
                    Php::ByVal("newX", Php::numericType)
                }),
                Php::Public("__construct", Php::Method<myScrNavApp>(&myScrNavApp::__construct), {
                    Php::ByVal("pageNo",  Php::numericType),
                    Php::ByVal("Count",   Php::numericType),
                    Php::ByVal("curPath", Php::stringType)
                }),
                
                //GETERS
                Php::Public("getStartPos", Php::Method<myScrNavApp>(&myScrNavApp::getStartPos)),
                Php::Public("getLimitPos", Php::Method<myScrNavApp>(&myScrNavApp::getLimitPos)),
                Php::Public("getPageCnt",  Php::Method<myScrNavApp>(&myScrNavApp::getPageCnt)),
                Php::Public("getPageNo", Php::Method<myScrNavApp>(&myScrNavApp::getPageNo)),
                
                Php::Public("getInterval", Php::Method<myScrNavApp>(&myScrNavApp::getInterval),{}),
                
                
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
                })
                
                
            }));
                
        // return the extension module
        return extension.module();
    }
}
