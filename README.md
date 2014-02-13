Pagination php class and php (C++) extention

Представлено два варианта Pagination-модуля. C++-extention & native-php Оба варианта рабочие. Идентичные интерфейсы, идентичное поведение.
##Установка
```
make
make install
make test
```

##Как пользоваться
Пример использования есть в исходниках: [https://github.com/valmat/myscrnav/blob/master/screennav_test.php](https://github.com/valmat/myscrnav/blob/master/screennav_test.php)

Создаем pagination-объект из расширения: 

    scr = new myScrNav($pageNom, $Count, '/url/to/page/'); 

Или из php класса:

    require 'php/class.screennav.php';
    $scr = new ScreenNav($pageNom, $Count, '/url/to/page/'); 

Задаем необходимые параметры:

    $scr->setInterval(10); // Сколько объектов на странице
    $scr->setPrefix('?qwe&part='); // URL prefix
    $scr->setPostfix('&prm=132'); // URL prefix
    $scr->setSpace('...'); // Разделитель блоков табов
    $scr->setCssName('newClassName'); // Имя класса css блока управления постраничным выводом
    $scr->setMidTab(15); // см. info.png
    $scr->setMaxTab(5); // см. info.png
    $scr->showCount(true); // Показывать ли общее количество элементов

![MidTab & MaxTab](https://raw2.github.com/valmat/myscrnav/master/info.png)
Кроме того доступны следующие методы для получения вычисленных данных:

    getStartPos() // Номер начального элемента на текущей странице (для выборки из БД)
    getLimitPos() // Длина списка элементов на странице на текущей странице (для выборки из БД)
    getPageCnt() // Количество страниц при разбивке на части
    getStartPos() // Номер (вычисленный) текущей страницы
    show()         // Возвращает собственно сам элемент управления постраничной разбивкой (html)

Т.е. можно управлять постраничной разбивкой и делать запросы к БД на основе этой постраничной разбивки. Внешний вид, разумеется, полностью настраивается через css

License BSD
