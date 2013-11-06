#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qtopia-sl
PKG_VERSION:=2.1.1
PKG_RELEASE:=1
PKG_MD5SUM:=c2c028fad85e5584d9af04250d23104d

PKG_SOURCE:=qtopia-free-source-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.trolltech.com/qtopia/source/ \
	http://sourceforge.net/projects/qpe/files/QPE/qtopia/ \
	http://ftp.roedu.net/mirrors/ftp.trolltech.com/qtopia/source/
PKG_BUILD_DIR=$(BUILD_DIR)/qtopia-free-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk


define Package/$(PKG_NAME)
  TITLE:=qtopia for PC simulation
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-base
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build +qte2-sl +qt2 @!PACKAGE_qtopia
  URL:=http://qt.nokia.com/ ftp://ftp.trolltech.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  qtopia-free-2.1.1
endef


###########################
#export QTDIR=$(BUILD_DIR)/qt-2.3.10
export QTDIR=$(DEV_QTDIR)
export QPEDIR=$(PKG_BUILD_DIR)


define Build/Configure
	$(CP) ./files/linux-openwrt-g++/qmake-mkspecs/ $(PKG_BUILD_DIR)/mkspecs/qws/linux-openwrt-g++/
	$(CP) ./files/linux-openwrt-g++/configs/linux-openwrt-g++* $(PKG_BUILD_DIR)/src/configs/
	$(CP) ./files/linux-openwrt-g++/custom-linux-openwrt-g++.* $(PKG_BUILD_DIR)/src/libraries/qtopia/

	( cd $(PKG_BUILD_DIR)/ ; \
		echo yes | $(CONFIGURE_CMD) \
		-arch $(HOST_ARCH) \
		-platform linux-g++ \
		-xplatform linux-generic-g++ \
		-prefix $(PKG_INSTALL_DIR) \
		-release \
		-shared \
		-qconfig qpe \
		-displaysize 240x320 \
		-edition pda \
		-qvfb \
	)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)
	$(MAKE) -C $(PKG_BUILD_DIR) install
endef

define Build/InstallDev

	$(CP) $(PKG_BUILD_DIR)/include/ $(PKG_BUILD_DIR)/tmp-include/
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/tmp-include/tmp/tmp/tmp/
	( cd $(PKG_BUILD_DIR)/tmp-include/tmp/ ; \
	for file in ../qtopia/*.h ; do awk -F'"' '/^#include/{print $$$$2}' $$$$file | $(XARGS) -i $(CP) -v {} $$$$file ; done ; \
	)

	( cd $(PKG_BUILD_DIR)/tmp-include/tmp/tmp/ ; \
	for file in ../../qtopia/*/*.h ; do awk -F'"' '/^#include/{print $$$$2}' $$$$file | $(XARGS) -i $(CP) -v {} $$$$file ; done ; \
	)

	( cd $(PKG_BUILD_DIR)/tmp-include/tmp/tmp/tmp/ ; \
	for file in ../../../qtopia/*/*/*.h ; do awk -F'"' '/^#include/{print $$$$2}' $$$$file | $(XARGS) -i $(CP) -v {} $$$$file ; done ; \
	)

	( cd $(PKG_BUILD_DIR)/tmp-include/ ; \
	rm -rvf qpe qwizard.h tmp/ ; \
	ln -sv ./qtopia ./qpe ; \
	ln -sv ./qtopia/qwizard.h ./ ; \
	)

## 1. install qtopia headers and libs
	$(INSTALL_DIR) \
		$(DEV_QTOPIADIR)/include \
		$(DEV_QTOPIADIR)/lib
	$(CP) $(PKG_BUILD_DIR)/tmp-include/*	$(DEV_QTOPIADIR)/include/
	$(CP) $(PKG_BUILD_DIR)/lib/*		$(DEV_QTOPIADIR)/lib/

## 2. install qmake
#	$(INSTALL_DIR) $(DEV_QTDIR)/bin/
#	$(CP) $(PKG_BUILD_DIR)/bin/qmake	$(DEV_QTDIR)/bin/
#	$(CP) $(PKG_BUILD_DIR)/mkspecs/		$(DEV_QTDIR)/bin/qmake-mkspecs/

endef

define Package/$(PKG_NAME)/install
## ipkg
	$(CP) $(PKG_BUILD_DIR)/etc/ipkg.conf $(PKG_INSTALL_DIR)/etc/
	$(CP) $(PKG_BUILD_DIR)/bin/ipkg $(PKG_INSTALL_DIR)/bin/

## Home dir
	$(INSTALL_DIR) $(PKG_INSTALL_DIR)/apps/Home/
	$(CP) ./files/directory $(PKG_INSTALL_DIR)/apps/Home/.directory
	$(CP) ./files/Home.png $(PKG_INSTALL_DIR)/pics/
	
#################
## cp ipkg-install opt/Qtopia
	$(INSTALL_DIR) $(1)/$(INSTALL_QTOPIADIR)
	$(CP) $(PKG_INSTALL_DIR)/*	$(1)/$(INSTALL_QTOPIADIR)

	$(INSTALL_DIR) $(1)/usr/share/
	$(CP) $(PKG_BUILD_DIR)/etc/zoneinfo/ $(1)/usr/share/

## qtopia env
	$(INSTALL_DIR) $(1)/etc/
	$(CP) ./files/qtopia-env.sh $(1)/etc/
## qt4 demo
	$(INSTALL_DIR) $(1)/etc/ $(1)/usr/bin/
	$(CP) ./files/qt4-env.sh $(1)/etc/
	$(CP) ./files/qt4-demo $(1)/usr/bin/

## simulation
	$(INSTALL_DIR) $(HOST_SLDIR)
	$(CP) $(1)/* $(HOST_SLDIR)

	$(INSTALL_DIR) $(HOST_SLDIR)/bin/
	$(CP) $(DEV_QTDIR)/bin/qvfb $(HOST_SLDIR)/bin/
	$(CP) $(DEV_QTDIR)/bin/qvfb_skins $(HOST_SLDIR)/bin/
	$(CP) ./files/run-host-qtopia.sh $(HOST_SLDIR)/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
