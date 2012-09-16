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
cd ${bindir}/../../lib

ln -s libQtCore.so.4.6.3 libQtCore.so.4
ln -s libQtGui.so.4.6.3 libQtGui.so.4
ln -s libQtNetwork.so.4.6.3 libQtNetwork.so.4
ln -s libQtSql.so.4.6.3 libQtSql.so.4
ln -s libQtXml.so.4.6.3 libQtXml.so.4
ln -s libQtScript.so.4.6.3 libQtScript.so.4

cd ../bin
chmod 775 autopark
chmod 775 autopark.bin
chmod 775 updater
chmod 775 updater.bin

desctop_path=`kde-config --userpath desktop`

cd ../

#Creating KDE desktop shortcut
echo "[Desktop Entry]
Comment[uk]=Господарська діяльність підприємств, що займаються пасажирськими перевезеннями
Comment=Господарська діяльність підприємств, що займаються пасажирськими перевезеннями
Exec=$PWD/bin/updater
GenericName[uk]=Господарська діяльність підприємств, що займаються пасажирськими перевезеннями
GenericName=Господарська діяльність підприємств, що займаються пасажирськими перевезеннями
Icon=$PWD/install/linux/bus-32x32.png
MimeType=
Name[uk]=Автопарк менеджер
Name=Автопарк менеджер
Path=$PWD/bin
StartupNotify=true
Terminal=false
TerminalOptions=
Type=Application
X-DBUS-ServiceName=
X-DBUS-StartupType=
X-KDE-SubstituteUID=false
X-KDE-Username=" > "$desctop_path/Автопарк менеджер"

