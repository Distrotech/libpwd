/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2004 Marc Maurer (uwog@uwog.net)
 * Copyright (C) 2006 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#ifndef WP3FIXEDLENGTHGROUP_H
#define WP3FIXEDLENGTHGROUP_H

#include <librevenge/librevenge.h>
#include "WP3Part.h"

class WPXEncryption;

class WP3FixedLengthGroup : public WP3Part
{
public:
	WP3FixedLengthGroup(const uint8_t groupID);
	static WP3FixedLengthGroup *constructFixedLengthGroup(RVNGInputStream *input, WPXEncryption *encryption, uint8_t const groupID);

	static bool isGroupConsistent(RVNGInputStream *input, WPXEncryption *encryption, const uint8_t groupID);

	uint8_t getGroup() const
	{
		return m_group;
	}

protected:
	void _read(RVNGInputStream *input, WPXEncryption *encryption);
	virtual void _readContents(RVNGInputStream *input, WPXEncryption *encryption) = 0; // we always read the contents in the case of a fixed length group
private:
	uint8_t m_group;
};

#endif /* WP3FIXEDLENGTHGROUP_H */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
