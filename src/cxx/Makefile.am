EXTRA_DIST = libinifile++.pc libinifile++.pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libinifile++.pc

lib_LTLIBRARIES = libinifile++.la

libinifile___la_SOURCES = inifile++.hpp inifile++.cpp 
libinifile___la_LDFLAGS = -version-info 4:0:0 
libinifile___la_LIBADD  = $(top_srcdir)/src/libinifile.la

AM_CPPFLAGS = -I$(top_srcdir)/src/cxx -I$(top_srcdir)/src

library_includedir=$(includedir)
library_include_HEADERS = inifile++.hpp
