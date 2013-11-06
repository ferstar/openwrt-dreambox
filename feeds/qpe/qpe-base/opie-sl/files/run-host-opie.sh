#!/bin/sh
#CURRENT DIR: $(TOPDIR)/bin/host

mkdir -pv root

export HOME=$PWD/root

export QTDIR=$PWD/opt/QtPalmtop
export OPIEDIR=$PWD/opt/QtPalmtop
export KDEDIR=$PWD/opt/kde
export QT_PLUGIN_PATH=$OPIEDIR/plugins
export QT_QWS_FONTDIR=$QTDIR/lib/fonts

export QWS_SW_CURSOR=1
export QWS_DISPLAY=QVFb:0
#export QWS_MOUSE_PROTO="TPanel USB:/dev/input/mice"
#export QWS_KEYBOARD=TTY:/dev/tty1
#export CAMERA_DEVICE=/dev/video1

export PATH=$OPIEDIR/bin:$PATH
export LD_LIBRARY_PATH=$OPIEDIR/lib:$QTDIR/lib:$LD_LIBRARY_PATH



QVFB_DIR=$PWD/bin
QVFB_SKIN=QtopiaPDA.skin

cd $QVFB_DIR/qvfb_skins/$QVFB_SKIN
$QVFB_DIR/qvfb -nocursor -qwsdisplay :0 -skin $QVFB_SKIN &
sleep 1

qpe

exit 0
