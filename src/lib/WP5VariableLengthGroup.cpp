/* libwpd2
 * Copyright (C) 2003 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2003 Marc Maurer (j.m.maurer@student.utwente.nl)
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

#include "WP5VariableLengthGroup.h"
#include "WP5UnsupportedVariableLengthGroup.h"
#include "libwpd_internal.h"

WP5VariableLengthGroup::WP5VariableLengthGroup(guint8 group)
	: m_group(group)
{
}

WP5VariableLengthGroup * WP5VariableLengthGroup::constructVariableLengthGroup(GsfInput *input, guint8 group)
{
	switch (group)
	{
		default:
			// this is an unhandled group, just skip it
			return new WP5UnsupportedVariableLengthGroup(input, group);
	}
}

void WP5VariableLengthGroup::_read(GsfInput *input)
{
	guint32 startPosition = gsf_input_tell(input);

	WPD_DEBUG_MSG(("WordPerfect: handling a variable length group (group id: 0x%x)\n", m_group));	
	
	m_subGroup = gsf_le_read_guint8(input);
	m_size = gsf_le_read_guint16(input) + 4; // the length is the number of data bytes minus 4 (ie. the function codes)
	
	WPD_DEBUG_MSG(("WordPerfect: Read variable group header (start_position: %i, sub_group: 0x%x, size: %i)\n", startPosition, m_subGroup, m_size));
	
	_readContents(input);
	
	WPD_CHECK_FILE_SEEK_ERROR(gsf_input_seek(input, (startPosition + m_size - 1 - gsf_input_tell(input)), G_SEEK_CUR));

}