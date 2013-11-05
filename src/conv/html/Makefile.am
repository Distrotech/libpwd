if BUILD_TOOLS

bin_PROGRAMS = wpd2html

AM_CXXFLAGS = -I$(top_srcdir)/inc $(REVENGE_CFLAGS) $(REVENGE_GENERATORS_CFLAGS) $(DEBUG_CXXFLAGS)

wpd2html_DEPENDENCIES = @WPD2HTML_WIN32_RESOURCE@

wpd2html_LDADD = \
	../../lib/libwpd-@WPD_MAJOR_VERSION@.@WPD_MINOR_VERSION@.la \
	$(REVENGE_LIBS) \
	$(REVENGE_GENERATORS_LIBS) \
	$(REVENGE_STREAM_LIBS) \
	@WPD2HTML_WIN32_RESOURCE@

wpd2html_SOURCES = \
	wpd2html.cpp

if OS_WIN32

@WPD2HTML_WIN32_RESOURCE@ : wpd2html.rc $(wpd2html_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource && \
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource wpd2html.rc @WPD2HTML_WIN32_RESOURCE@
endif

# Include the wpd2html_SOURCES in case we build a tarball without stream
EXTRA_DIST = \
	$(wpd2html_SOURCES)	\
	wpd2html.rc.in

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	wpd2html.rc	 

endif
