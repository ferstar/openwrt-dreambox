#
# Copyright (C) 2012 OpenWrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libts
PKG_VERSION:=2012.02.12
PKG_RELEASE:=1

PKG_SOURCE:=tslib-$(PKG_VERSION).tar.bz2
PKG_SOURCE_SUBDIR:=tslib-$(PKG_VERSION)
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_SOURCE_SUBDIR)
PKG_SOURCE_URL:=https://github.com/kergoth/tslib.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=f6c499a523bff845ddd57b1d96c9d1389f0df17b


PKG_INSTALL:=1
PKG_FIXUP:=libtool

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=tslib is an abstraction layer for touchscreen panel events
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=@!LINUX_2_4
  URL:=http://tslib.berlios.de/ https://github.com/kergoth/tslib
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  tslib is an abstraction layer for touchscreen panel events,
  as well as a filter stack for the manipulation of those events.
  Examples of implemented filters include jitter smoothing and the calibration transform.
endef

define Build/Configure
	(cd $(PKG_BUILD_DIR); ./autogen.sh; echo "ac_cv_func_malloc_0_nonnull=yes" > cache-file.cache );
	$(call Build/Configure/Default, --cache-file=cache-file.cache)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/
endef

# default, if other TARGETs, then use the default
TSLIB_CONFDIR:=s3c24xx

ifeq ($(CONFIG_TARGET_s3c24xx),y)
TSLIB_CONFDIR:=s3c24xx
endif
ifeq ($(CONFIG_TARGET_s5pc1xx),y)
TSLIB_CONFDIR:=s5pc1xx
endif

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/ts $(1)/usr/bin $(1)/etc
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/ts_* $(1)/usr/bin/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/ts/*.so* $(1)/usr/lib/ts/

	$(if $(TSLIB_CONFDIR),$(CP) ./files/$(TSLIB_CONFDIR)/* $(1)/etc/ )

endef

$(eval $(call BuildPackage,$(PKG_NAME)))
