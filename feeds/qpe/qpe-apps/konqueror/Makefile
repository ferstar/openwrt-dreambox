#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=konqueror-embedded
PKG_VERSION:=20030705
PKG_RELEASE:=3
PKG_MD5SUM:=30dc3e109124e8532c7c0ed6ad3ec6fb

PKG_SOURCE:=$(PKG_NAME)-snapshot-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://openwrt-for-embedded.googlecode.com/files/
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)-snapshot-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

#PKG_FIXUP:=libtool
#PKG_MACRO_PATHS:=acinclude
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
QPE_DEPENDS:=+qpe-build @PACKAGE_opie||@PACKAGE_opie-sl||@PACKAGE_qtopia||@PACKAGE_qtopia-sl


define Package/$(PKG_NAME)
  TITLE:=KDE Web Browser Konqueror
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-apps
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build $(QPE_DEPENDS)
  URL:=http://www.konqueror.org/embedded
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  KDE Web Browser Konqueror, QtE based Palmtop Environments Edition
endef

#export QTDIR
#export QPEDIR

define Build/Configure
	$(call Build/Configure/Default, \
	--disable-debug \
	--enable-static \
	--disable-shared \
	--disable-mt \
	 \
	--enable-embedded \
	--enable-qt-embedded \
	--enable-qpe \
	--enable-qtopia \
	--with-gui=qpe \
	 \
	--without-ssl \
	--with-javascript=static \
	 \
	--with-qt-dir=$(QTDIR) \
	--with-qtopia-dir=$(QPEDIR) \
	--with-extra-includes=$(STAGING_DIR)/usr/include \
	--with-extra-libs=$(STAGING_DIR)/usr/lib \
	)
endef

define Build/Compile
	$(call Build/Compile/Default)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/$(QPE_INSTALLDIR)/bin/ \
		$(1)/$(QPE_INSTALLDIR)/apps/Home/ \
		$(1)/$(QPE_INSTALLDIR)/pics/konqueror/ \
		$(1)/opt/kde/

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/konqueror			$(1)/$(QPE_INSTALLDIR)/bin/
	$(CP) $(PKG_INSTALL_DIR)/usr/apps/Applications/konqueror.desktop	$(1)/$(QPE_INSTALLDIR)/apps/Home/
	$(CP) $(PKG_INSTALL_DIR)/usr/pics/konqueror.png				$(1)/$(QPE_INSTALLDIR)/pics/konqueror/

	$(CP) $(PKG_INSTALL_DIR)/usr/share/	$(1)/opt/kde/
	$(CP) ./files/konq-embedrc		$(1)/opt/kde/share/config/

endef

$(eval $(call BuildPackage,$(PKG_NAME)))
