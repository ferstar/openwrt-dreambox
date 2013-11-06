#
# Copyright (C) 2008-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

# TODO:
#  - test/add xcb support
#  - handle plugins in a granular way (find out which packages should provide which plugins)

include $(TOPDIR)/rules.mk

PKG_NAME:=Qt4
PKG_VERSION:=4.8.1
PKG_RELEASE:=1
PKG_MD5SUM:=7960ba8e18ca31f0c6e4895a312f92ff

PKG_SOURCE:=qt-everywhere-opensource-src-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=ftp://ftp.qt.nokia.com/qt/source
PKG_BUILD_DIR=$(BUILD_DIR)/qt-everywhere-opensource-src-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

PKG_CONFIG_DEPENDS:= \
	CONFIG_Qt4_WS_QWS \
	CONFIG_Qt4_WS_X11 \
	CONFIG_PACKAGE_directfb \
	CONFIG_PACKAGE_$(PKG_NAME)-demos \
	CONFIG_PACKAGE_$(PKG_NAME)-examples \
	CONFIG_PACKAGE_$(PKG_NAME)-svg \
	CONFIG_PACKAGE_$(PKG_NAME)-qt3support \
	CONFIG_PACKAGE_$(PKG_NAME)-dbus \
	CONFIG_PACKAGE_$(PKG_NAME)-phonon \
	CONFIG_PACKAGE_$(PKG_NAME)-sqlite \
	CONFIG_PACKAGE_$(PKG_NAME)-mysql \
	CONFIG_PACKAGE_$(PKG_NAME)-pgsql \
	CONFIG_PACKAGE_$(PKG_NAME)-webkit \
	CONFIG_PACKAGE_$(PKG_NAME)-script \
	CONFIG_PACKAGE_$(PKG_NAME)-scriptools \
	CONFIG_PACKAGE_$(PKG_NAME)-openssl \
	CONFIG_PACKAGE_$(PKG_NAME)-xmlpatterns \
	CONFIG_PACKAGE_$(PKG_NAME)-drivers-mouse-tslibmousedriver \
	CONFIG_PACKAGE_$(PKG_NAME)-declarative \
	CONFIG_PACKAGE_$(PKG_NAME)-drivers-gfx-vnc \

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk
-include $(if $(DUMP),,./files/qmake.mk)

define Package/$(PKG_NAME)/config
	source "$(SOURCE)/Config.in"
endef

define Package/$(PKG_NAME)/Default
  TITLE:=Qt4
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-base
  SECTION:=qtopia-libs
  DEPENDS:=$(PKG_NAME)
  URL:=http://qt.nokia.com/
  MAINTAINER:=Mirko Vogt <mirko@openwrt.org>
endef

define Package/$(PKG_NAME)
  $(call Package/$(PKG_NAME)/Default)
  DEPENDS:=+zlib +librt +libstdcpp @!LINUX_2_4
endef

define Package/$(PKG_NAME)-gui
  $(call Package/$(PKG_NAME)/Default)
  DEFAULT:=y
  DEPENDS+=+PACKAGE_$(PKG_NAME)-gui:libpng +PACKAGE_$(PKG_NAME)-gui:libtiff +PACKAGE_$(PKG_NAME)-gui:libjpeg +PACKAGE_$(PKG_NAME)-gui:libfreetype +$(PKG_NAME)-network \
	+FEATURE_drawing-backend_libX11:libX11 \
	+FEATURE_drawing-backend_libX11:libXext @DISPLAY_SUPPORT
  TITLE+=(gui)
endef

define Package/$(PKG_NAME)-demos
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(demos)
  DEPENDS+=+$(PKG_NAME)-gui
endef

define Package/$(PKG_NAME)-examples
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(examples)
  DEPENDS+=+$(PKG_NAME)-gui +$(PKG_NAME)-svg
endef

define Package/$(PKG_NAME)-network
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(network)
endef

define Package/$(PKG_NAME)-sqlite
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(sqlite)
  DEPENDS+=+PACKAGE_$(PKG_NAME)-sqlite:libsqlite3
