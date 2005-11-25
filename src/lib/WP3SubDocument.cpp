/* libwpd
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#include "WP3SubDocument.h"
#include "WP3Parser.h"
#include "libwpd_internal.h"

WP3SubDocument::WP3SubDocument(WPXInputStream *input, int dataSize) :
	m_stream(NULL)
{
	uint8_t *streamData = new uint8_t[dataSize];
	for (int i=0; i<dataSize; i++)
	{
		streamData[i] = readU8(input);
	}
	m_stream = new WPXMemoryInputStream(streamData, dataSize);
}

WP3SubDocument::~WP3SubDocument()
{
	delete m_stream;
}

void WP3SubDocument::parse(WP3Listener *listener) const
{
	m_stream->seek(0, WPX_SEEK_SET);
	WP3Parser::parseDocument(m_stream, listener);
}
