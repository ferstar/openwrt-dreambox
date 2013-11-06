#
# Copyright (C) 2012 OpenWrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mplayer
PKG_VERSION:=1.0rc3
PKG_RELEASE:=1
PKG_MD5SUM:=e1221be5fcad74a2a4185f67ba6c9ae0

PKG_SOURCE:=MPlayer-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://www.mplayerhq.hu/MPlayer/releases/
PKG_BUILD_DIR=$(BUILD_DIR)/MPlayer-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=MPlayer
  CATEGORY:=Qt/Qtopia
  SUBMENU:=apps
  SECTION:=sound
  DEPENDS:=+libpthread +libmad +libpng +libjpeg +libmng +giflib
  URL:=http://www.mplayerhq.hu/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
 MPlayer can play most standard video formats out of the box
 and almost all others with the help of external codecs.
endef

MPLAYER_SKINS:=Ater-1.2
define Download/$(MPLAYER_SKINS)
  FILE:=$(MPLAYER_SKINS).tar.bz2
  URL:=http://www.mplayerhq.hu/MPlayer/skins/
  MD5SUM:=316e29f7da492edf697baee205fc47c6
endef
$(eval $(call Download,$(MPLAYER_SKINS)))

CONFIGURE_ARGS = \
	--target=$(GNU_TARGET_NAME) \
	--prefix=/usr \
	 \
	--disable-mencoder \
	--disable-vidix \
	--disable-vm \
	--disable-dvdnav \
	--disable-dvdread \
	--disable-dvdread-internal \
	--disable-libdvdcss-internal \
	--disable-pvr \
	--disable-tv \
	--disable-v4l2 \
	--disable-tv-v4l1 \
	--disable-tv-v4l2 \
	--disable-dvb \
	--disable-xanim \
	--disable-win32dll \
	--disable-dvb \
	--disable-yuv4mpeg \
	--disable-pnm \
	--disable-tga \
	--enable-fbdev

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/usr/bin \
		$(1)/etc/mplayer \
		$(1)/usr/share/mplayer \
		$(1)/usr/share/mplayer/skins
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mplayer $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/etc/example.conf $(1)/etc/mplayer/mplayer.conf
	$(CP) $(PKG_BUILD_DIR)/etc/{codecs.conf,dvb-menu.conf,input.conf,menu.conf,mplayer.desktop,mplayer.ico,mplayer.xpm} $(1)/etc/mplayer/

	$(CP) $(PKG_BUILD_DIR)/TOOLS/*.sh	$(1)/usr/share/mplayer/
	$(CP) $(PKG_BUILD_DIR)/TOOLS/*.p*       $(1)/usr/share/mplayer/

	tar jxf $(DL_DIR)/$(MPLAYER_SKINS).tar.bz2 -C $(1)/usr/share/mplayer/skins/
	( cd $(1)/usr/share/mplayer/skins/ ; \
		ln -sv Ater default \
	)
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
