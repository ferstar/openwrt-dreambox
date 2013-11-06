#
# Copyright (C) 2012 OpenWrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=smplayer
PKG_VERSION:=0.8.1
PKG_RELEASE:=1
PKG_MD5SUM:=39556a6113afcd9ceee071a8f85477dc

PKG_SOURCE:=smplayer-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://sourceforge.net/projects/smplayer/files/SMPlayer/$(PKG_VERSION)/
PKG_BUILD_DIR=$(BUILD_DIR)/smplayer-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qmake.mk
export QMAKESPEC=$(QMAKE_SPECFILE)

define Package/$(PKG_NAME)
  TITLE:=SMPlayer
  CATEGORY:=Qt/Qtopia
  SUBMENU:=apps
  SECTION:=sound
  DEPENDS:=+mplayer +Qt4
  URL:=http://smplayer.sourceforge.net/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  SMPlayer is a complete front-end for MPlayer,
  from basic features like playing videos, DVDs, VCDs
  to more advanced features like support for MPlayer filters, edl lists, and more.
endef

TARGET_CFLAGS +=-I$(STAGING_DIR)/usr/include
TARGET_CXXFLAGS +=-I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS +=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib

SMPLAYER_THEMES:=smplayer-themes-20120919
define Download/$(SMPLAYER_THEMES)
  FILE:=$(SMPLAYER_THEMES).tar.bz2
  URL:=http://sourceforge.net/projects/smplayer/files/SMPlayer-themes/20120919/
  MD5SUM:=4af3433f2fc7a4b543e576fb7985eb35
endef
$(eval $(call Download,$(SMPLAYER_THEMES)))

define Build/Compile
	TARGET_CC="$(TARGET_CROSS)gcc" \
	TARGET_CXX="$(TARGET_CROSS)g++" \
	TARGET_AR="$(TARGET_CROSS)ar cqs" \
	TARGET_OBJCOPY="$(TARGET_CROSS)objcopy" \
	TARGET_RANLIB="$(TARGET_CROSS)ranlib" \
	TARGET_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_LDFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS)" \
	TARGET_INCDIRS="$(TARGET_INCDIRS)" \
	TARGET_LIBDIRS="$(TARGET_LIBDIRS)" \
	TARGET_LIBS="$(TARGET_LIBS)" \
	STAGING_DIR_HOST="$(STAGING_DIR_HOST)" \
	STAGING_DIR="$(STAGING_DIR)" \
	$(MAKE) -C $(PKG_BUILD_DIR) \
		PREFIX="/usr" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		QMAKE="$(STAGING_DIR_HOST)/bin/qmake" \
		LRELEASE="$(STAGING_DIR_HOST)/bin/lrelease"
endef

define Build/Install
	TARGET_CC="$(TARGET_CROSS)gcc" \
	TARGET_CXX="$(TARGET_CROSS)g++" \
	TARGET_AR="$(TARGET_CROSS)ar cqs" \
	TARGET_OBJCOPY="$(TARGET_CROSS)objcopy" \
	TARGET_RANLIB="$(TARGET_CROSS)ranlib" \
	TARGET_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_LDFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS)" \
	TARGET_INCDIRS="$(TARGET_INCDIRS)" \
	TARGET_LIBDIRS="$(TARGET_LIBDIRS)" \
	TARGET_LIBS="$(TARGET_LIBS)" \
	STAGING_DIR_HOST="$(STAGING_DIR_HOST)" \
	STAGING_DIR="$(STAGING_DIR)" \
	$(MAKE) -C $(PKG_BUILD_DIR) \
		PREFIX="/usr" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		QMAKE="$(STAGING_DIR_HOST)/bin/qmake" \
		LRELEASE="$(STAGING_DIR_HOST)/bin/lrelease" \
		install
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/usr/bin \
		$(1)/usr/share/smplayer \
		$(1)/usr/share/doc/smplayer \
		$(1)/usr/share/man/man1
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/smplayer		$(1)/usr/bin/
	$(CP) $(PKG_INSTALL_DIR)/usr/share/smplayer/*			$(1)/usr/share/smplayer/
	$(CP) $(PKG_INSTALL_DIR)/usr/share/doc/packages/smplayer/*	$(1)/usr/share/doc/smplayer/
	$(CP) $(PKG_INSTALL_DIR)/usr/share/man/man1/smplayer.1.gz	$(1)/usr/share/man/man1/

	$(INSTALL_DIR) $(1)/usr/share/smplayer/themes
	tar jxf $(DL_DIR)/$(SMPLAYER_THEMES).tar.bz2 -C $(PKG_BUILD_DIR)
	$(CP) $(PKG_BUILD_DIR)/$(SMPLAYER_THEMES)/themes/*	$(1)/usr/share/smplayer/themes/

	$(INSTALL_DIR) $(1)/usr/share/applications $(1)/usr/share/icons
	$(CP) $(PKG_INSTALL_DIR)/usr/share/applications/*.desktop	$(1)/usr/share/applications/
	$(CP) $(PKG_INSTALL_DIR)/usr/share/icons/hicolor		$(1)/usr/share/icons/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
