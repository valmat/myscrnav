Pagination php class and php (C++) extension

Presents two variants of Pagination module. C++-extension & native-php. Both variants are workable. Identical interfaces, identical behavior.
##Installation
First you need to install the library [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)
Perhaps if the compilation will fail or will not pass the tests, you will need to switch to a state in which the extension works exactly.
So, to install PHP-CPP:
```
git clone git@github.com:CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
git checkout 5852a65e876421b118de9e76a9f83388be590690
make
make test
sudo make install
```
Then:
```
make
make test
make install
```
##How to use
A usage example is the source code: [https://github.com/valmat/myscrnav/blob/master/screennav_test.php](https://github.com/valmat/myscrnav/blob/master/screennav_test.php)

Create the pagination-object of myScrNav from extension:

    scr = new myScrNav($pageNom, $Count, '/url/to/page/'); 

Or from php class:

    require 'php/class.screennav.php';
    $scr = new ScreenNav($pageNom, $Count, '/url/to/page/'); 

Specify the necessary parameters:

```php
$scr->setInterval(10);            // How many objects on the page
$scr->setPrefix('?qwe&part=');    // URL prefix
$scr->setPostfix('&prm=132');     // URL prefix
$scr->setSpace('...');            // Splitter blocks tabs
$scr->setCssName('newClassName'); // The css class name control unit paged output
$scr->setMidTab(15);              // see info.png
$scr->setMaxTab(5);               // see info.png
$scr->showCount(true);            // Whether to show the total number of items?
```
![MidTab & MaxTab](https://raw2.github.com/valmat/myscrnav/master/info.png)
Additionally, the following methods are available to obtain calculated data:
```php
getStartPos() // The number of the first item on the current page (to fetch from database)
getLimitPos() // The length of the list elements on the current page (to fetch from database)
getPageCnt()  // Number of pagination pages
getPageNo()   // The current number (calculated) of the current page
show()        // Returns the control-element to the paginal laying (html)
```
I.e. you can control the paginal laying out and make queries to the database on the basis of this pagination. Appearance, of course, fully customizable via css.

--

**License BSD**
