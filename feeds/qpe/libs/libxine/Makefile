#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libxine
PKG_VERSION:=1.1.1
PKG_RELEASE:=2

PKG_SOURCE:=xine-lib-$(PKG_VERSION).tar.gz
PKG_BUILD_DIR=$(BUILD_DIR)/xine-lib-$(PKG_VERSION)
PKG_SOURCE_URL:=@SF/xine
PKG_MD5SUM:=b1f42602c776bb93e3cbf127e220cbfd

#PKG_FIXUP:=libtool
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

CONFIGURE_ARGS+=\
	--enable-static \
	--disable-vcd \
	--disable-imagemagick \
	--disable-flac

XINE_LIB_FLAGS:=\
	LIBFLAC_CFLAGS="" \
	LIBFLAC_LIBS="" \
	X_CFLAGS="" \
	X_LIBS="" \
	XINE_ACFLAGS="" \
	CXXFLAGS="$(TARGET_CFLAGS)"

CONFIGURE_VARS+=$(XINE_LIB_FLAGS)

define Package/$(PKG_NAME)
  TITLE:=xine libraries
  CATEGORY:=Qt/Qtopia
  SUBMENU:=libs
  SECTION:=qpe-$(SUBMENU)
  DEPENDS:=+alsa-lib +zlib +libfreetype
  URL:=http://www.xine-project.org/
endef

define Package/$(PKG_NAME)/description
  xine is a free multimedia player. It plays back CDs, DVDs, and VCDs.
  It also decodes multimedia files like AVI, MOV, WMV, and MP3 
  from local disk drives, and displays multimedia streamed over the Internet.
  It interprets many of the most common multimedia formats available – 
  and some of the most uncommon formats, too.
endef

MAKE_FLAGS+=$(XINE_LIB_FLAGS)

define Build/InstallDev
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_INSTALL_DIR)/* $(1)/
	$(SED) 's,-I$$$${prefix}/include,-I$(STAGING_DIR)/usr/include/,g' $(1)/usr/bin/xine-config 
	$(SED) 's,-L$$$${exec_prefix}/lib,-L$(STAGING_DIR)/usr/lib/,g' $(1)/usr/bin/xine-config
	$(INSTALL_DIR) $(2)/bin
	mv $(1)/usr/bin/xine-config $(2)/bin
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
