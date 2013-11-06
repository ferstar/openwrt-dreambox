#! /bin/sh

export QTDIR=/opt/Qtopia
export QPEDIR=/opt/Qtopia
export KDEDIR=/opt/kde
export QT_PLUGIN_PATH=$QPEDIR/plugins
export QT_QWS_FONTDIR=$QPEDIR/lib/fonts

export QWS_MOUSE_PROTO="TPanel USB:/dev/input/mice"
#export QWS_MOUSE_PROTO="Tslib:/dev/touchscreen-1wire MouseMan:/dev/input/mice"
export QWS_KEYBOARD=TTY:/dev/tty1
export QWS_SW_CURSOR=1
export QWS_DISPLAY=:1

#export QWS_DISPLAY=Transformed:LinuxFb:mmWidth130:mmHeight100
#FB_SIZE=$(cat /sys/class/graphics/fb0/virtual_size)
#case "$FB_SIZE" in
#800,480)
#export QWS_DISPLAY="LinuxFb:mmWidth91:mmHeight53:1"
#;;
#480,272)
#export QWS_DISPLAY="LinuxFb:mmWidth76:mmHeight44:1"
#;;
#*)
#export QWS_DISPLAY="LinuxFb:mmWidth91:mmHeight53:1"
#;;
#esac

export PATH=$QTDIR/bin:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib:/usr/local/lib:$LD_LIBRARY_PATH
