#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qpe-build
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=the makefiles of building qpe
  CATEGORY:=Qt/Qtopia
  SUBMENU:=
  SECTION:=qpe
  URL:=http://code.google.com/p/openwrt-for-embedded/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/mk
	$(CP) ./qpe*.mk $(1)/mk/
endef

define Build/Compile
	echo "actually, not compile anything !"
endef

define Package/$(PKG_NAME)/install
	echo "actually, not install anything !"
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
