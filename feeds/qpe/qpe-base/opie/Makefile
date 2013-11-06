#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=opie
PKG_VERSION:=1.2.5
PKG_RELEASE:=1
PKG_MD5SUM:=3827be592c1d3ca704288622b6252331

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://sourceforge.net/projects/opie/files/
PKG_BUILD_DIR=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
SUB_MENU:=qpe-base


define Package/$(PKG_NAME)/config
	source "$(SOURCE)/Config.in"
endef

define Package/$(PKG_NAME)
  TITLE:=Open Palmtop Integrated Environment
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build +qte2 +libsysfs +libpng +libjpeg +zlib @!PACKAGE_qtopia
  URL:=http://opie.sourceforge.net/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  Opie - Open Palmtop Integrated Environment
  Applications and libraries for mobile devices.
endef

define Package/$(PKG_NAME)-have-sqlite
  TITLE:=SQLite PIM backends(libsqlite3)
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libsqlite3
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-freetype
  TITLE:=libfreetype font engine
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libfreetype
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-libsword
  TITLE:=The SWORD API/library(libsword)
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libsword
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-libetpan
  TITLE:=Mail Framework for C Language(libetpan)
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libetpan
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-libpcap
  TITLE:=packet capture library(libpcap)
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libpcap
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-bluez-libs
  TITLE:=Bluetooth library(bluez-libs)
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +bluez-libs
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-xine-lib
  TITLE:=Xine libraries(xine-lib)
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libxine
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-alsa-lib
  TITLE:=Advanced Linux Sound Architecture libraries
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +alsa-lib
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-flite
  TITLE:=Text-to-speech for embedded systems
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +flite
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-obexftp
  TITLE:=ObexFTP libraries
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libopenobex +libobexftp
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-libpcsclite
  TITLE:=(libpcsclite) PC/SC Lite
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libpcsclite
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-libpam
  TITLE:=(libpam)Linux-PAM
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libpam @BROKEN
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-have-opkg
  TITLE:=(opkg)lightweight package management system
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=$(PKG_NAME) +libopkg
  DEFAULT:=y
endef


###########################
#export QTDIR=$(BUILD_DIR)/qt-2.3.10
export QTDIR=$(DEV_QTDIR)
export OPIEDIR=$(PKG_BUILD_DIR)

TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include \
	-I$(STAGING_DIR)/usr/include/freetype2 \
	-I$(STAGING_DIR)/usr/include/alsa \
	-I$(STAGING_DIR)/usr/include/flite \
	-I$(STAGING_DIR)/usr/include/libopkg \
	-I$(STAGING_DIR)/usr/include/sword

TARGET_CXXFLAGS+=$(TARGET_CFLAGS)
TARGET_LDFLAGS+=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib -L$(STAGING_DIR)/usr/lib

define Build/Configure
	$(CP) ./config/.config		$(PKG_BUILD_DIR)
	$(CP) ./config/.tmpconfig.h	$(PKG_BUILD_DIR)
	$(CP) ./config/*		$(PKG_BUILD_DIR)
	$(CP) ./config/.depends.cfgs	$(PKG_BUILD_DIR)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		ARCH="$(ARCH)" \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_CXXFLAGS="$(TARGET_CXXFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)"
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
endef


$(eval $(call BuildPackage,$(PKG_NAME)))

$(eval $(call BuildPackage,$(PKG_NAME)-have-sqlite))
$(eval $(call BuildPackage,$(PKG_NAME)-have-freetype))
$(eval $(call BuildPackage,$(PKG_NAME)-have-libsword))
$(eval $(call BuildPackage,$(PKG_NAME)-have-libetpan))
$(eval $(call BuildPackage,$(PKG_NAME)-have-libpcap))
$(eval $(call BuildPackage,$(PKG_NAME)-have-bluez-libs))
$(eval $(call BuildPackage,$(PKG_NAME)-have-xine-lib))
$(eval $(call BuildPackage,$(PKG_NAME)-have-alsa-lib))
$(eval $(call BuildPackage,$(PKG_NAME)-have-flite))
$(eval $(call BuildPackage,$(PKG_NAME)-have-obexftp))
$(eval $(call BuildPackage,$(PKG_NAME)-have-libpam))
$(eval $(call BuildPackage,$(PKG_NAME)-have-libpcsclite))
$(eval $(call BuildPackage,$(PKG_NAME)-have-opkg))
