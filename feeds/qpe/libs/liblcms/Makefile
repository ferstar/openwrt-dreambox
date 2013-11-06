#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=liblcms
PKG_VERSION:=1.19
PKG_RELEASE:=1
PKG_MD5SUM:=8af94611baf20d9646c7c2c285859818

PKG_SOURCE:=lcms-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/lcms-$(PKG_VERSION)
PKG_SOURCE_URL:=http://sourceforge.net/projects/lcms/files/lcms/$(PKG_VERSION)/
PKG_BUILD_PARALLEL:=1

PKG_FIXUP:=libtool
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=little cms color engine
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=+zlib +libjpeg +libtiff
  URL:=http://www.littlecms.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Build/InstallDev
	$(INSTALL_DIR) \
		$(1)/usr/include \
		$(1)/usr/lib

	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/usr/bin \
		$(1)/usr/lib \
		$(1)/usr/man

	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/man/* $(1)/usr/man/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
