/* libwpd
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
 * Copyright (C) 2004 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#ifndef WP3MISCELLANEOUSGROUP_H
#define WP3MISCELLANEOUSGROUP_H

#include "WP3VariableLengthGroup.h"

class WP3MiscellaneousGroup : public WP3VariableLengthGroup
{
 public:
	WP3MiscellaneousGroup(WPXInputStream *input);	
	virtual ~WP3MiscellaneousGroup();
	virtual void _readContents(WPXInputStream *input);
	virtual void parse(WP3Listener *listener);

 private:
	// variables needed for subgroup 4 (Page Size Override)
	uint16_t m_pageWidth;
	uint16_t m_pageHeight;
	WPXFormOrientation m_pageOrientation;
	bool m_isPersistent;
};

#endif /* WP3MISCELLANEOUSGROUP_H */
