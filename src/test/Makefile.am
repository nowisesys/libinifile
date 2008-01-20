bin_PROGRAMS = clibtest cxxlibtest

clibtest_SOURCES = clibtest.c
clibtest_LDADD = -L$(top_srcdir)/src/.libs -linifile

cxxlibtest_SOURCES = cxxlibtest.cpp
cxxlibtest_LDADD = -L$(top_srcdir)/src/cxx/.libs -linifile++

INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/cxx
