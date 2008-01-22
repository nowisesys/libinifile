EXTRA_DIST = libinifile++.pc libinifile++.pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libinifile++.pc

lib_LTLIBRARIES = libinifile++.la
libinifile___la_SOURCES = inifile++.hpp inifile++.cpp ../inifile.c \
			  ../lexer.c ../parser.c ../token.c
libinifile___la_LDFLAGS = -version-info 4:0:0 

INCLUDES = -I$(top_srcdir)/src/cxx -I$(top_srcdir)/src
