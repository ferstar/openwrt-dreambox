#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libSDL_pango
PKG_VERSION:=0.1.2
PKG_RELEASE:=1

PKG_SOURCE:=SDL_Pango-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/SDL_Pango-$(PKG_VERSION)
PKG_SOURCE_URL:=http://sourceforge.net/projects/sdlpango/files/SDL_Pango/$(PKG_VERSION)/
PKG_MD5SUM:=85bbf9bb7b1cee0538154dadd045418c

PKG_FIXUP:=libtool
PKG_MACRO_PATHS:=acinclude
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Package/$(PKG_NAME)
  TITLE:=SDL Pango text rendering engine
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=SDL-$(SUBMENU)
  URL:=http://sdlpango.sourceforge.net/
  DEPENDS:=+libSDL +fontconfig +pango
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  Pango is the text rendering engine of GNOME 2.x.
  SDL_Pango connects the engine to SDL.
  In Windows, pre-built binary package (MSI and merge module) is provided.
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
		$(PKG_INSTALL_DIR)/usr/include/*.h \
		$(1)/usr/include/SDL/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/* \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
