#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qte2
PKG_VERSION:=2.3.10
PKG_RELEASE:=1
PKG_MD5SUM:=1f7ad30113afc500cab7f5b2f4dec0d7

PKG_SOURCE:=qt-embedded-$(PKG_VERSION)-free.tar.gz
PKG_SOURCE_URL:=ftp://ftp.trolltech.com/qt/source/
PKG_BUILD_DIR=$(BUILD_DIR)/qt-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
SUB_MENU:=qpe-base


define Package/$(PKG_NAME)/config
	source "$(SOURCE)/Config.in"
endef

define Package/$(PKG_NAME)
  TITLE:=qt-embedded-2.3.10
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=+qpe-build +libuuid +libstdcpp +libgcc
  URL:=http://qt.nokia.com/ ftp://ftp.trolltech.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  qt-embedded-2.3.10
endef

### 1. main modules
define Package/$(PKG_NAME)-support-thread
  TITLE:=Compile with Threading Support
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME) +libpthread
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-tslib
  TITLE:=Enable TSlib (touchscreen library) mouse handler
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME) +libts
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-zlib
  TITLE:=Use a zlib from the operating system
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME) +zlib
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-libpng
  TITLE:=Use a libpng from the operating system
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME) +libpng
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-jpeg
  TITLE:=Use jpeglib from the operating system
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME) +libjpeg
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-gif
  TITLE:=Compile in GIF reading support
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

### 2. other modules
define Package/$(PKG_NAME)-support-libmng
  TITLE:=Use libmng from the operating system
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME) +libmng
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-nas-sound
  TITLE:=Use NAS libaudio from the operating system
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-xft
  TITLE:=Enable support for Anti-Aliased fonts
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-sm
  TITLE:=Support X Session Management
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-module-opengl
  TITLE:=Support opengl module
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-module-network
  TITLE:=Support network module
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-module-table
  TITLE:=Support table module
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef

define Package/$(PKG_NAME)-support-module-canvas
  TITLE:=Support canvas module
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=y
endef


### 3. only for Qt/Embedded
define Package/$(PKG_NAME)-support-graphics-accel-snap
  TITLE:=Enable SciTech SNAP Graphics acceleration
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-graphics-accel-voodoo3
  TITLE:=Enable Voodoo3 Graphics acceleration
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-graphics-accel-mach64
  TITLE:=Enable Mach64 Graphics acceleration
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-graphics-accel-matrox
  TITLE:=Enable Matrox MGA Graphics acceleration
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-qvfb
  TITLE:=Enable X11-based Qt Virtual Frame Buffer
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-support-vnc
  TITLE:=Enable VNC server (requires network module)
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME) +$(PKG_NAME)-support-module-network
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-keypad-mode
  TITLE:=Enable keypad widget navigation
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

define Package/$(PKG_NAME)-keypad-input
  TITLE:=Include keypad keys
  CATEGORY:=Qt/Qtopia
  SUBMENU:=$(SUB_MENU)
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  DEFAULT:=n
endef

###########################
export QTDIR=$(PKG_BUILD_DIR)

TARGET_LDFLAGS+=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib,-rpath-link=$(PKG_BUILD_DIR)/lib
TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include -I$(PKG_BUILD_DIR)/include

ifeq ($(CONFIG_PACKAGE_opie),y)
QCONFIG_FILE:=qconfig-qpe-opie.h
else
QCONFIG_FILE:=qconfig-qpe-qtopia.h
endif

define Build/Configure
	$(INSTALL_DIR) $(PKG_BUILD_DIR)/bin/
	$(CP) ./files/uic $(PKG_BUILD_DIR)/bin/
	$(CP) ./files/configs/linux-openwrt-g++* $(PKG_BUILD_DIR)/configs/

	echo "QCONFIG_FILE=$(QCONFIG_FILE)"
	$(CP) ./files/$(QCONFIG_FILE) $(PKG_BUILD_DIR)/src/tools/qconfig-qpe.h

	( cd $(PKG_BUILD_DIR)/ ; \
		echo yes | $(CONFIGURE_CMD) \
		-platform linux-generic-g++ \
		-xplatform linux-openwrt-g++ \
		$(if $(CONFIG_QTE2_RELEASE),-release,-debug) \
		$(if $(CONFIG_QTE2_SHARED),-shared,-static) \
		$(if $(CONFIG_QTE2_NO_EXCEPTIONS),-no-g++-exceptions) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-thread),-thread,-no-thread) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-tslib),-tslib) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-zlib),-system-zlib,-qt-zlib) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-libpng),-system-libpng,-qt-libpng) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-jpeg),-system-jpeg,-no-jpeg) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-gif),-gif,-no-gif) \
		 \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-libmng),-system-libmng,-no-mng) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-nas-sound),-system-nas-sound,-no-nas-sound) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-xft),-xft,-no-xft) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-sm),-sm,-no-sm) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-opengl),,-no-opengl) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-network),,-no-network) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-table),,-no-table) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-module-canvas),,-no-canvas) \
		 \
		-qconfig qpe \
		-depths 4,8,16,32 \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-graphics-accel-snap),-accel-snap) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-graphics-accel-voodoo3),-accel-voodoo3) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-graphics-accel-mach64),-accel-mach64) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-graphics-accel-matrox),-accel-matrox) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-keypad-mode),-keypad-mode) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-keypad-input),-keypad-input) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-vnc),-vnc) \
		$(if $(CONFIG_PACKAGE_$(PKG_NAME)-support-qvfb),-qvfb) \
		 \
	)

endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		ARCH="$(ARCH)" \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Build/InstallDev
## 0. libpng, zlib and freetype source codes needed by qtopia-free-2.1.1/util/pngscale
	$(INSTALL_DIR) $(DEV_QTDIR)/src/3rdparty/
	$(CP) $(PKG_BUILD_DIR)/src/3rdparty/*	$(DEV_QTDIR)/src/3rdparty/
	$(CP) $(PKG_BUILD_DIR)/.buildopts	$(DEV_QTDIR)/

## 1. install Qte2 headers, libs and qte tools "moc"
	$(INSTALL_DIR) $(DEV_QTDIR)/bin/
	$(CP) $(PKG_BUILD_DIR)/bin/{moc,uic}	$(DEV_QTDIR)/bin/

	$(INSTALL_DIR) \
		$(DEV_QTDIR)/include \
		$(DEV_QTDIR)/lib

	$(CP) $(PKG_BUILD_DIR)/include/*	$(DEV_QTDIR)/include/
	$(CP) $(PKG_BUILD_DIR)/lib/*		$(DEV_QTDIR)/lib/

endef

## install fonts
define qte2/fonts/install
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_BUILD_DIR)/lib/fonts/fontdir{,-lots}	$(1)
	$(CP) $(PKG_BUILD_DIR)/lib/fonts/{mkfontdir-qws,README}	$(1)

	$(if $(CONFIG_QTE2_FONTS_songti),	$(CP) ./files/fonts/songti*				$(1) )
	$(if $(CONFIG_QTE2_FONTS_unifont),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/unifont* 		$(1) )
	#$(if $(CONFIG_QTE2_FONTS_helvetica),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/helv* 			$(1) )
	$(if $(CONFIG_QTE2_FONTS_helvetica),	$(CP) ./files/fonts/helvetica*				$(1) )
	$(if $(CONFIG_QTE2_FONTS_fixed),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/fixed* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_fixed),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/5x7.bdf 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_micro),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/micro* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smallsmooth),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/smallsmooth* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothtimes),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/smoothtimes* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothmono),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/smoothmono* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothmono),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/VeraMo* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothsans),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/Vera.ttf 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothsans),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/VeraBd.ttf 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothsans),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/VeraIt.ttf 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothsans),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/VeraBI.ttf 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothsans),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/smoothsans* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothserif),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/smoothserif* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_smoothserif),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/VeraSe* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_babelfish),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/babelfish* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_utopia),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/UT* 			$(1) )
	$(if $(CONFIG_QTE2_FONTS_lucidux),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/lcdx* 			$(1) )
	$(if $(CONFIG_QTE2_FONTS_cursor),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/cursor* 		$(1) )
	$(if $(CONFIG_QTE2_FONTS_courier),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/cour* 			$(1) )
	$(if $(CONFIG_QTE2_FONTS_courier),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/c0* 			$(1) )
	$(if $(CONFIG_QTE2_FONTS_japanese),	$(CP) $(PKG_BUILD_DIR)/lib/fonts/japanese* 		$(1) )
endef
## fonts end

# install in $QPE/lib/, while Qt4 in /usr/lib/
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/$(QPE_INSTALLDIR)/lib
	$(CP) $(PKG_BUILD_DIR)/lib/*.so*	$(1)/$(QPE_INSTALLDIR)/lib/

	$(call qte2/fonts/install, $(1)/$(QPE_INSTALLDIR)/lib/fonts )
endef


$(eval $(call BuildPackage,$(PKG_NAME)))

$(eval $(call BuildPackage,$(PKG_NAME)-support-thread))
$(eval $(call BuildPackage,$(PKG_NAME)-support-tslib))
$(eval $(call BuildPackage,$(PKG_NAME)-support-zlib))
$(eval $(call BuildPackage,$(PKG_NAME)-support-libpng))
$(eval $(call BuildPackage,$(PKG_NAME)-support-jpeg))
$(eval $(call BuildPackage,$(PKG_NAME)-support-gif))

$(eval $(call BuildPackage,$(PKG_NAME)-support-libmng))
$(eval $(call BuildPackage,$(PKG_NAME)-support-nas-sound))
$(eval $(call BuildPackage,$(PKG_NAME)-support-xft))
$(eval $(call BuildPackage,$(PKG_NAME)-support-sm))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-opengl))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-network))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-table))
$(eval $(call BuildPackage,$(PKG_NAME)-support-module-canvas))

$(eval $(call BuildPackage,$(PKG_NAME)-support-graphics-accel-snap))
$(eval $(call BuildPackage,$(PKG_NAME)-support-graphics-accel-voodoo3))
$(eval $(call BuildPackage,$(PKG_NAME)-support-graphics-accel-mach64))
$(eval $(call BuildPackage,$(PKG_NAME)-support-graphics-accel-matrox))
$(eval $(call BuildPackage,$(PKG_NAME)-keypad-mode))
$(eval $(call BuildPackage,$(PKG_NAME)-keypad-input))
$(eval $(call BuildPackage,$(PKG_NAME)-support-vnc))
$(eval $(call BuildPackage,$(PKG_NAME)-support-qvfb))


