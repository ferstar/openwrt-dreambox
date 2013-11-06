#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libopenobex
PKG_VERSION:=1.6
PKG_RELEASE:=1
PKG_MD5SUM:=485734c0e5a6c4a7bd697a0989b67a56

PKG_SOURCE:=openobex-$(PKG_VERSION)-Source.tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/openobex-$(PKG_VERSION)-Source
PKG_SOURCE_URL:=http://triq.net/obexftp/ \
	http://sourceforge.net/projects/openobex/files/openobex/1.6/

PKG_FIXUP:=libtool
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk


define Package/$(PKG_NAME)
  TITLE:= OpenOBEX
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=
  URL:=http://dev.zuckschwerdt.org/openobex
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  The overall goal of this project is to make an open source 
  implementation of the Object Exchange (OBEX) protocol. 
  OBEX is a session protocol and can best be described as a binary HTTP protocol.
endef

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib
TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include
TARGET_CXXFLAGS+=-I$(STAGING_DIR)/usr/include


define Build/InstallDev
	$(INSTALL_DIR) \
		$(1)/usr/include \
		$(1)/usr/lib \
		$(1)/usr/lib/pkgconfig/

	$(CP) $(PKG_INSTALL_DIR)/usr/include/openobex $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libopenobex.{a,so*,la} $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/openobex.pc $(1)/usr/lib/pkgconfig/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libopenobex.so* $(1)/usr/lib/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
