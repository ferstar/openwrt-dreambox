#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libSDL_ttf
PKG_VERSION:=2.0.11
PKG_RELEASE:=2

PKG_SOURCE:=SDL_ttf-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/SDL_ttf-$(PKG_VERSION)
PKG_SOURCE_URL:=http://www.libsdl.org/projects/SDL_ttf/release/
PKG_MD5SUM:=61e29bd9da8d245bc2471d1b2ce591aa

PKG_FIXUP:=libtool
PKG_MACRO_PATHS:=acinclude
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Package/$(PKG_NAME)
  TITLE:=ttf library for Simple DirectMedia Layer
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=SDL-$(SUBMENU)
  URL:=http://www.libsdl.org/projects/SDL_ttf/
  DEPENDS:=+libSDL +libpthread +libfreetype +zlib $(ICONV_DEPENDS)
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  SDL_ttf is a sample library for Simple DirectMedia Layer.
endef

define Build/Configure
	$(call Build/Configure/Default, \
		--disable-sdltest \
		--with-sdl-exec-prefix="$(STAGING_DIR)/usr" \
	)
	rm $(PKG_BUILD_DIR)/glfont.c
	echo "void main(){}" >$(PKG_BUILD_DIR)/glfont.c
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/SDL $(1)/usr/lib/pkgconfig
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/SDL/SDL_ttf.h \
		$(1)/usr/include/SDL/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libSDL_ttf*.{a,la,so*} \
		$(1)/usr/lib/
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/* \
		$(1)/usr/lib/pkgconfig/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libSDL_ttf*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
