if BUILD_TOOLS

bin_PROGRAMS = wpd2raw

AM_CXXFLAGS = -I$(top_srcdir)/inc $(REVENGE_CFLAGS) $(REVENGE_GENERATORS_CFLAGS) $(DEBUG_CXXFLAGS)

wpd2raw_DEPENDENCIES = @WPD2RAW_WIN32_RESOURCE@

wpd2raw_LDADD = \
	../../lib/libwpd-@WPD_MAJOR_VERSION@.@WPD_MINOR_VERSION@.la \
	$(REVENGE_LIBS) \
	$(REVENGE_GENERATORS_LIBS) \
	$(REVENGE_STREAM_LIBS) \
	@WPD2RAW_WIN32_RESOURCE@

wpd2raw_SOURCES = \
	wpd2raw.cpp

if OS_WIN32

@WPD2RAW_WIN32_RESOURCE@ : wpd2raw.rc $(wpd2raw_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource && \
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource wpd2raw.rc @WPD2RAW_WIN32_RESOURCE@
endif

# Include the wpd2raw_SOURCES in case we build a tarball without stream
EXTRA_DIST = \
	$(wpd2raw_SOURCES)	\
	wpd2raw.rc.in

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	wpd2raw.rc	 
 
endif
