#!/bin/bash

#export TEST_PHP_EXECUTABLE=/usr/bin/php
#export TEST_PHP_CGI_EXECUTABLE=/usr/bin/php

#/usr/bin/php run-tests.php t/*.phpt -s testout -p /usr/bin/php
/usr/bin/php run-tests.php t/native/*.phpt t/ext/*.phpt -p /usr/bin/php

