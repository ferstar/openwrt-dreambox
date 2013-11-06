#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qt3
PKG_VERSION:=3.3.5
PKG_RELEASE:=1
PKG_MD5SUM:=fecaf5435c6b0a1a2c23e67991f74e7a

PKG_SOURCE:=qt-x11-free-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.trolltech.com/qt/source/
PKG_BUILD_DIR=$(BUILD_DIR)/qt-x11-free-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk


define Package/$(PKG_NAME)
  TITLE:=qt-x11-3.3.5 tools
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-host
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build
  URL:=http://qt.nokia.com/ ftp://ftp.trolltech.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  qt-x11-3.3.5 tools
endef


###########################
export QTDIR=$(PKG_BUILD_DIR)


define Build/Configure
	( cd $(PKG_BUILD_DIR)/ ; \
		echo yes | $(CONFIGURE_CMD) \
		-static \
		-thread \
		-no-xft \
		 \
	)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)
endef

## install qt tools
define Build/InstallDev
	$(INSTALL_DIR) $(DEV_QTDIR)/bin/
	$(CP) $(PKG_BUILD_DIR)/bin/{assistant,linguist,lrelease,lupdate,qm2ts,qtconfig} $(DEV_QTDIR)/bin/

	$(CP) $(PKG_BUILD_DIR)/bin/designer	$(DEV_QTDIR)/bin/designer-qt3
	$(CP) $(PKG_BUILD_DIR)/bin/moc		$(DEV_QTDIR)/bin/moc-qt3
	$(CP) $(PKG_BUILD_DIR)/bin/uic		$(DEV_QTDIR)/bin/uic-qt3
endef

define Package/$(PKG_NAME)/install
	echo "actually not install !"
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

