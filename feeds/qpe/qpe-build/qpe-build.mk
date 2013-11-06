#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#


QT_NAME:=Qt2
QTOPIA_NAME:=Qtopia
OPIE_NAME:=QtPalmtop

#1. development $(STAGING_DIR)/usr/lib/Qt
DEV_QTDIR:=$(STAGING_DIR)/usr/lib/$(QT_NAME)
DEV_QTOPIADIR:=$(DEV_QTDIR)/$(QTOPIA_NAME)
DEV_OPIEDIR:=$(DEV_QTDIR)/$(OPIE_NAME)

#2. install $(1)/opt/Qtopia
INSTALL_QTDIR:=/usr/lib
INSTALL_QTOPIADIR:=/opt/$(QTOPIA_NAME)
INSTALL_OPIEDIR:=/opt/$(OPIE_NAME)
## INSTALL_QTOPIADIR or INSTALL_OPIEDIR
QPE_INSTALLDIR:=

#3. install simulation
HOST_SLDIR:=$(TOPDIR)/bin/host