endef

define Package/$(PKG_NAME)-mysql
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(mysql)
  DEPENDS+=+PACKAGE_$(PKG_NAME)-mysql:libmysqlclient
endef

define Package/$(PKG_NAME)-pgsql
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(pgsql)
  DEPENDS+=+coreutils +coreutils-su +PACKAGE_$(PKG_NAME)-pgsql:libpq
endef

define Package/$(PKG_NAME)-openssl
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(openssl)
  DEPENDS+=+PACKAGE_$(PKG_NAME)-openssl:libopenssl
endef

#define Package/$(PKG_NAME)-multimedia
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(multimedia)
#endef

#define Package/$(PKG_NAME)-audio-backend
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(audio-backend)
#endef

define Package/$(PKG_NAME)-phonon
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(phonon)
  DEPENDS+=+$(PKG_NAME)-gui +$(PKG_NAME)-xml +$(PKG_NAME)-dbus +$(PKG_NAME)-network
endef

#define Package/$(PKG_NAME)-phonon-backend
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(phonon-backend)
#endef

define Package/$(PKG_NAME)-svg
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(svg)
  DEPENDS+=+$(PKG_NAME)-gui +$(PKG_NAME)-network
endef

define Package/$(PKG_NAME)-webkit
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(webkit)
  DEPENDS+=+PACKAGE_$(PKG_NAME)-webkit:libsqlite3 +$(PKG_NAME)-phonon +$(PKG_NAME)-dbus +$(PKG_NAME)-xml +$(PKG_NAME)-gui +$(PKG_NAME)-network
endef

define Package/$(PKG_NAME)-script
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(script)
endef

define Package/$(PKG_NAME)-scripttools
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(scripttools)
  DEPENDS+=+$(PKG_NAME)-script +$(PKG_NAME)-gui +$(PKG_NAME)-network
endef

#define Package/$(PKG_NAME)-accessibility
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(accessibility)
#endef

#define Package/$(PKG_NAME)-javascript-jit
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(javascript-jit)
#endef

#define Package/$(PKG_NAME)-cups
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(cups)
#endef

define Package/$(PKG_NAME)-dbus
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(dbus)
  DEPENDS+=+PACKAGE_$(PKG_NAME)-dbus:libdbus +$(PKG_NAME)-xml
endef

#define Package/$(PKG_NAME)-gtkstyle
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(gtkstyle)
#endef

#define Package/$(PKG_NAME)-glib
#  $(call Package/$(PKG_NAME)/Default)
#  TITLE+=(glib)
#endef

define Package/$(PKG_NAME)-qt3support
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(qt3support)
  DEPENDS+=+$(PKG_NAME)-gui +$(PKG_NAME)-xml
endef

define Package/$(PKG_NAME)-declarative
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(declarative)
  DEPENDS+=+$(PKG_NAME)-script +$(PKG_NAME)-xml +$(PKG_NAME)-gui +$(PKG_NAME)-network
endef

define Package/$(PKG_NAME)-xml
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(xml)
endef

define Package/$(PKG_NAME)-xmlpatterns
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=(xmlpatterns)
endef

###
define Package/$(PKG_NAME)-drivers-mouse/Default
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=mousedrivers
  DEPENDS+=@Qt4_WS_QWS
endef

define Package/$(PKG_NAME)-drivers-mouse-tpmousedriver
  $(call Package/$(PKG_NAME)-drivers-mouse/Default)
  TITLE+=tpmousedriver
endef

define Package/$(PKG_NAME)-drivers-mouse-pcmousedriver
  $(call Package/$(PKG_NAME)-drivers-mouse/Default)
  TITLE+=pcmousedriver
endef

define Package/$(PKG_NAME)-drivers-mouse-tslibmousedriver
  $(call Package/$(PKG_NAME)-drivers-mouse/Default)
  TITLE+=tslibmousedriver
  DEPENDS+=+PACKAGE_$(PKG_NAME)-drivers-mouse-tslibmousedriver:libts
endef

