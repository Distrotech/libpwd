/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2004-2005 William Lachance (wrlach@gmail.com)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H
#include <librevenge-stream/librevenge-stream.h>

class WPXMemoryInputStream : public RVNGInputStream
{
public:
	WPXMemoryInputStream(unsigned char *data, unsigned long size);
	virtual ~WPXMemoryInputStream();

	virtual bool isOLEStream()
	{
		return false;
	}
	virtual RVNGInputStream *getDocumentOLEStream(const char *)
	{
		return 0;
	}

	virtual const unsigned char *read(unsigned long numBytes, unsigned long &numBytesRead);
	virtual int seek(long offset, RVNG_SEEK_TYPE seekType);
	virtual long tell();
	virtual bool atEOS();
	virtual unsigned long getSize() const
	{
		return m_size;
	}

private:
	long m_offset;
	unsigned long m_size;
	unsigned char *m_data;
	WPXMemoryInputStream(const WPXMemoryInputStream &);
	WPXMemoryInputStream &operator=(const WPXMemoryInputStream &);
};

#endif
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
