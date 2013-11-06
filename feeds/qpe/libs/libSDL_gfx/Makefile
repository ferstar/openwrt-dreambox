#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libSDL_gfx
PKG_VERSION:=2.0.23
PKG_RELEASE:=1

PKG_SOURCE:=SDL_gfx-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/SDL_gfx-$(PKG_VERSION)
PKG_SOURCE_URL:=http://www.ferzkopp.net/Software/SDL_gfx-2.0/
PKG_MD5SUM:=fcc3c4f2d1b4943409bf7e67dd65d03a

PKG_FIXUP:=libtool
PKG_MACRO_PATHS:=acinclude
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Package/$(PKG_NAME)
  TITLE:=SDL graphics drawing supporting functions
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=SDL-$(SUBMENU)
  URL:=http://www.ferzkopp.net/ http://www.ferzkopp.net/Software/SDL_gfx-2.0/
  DEPENDS:=+libSDL
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  The SDL_gfx library evolved out of the SDL_gfxPrimitives code which
  provided basic drawing routines such as lines, circles or polygons for 
  SDL Surfaces and adding a couple other useful functions for zooming 
  images for example and doing basic image processing on byte arrays.

  The current components of the SDL_gfx library are:
  - Graphic Primitives (SDL_gfxPrimitives.h, SDL_gfxPrimitives.c)
  - Rotozoomer (SDL_rotozoom.h, SDL_rotozoom.c)
  - Framerate control (SDL_framerate.h, SDL_framerate.c)
  - MMX image filters (SDL_imageFilter.h, SDL_imageFilter.c)
  - Custom Blit functions (SDL_gfxBlitFunc.h, SDL_gfxBlitFunc.c)
  - Build-in 8x8 Font (SDL_gfxPrimitives_font.h)
endef

define Build/Configure
	$(call Build/Configure/Default, \
		--disable-sdltest \
		--enable-mmx=$(if $(CONFIG_TARGET_x86),yes,no) \
		--with-sdl-exec-prefix="$(STAGING_DIR)/usr" \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/SDL $(1)/usr/lib/pkgconfig
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/SDL/SDL_*.h \
		$(1)/usr/include/SDL/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libSDL_*.{a,la,so*} \
		$(1)/usr/lib/
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/* \
		$(1)/usr/lib/pkgconfig/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libSDL_*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
