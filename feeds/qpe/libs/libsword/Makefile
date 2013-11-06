#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libsword
PKG_VERSION:=1.5.9
PKG_RELEASE:=1
PKG_MD5SUM:=e1f1af8c2add8310d0bbcddc9af523b8

PKG_SOURCE:=sword-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=http://crosswire.org/ftpmirror/pub/sword/source/v1.5/ \
	http://pkgs.fedoraproject.org/repo/pkgs/sword/sword-1.5.9.tar.gz/e1f1af8c2add8310d0bbcddc9af523b8/
PKG_BUILD_DIR=$(BUILD_DIR)/sword-$(PKG_VERSION)

PKG_FIXUP:=libtool
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk


define Package/$(PKG_NAME)
  TITLE:=The SWORD API/library for Bible software
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=+zlib +libcurl
  URL:=http://www.crosswire.org
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)-utils
  TITLE:=utils for bible documents in SWORD supported formats
  CATEGORY:=Qt/Qtopia
  SUBMENU:=apps
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=+$(PKG_NAME)
  URL:=http://www.crosswire.org
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  The SWORD Project is an open source, cross-platform (Linux, Windows, Solaris, MacOSX etc.) 
  API/library for Bible software with a constantly growing list of front-ends 
  (GUI, textmode, web-based, etc.) and a library of over 200 text modules.
endef

TARGET_LDFLAGS += -Wl,-rpath-link,$(STAGING_DIR)/usr/lib
TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include -I$(STAGING_DIR)/usr/include/curl
TARGET_CXXFLAGS+=-I$(STAGING_DIR)/usr/include -I$(STAGING_DIR)/usr/include/curl

# /* curl/types.h is empty,and not be used */
define fix/curl-types.h
	( \
	if [ -e $(STAGING_DIR)/usr/include/curl -a ! -e $(STAGING_DIR)/usr/include/curl/types.h ] ; then \
		touch $(STAGING_DIR)/usr/include/curl/types.h ; \
	fi ; \
	)
endef

define Build/Configure
	$(call fix/curl-types.h)
	$(call Build/Configure/Default, \
		--with-zlib \
		--with-curl \
	)
endef

define Build/InstallDev
	$(INSTALL_DIR) \
		$(1)/usr/include \
		$(1)/usr/lib \
		$(1)/usr/lib/pkgconfig

	$(CP) $(PKG_INSTALL_DIR)/usr/include/sword $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libsword*.{a,so*,la} $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/sword.pc $(1)/usr/lib/pkgconfig/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libsword*.so* $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-utils/install
	$(INSTALL_DIR) \
		$(1)/usr/bin \
		$(1)/usr/share \
		$(1)/etc
		
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/*		$(1)/usr/bin/
	$(CP) $(PKG_INSTALL_DIR)/usr/share/sword	$(1)/usr/share/
	$(CP) $(PKG_INSTALL_DIR)/etc/sword.conf		$(1)/etc/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)-utils))
