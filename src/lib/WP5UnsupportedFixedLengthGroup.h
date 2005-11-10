/* libwpd
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

#ifndef WP5UNSUPPORTEDFIXEDLENGTHGROUP_H
#define WP5UNSUPPORTEDFIXEDLENGTHGROUP_H

#include "WP5FixedLengthGroup.h"

class WP5UnsupportedFixedLengthGroup : public WP5FixedLengthGroup
{
 public:
	WP5UnsupportedFixedLengthGroup(WPXInputStream *input, uint8_t groupID);	
	virtual void parse(WP5Listener *listener) {}
	
 protected:
	virtual void _readContents(WPXInputStream *input) {}
};

#endif /* WP5UNSUPPORTEDFIXEDLENGTHGROUP_H */
