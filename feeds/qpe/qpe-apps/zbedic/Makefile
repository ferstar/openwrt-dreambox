#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=zbedic
PKG_VERSION:=1.2-2
PKG_RELEASE:=3
PKG_MD5SUM:=c7e8e267567a96cff7920a0365978c4d

PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION).tgz
PKG_SOURCE_URL:=http://sourceforge.net/projects/bedic/files/zbedic-src/1.2-2/
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)_$(PKG_VERSION)

PKG_FIXUP:=libtool
#PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
QPE_DEPENDS:=+qpe-build @PACKAGE_opie||@PACKAGE_opie-sl||@PACKAGE_qtopia||@PACKAGE_qtopia-sl


define Package/$(PKG_NAME)
  TITLE:=Zbedic is an electronic dictionary
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-apps
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build +libpthread +libc +libstdcpp +libsqlite3 +libjpeg +libpng +zlib +libuuid $(QPE_DEPENDS)
  URL:=http://bedic.sourceforge.net/ http://sourceforge.net/projects/bedic/files/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  Zbedic is an electronic dictionary reader for Sharp Zaurus and Linux desktop.
  Now it's ported to every platform which OpenWrt supported.
endef

LIBBEDIC:=libbedic_1.1-0
define Download/$(LIBBEDIC)
  FILE:=$(LIBBEDIC).tgz
  URL:=http://sourceforge.net/projects/bedic/files/libbedic-src/1.1/
  MD5SUM:=211ea5a881b5691ec7a1aedbe7fc406c
endef
$(eval $(call Download,$(LIBBEDIC)))

CEDICT:=cn-en_CEDICT_200512
define Download/$(CEDICT)
  FILE:=$(CEDICT).dic.dz
  URL:=http://sourceforge.net/projects/bedic/files/Chine-English%20%28CEDICT%29/2005_12/
  MD5SUM:=cb2cd79b09c58e6ebda2ae06e8eaeb15
endef
$(eval $(call Download,$(CEDICT)))

define Build/Prepare
	$(INSTALL_DIR) \
		$(PKG_BUILD_DIR)/zbedic \
		$(PKG_BUILD_DIR)/libbedic
	tar zxf $(DL_DIR)/$(PKG_SOURCE) -C $(PKG_BUILD_DIR)/zbedic
	tar zxf $(DL_DIR)/$(LIBBEDIC).tgz -C $(PKG_BUILD_DIR)/libbedic

	$(Build/Patch)
endef

#export QTDIR
#export QPEDIR

define build/libbedic
	$(MAKE) -C $(PKG_BUILD_DIR)/libbedic \
		ARCH="$(ARCH)" \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(TARGET_CXXFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)" \
		INSTALL_DIR="$(PKG_INSTALL_DIR)" \
		QTDIR="$(QTDIR)"
endef

define Build/Configure
	$(call build/libbedic)

	(cd $(PKG_BUILD_DIR)/zbedic; \
	$(CONFIGURE_CMD) \
		--with-qpe \
		--host="$(ARCH)" \
		--prefix="$(PKG_INSTALL_DIR)" \
		ARCH="$(ARCH)" \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(TARGET_CXXFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)" \
		SQLITE3_CFLAGS=-I$(STAGING_DIR)/usr/include \
		SQLITE3_LIBS=-L$(STAGING_DIR)/usr/lib \
		QPEDIR="$(QPEDIR)" \
		QTDIR="$(QTDIR)" \
	)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/zbedic \
		QPEDIR="$(QPEDIR)" \
		ARCH="$(ARCH)"

	$(MAKE) -C $(PKG_BUILD_DIR)/zbedic \
		QPEDIR="$(QPEDIR)" \
		ARCH="$(ARCH)" \
		install
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/$(QPE_INSTALLDIR)/bin/ \
		$(1)/$(QPE_INSTALLDIR)/apps/Home/ \
		$(1)/$(QPE_INSTALLDIR)/pics/$(PKG_NAME)/ \
		$(1)/$(QPE_INSTALLDIR)/help/en/html/

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/bin/zbedic		$(1)/$(QPE_INSTALLDIR)/bin/
	$(CP) $(PKG_INSTALL_DIR)/share/zbedic/*			$(1)/$(QPE_INSTALLDIR)/pics/$(PKG_NAME)/
	$(CP) $(PKG_BUILD_DIR)/zbedic/misc/zbedic.desktop	$(1)/$(QPE_INSTALLDIR)/apps/Home/
	$(CP) $(PKG_BUILD_DIR)/zbedic/doc/manual/zbedic*	$(1)/$(QPE_INSTALLDIR)/help/en/html/

	$(INSTALL_DIR) $(1)/root/Documents/
	$(CP) $(DL_DIR)/$(CEDICT).dic.dz $(1)/root/Documents/

endef

$(eval $(call BuildPackage,$(PKG_NAME)))
