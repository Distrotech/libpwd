/* libwpd
 * Copyright (C) 2004 Marc Maurer (j.m.maurer@student.utwente.nl)
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

#ifndef WP3HLLISTENER_H
#define WP3HLLISTENER_H

#include "WPXListener.h"
#include "WPXHLListenerImpl.h"

typedef struct _WP3ParsingState WP3ParsingState;
struct _WP3ParsingState
{
	_WP3ParsingState();
	~_WP3ParsingState();
};


class WP3Listener : public WPXListener
{
public:
	WP3Listener(std::vector<WPXPageSpan *> *pageList, WPXHLListenerImpl *listenerImpl);
	virtual ~WP3Listener();

	virtual void setAlignmentCharacter(const uint16_t character) {};
	virtual void setLeaderCharacter(const uint16_t character, const uint8_t numberOfSpaces) {};
	virtual void defineTabStops(const bool isRelative, const std::vector<WPXTabStop> &tabStops, 
				    const std::vector<bool> &usePreWP9LeaderMethods) {};
	virtual void insertCharacter(const uint16_t character);
	virtual void insertTab(const uint8_t tabType, const float tabPosition);
	virtual void handleLineBreak() {};
	virtual void insertEOL();
	virtual void attributeChange(const bool isOn, const uint8_t attribute);
	virtual void spacingAfterParagraphChange(const float spacingRelative, const float spacingAbsolute) {};
	virtual void pageMarginChange(const uint8_t side, const uint16_t margin) {};
	virtual void pageFormChange(const uint16_t length, const uint16_t width, const WPXFormOrientation orientation, const bool isPersistent) {};
	virtual void marginChange(const uint8_t side, const uint16_t margin);
	virtual void paragraphMarginChange(const uint8_t side, const int16_t margin) {};
	virtual void indentFirstLineChange(const int16_t offset);
	virtual void columnChange(const WPXTextColumnType columnType, const uint8_t numColumns, const std::vector<float> &columnWidth,
				  const std::vector<bool> &isFixedWidth) {};
	virtual void endDocument();

	virtual void defineTable(uint8_t position, uint16_t leftOffset) {};
	virtual void addTableColumnDefinition(uint32_t width, uint32_t leftGutter, uint32_t rightGutter, uint32_t attributes, uint8_t alignment) {};
	virtual void startTable() {};
 	virtual void insertRow(const uint16_t rowHeight, const bool isMinimumHeight, const bool isHeaderRow) {};
 	virtual void insertCell(const uint8_t colSpan, const uint8_t rowSpan, const bool boundFromLeft, const bool boundFromAbove,
				const uint8_t borderBits, const RGBSColor * cellFgColor, const RGBSColor * cellBgColor,
				const RGBSColor * cellBorderColor, const WPXVerticalAlignment cellVerticalAlignment, 
				const bool useCellAttributes, const uint32_t cellAttributes) {};
 	virtual void endTable() {};
        virtual void undoChange(const uint8_t undoType, const uint16_t undoLevel);

protected:
	virtual void _handleSubDocument(uint16_t textPID, const bool isHeaderFooter, WPXTableList tableList, int nextTableIndice = 0) {}

private:
	void _flushText();
	void _changeList() {};

	WPXString m_textBuffer;

	WP3ParsingState *m_parseState;
};

#endif /* WP3HLLISTENER_H */
