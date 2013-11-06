#
# Copyright (C) 2012 Openwrt-for-Embedded http://code.google.com/p/openwrt-for-embedded/
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#


QT_NAME:=Qt2
QTOPIA_NAME:=Qtopia
OPIE_NAME:=QtPalmtop

#1. development $(STAGING_DIR)/usr/lib/Qt
DEV_QTDIR:=$(STAGING_DIR)/usr/lib/$(QT_NAME)
DEV_QTOPIADIR:=$(DEV_QTDIR)/$(QTOPIA_NAME)
DEV_OPIEDIR:=$(DEV_QTDIR)/$(OPIE_NAME)

#2. install $(1)/opt/Qtopia
INSTALL_QTDIR:=/usr/lib
INSTALL_QTOPIADIR:=/opt/$(QTOPIA_NAME)
INSTALL_OPIEDIR:=/opt/$(OPIE_NAME)
## INSTALL_QTOPIADIR or INSTALL_OPIEDIR
QPE_INSTALLDIR:=

#3. install simulation
HOST_SLDIR:=$(TOPDIR)/bin/host

###### depends ####
QPE_DEPENDS:=+qpe-build @PACKAGE_opie||@PACKAGE_opie-sl||@PACKAGE_qtopia||@PACKAGE_qtopia-sl
QTE_DEPENDS:=+qpe-build @PACKAGE_qte2||@PACKAGE_qte2-sl

###### qpe = (qtopia/opie) ######
# default Qtopia
ifneq ($(CONFIG_PACKAGE_opie)$(CONFIG_PACKAGE_opie-sl),)
	QPE_PREFIX:=$(DEV_OPIEDIR)
	QPE_INSTALLDIR:=$(INSTALL_OPIEDIR)
else
	QPE_PREFIX:=$(DEV_QTOPIADIR)
	QPE_INSTALLDIR:=$(INSTALL_QTOPIADIR)
endif

QPE_CFLAGS:=-I$(QPE_PREFIX)/include
QPE_CXXFLAGS:=-I$(QPE_PREFIX)/include
QPE_LDFLAGS:=-Wl,-rpath-link=$(QPE_PREFIX)/lib -L$(QPE_PREFIX)/lib

QPEDIR:=$(QPE_PREFIX)
#OPIEDIR:=

########### qte ###########
QTE_PREFIX:=$(DEV_QTDIR)
QTE_INSTALLDIR:=$(INSTALL_QTDIR)
QTE_CFLAGS:=-I$(QTE_PREFIX)/include
QTE_CXXFLAGS:=-I$(QTE_PREFIX)/include
QTE_LDFLAGS:=-Wl,-rpath-link=$(QTE_PREFIX)/lib -L$(QTE_PREFIX)/lib

QTDIR:=$(QTE_PREFIX)

########## flags ##########
TARGET_CFLAGS +=-I$(STAGING_DIR)/usr/include \
	$(QPE_CFLAGS) \
	$(QTE_CFLAGS)
TARGET_CXXFLAGS +=-I$(STAGING_DIR)/usr/include \
	$(QPE_CXXFLAGS) \
	$(QTE_CXXFLAGS)
TARGET_LDFLAGS +=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib \
	$(QPE_LDFLAGS) \
	$(QTE_LDFLAGS)

##########################################################
ifneq ($(CONFIG_PACKAGE_qte2-sl)$(CONFIG_PACKAGE_qtopia-sl)$(CONFIG_PACKAGE_opie-sl),)
QPE_SIMULATION:=y
endif

define Build/Compile/QPE

ifeq ($(QPE_SIMULATION),y)

	$(MAKE) -C $(PKG_BUILD_DIR)/$(MAKE_PATH) \
		TARGET_CFLAGS="$(QTE_CFLAGS) $(QPE_CFLAGS)" \
		TARGET_CXXFLAGS="$(QTE_CXXFLAGS) $(QPE_CXXFLAGS)" \
		TARGET_LDFLAGS="$(QTE_LDFLAGS) $(QPE_LDFLAGS)" \
		QTDIR="$(QTDIR)" \
		QPEDIR="$(QPEDIR)" \
		$(1);

else
	$(MAKE) -C $(PKG_BUILD_DIR)/$(MAKE_PATH) \
		TARGET_CROSS="$(TARGET_CROSS)" \
		TARGET_CFLAGS="$(TARGET_CFLAGS)" \
		TARGET_CXXFLAGS="$(TARGET_CXXFLAGS)" \
		TARGET_LDFLAGS="$(TARGET_LDFLAGS)" \
		QTDIR="$(QTDIR)" \
		QPEDIR="$(QPEDIR)" \
		$(1);

endif

endef

define HostSimulation/Install/QPE

ifeq ($(QPE_SIMULATION),y)

	$(INSTALL_DIR) $(if $(2), $(2), $(HOST_SLDIR) ); \
	$(CP) $(1) $(if $(2), $(2), $(HOST_SLDIR) );

endif

endef

