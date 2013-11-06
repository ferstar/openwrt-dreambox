TEMPLATE	= app
CONFIG		+= qtopia warn_on release
HEADERS		= inlineedit.h \
		  services.h \
		  filebrowser.h
SOURCES		= filebrowser.cpp \
		  services.cpp \
		  inlineedit.cpp \
		  main.cpp

INTERFACES	= 
TARGET		= filebrowser
TRANSLATIONS = filebrowser-en_GB.ts filebrowser-de.ts filebrowser-ja.ts filebrowser-no.ts
