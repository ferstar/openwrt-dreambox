#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libSDL_rtf
PKG_VERSION:=0.1.0
PKG_RELEASE:=1

PKG_SOURCE:=SDL_rtf-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/SDL_rtf-$(PKG_VERSION)
PKG_SOURCE_URL:=http://www.libsdl.org/projects/SDL_rtf/release/
PKG_MD5SUM:=fe36733167b5c89f128414f32612121a

PKG_FIXUP:=libtool
PKG_MACRO_PATHS:=acinclude
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Package/$(PKG_NAME)
  TITLE:=Display simple Rich Text Format (RTF) files for SDL
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=SDL-$(SUBMENU)
  URL:=http://www.libsdl.org/projects/SDL_rtf/
  DEPENDS:=+libSDL +libSDL_ttf
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  This library allows you to display simple 
  Rich Text Format (RTF) files in SDL applications.
endef

define Build/Configure
	$(call Build/Configure/Default, \
		--disable-sdltest \
		--enable-SDL_ttf \
		--with-sdl-exec-prefix="$(STAGING_DIR)/usr" \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/SDL $(1)/usr/lib/pkgconfig
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/SDL/SDL_rtf.h \
		$(1)/usr/include/SDL/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libSDL_rtf*.{a,la,so*} \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libSDL_rtf*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
