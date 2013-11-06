#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#


include $(TOPDIR)/rules.mk


PKG_NAME:=tmake
PKG_VERSION:=1.13
PKG_RELEASE:=1
PKG_MD5SUM:=02909d15e5eee9d355b81d74b98a3bea

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.trolltech.com/freebies/tmake/

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk

define Package/$(PKG_NAME)
  TITLE:=tmake-1.13
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-host
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build
  URL:=ftp://ftp.trolltech.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  tmake-1.13.tar.gz
endef

define Build/Compile
	echo "actually not compile !"
endef

define Package/$(PKG_NAME)/install
	echo "actually not install !"
endef

define Build/InstallDev
	$(CP) ./files/linux-openwrt-g++/ $(PKG_BUILD_DIR)/lib/qws/

	$(INSTALL_DIR) $(DEV_QTDIR)/bin/
	$(CP) $(PKG_BUILD_DIR)/bin/*	$(DEV_QTDIR)/bin/
	$(CP) $(PKG_BUILD_DIR)/lib/	$(DEV_QTDIR)/bin/tmake-mkspecs/

# setTmakeEnv
	echo "export TMAKEDIR=$(DEV_QTDIR)/bin" > $(DEV_QTDIR)/setTmakeEnv
	echo "export TMAKEPATH=$(DEV_QTDIR)/bin/tmake-mkspecs/qws/linux-openwrt-g++" >>$(DEV_QTDIR)/setTmakeEnv
#	echo "export PATH=$TMAKEDIR:$$$$PATH" >>$(DEV_QTDIR)/setTmakeEnv

endef

$(eval $(call BuildPackage,$(PKG_NAME)))