###
define Package/$(PKG_NAME)-drivers-gfx/Default
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=gfxdrivers
  DEPENDS+=@Qt4_WS_QWS
endef

define Package/$(PKG_NAME)-drivers-gfx-directfb
  $(call Package/$(PKG_NAME)-drivers-gfx/Default)
  TITLE+=directfb
  DEPENDS+=@FEATURE_drawing-backend_DirectFB +$(PKG_NAME)-drivers-gfx-directfb:directfb
endef

define Package/$(PKG_NAME)-drivers-gfx-linuxfb
  $(call Package/$(PKG_NAME)-drivers-gfx/Default)
  TITLE+=linuxfb
endef

define Package/$(PKG_NAME)-drivers-gfx-vnc
  $(call Package/$(PKG_NAME)-drivers-gfx/Default)
  TITLE+=VNC
endef

###
define Package/$(PKG_NAME)-drivers-kbd/Default
  $(call Package/$(PKG_NAME)/Default)
  TITLE+=kbddrivers
  DEPENDS+=@Qt4_WS_QWS
endef


TARGET_INCDIRS+=$(STAGING_DIR)/include $(STAGING_DIR)/usr/include $(TOOLCHAIN_DIR)/include $(TOOLCHAIN_DIR)/usr/include
TARGET_LIBDIRS+=$(STAGING_DIR)/lib $(STAGING_DIR)/usr/lib $(TOOLCHAIN_DIR)/lib $(TOOLCHAIN_DIR)/usr/lib
TARGET_LDFLAGS+=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib,-rpath-link=$(PKG_BUILD_DIR)/lib
TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include/freetype2 -I$(PKG_BUILD_DIR)/include -I$(STAGING_DIR)/usr/include/directfb
TARGET_CFLAGS+=-fpermissive

ifeq ($(CONFIG_Qt4_WS_QWS),y)
  FILEPFX:=qws-
endif
ifeq ($(CONFIG_Qt4_WS_X11),y)
  FILEPFX:=x11-
endif
ifeq ($(CONFIG_PACKAGE_$(PKG_NAME)-gui),)
  # If GUI is disabled, we use the X11 prefix. That's good enough, for now.
  # The X11 files also work for non-GUI.
  FILEPFX:=x11-
endif

