/* libwpd2
 * Copyright (C) 2002 William Lachance (william.lachance@sympatico.ca)
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
#include <string.h>
#include <gsf/gsf-input-memory.h>

#include "WP6ExtendedDocumentSummaryPacket.h"
#include "libwpd_internal.h"

WP6ExtendedDocumentSummaryPacket::WP6ExtendedDocumentSummaryPacket(GsfInput *input, int id, guint32 dataOffset, guint32 dataSize) 
	: WP6PrefixDataPacket(input),
	  m_dataSize(dataSize)
{	
	_read(input, dataOffset, dataSize);
}

WP6ExtendedDocumentSummaryPacket::~WP6ExtendedDocumentSummaryPacket()
{
	g_object_unref(G_OBJECT(m_stream));
}

void WP6ExtendedDocumentSummaryPacket::_readContents(GsfInput *input)
{
	// we have to use glib's allocation function because libgsf disposes of the data
	guint8 *streamData = (guint8 *)g_malloc(sizeof(guint8)*m_dataSize); 
	for(int i=0; i<m_dataSize; i++)
		streamData[i] = gsf_le_read_guint8(input);
                   
	m_stream = GSF_INPUT(gsf_input_memory_new(streamData, m_dataSize, TRUE));
}

void WP6ExtendedDocumentSummaryPacket::parse(WP6LLListener *llListener) const
{
	guint16 groupLength = 0;

	for (int i=0; i < m_dataSize; i+=groupLength)
	{
		groupLength = gsf_le_read_guint16(m_stream);
		guint16 tagID = gsf_le_read_guint16(m_stream);
		guint16 flags = gsf_le_read_guint16(m_stream);

		UCSString name;
		for (guint16 wpChar = gsf_le_read_guint16(m_stream);
		     wpChar != 0; 
		     wpChar = gsf_le_read_guint16(m_stream))
		{
			guint8 character = (wpChar & 0xFF);
			guint8 characterSet = (wpChar & 0xFF00) >> 8;
			name.append(extendedCharacterToUCS2(character, characterSet));
		} 
		
		if (tagID == WP6_INDEX_HEADER_EXTENDED_DOCUMENT_SUMMARY_CREATION_DATE ||
		    tagID == WP6_INDEX_HEADER_EXTENDED_DOCUMENT_SUMMARY_DATE_COMPLETED)
		{
			guint16 year = gsf_le_read_guint16(m_stream);
			guint8 month = gsf_le_read_guint8(m_stream);
			guint8 day = gsf_le_read_guint8(m_stream);
			guint8 hour = gsf_le_read_guint8(m_stream);
			guint8 minute = gsf_le_read_guint8(m_stream);
			guint8 second = gsf_le_read_guint8(m_stream);
			guint8 dayOfWeek = gsf_le_read_guint8(m_stream);
			guint8 timeZone = gsf_le_read_guint8(m_stream);
			guint8 unused = gsf_le_read_guint8(m_stream);
			llListener->setDate(year, month, day, hour, minute, second, dayOfWeek, timeZone, unused);
		}
		else
		{
			UCSString data;
			for (guint16 wpChar = gsf_le_read_guint16(m_stream);
			     wpChar != 0; 
			     wpChar = gsf_le_read_guint16(m_stream))
			{				
			guint8 character = (wpChar & 0xFF);
			guint8 characterSet = (wpChar & 0xFF00) >> 8;
			data.append(extendedCharacterToUCS2(character, characterSet));
			} 
			llListener->setExtendedInformation(tagID, data);
		}
		WPD_CHECK_FILE_SEEK_ERROR(gsf_input_seek(m_stream, (i+groupLength), G_SEEK_SET));
	}
}