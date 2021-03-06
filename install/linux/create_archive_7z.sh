#!/bin/sh

makeAbsolute() {
    case "$1" in
	/*)
	    # already absolute, return it
	    echo "$1"
	    ;;
	*)
	    # relative, prepend $2 made absolute
	    echo `makeAbsolute "$2" "$PWD"`/"$1" | sed 's,/\.$,,'
	    ;;
    esac
}

if test -L "$0"; then
    # Try readlink(1)
    readlink=`type readlink 2>/dev/null` || readlink=
    if test -n "$readlink"; then
	# We have readlink(1), so we can use it
	me=`readlink -nf "$0"`
    else
	# No readlink(1), so let's try ls -l
	me=`ls -l "$0" | sed 's/^.*-> //'`
	base=`dirname "$0"`
	me=`makeAbsolute "$me" "$base"`
    fi
else
    me="$0"
fi

bindir=`dirname "$me"`
cd ${bindir}/../..
archiveName=install/linux/autopark.sfx
if [ -f $archiveName ]
  then
    echo "It exists"
    rm $archiveName
fi
install/linux/7z a -sfx $archiveName @install/linux/arch_files_list.txt -y
