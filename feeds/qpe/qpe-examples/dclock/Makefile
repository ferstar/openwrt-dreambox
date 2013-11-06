#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#


include $(TOPDIR)/rules.mk


PKG_NAME:=dclock
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
QPE_DEPENDS:=+qpe-build @PACKAGE_opie||@PACKAGE_opie-sl||@PACKAGE_qtopia||@PACKAGE_qtopia-sl


define Package/$(PKG_NAME)
  TITLE:=A simple $(PKG_NAME) example of Qtopia
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-examples
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build $(QPE_DEPENDS)
  URL:=http://code.google.com/p/openwrt-for-embedded/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  /*
   * Created by Richard Nee <richard.nee.cn@gmail.com>
   * Supported by the OpenWRT-for-Embedded Project:http://code.google.com/p/openwrt-for-embedded/
  /*
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(call Build/Compile/QPE)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/$(QPE_INSTALLDIR)/bin/ \
		$(1)/$(QPE_INSTALLDIR)/apps/Home/ \
		$(1)/$(QPE_INSTALLDIR)/pics/$(PKG_NAME)/

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME)	$(1)/$(QPE_INSTALLDIR)/bin/$(PKG_NAME)
	$(CP) $(PKG_BUILD_DIR)/$(PKG_NAME).desktop	$(1)/$(QPE_INSTALLDIR)/apps/Home/
	$(CP) $(PKG_BUILD_DIR)/$(PKG_NAME).png		$(1)/$(QPE_INSTALLDIR)/pics/$(PKG_NAME)/

	$(call HostSimulation/Install/QPE,$(1)/*)

endef

$(eval $(call BuildPackage,$(PKG_NAME)))

