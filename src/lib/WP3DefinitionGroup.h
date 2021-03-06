/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#ifndef WP3DEFINITIONGROUP_H
#define WP3DEFINITIONGROUP_H

#include "WP3VariableLengthGroup.h"
#include "libwpd_types.h"
#include <vector>

class WPXInputStream;
class WP3Listener;

class WP3DefinitionGroup : public WP3VariableLengthGroup
{
public:
	WP3DefinitionGroup(WPXInputStream *input, WPXEncryption *encryption);
	~WP3DefinitionGroup();
	void _readContents(WPXInputStream *input, WPXEncryption *encryption);
	void parse(WP3Listener *listener);

private:
	/* Variables used for subgroup 0x01 Set Columns On/Off */
	uint8_t m_colType;
	uint8_t m_numColumns;
	std::vector<bool> m_isFixedWidth;
	std::vector<double> m_columnWidth;

};

#endif /* WP3DefinitionGroup_H */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
