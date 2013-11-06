#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=tree
PKG_VERSION:=1.6.0
PKG_RELEASE:=1
PKG_MD5SUM:=04e967a3f4108d50cde3b4b0e89e970a

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tgz
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=ftp://mama.indstate.edu/linux/tree/ \
	http://mama.indstate.edu/users/ice/tree/src/
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=Tree is a recursive directory listing command
  CATEGORY:=Qt/Qtopia
  SUBMENU:=apps
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=
  URL:=http://mama.indstate.edu/users/ice/tree/index.html
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/usr/bin \
		$(1)/usr/man/man1

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tree $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/doc/* $(1)/usr/man/man1/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
