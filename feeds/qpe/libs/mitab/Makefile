#
# Copyright (C) 2012 OpenWrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mitab
PKG_VERSION:=1.7.0
PKG_RELEASE:=1

PKG_SOURCE:=mitab-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/mitab-$(PKG_VERSION)
PKG_SOURCE_URL:=http://mitab.maptools.org/dl
PKG_MD5SUM:=6a9e1f6926100058088553664a13b9ca

include $(INCLUDE_DIR)/package.mk


define Package/$(PKG_NAME)
  TITLE:=MITAB MapInfo Library
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=libs-$(SUBMENU)
  DEPENDS:=
  URL:=http://mitab.maptools.org
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  MITAB is an Open Source (i.e. Free!) C++ library 
  to read and write MapInfo .TAB (binary) and .MIF/MID files.
  It is based on the OGR library which is an implementation 
  of the Open GIS Consortium Simple Feature specification.
endef

define Build/Compile
	$(call Build/Compile/Default)
endef

define Build/InstallDev
	$(INSTALL_DIR) \
		$(1)/usr/include/mitab \
		$(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/mitab/*.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/mitab/*.h $(1)/usr/include/mitab/
	$(CP) $(PKG_BUILD_DIR)/cpl/*.h $(1)/usr/include/mitab/
	$(CP) $(PKG_BUILD_DIR)/ogr/*.h $(1)/usr/include/mitab/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/mitab/*.so* $(1)/usr/lib/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))

