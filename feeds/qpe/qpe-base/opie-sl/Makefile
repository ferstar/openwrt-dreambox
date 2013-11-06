#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opie-sl
PKG_VERSION:=1.2.5
PKG_RELEASE:=1
PKG_MD5SUM:=3827be592c1d3ca704288622b6252331

PKG_SOURCE:=opie-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://sourceforge.net/projects/opie/files/
PKG_BUILD_DIR=$(BUILD_DIR)/opie-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
SUB_MENU:=qpe-base


define Package/$(PKG_NAME)
  TITLE:=OPIE for PC simulation
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build +qte2-sl +qt2 @!PACKAGE_opie @!PACKAGE_qtopia-sl
  URL:=http://opie.sourceforge.net/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  Opie - Open Palmtop Integrated Environment
  Applications and libraries for mobile devices.
endef


###########################
#export QTDIR=$(BUILD_DIR)/qt-2.3.10
export QTDIR=$(DEV_QTDIR)
export OPIEDIR=$(PKG_BUILD_DIR)

TARGET_HOST_CFLAGS+=-I/usr/include \
	-I/usr/include/freetype2 \
	-I/usr/include/alsa \
	-I/usr/include/flite \
	-I/usr/include/libopkg \
	-I/usr/include/sword

TARGET_HOST_CXXFLAGS+=$(TARGET_HOST_CFLAGS)
TARGET_HOST_LDFLAGS+=-Wl,-rpath-link=/usr/lib -L/usr/lib

define Build/Configure
	$(CP) ./config/.config		$(PKG_BUILD_DIR)
	$(CP) ./config/.tmpconfig.h	$(PKG_BUILD_DIR)
	$(CP) ./config/*		$(PKG_BUILD_DIR)
	$(CP) ./config/.depends.cfgs	$(PKG_BUILD_DIR)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		ARCH="$(HOST_ARCH)" \
		TARGET_CFLAGS="$(TARGET_HOST_CFLAGS)" \
		TARGET_CXXFLAGS="$(TARGET_HOST_CXXFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_HOST_LDFLAGS)"
endef

define Build/InstallDev
	( cd $(PKG_BUILD_DIR)/include/opie2; \
		for generatedHeader in `cd ../../libopie2/opieui; ls *.ui | sed -e "s,\.ui,\.h,g"`; do \
		rm -f $$$$generatedHeader ; \
		cp -fpR ../../libopie2/opieui/$$$$generatedHeader $$$$generatedHeader; done )
	( cd $(PKG_BUILD_DIR)/include/opie2; \
		for generatedHeader in `cd ../../libopie2/opiepim/ui; ls *.ui | sed -e "s,\.ui,\.h,g"`; do \
		rm -f $$$$generatedHeader ; \
		cp -fpR ../../libopie2/opiepim/ui/$$$$generatedHeader $$$$generatedHeader; done )
	rm -f $(PKG_BUILD_DIR)/include/qpe/custom.h
	cp -fpR $(PKG_BUILD_DIR)/library/custom-openwrt.h $(PKG_BUILD_DIR)/include/qpe/custom.h

	$(INSTALL_DIR) \
		$(DEV_OPIEDIR)/include \
		$(DEV_OPIEDIR)/lib
	$(CP) $(PKG_BUILD_DIR)/include/*	$(DEV_OPIEDIR)/include
	$(CP) $(PKG_BUILD_DIR)/lib/*		$(DEV_OPIEDIR)/lib
endef

define Package/$(PKG_NAME)/install
## all
	$(INSTALL_DIR) $(1)/$(INSTALL_OPIEDIR)
	$(CP) $(PKG_BUILD_DIR)/{apps,bin,etc,help,i18n,lib,pics,plugins,share,sounds} \
		$(1)/$(INSTALL_OPIEDIR)
## Home dir
	$(INSTALL_DIR) $(1)/$(INSTALL_OPIEDIR)/apps/Home/
	$(CP) ./files/directory $(1)/$(INSTALL_OPIEDIR)/apps/Home/.directory
	$(CP) ./files/Home.png $(1)/$(INSTALL_OPIEDIR)/pics/

	$(CP) $(PKG_BUILD_DIR)/pics-hires/* $(1)/$(INSTALL_OPIEDIR)/pics/
	$(CP) $(PKG_BUILD_DIR)/root/opt/QtPalmtop/* $(1)/$(INSTALL_OPIEDIR)/

	$(INSTALL_DIR) \
		$(1)/etc \
		$(1)/usr
	$(CP) $(PKG_BUILD_DIR)/root/etc/* $(1)/etc/
	$(CP) $(PKG_BUILD_DIR)/root/usr/* $(1)/usr/
## simulation
	$(INSTALL_DIR) $(HOST_SLDIR)
	$(CP) $(1)/* $(HOST_SLDIR)

	$(INSTALL_DIR) $(HOST_SLDIR)/bin/
	$(CP) $(DEV_QTDIR)/bin/qvfb $(HOST_SLDIR)/bin/
	$(CP) $(DEV_QTDIR)/bin/qvfb_skins $(HOST_SLDIR)/bin/
	$(CP) ./files/run-host-*.sh $(HOST_SLDIR)/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