define Build/Configure
	# NOTES:
	#  demos/examples: which demos are going to be built depends on which features are going to to be compiled into qt
	#  linuxfb/directfb: since directfb is not much overhead compared to plain framebuffer, force using directfb
	#  do not use fontconfig as it doesn't work anyway for qte
	#  bindir: bindir is where the host tools (qmake, moc, rcc, uic) will get installed into - they are just used on the host and not goig to be packaged
	mkdir -p $(PKG_BUILD_DIR)/mkspecs/$(QMAKE_PLATFORM_PREFIX)linux-openwrt-g++
	$(CP) ./files/$(FILEPFX)qmake.conf $(PKG_BUILD_DIR)/mkspecs/$(QMAKE_PLATFORM_PREFIX)linux-openwrt-g++/qmake.conf
	$(CP) ./files/$(FILEPFX)qplatformdefs.h $(PKG_BUILD_DIR)/mkspecs/$(QMAKE_PLATFORM_PREFIX)linux-openwrt-g++/qplatformdefs.h
	( cd $(PKG_BUILD_DIR) ; \
		TARGET_CC="$(TARGET_CROSS)gcc" \
		TARGET_CXX="$(TARGET_CROSS)g++" \
		TARGET_AR="$(TARGET_CROSS)ar cqs" \
		TARGET_OBJCOPY="$(TARGET_CROSS)objcopy" \
		TARGET_RANLIB="$(TARGET_CROSS)ranlib" \
		TARGET_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
		TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS)" \
		TARGET_INCDIRS="$(TARGET_INCDIRS)" \
		TARGET_LIBDIRS="$(TARGET_LIBDIRS)" \
		CFLAGS= \
		CXXFLAGS= \
		LDFLAGS= \
		STAGING_DIR="$(STAGING_DIR)" \
		STAGING_DIR_HOST="$(STAGING_DIR_HOST)" \
		./configure \
			-arch $(ARCH) \
			-prefix $(CONFIGURE_PREFIX) \
			-bindir $(CONFIGURE_PREFIX)/bin \
			-libdir $(CONFIGURE_PREFIX)/lib \
			-datadir $(CONFIGURE_PREFIX)/share/Qt \
			-plugindir $(CONFIGURE_PREFIX)/lib/Qt/plugins \
			-demosdir $(CONFIGURE_PREFIX)/share/Qt/demos \
			-examplesdir $(CONFIGURE_PREFIX)/share/Qt/examples \
			-sysconfdir /etc/Qt \
			-no-rpath \
			-force-pkg-config \
			-continue \
			-make tools \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-demos),-make,-nomake) demos \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-examples),-make,-nomake) examples \
			-nomake docs \
			-nomake translations \
			-xplatform $(QMAKE_PLATFORM_PREFIX)linux-openwrt-g++ \
			-platform linux-g++ \
			$(if $(CONFIG_Qt4_WS_X11),-x11,-embedded) \
			-release \
			-confirm-license \
			-opensource \
			-stl \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-xmlpatterns),-xmlpatterns,-no-xmlpatterns) \
			-no-fast \
			-no-largefile \
			-exceptions \
			-no-mmx \
			-no-3dnow \
			-no-sse \
			-no-sse2 \
			-no-sse3 \
			-no-ssse3 \
			-no-sse4.1 \
			-no-sse4.2 \
			-no-avx \
			-no-neon \
			-no-armfpa \
			-system-zlib \
			-system-libtiff \
			-system-libpng \
			-system-libjpeg \
			-system-freetype \
			-system-sqlite \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-sqlite),-plugin-sql-sqlite) \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-mysql),-plugin-sql-mysql) \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-pgsql),-plugin-sql-psql) \
			-no-decoration-styled \
			-no-decoration-windows \
			-no-decoration-default \
			-verbose \
			-no-multimedia \
			-no-audio-backend \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-phonon),-phonon,-no-phonon) \
			-no-phonon-backend \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-svg),-svg,-no-svg) \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-webkit),-webkit,-no-webkit) \
			-no-javascript-jit \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-script),-script,-no-script) \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-scripttools),-scripttools,-no-scripttools) \
			-no-accessibility \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-declarative),-declarative,-no-declarative) \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-openssl),-openssl -I $(STAGING_DIR)/usr/include,-no-openssl) \
			-no-nis \
			-no-cups \
			-iconv \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-dbus),-dbus,-no-dbus) \
			-no-gtkstyle \
			-no-nas-sound \
			-no-opengl \
			-no-openvg \
			-no-sm \
			-no-xshape \
			$(if $(CONFIG_Qt4_WS_X11),-no-xsync,-xsync) \
			-no-xinerama \
			$(if $(CONFIG_Qt4_WS_X11),-no-xcursor,-xcursor) \
			-no-xfixes \
			-no-xrandr \
			-no-xrender \
			-no-mitshm \
			$(if $(CONFIG_Qt4_WS_X11),-no-fontconfig,-fontconfig) \
			$(if $(CONFIG_Qt4_WS_X11),-no-xinput,-xinput) \
			$(if $(CONFIG_Qt4_WS_X11),-no-xkb,-xkb) \
			-no-glib \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-qt3support),-qt3support,-no-qt3support) \
			-no-gfx-transformed \
			-no-gfx-qvfb \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-drivers-gfx-vnc),-plugin-gfx-vnc,-no-gfx-vnc) \
			-no-gfx-multiscreen \
			-no-gfx-qnx \
			$(if $(CONFIG_FEATURE_drawing-backend_DirectFB),$(if $(CONFIG_PACKAGE_directfb),-plugin-gfx-directfb)) \
			-plugin-gfx-linuxfb \
			-no-mouse-qvfb \
			-no-mouse-qnx \
			-qt-mouse-linuxinput \
			-plugin-mouse-linuxtp \
			-plugin-mouse-pc \
			$(if $(CONFIG_PACKAGE_$(PKG_NAME)-drivers-mouse-tslibmousedriver),-plugin-mouse-tslib) \
			-no-kbd-qvfb \
			-no-kbd-qnx \
			-qt-kbd-tty \
			-qt-kbd-linuxinput \
	)
