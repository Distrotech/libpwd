if BUILD_TOOLS

bin_PROGRAMS = wpd2text

AM_CXXFLAGS = -I$(top_srcdir)/inc $(REVENGE_CFLAGS) $(REVENGE_GENERATORS_CFLAGS) $(DEBUG_CXXFLAGS)

wpd2text_DEPENDENCIES = @WPD2TEXT_WIN32_RESOURCE@ 

wpd2text_LDADD = \
	../../lib/libwpd-@WPD_MAJOR_VERSION@.@WPD_MINOR_VERSION@.la \
	$(REVENGE_LIBS) \
	$(REVENGE_GENERATORS_LIBS) \
	$(REVENGE_STREAM_LIBS) \
	@WPD2TEXT_WIN32_RESOURCE@
 
wpd2text_SOURCES = \
	wpd2text.cpp

if OS_WIN32

@WPD2TEXT_WIN32_RESOURCE@ : wpd2text.rc $(wpd2text_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource && \
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource wpd2text.rc @WPD2TEXT_WIN32_RESOURCE@
endif

# Include the wpd2text_SOURCES in case we build a tarball without stream
EXTRA_DIST = \
	$(wpd2text_SOURCES) \
	wpd2text.rc.in

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	wpd2text.rc	 
 
endif
