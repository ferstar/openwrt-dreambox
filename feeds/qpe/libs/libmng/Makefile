#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libmng
PKG_VERSION:=1.0.10
PKG_RELEASE:=1
PKG_MD5SUM:=eaf1476a3bb29f6190bca660e6abef16

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=http://sourceforge.net/projects/libmng/files/libmng-devel/$(PKG_VERSION)/

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=A MNG format files handling library
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=+zlib +libjpeg +liblcms
  URL:=www.libmng.com/MNGsuite/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

MAKE_FLAGS += \
	prefix="$(PKG_INSTALL_DIR)" \
	ZLIBLIB="$(STAGING_DIR)/usr/lib" \
	ZLIBINC="$(STAGING_DIR)/usr/include" \
	JPEGLIB="$(STAGING_DIR)/usr/lib" \
	JPEGINC="$(STAGING_DIR)/usr/include" \
	LCMSLIB="$(STAGING_DIR)/usr/lib" \
	LCMSINC="$(STAGING_DIR)/usr/include"

define Build/Configure
	$(CP) $(PKG_BUILD_DIR)/makefiles/makefile.linux $(PKG_BUILD_DIR)/Makefile
endef

define Build/InstallDev
	$(INSTALL_DIR) \
		$(1)/usr/include \
		$(1)/usr/lib

	$(CP) $(PKG_INSTALL_DIR)/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/lib/* $(1)/usr/lib/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/lib/*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
