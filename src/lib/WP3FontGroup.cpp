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
#include "WP3FontGroup.h"
#include "WP3FileStructure.h"
#include "libwpd_internal.h"
#include "libwpd_math.h"

WP3FontGroup::WP3FontGroup(WPXInputStream *input) :
	WP3VariableLengthGroup(),
	m_fontName(NULL),
	m_fontSize(0)
{
	_read(input);
}

WP3FontGroup::~WP3FontGroup()
{
	// fixme delete the font name
}

void WP3FontGroup::_readContents(WPXInputStream *input)
{
	// this group can contain different kinds of data, thus we need to read
	// the contents accordingly
	uint8_t tmpFontNameLength;
	switch (getSubGroup())
	{
	case WP3_FONT_GROUP_SET_TEXT_FONT:
		input->seek(12, WPX_SEEK_CUR);
		tmpFontNameLength = readU8(input);
		m_fontName = new char[tmpFontNameLength+1];
		for (uint8_t i=0; i<tmpFontNameLength; i++)
			m_fontName[i]=readU8(input);
		m_fontName[tmpFontNameLength]='\0';
		break;
	case WP3_FONT_GROUP_SET_FONT_SIZE:
		input->seek(2, WPX_SEEK_CUR);
		m_fontSize = readU16(input, true);
		break;
	default: /* something else we don't support, since it isn't in the docs */
		break;
	}
}

void WP3FontGroup::parse(WP3Listener *listener)
{
	WPD_DEBUG_MSG(("WordPerfect: handling a Page group\n"));

	switch (getSubGroup())
	{
	case WP3_FONT_GROUP_SET_TEXT_FONT:
		listener->setTextFont(m_fontName);
		delete [] m_fontName;
		break;
	case WP3_FONT_GROUP_SET_FONT_SIZE:
		listener->setFontSize(m_fontSize);
		break;
	default: // something else we don't support, since it isn't in the docs
		break;
	}
}
