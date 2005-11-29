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

#ifndef WP3STYLESLISTENER_H
#define WP3STYLESLISTENER_H

#include "WP3Listener.h"
#include <vector>
#include "WPXPageSpan.h"
#include "WPXTable.h"

class WP3StylesListener : public WP3Listener
{
public:
	WP3StylesListener(std::vector<WPXPageSpan *> *pageList, WPXTableList tableList);

	virtual void startDocument() {}
	virtual void setAlignmentCharacter(const uint16_t character) {}
	virtual void setLeaderCharacter(const uint16_t character, const uint8_t numberOfSpaces) {}
	virtual void defineTabStops(const bool isRelative, const std::vector<WPXTabStop> &tabStops, 
				    const std::vector<bool> &usePreWP9LeaderMethods) {}
	virtual void insertCharacter(const uint16_t character) {}
	virtual void insertTab(const uint8_t tabType, const uint16_t tabPosition) {}
	virtual void insertEOL() {}
 	virtual void insertBreak(const uint8_t breakType);
	virtual void attributeChange(const bool isOn, const uint8_t attribute) {}
	virtual void lineSpacingChange(const float lineSpacing) {}
	virtual void spacingAfterParagraphChange(const float spacingRelative, const float spacingAbsolute) {}
	virtual void justificationChange(const uint8_t justification) {}
	virtual void pageMarginChange(const uint8_t side, const uint16_t margin);
	virtual void pageFormChange(const uint16_t length, const uint16_t width, const WPXFormOrientation orientation, const bool isPersistent);
	virtual void marginChange(const uint8_t side, const uint16_t margin);
	virtual void paragraphMarginChange(const uint8_t side, const int16_t margin) {}
	virtual void indentFirstLineChange(const int16_t offset) {}
	virtual void columnChange(const WPXTextColumnType columnType, const uint8_t numColumns, const std::vector<float> &columnWidth,
				  const std::vector<bool> &isFixedWidth) {}
	virtual void endDocument();

	virtual void defineTable(const uint8_t position, const uint16_t leftOffset){}
	virtual void addTableColumnDefinition(const uint32_t width, const uint32_t leftGutter, const uint32_t rightGutter, const uint32_t attributes,
				const uint8_t alignment){}
	virtual void startTable();
 	virtual void insertRow(const uint16_t rowHeight, const bool isMinimumHeight, const bool isHeaderRow);
 	virtual void insertCell(const uint8_t colSpan, const uint8_t rowSpan, const uint8_t borderBits, 
				const RGBSColor * cellFgColor, const RGBSColor * cellBgColor, 
				const RGBSColor * cellBorderColor, const WPXVerticalAlignment cellVerticalAlignment, 
				const bool useCellAttributes, const uint32_t cellAttributes);
 	virtual void closeCell() {}
	virtual void closeRow() {}
	virtual void setTableCellSpan(const uint16_t colSpan, const uint16_t rowSpan) {}
 	virtual void endTable() {}
	virtual void setTextFont(const std::string fontName) {}
	virtual void setFontSize(const uint16_t fontSize) {}
	virtual void insertNoteReference(const WPXNoteType noteType, const std::string noteReference) {};
	virtual void insertNote(const WPXNoteType noteType, const WP3SubDocument *subDocument) {};

protected:
	virtual void _openPageSpan() { /* FIXME: REMOVE ME WHEN IMPLEMENTED IN WPXListener */ };

private:
	WPXPageSpan *m_currentPage;

	WPXTableList m_tableList;
	WPXTable *m_currentTable;
	float m_tempMarginLeft, m_tempMarginRight;
	bool m_currentPageHasContent;
};

#endif /* WP3STYLESLISTENER_H */
