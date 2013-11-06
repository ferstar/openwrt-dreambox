#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=sdlpal
PKG_VERSION:=61376
PKG_RELEASE:=2
PKG_MD5SUM:=0a4cf1023dc6eb78002bd0516c2d3d1b

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://openwrt-for-embedded.googlecode.com/files/
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

PKG_FIXUP:=libtool

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
QPE_DEPENDS:=+qpe-build @PACKAGE_opie||@PACKAGE_opie-sl||@PACKAGE_qtopia||@PACKAGE_qtopia-sl

define Package/$(PKG_NAME)
  TITLE:=RPG game Paladin - Xian Jian Qi Xia Zhuan
  CATEGORY:=Qt/Qtopia
  SUBMENU:=games
  SECTION:=SDL-$(SUBMENU)
  URL:=http://sdlpal.codeplex.com/
  DEPENDS:=+libSDL +libSDL_image +libSDL_ttf +libSDL_mixer $(ICONV_DEPENDS) +zlib +libfreetype +libmad +libjpeg +libpng
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  An SDL-based reimplemention of the classic Chinese-language RPG "Xian Jian Qi Xia Zhuan" 
  (aka "The Legend of Sword and Fairy" or "PAL") which runs under modern operating systems 
  (Microsoft Windows, GNU/Linux, Mac OS X, etc.) as well as several embedded systems.
endef

define Package/$(PKG_NAME)-desktop
  TITLE:=Qtopia desktop of RPG game Paladin
  CATEGORY:=Qt/Qtopia
  SUBMENU:=games
  SECTION:=games
  DEPENDS:=$(QPE_DEPENDS) $(PKG_NAME)
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

PALADIN_FILE:=paladin_res
define Download/$(PALADIN_FILE)
  FILE:=$(PALADIN_FILE).tar.bz2
  URL:=https://openwrt-for-embedded.googlecode.com/files/
  MD5SUM:=27cbeacbd6eb0bebcb3039a670f89d22
endef
$(eval $(call Download,$(PALADIN_FILE)))

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

define Build/Compile
	$(call Build/Compile/Default, \
 		ARCH="$(ARCH)" \
		TARGET_CROSS="$(TARGET_CROSS)" \
	)

endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/opt/ $(1)/usr/bin/
	tar jxvf $(DL_DIR)/$(PALADIN_FILE).tar.bz2 -C $(1)/opt/
	$(CP) $(PKG_BUILD_DIR)/sdlpal_$(ARCH) $(1)/opt/paladin/run-sdlpal
endef

########### could not work now !! main.cpp should be modified !
define Package/$(PKG_NAME)-desktop/install
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/desktop/
	$(CP) ./src/* $(PKG_BUILD_DIR)/desktop/

	$(MAKE) -C $(PKG_BUILD_DIR)/desktop \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)" \
		QTDIR="$(QTDIR)" \
		QPEDIR="$(QPEDIR)"

	$(INSTALL_DIR) \
		$(1)/$(QPE_INSTALLDIR)/bin/ \
		$(1)/$(QPE_INSTALLDIR)/apps/Home/ \
		$(1)/$(QPE_INSTALLDIR)/pics/$(PKG_NAME)/

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/desktop/$(PKG_NAME)	$(1)/$(QPE_INSTALLDIR)/bin/$(PKG_NAME)
	$(CP) $(PKG_BUILD_DIR)/desktop/$(PKG_NAME).desktop	$(1)/$(QPE_INSTALLDIR)/apps/Home/
	$(CP) $(PKG_BUILD_DIR)/desktop/$(PKG_NAME).png		$(1)/$(QPE_INSTALLDIR)/pics/$(PKG_NAME)/

	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/desktop/paladin		$(1)/usr/bin/

endef

$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)-desktop))
