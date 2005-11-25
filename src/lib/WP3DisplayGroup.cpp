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
#include "WP3DisplayGroup.h"
#include "WP3FileStructure.h"
#include "libwpd_internal.h"
#include "libwpd_math.h"

WP3DisplayGroup::WP3DisplayGroup(WPXInputStream *input) :
	WP3VariableLengthGroup(),
	m_noteReference(NULL)
	
{
	_read(input);
}

WP3DisplayGroup::~WP3DisplayGroup()
{
	if (m_noteReference)
		delete [] m_noteReference;
}

void WP3DisplayGroup::_readContents(WPXInputStream *input)
{
	input->seek(4, WPX_SEEK_CUR);
	uint8_t tmpNoteReferenceLength = readU8(input);
	m_noteReference = new char[tmpNoteReferenceLength+1];
	for (uint8_t i=0; i < tmpNoteReferenceLength; i++)
		m_noteReference[i]=readU8(input);
	m_noteReference[tmpNoteReferenceLength]='\0';
}

void WP3DisplayGroup::parse(WP3Listener *listener)
{
	WPD_DEBUG_MSG(("WordPerfect: handling a Display group\n"));

	switch (getSubGroup())
	{
	case WP3_DISPLAY_GROUP_INSERT_FOOTNOTE_NUMBER:
		listener->insertNoteReference(FOOTNOTE, m_noteReference);
		break;
	case WP3_DISPLAY_GROUP_INSERT_ENDNOTE_NUMBER:
		listener->insertNoteReference(ENDNOTE, m_noteReference);
		break;
	default: // something else we don't support, since it isn't in the docs
		break;
	}
	
//	if (m_noteReference)
//		delete [] m_noteReference;
}
