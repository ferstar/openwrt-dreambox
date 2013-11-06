#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qt4map
PKG_VERSION:=1.0
PKG_RELEASE:=1


include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qmake.mk

define Package/$(PKG_NAME)
  TITLE:=qt4-mitab-mif-map
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-apps
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+mitab +Qt4
  URL:=http://blog.chinaunix.net/uid/11153816.html
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  Author:   hugerat <njjqs115@jlonline.com>
  Blog:
            http://blog.chinaunix.net/uid/11153816.html
            http://blog.csdn.net/zy_emb
  detail:
            http://blog.chinaunix.net/uid-11153816-id-2903476.html
            http://blog.csdn.net/zy_emb/article/details/6213486
            http://www.arm9home.net/read.php?tid-10310.html
endef

TARGET_LDFLAGS+=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib
TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include -I$(STAGING_DIR)/usr/include/mitab

define Build/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
	$(call Build/Configure/Qmake,qt-map)
endef

define Build/Compile
	$(call Build/Compile/Default)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
