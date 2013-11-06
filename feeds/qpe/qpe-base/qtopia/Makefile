#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qtopia
PKG_VERSION:=2.1.1
PKG_RELEASE:=1
PKG_MD5SUM:=c2c028fad85e5584d9af04250d23104d

PKG_SOURCE:=$(PKG_NAME)-free-source-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.trolltech.com/qtopia/source/ \
	http://sourceforge.net/projects/qpe/files/QPE/qtopia/ \
	http://ftp.roedu.net/mirrors/ftp.trolltech.com/qtopia/source/
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)-free-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
SUB_MENU:=qpe-base

define Package/$(PKG_NAME)/config
	source "$(SOURCE)/Config.in"
endef

define Package/$(PKG_NAME)
  TITLE:=Qtopia-free-2.1.1
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-desktop
  DEPENDS:=+qpe-build +qte2
  URL:=http://qt.nokia.com/ ftp://ftp.trolltech.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  qtopia-free-2.1.1
endef

# 1. main modules
define Package/$(PKG_NAME)-support-thread
  TITLE:=Build with threading support
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-desktop
  DEPENDS:=$(PKG_NAME) +qte2-support-thread +libpthread
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-qvfb
  TITLE:=Build with the X11-based Qt Virtual Frame Buffer
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-desktop
  DEPENDS:=$(PKG_NAME) +qte2-support-qvfb
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-module-freetype
  TITLE:=Build freetype module into Qtopia
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-desktop
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-module-libmad
  TITLE:=Build libmad module into Qtopia
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-desktop
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-module-libffmpeg
  TITLE:=Build libffmpeg module into Qtopia
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-desktop
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-module-libamr
  TITLE:=Build libamr module into Qtopia
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-desktop
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

###########################
#export QTDIR=$(BUILD_DIR)/qt-2.3.10
export QTDIR=$(DEV_QTDIR)
export QPEDIR=$(PKG_BUILD_DIR)

# RSTRIP:=:
# STRIP:=:
# STRIP:=true


TARGET_LDFLAGS+=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib
TARGET_CFLAGS:=-I$(PKG_BUILD_DIR)/include -I$(STAGING_DIR)/usr/include $(TARGET_CFLAGS)

define Build/Configure
	$(CP) ./files/linux-openwrt-g++/qmake-mkspecs/ $(PKG_BUILD_DIR)/mkspecs/qws/linux-openwrt-g++/
	$(CP) ./files/linux-openwrt-g++/configs/linux-openwrt-g++* $(PKG_BUILD_DIR)/src/configs/
	$(CP) ./files/linux-openwrt-g++/custom-linux-openwrt-g++.* $(PKG_BUILD_DIR)/src/libraries/qtopia/

	( cd $(PKG_BUILD_DIR)/ ; \
		echo yes | $(CONFIGURE_CMD) \
		-arch $(ARCH) \
		-platform linux-g++ \
		-xplatform linux-openwrt-g++ \
		-prefix $(PKG_INSTALL_DIR) \
		$(if $(CONFIG_QTOPIA_RELEASE),-release,-debug) \
		$(if $(CONFIG_QTOPIA_SHARED),-shared,-static) \
		 \
		-qconfig qpe \
		-iconsizes "14 16 22" \
		-languages $(CONFIG_QTOPIA_LANG) \
		-displaysize $(CONFIG_QTOPIA_DISPLAYSIZE) \
		-displayrot "0 90 180 270" \
		-edition $(if $(CONFIG_QTOPIA_EDITION_PDA),pda) \
		$(if $(CONFIG_QTOPIA_EDITION_PHONE),phone) \
		$(if $(CONFIG_QTOPIA_EDITION_CORE),core) \
		 \
		$(if $(CONFIG_QTOPIA_COMPAT),-compat,-no-compat) \
		$(if $(CONFIG_QTOPIA_SINGLEEXEC),-singleexec) \
		$(if $(CONFIG_QTOPIA_QUICKLAUNCH),-quicklaunch,-no-quicklaunch) \
		$(if $(CONFIG_QTOPIA_QDL),-qdl,-no-qdl) \
		$(if $(CONFIG_QTOPIA_QTOPIA),-qtopia,-no-qtopia) \
		 \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-thread),-thread) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-qvfb),-qvfb,-no-qvfb) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-freetype),) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-libmad),-with-libmad,-without-libmad) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-libffmpeg),-with-libffmpeg,-without-libffmpeg) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-libamr),-with-libamr,-without-libamr) \
		 \
	)
