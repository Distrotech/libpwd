/* libwpd
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
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

#include <math.h>
#include "WP3FootnoteEndnoteGroup.h"
#include "WP3FileStructure.h"
#include "WP3Parser.h"

WP3FootnoteEndnoteGroup::WP3FootnoteEndnoteGroup(WPXInputStream *input) :
	WP3VariableLengthGroup(),
	m_stream(NULL)
{
	_read(input);
}

WP3FootnoteEndnoteGroup::~WP3FootnoteEndnoteGroup()
{
	delete m_stream;
}

void WP3FootnoteEndnoteGroup::_readContents(WPXInputStream *input)
{
	int tmpSizeOfNote = getSize() - 6;
	input->seek(25, WPX_SEEK_CUR);
	tmpSizeOfNote -= 25;
	int tmpNumOfPages = readU16(input, true);
	tmpSizeOfNote -= 2;
	int i;
	for (i=0; i<tmpNumOfPages; i++)
	{
		input->seek(4, WPX_SEEK_CUR);
		tmpSizeOfNote -= 4;
	}
	int tmpNumBreakTableEntries = readU16(input, true);
	tmpSizeOfNote -= 2;
	for (i=0; i<tmpNumBreakTableEntries; i++)
	{
		input->seek(6, WPX_SEEK_CUR);
		tmpSizeOfNote -= 6;
	}
	// here we skipped all the useless junk and we are at the beginning of the
	// actual subdocument. tmpSizeOfNote should give the size in bytes of the
	// subdocument

	uint8_t *streamData = new uint8_t[tmpSizeOfNote];
	for (i=0; i<tmpSizeOfNote; i++)
	{
		streamData[i] = readU8(input);
	}
	m_stream = new WPXMemoryInputStream(streamData, tmpSizeOfNote);
	}

void WP3FootnoteEndnoteGroup::parse(WP3Listener *listener)
{
	WPD_DEBUG_MSG(("WordPerfect: handling a Footnote/Endnote group\n"));
	m_stream->seek(0, WPX_SEEK_SET);
	switch (getSubGroup())
	{
	case WP3_FOOTNOTE_ENDNOTE_GROUP_FOOTNOTE_FUNCTION:
		break;
	case WP3_FOOTNOTE_ENDNOTE_GROUP_ENDNOTE_FUNCTION:
		break;
	default: // something else we don't support, since it isn't in the docs
		break;
	}
}
