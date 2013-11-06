#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qt2
PKG_VERSION:=2.3.2
PKG_RELEASE:=1
PKG_MD5SUM:=8b74c7bd9ff0c4752a009f2e5a6482e4

PKG_SOURCE:=qt-x11-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.trolltech.com/qt/source/
PKG_BUILD_DIR=$(BUILD_DIR)/qt-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk


define Package/$(PKG_NAME)
  TITLE:=qt-x11-2.3.2 tools
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-host
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build
  URL:=http://qt.nokia.com/ ftp://ftp.trolltech.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  qt-x11-2.3.2
endef


###########################
export QTDIR=$(PKG_BUILD_DIR)


define Build/Configure
	( cd $(PKG_BUILD_DIR)/ ; \
		echo yes | $(CONFIGURE_CMD) \
		-static \
		-thread \
		-no-opengl \
		-no-xft \
		 \
	)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)
	$(MAKE) -C $(PKG_BUILD_DIR)/tools/qvfb/

	$(CP) $(PKG_BUILD_DIR)/tools/qvfb/qvfb $(PKG_BUILD_DIR)/bin/
endef

## install qt tools
define Build/InstallDev
	$(INSTALL_DIR) $(DEV_QTDIR)/bin/

	$(CP) $(PKG_BUILD_DIR)/bin/{designer,uic,qvfb}	$(DEV_QTDIR)/bin/
	$(CP) $(PKG_BUILD_DIR)/bin/moc			$(DEV_QTDIR)/bin/moc-qt2-x11
	$(CP) ./files/qvfb_skins			$(DEV_QTDIR)/bin/
endef

define Package/$(PKG_NAME)/install
	echo "actually not install !"
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