endef

define Build/Compile
	# just passing <make install> results in not building 3rdparty/webkit/JavaScriptCore
	# unfortunately in this particular case, <make> makes further <qmake> calls, therewith
	#  uses the qmake.conf which needs get the cross-compiling vars passed once again
	TARGET_CC="$(TARGET_CROSS)gcc" \
	TARGET_CXX="$(TARGET_CROSS)g++" \
	TARGET_AR="$(TARGET_CROSS)ar cqs" \
	TARGET_OBJCOPY="$(TARGET_CROSS)objcopy" \
	TARGET_RANLIB="$(TARGET_CROSS)ranlib" \
	TARGET_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	TARGET_LDFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS)" \
	TARGET_INCDIRS="$(TARGET_INCDIRS)" \
	TARGET_LIBDIRS="$(TARGET_LIBDIRS)" \
	STAGING_DIR="$(STAGING_DIR)" \
	STAGING_DIR_HOST="$(STAGING_DIR_HOST)" \
	$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR)
	INSTALL_ROOT=$(PKG_INSTALL_DIR) \
		$(MAKE) -C $(PKG_BUILD_DIR) install
endef

define Build/InstallDev
	$(INSTALL_DIR) \
		$(STAGING_DIR_HOST)/bin

	# host tools (qmake, moc, rcc, uic)
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/bin/* \
		$(STAGING_DIR_HOST)/bin/

	$(INSTALL_DIR) \
		$(1)/mk \
		$(1)/usr/share/mkspecs \
		$(1)/usr/lib/pkgconfig \
		$(1)/usr/lib \
		$(1)/usr/include \
		$(1)/usr/lib/Qt/plugins

	$(CP) \
		./files/qmake.mk \
		$(1)/mk/

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/share/Qt/mkspecs/* \
		$(1)/usr/share/mkspecs/

	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/* \
		$(1)/usr/lib/pkgconfig/

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/* \
		$(1)/usr/include/

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/*.so* \
		$(1)/usr/lib/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/* \
	#	$(1)/usr/lib/Qt/plugins/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/usr/lib \
		$(1)/usr/lib/Qt/plugins

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtCore.so* \
		$(1)/usr/lib/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/codecs/*.so \
	#	$(1)/usr/lib/Qt/plugins/codecs/
endef

define Package/$(PKG_NAME)-gui/install
	$(INSTALL_DIR) \
		$(1)/usr/lib \
		$(1)/usr/lib/Qt/plugins

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtGui.so* \
		$(1)/usr/lib/

	#HACK: Qt4 requires having truetype fonts stored in /usr/lib/fonts - no subdirectories allowed,
	#so use the dejavue set by default
	#ln -s \
	#	/usr/share/fonts/ttf-dejavu \
	#	$(1)/usr/lib/fonts

	# we use the dejavue font package instead
	$(INSTALL_DIR) $(1)/usr/lib/fonts
	$(INSTALL_DATA) \
		$(PKG_INSTALL_DIR)/usr/lib/fonts/*.ttf \
		$(1)/usr/lib/fonts/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/accessible \
	#	$(1)/usr/lib/Qt/plugins/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/imageformats \
	#	$(1)/usr/lib/Qt/plugins/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/inputmethods \
	#	$(1)/usr/lib/Qt/plugins/
endef

define Package/$(PKG_NAME)-demos/install
	$(INSTALL_DIR) \
		$(1)/usr/share/Qt

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/share/Qt/demos \
		$(1)/usr/share/Qt/

	$(FIND) \
		$(1) \
		-name "*.cpp" -o \
		-name "*.h" -o \
		-name "*.pro" \
		| $(XARGS) rm
endef

define Package/$(PKG_NAME)-examples/install
	$(INSTALL_DIR) \
		$(1)/usr/share/Qt

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/share/Qt/examples \
		$(1)/usr/share/Qt/

	$(FIND) \
		$(1) \
		-name "*.cpp" -o \
		-name "*.h" -o \
		-name "*.pro" \
		| $(XARGS) rm
endef

define Package/$(PKG_NAME)-network/install
	$(INSTALL_DIR) \
		$(1)/usr/lib

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtNetwork.so* \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)-sqlite/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/sqldrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtSql.so* \
		$(1)/usr/lib/

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/sqldrivers/libqsqlite.so \
		$(1)/usr/lib/Qt/plugins/sqldrivers/
endef

define Package/$(PKG_NAME)-mysql/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/sqldrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtSql.so* \
		$(1)/usr/lib/

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/sqldrivers/libqsqlmysql.so \
		$(1)/usr/lib/Qt/plugins/sqldrivers/
endef

define Package/$(PKG_NAME)-pgsql/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/sqldrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtSql.so* \
		$(1)/usr/lib/

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/sqldrivers/libqsqlpsql.so \
		$(1)/usr/lib/Qt/plugins/sqldrivers/
endef

#define Package/$(PKG_NAME)-multimedia/install
#	$(INSTALL_DIR) \
#		$(1)/usr/bin
#
#	$(CP) \
#		$(PKG_INSTALL_DIR)/usr/bin/examples/* \
#		$(1)/usr/bin/
#endef

define Package/$(PKG_NAME)-phonon/install
	$(INSTALL_DIR) \
		$(1)/usr/lib

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libphonon.so* \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)-svg/install
	$(INSTALL_DIR) \
		$(1)/usr/lib \
		$(1)/usr/lib/Qt/plugins

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtSvg.so* \
		$(1)/usr/lib/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/iconengines \
	#	$(1)/usr/lib/Qt/plugins/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/imageformats \
	#	$(1)/usr/lib/Qt/plugins/
endef

define Package/$(PKG_NAME)-webkit/install
	$(INSTALL_DIR) \
		$(1)/usr/lib \
		$(1)/usr/lib/Qt/plugins

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtWebKit.so* \
		$(1)/usr/lib/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/designer \
	#	$(1)/usr/lib/Qt/plugins/
endef

define Package/$(PKG_NAME)-script/install
	$(INSTALL_DIR) \
		$(1)/usr/lib \
		$(1)/usr/lib/Qt/plugins

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtScript.so* \
		$(1)/usr/lib/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/script \
	#	$(1)/usr/lib/Qt/plugins/
endef

define Package/$(PKG_NAME)-scripttools/install
	$(INSTALL_DIR) \
		$(1)/usr/lib

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtScriptTools.so* \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)-dbus/install
	$(INSTALL_DIR) \
		$(1)/usr/lib

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtDBus.so* \
		$(1)/usr/lib/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/bin/qdbus \
	#	$(1)/usr/bin/
endef

define Package/$(PKG_NAME)-qt3support/install
	$(INSTALL_DIR) \
		$(1)/usr/lib \
		$(1)/usr/lib/Qt/plugins

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQt3Support.so* \
		$(1)/usr/lib/

	#$(CP) \
	#	$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/accessible \
	#	$(1)/usr/lib/Qt/plugins/
endef

define Package/$(PKG_NAME)-declarative/install
	$(INSTALL_DIR) \
		$(1)/usr/lib

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtDeclarative.so* \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)-xml/install
	$(INSTALL_DIR) \
		$(1)/usr/lib

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtXml.so* \
		$(1)/usr/lib/
endef

define Package/$(PKG_NAME)-xmlpatterns/install
	$(INSTALL_DIR) \
		$(1)/usr/lib

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libQtXmlPatterns.so* \
		$(1)/usr/lib/
endef

# plugins
#  mouse drivers
define Package/$(PKG_NAME)-drivers-mouse-tpmousedriver/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/mousedrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/mousedrivers/libqlinuxtpmousedriver.so \
		$(1)/usr/lib/Qt/plugins/mousedrivers/
endef

define Package/$(PKG_NAME)-drivers-mouse-pcmousedriver/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/mousedrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/mousedrivers/libqpcmousedriver.so \
		$(1)/usr/lib/Qt/plugins/mousedrivers/
endef

define Package/$(PKG_NAME)-drivers-mouse-tslibmousedriver/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/mousedrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/mousedrivers/libqtslibmousedriver.so \
		$(1)/usr/lib/Qt/plugins/mousedrivers/
endef

#  graphics drivers
define Package/$(PKG_NAME)-drivers-gfx-directfb/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/gfxdrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/gfxdrivers/libqdirectfbscreen.so \
		$(1)/usr/lib/Qt/plugins/gfxdrivers/
endef

define Package/$(PKG_NAME)-drivers-gfx-linuxfb/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/gfxdrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/gfxdrivers/libqscreenlinuxfb.so \
		$(1)/usr/lib/Qt/plugins/gfxdrivers/
endef

define Package/$(PKG_NAME)-drivers-gfx-vnc/install
	$(INSTALL_DIR) \
		$(1)/usr/lib/Qt/plugins/gfxdrivers

	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/Qt/plugins/gfxdrivers/libqgfxvnc.so \
		$(1)/usr/lib/Qt/plugins/gfxdrivers/
endef

#  keyboard drivers



$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)-gui))
$(eval $(call BuildPackage,$(PKG_NAME)-demos))
$(eval $(call BuildPackage,$(PKG_NAME)-examples))
$(eval $(call BuildPackage,$(PKG_NAME)-network))
$(eval $(call BuildPackage,$(PKG_NAME)-sqlite))
$(eval $(call BuildPackage,$(PKG_NAME)-mysql))
$(eval $(call BuildPackage,$(PKG_NAME)-pgsql))
$(eval $(call BuildPackage,$(PKG_NAME)-openssl))
#$(eval $(call BuildPackage,$(PKG_NAME)-multimedia))
#$(eval $(call BuildPackage,$(PKG_NAME)-audio-backend))
$(eval $(call BuildPackage,$(PKG_NAME)-phonon))
#$(eval $(call BuildPackage,$(PKG_NAME)-phonon-backend))
$(eval $(call BuildPackage,$(PKG_NAME)-svg))
$(eval $(call BuildPackage,$(PKG_NAME)-webkit))
$(eval $(call BuildPackage,$(PKG_NAME)-script))
$(eval $(call BuildPackage,$(PKG_NAME)-scripttools))
#$(eval $(call BuildPackage,$(PKG_NAME)-accessibility))
#$(eval $(call BuildPackage,$(PKG_NAME)-javascript-jit))
#$(eval $(call BuildPackage,$(PKG_NAME)-cups))
$(eval $(call BuildPackage,$(PKG_NAME)-dbus))
#$(eval $(call BuildPackage,$(PKG_NAME)-gtkstyle))
#$(eval $(call BuildPackage,$(PKG_NAME)-glib))
$(eval $(call BuildPackage,$(PKG_NAME)-qt3support))
$(eval $(call BuildPackage,$(PKG_NAME)-declarative))
$(eval $(call BuildPackage,$(PKG_NAME)-xml))
$(eval $(call BuildPackage,$(PKG_NAME)-xmlpatterns))

$(eval $(call BuildPackage,$(PKG_NAME)-drivers-mouse-tpmousedriver))
$(eval $(call BuildPackage,$(PKG_NAME)-drivers-mouse-pcmousedriver))
$(eval $(call BuildPackage,$(PKG_NAME)-drivers-mouse-tslibmousedriver))

$(eval $(call BuildPackage,$(PKG_NAME)-drivers-gfx-directfb))
$(eval $(call BuildPackage,$(PKG_NAME)-drivers-gfx-linuxfb))
$(eval $(call BuildPackage,$(PKG_NAME)-drivers-gfx-vnc))
