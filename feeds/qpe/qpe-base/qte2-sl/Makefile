#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qte2-sl
PKG_VERSION:=2.3.10
PKG_RELEASE:=1
PKG_MD5SUM:=1f7ad30113afc500cab7f5b2f4dec0d7

PKG_SOURCE:=qt-embedded-$(PKG_VERSION)-free.tar.gz
PKG_SOURCE_URL:=ftp://ftp.trolltech.com/qt/source/
PKG_BUILD_DIR=$(BUILD_DIR)/qt-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk


define Package/$(PKG_NAME)
  TITLE:=qte2 for PC simulation
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-base
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build @!PACKAGE_qte2
  URL:=http://qt.nokia.com/ ftp://ftp.trolltech.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  qte2 for PC simulation
endef


###########################
export QTDIR=$(PKG_BUILD_DIR)

ifeq ($(CONFIG_PACKAGE_opie-sl),y)
QCONFIG_FILE:=qconfig-qpe-opie.h
else
QCONFIG_FILE:=qconfig-qpe-qtopia.h
endif

define Build/Configure
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/bin/
	$(CP) ./files/uic $(PKG_BUILD_DIR)/bin/
	$(CP) ./files/configs/linux-openwrt-g++* $(PKG_BUILD_DIR)/configs/

	echo "QCONFIG_FILE=$(QCONFIG_FILE)"
	$(CP) ./files/$(QCONFIG_FILE) $(PKG_BUILD_DIR)/src/tools/qconfig-qpe.h

	( cd $(PKG_BUILD_DIR)/ ; \
		echo yes | $(CONFIGURE_CMD) \
		-platform linux-generic-g++ \
		-release \
		-shared \
		-qconfig qpe \
		-depths 4,8,16,32 \
		-no-xft \
		-gif \
		-system-jpeg \
		-system-libpng \
		-system-zlib \
		-qvfb \
	)

endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

define Build/InstallDev
## 0. libpng, zlib and freetype source codes needed by qtopia-free-2.1.1/util/pngscale
	$(INSTALL_DIR) $(DEV_QTDIR)/src/3rdparty/
	$(CP) $(PKG_BUILD_DIR)/src/3rdparty/*	$(DEV_QTDIR)/src/3rdparty/
	$(CP) $(PKG_BUILD_DIR)/.buildopts	$(DEV_QTDIR)/

## 1. install qte2 headers, libs and qte tools "moc"
	$(INSTALL_DIR) $(DEV_QTDIR)/bin/
	$(CP) $(PKG_BUILD_DIR)/bin/{moc,uic}	$(DEV_QTDIR)/bin/

	$(INSTALL_DIR) \
		$(DEV_QTDIR)/include \
		$(DEV_QTDIR)/lib

	$(CP) $(PKG_BUILD_DIR)/include/*	$(DEV_QTDIR)/include/
	$(CP) $(PKG_BUILD_DIR)/lib/*		$(DEV_QTDIR)/lib/

endef

# install in $QPE/lib/, while Qt4 in /usr/lib/
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/$(QPE_INSTALLDIR)/lib
	$(CP) $(PKG_BUILD_DIR)/lib/*.so*	$(1)/$(QPE_INSTALLDIR)/lib/
	$(CP) $(PKG_BUILD_DIR)/lib/fonts	$(1)/$(QPE_INSTALLDIR)/lib/

## simulation
	$(INSTALL_DIR) $(HOST_SLDIR)
	$(CP) $(1)/* $(HOST_SLDIR)
endef
##

$(eval $(call BuildPackage,$(PKG_NAME)))
