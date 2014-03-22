#!/bin/bash
#
#  do not run this script manualy.
#  This script is intended to be run from a script test.sh
#  Create a local copy of the directory with the extension for run tests without installation
#
#  @author valmat <ufabiz@gmail.com>
#  @github https://github.com/valmat/myscrnav
#


# Local directory in which to copy the links to all installed extensions
EXTDLOC=ext_dir

# to check whether specified the extension name as parameter
if [ $1 ]
then
    SO="$1.so"
else
    echo "Required extension name"
    echo "Use: $0 <extension_name>"
    exit;
fi

# a directory of extensions already installed in the operating system
EXTDIR=$(php-config --extension-dir)

mkdir -p "./$EXTDLOC"

# To copy references for all extensions to the local directory
for LIBFILE in `find $EXTDIR -type f -or -type l -name "*.so"`; do

    BN=$(basename $LIBFILE)
    NF="$PWD/$EXTDLOC/$BN"
    
    # if still no exist
    if [ ! -L $NF ];
    then
        if [ -L $LIBFILE ];
        then
            cp --no-dereference $LIBFILE $NF
        else
            ln -s $LIBFILE $NF
        fi
    else
        :
    fi;
done

# current extension
if [ ! -L "$PWD/$EXTDLOC/$SO" ]
then
    CUR_EXT_PATH=$(cd "$PWD/../cpp" && echo $PWD)
    ln -s "$CUR_EXT_PATH/$SO" "$PWD/$EXTDLOC/$SO"
fi
    
