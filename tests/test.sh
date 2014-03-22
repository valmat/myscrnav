#!/bin/bash
#
#  It is intended to run the command "make test"
#
#  @author valmat <ufabiz@gmail.com>
#  @github https://github.com/valmat/myscrnav
#


THIS=`basename $0`
    
function print_help() {
    echo "Use: $THIS -e <file> [options...]"
    echo "Options:"
    echo "  -p <php>     Specify PHP executable to run (default: /usr/bin/php)."
    echo "  -e <file>    Name of test extension (default: extfortest.so)."
    echo "  -w <file>    Write a list of all failed tests to <file>."
    echo "  -a <file>    Same as -w but append rather then truncating <file>."
    echo "  -d foo=bar   Pass -d option to the php binary (Define INI entry foo"
    echo "               with value 'bar')."
    echo "  -g <opt>     Comma separated list of groups to show during test run"
    echo "               (possible values: PASS, FAIL, XFAIL, SKIP, BORK, WARN, LEAK, REDIRECT)."
    echo "  -m           Test for memory leaks with Valgrind."
    echo "  -s <file>    Write output to <file>."
    echo "  -x           Sets 'SKIP_SLOW_TESTS' environmental variable."
    echo "  -o           Cancels sets 'SKIP_ONLINE_TESTS' (default set)."
    echo "  -q           Quiet, no user interaction (same as environment NO_INTERACTION)."
    echo "  -v           Verbose mode."
    echo "  -h           This Help."
    echo
    exit;
}

PHP_BIN="/usr/bin/php"
# options list
SCR_OPT=""
# SKIP_ONLINE_TESTS == true
OFFLINE=1
EXT_NAME=""

while getopts ":p:e:w:a:d:g:ms:xoqvh" opt ;
do
    case $opt in
        p)
            PHP_BIN=$OPTARG;
            ;;
        e)
            EXT_NAME=$OPTARG;
            ;;
        w)
            SCR_OPT="$SCR_OPT -w $OPTARG"
            ;;
        a)
            SCR_OPT="$SCR_OPT -a $OPTARG"
            ;;
        d)
            SCR_OPT="$SCR_OPT -d $OPTARG"
            ;;
        g)
            SCR_OPT="$SCR_OPT -g $OPTARG"
            ;;
        s)
            SCR_OPT="$SCR_OPT -s $OPTARG"
            ;;
        m)
            SCR_OPT="$SCR_OPT -m"
            ;;
        x)
            SCR_OPT="$SCR_OPT -x"
            ;;
        o)
            # SKIP_ONLINE_TESTS == false
            OFFLINE=0
            ;;
        q)
            SCR_OPT="$SCR_OPT -q"
            ;;
        v)
            SCR_OPT="$SCR_OPT -v"
            ;;
        h)
            print_help
            ;;
        *)
            echo "wrong option -$OPTARG";
            echo "";
            print_help
            ;;
    esac
done

# To check requested option -e
if [ ! $EXT_NAME ]; then
    echo "Use: $THIS -e <file> [options...]"
    echo "Option -e is requested"
    exit;
fi

# default offline mode
if [ 1 = $OFFLINE ]; then
    SCR_OPT="$SCR_OPT --offline"
fi

# To check whether our extension installed
if [ ! $(php --ini | grep "$EXT_NAME.ini") ]; then
    SCR_OPT="$SCR_OPT -d extension=$EXT_NAME.so"
fi

# The file list of the tests that will be launched
TEST_FILES=`find ./t -type f -name "*.phpt"`


# Create a local copy of the directory with the extension for run without installation
./prepare.sh $EXT_NAME

# A list of all additional options
SCR_OPT="$SCR_OPT -d extension_dir=$PWD/ext_dir"

# run tests
$PHP_BIN run-tests.php $SCR_OPT -p "$PHP_BIN" $TEST_FILES


