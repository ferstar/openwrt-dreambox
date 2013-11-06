#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=murphytalk.pinyin
PKG_VERSION:=0.03
PKG_RELEASE:=3
PKG_MD5SUM:=2d75438b2a8131b69399993619df7574

PKG_SOURCE:=MurphyPinyin-$(PKG_VERSION)-src.tgz
PKG_SOURCE_URL:=http://sourceforge.net/projects/murphypinyin/files/murphypinyin/0.03/ \
	https://openwrt-for-embedded.googlecode.com/files/
PKG_BUILD_DIR=$(BUILD_DIR)/MurphyPinyin

PKG_FIXUP:=libtool

include $(INCLUDE_DIR)/package.mk
-include $(STAGING_DIR)/mk/qpe-package.mk
QPE_DEPENDS:=+qpe-build @PACKAGE_opie||@PACKAGE_opie-sl||@PACKAGE_qtopia||@PACKAGE_qtopia-sl

define Package/$(PKG_NAME)
  TITLE:=MurphyPinyin a Chinese Input Method
  CATEGORY:=Qt/Qtopia
  SUBMENU:=qpe-apps
  SECTION:=qtopia-$(SUBMENU)
  DEPENDS:=+qpe-build +libc +libgcc +libstdcpp $(QPE_DEPENDS)
  URL:=http://www.qkevin.com/
  MAINTAINER:=Richard Nee <richard.nee.cn@gmail.com>
endef

define Package/$(PKG_NAME)/description
  MurphyPinyin a Chinese Input Method,
  Port of Scim Chinese of James Su,released under GPL.
  Maintainer: MurphyTalk(murphytalk@gmail.com) SunsetYang(sunsetyang@gmail.com)
endef

# need omp.h of libgomp in toolchain !
define Build/Prepare
	$(call Build/Prepare/Default)
	( \
	if [ ! -e $(TOOLCHAIN_DIR)/usr/include/omp.h -a ! -e $(TOOLCHAIN_DIR)/usr/$(ARCH)-openwrt-linux/include/omp.h ] ; then \
		$(CP) ./files/omp.h $(TOOLCHAIN_DIR)/usr/$(ARCH)-openwrt-linux/include/ ; \
	fi ; \
	)
endef

define Build/Compile
	$(call Build/Compile/QPE)
endef

# maybe, database-0.02 should be used, as fatal errors when shortening !
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) \
		$(1)/$(QPE_INSTALLDIR)/plugins/inputmethods/

	$(CP) $(PKG_BUILD_DIR)/DIST/libmurphypinyin.so* $(1)/$(QPE_INSTALLDIR)/plugins/inputmethods/
	$(CP) ./files/qmurphypinyin.desktop $(1)/$(QPE_INSTALLDIR)/plugins/inputmethods/
	$(CP) ./files/murphytalk/ $(1)/opt/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
