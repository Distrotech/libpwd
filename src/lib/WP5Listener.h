/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2003 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2003 Marc Maurer (uwog@uwog.net)
 * Copyright (C) 2005-2007 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#ifndef WP5LISTENER_H
#define WP5LISTENER_H

#include <vector>
#include <librevenge/librevenge.h>
#include "libwpd_internal.h"

class WP5SubDocument;
class WP5PrefixData;
class WP5GeneralPacketData;

class WP5Listener
{
public:
	WP5Listener();
	virtual ~WP5Listener() {}

	virtual void startDocument() = 0;
	virtual void startSubDocument() = 0;
	virtual void setFont(const librevenge::RVNGString &fontName, double fontSize) = 0;
	virtual void setTabs(const std::vector<WPXTabStop> &tabStops, uint16_t tabOffset) = 0;
	virtual void insertCharacter(uint32_t character) = 0;
	virtual void insertTab(uint8_t tabType, double tabPosition) = 0;
	virtual void insertIndent(uint8_t indentType, double indentPosition) = 0;
	virtual void insertEOL() = 0;
	virtual void insertBreak(uint8_t breakType) = 0;
	virtual void lineSpacingChange(double lineSpacing) = 0;
	virtual void justificationChange(uint8_t justification) = 0;
	virtual void characterColorChange(uint8_t red, uint8_t green, uint8_t blue) = 0;
	virtual void attributeChange(bool isOn, uint8_t attribute) = 0;
	virtual void pageMarginChange(uint8_t side, uint16_t margin) = 0;
	virtual void pageFormChange(uint16_t length, uint16_t width, WPXFormOrientation orientation) = 0;
	virtual void marginChange(uint8_t side, uint16_t margin) = 0;
	virtual void endDocument() = 0;
	virtual void endSubDocument() = 0;

	virtual void defineTable(uint8_t position, uint16_t leftOffset) = 0;
	virtual void addTableColumnDefinition(uint32_t width, uint32_t leftGutter, uint32_t rightGutter,
	                                      uint32_t attributes, uint8_t alignment) = 0;
	virtual void startTable() = 0;
	virtual void insertRow(uint16_t rowHeight, bool isMinimumHeight, bool isHeaderRow) = 0;
	virtual void insertCell(uint8_t colSpan, uint8_t rowSpan, uint8_t borderBits,
	                        const RGBSColor *cellFgColor, const RGBSColor *cellBgColor,
	                        const RGBSColor *cellBorderColor, WPXVerticalAlignment cellVerticalAlignment,
	                        bool useCellAttributes, uint32_t cellAttributes) = 0;
	virtual void endTable() = 0;

	virtual void insertNoteReference(const librevenge::RVNGString &noteReference) = 0;
	virtual void insertNote(WPXNoteType noteType, const WP5SubDocument *subDocument) = 0;
	virtual void headerFooterGroup(uint8_t headerFooterType, uint8_t occurrenceBits, WP5SubDocument *subDocument) = 0;
	virtual void suppressPageCharacteristics(uint8_t suppressCode) = 0;

	virtual void boxOn(uint8_t positionAndType, uint8_t alignment, uint16_t width, uint16_t height, uint16_t x, uint16_t y) = 0;
	virtual void boxOff() = 0;
	virtual void insertGraphicsData(const librevenge::RVNGBinaryData *data) = 0;

	void setPrefixData(WP5PrefixData *prefixData)
	{
		m_prefixData = prefixData;
	}
	const WP5GeneralPacketData *getGeneralPacketData(const int type) const;

private:
	WP5Listener(const WP5Listener &);
	WP5Listener &operator=(const WP5Listener &);
	WP5PrefixData *m_prefixData;
};

#endif /* WP5LISTENER_H */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
