#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libSDL_bgrab
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

PKG_SOURCE:=SDL_bgrab-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/SDL_bgrab-$(PKG_VERSION)
PKG_SOURCE_URL:=http://www.ferzkopp.net/Software/SDL_bgrab/
PKG_MD5SUM:=048c3f64dce43a242655642bbd01b269

PKG_FIXUP:=libtool
PKG_MACRO_PATHS:=acinclude
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Package/$(PKG_NAME)
  TITLE:=SDL framegrabber client library
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=SDL-$(SUBMENU)
  URL:=http://www.ferzkopp.net/Software/SDL_bgrab/
  DEPENDS:=+libSDL
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  SDL framegrabber client library.
  SDL convertion of libbgrab (a framegrabber lib from the same author).
endef

define Build/Configure
	$(call Build/Configure/Default, \
		--disable-sdltest \
		--with-sdl-exec-prefix="$(STAGING_DIR)/usr" \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/SDL $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/SDL/*.h \
		$(1)/usr/include/SDL/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/lib*.{a,la,so*} \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
