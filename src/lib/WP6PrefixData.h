/* libwpd2
 * Copyright (C) 2002 William Lachance (wlach@interlog.com)
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

#ifndef WP6PREFIXDATA_H
#define WP6PREFIXDATA_H
#include <glib.h>
#include <gsf/gsf-input.h>
#include "WP6PrefixDataPacket.h"

class WP6PrefixData
{
 public:
	WP6PrefixData(GsfInput *input, const int numPrefixIndices);
	virtual ~WP6PrefixData();
	const WP6PrefixDataPacket *getPrefixDataPacket(const int prefixID) const;
	const guint16 getDefaultInitialFontPID() const { return m_defaultInitialFontPID; }

 private:
	GHashTable *m_prefixDataPacketHash;
	int m_defaultInitialFontPID;
};

#endif /* WP6PREFIXDATA_H */