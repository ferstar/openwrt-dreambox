#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libetpan
PKG_VERSION:=2012-09-01
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_SOURCE_SUBDIR)
PKG_SOURCE_URL:=git://github.com/dinhviethoa/libetpan.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=aff935754dd2b256db95e28f276e80e69de2f8a8

PKG_FIXUP:=libtool
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk


define Package/$(PKG_NAME)
  TITLE:=Mail Framework for C Language
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=
  URL:=http://www.etpan.org/ https://github.com/dinhviethoa/libetpan.git
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  The purpose of this mail library is to provide a portable, 
  efficient framework for different kinds of mail access. 
  When using the drivers interface, the interface is the same 
  for all kinds of mail access, remote and local mailboxes.
endef

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib
TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include
TARGET_CXXFLAGS+=-I$(STAGING_DIR)/usr/include


define Build/InstallDev
	$(INSTALL_DIR) \
		$(1)/usr/include \
		$(1)/usr/lib \
		$(1)/usr/bin

	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libetpan*.{a,so*,la} $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/libetpan-config $(1)/usr/bin/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libetpan.so* $(1)/usr/lib/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
