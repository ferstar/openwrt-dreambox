#
# Copyright (C) 2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libSDL_vnc
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

PKG_SOURCE:=SDL_vnc-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/SDL_vnc-$(PKG_VERSION)
PKG_SOURCE_URL:=http://www.ferzkopp.net/Software/SDL_vnc/
PKG_MD5SUM:=bf80162f6f86e108af71812b38fa561a

PKG_FIXUP:=libtool
PKG_MACRO_PATHS:=acinclude
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Package/$(PKG_NAME)
  TITLE:=SDL based VNC client library with a threaded renderer
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=SDL-$(SUBMENU)
  URL:=http://www.ferzkopp.net/Software/SDL_vnc/
  DEPENDS:=+libSDL
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  SDL based VNC client library with a threaded renderer.
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