endef
#$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-freetype),-with-freetype,-without-freetype) \

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		ARCH="$(ARCH)" \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)"

	$(MAKE) -C $(PKG_BUILD_DIR) \
		ARCH="$(ARCH)" \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)" \
		install
endef

define Build/InstallDev

	$(CP) $(PKG_BUILD_DIR)/include/ $(PKG_BUILD_DIR)/tmp-include/
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/tmp-include/tmp/tmp/tmp/
	( cd $(PKG_BUILD_DIR)/tmp-include/tmp/ ; \
	for file in ../qtopia/*.h ; do awk -F'"' '/^#include/{print $$$$2}' $$$$file | $(XARGS) -i $(CP) -v {} $$$$file ; done ; \
	)

	( cd $(PKG_BUILD_DIR)/tmp-include/tmp/tmp/ ; \
	for file in ../../qtopia/*/*.h ; do awk -F'"' '/^#include/{print $$$$2}' $$$$file | $(XARGS) -i $(CP) -v {} $$$$file ; done ; \
	)

	( cd $(PKG_BUILD_DIR)/tmp-include/tmp/tmp/tmp/ ; \
	for file in ../../../qtopia/*/*/*.h ; do awk -F'"' '/^#include/{print $$$$2}' $$$$file | $(XARGS) -i $(CP) -v {} $$$$file ; done ; \
	)

	( cd $(PKG_BUILD_DIR)/tmp-include/ ; \
	rm -rvf qpe qwizard.h tmp/ ; \
	ln -sv ./qtopia ./qpe ; \
	ln -sv ./qtopia/qwizard.h ./ ; \
	)

## 1. install qtopia headers and libs
	$(INSTALL_DIR) \
		$(DEV_QTOPIADIR)/include \
		$(DEV_QTOPIADIR)/lib
	$(CP) $(PKG_BUILD_DIR)/tmp-include/*	$(DEV_QTOPIADIR)/include/
	$(CP) $(PKG_BUILD_DIR)/lib/*		$(DEV_QTOPIADIR)/lib/

## 2. install qmake
#	$(INSTALL_DIR) $(DEV_QTDIR)/bin/
#	$(CP) $(PKG_BUILD_DIR)/bin/qmake	$(DEV_QTDIR)/bin/
#	$(CP) $(PKG_BUILD_DIR)/mkspecs/		$(DEV_QTDIR)/bin/qmake-mkspecs/

endef

define Package/$(PKG_NAME)/install
## ipkg
	$(CP) $(PKG_BUILD_DIR)/etc/ipkg.conf $(PKG_INSTALL_DIR)/etc/
	$(CP) $(PKG_BUILD_DIR)/bin/ipkg $(PKG_INSTALL_DIR)/bin/

## Home dir
	$(INSTALL_DIR) $(PKG_INSTALL_DIR)/apps/Home/
	$(CP) ./files/directory $(PKG_INSTALL_DIR)/apps/Home/.directory
	$(CP) ./files/Home.png $(PKG_INSTALL_DIR)/pics/
	
## cp ipkg-install opt/Qtopia
	$(INSTALL_DIR) $(1)/$(INSTALL_QTOPIADIR)
	$(CP) $(PKG_INSTALL_DIR)/*	$(1)/$(INSTALL_QTOPIADIR)

	$(INSTALL_DIR) $(1)/usr/share/
	$(CP) $(PKG_BUILD_DIR)/etc/zoneinfo/ $(1)/usr/share/

## qtopia env
	$(INSTALL_DIR) $(1)/etc/
	$(CP) ./files/qtopia-env.sh $(1)/etc/
## qt4 demo
	$(INSTALL_DIR) $(1)/etc/ $(1)/usr/bin/
	$(CP) ./files/qt4-env.sh $(1)/etc/
	$(CP) ./files/qt4-demo $(1)/usr/bin/

endef

$(eval $(call BuildPackage,$(PKG_NAME)))

$(eval $(call BuildPackage,$(PKG_NAME)-support-thread))
$(eval $(call BuildPackage,$(PKG_NAME)-support-qvfb))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-freetype))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-libmad))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-libffmpeg))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-libamr))
