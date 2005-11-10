/* libwpd
 * Copyright (C) 2003 William Lachance (william.lachance@sympatico.ca)
 * Copyright (C) 2003 Marc Maurer (j.m.maurer@student.utwente.nl)
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

#ifndef WP5PARSER_H
#define WP5PARSER_H

#include "WPXParser.h"

class WPXHLListenerImpl;
class WP5Listener;

class WP5Parser : public WPXParser
{
public:
	WP5Parser(WPXInputStream *input, WPXHeader *header);
	~WP5Parser();

	virtual void parse(WPXHLListenerImpl *listenerImpl);
	
	static void parseDocument(WPXInputStream *input, WP5Listener *listener);

private:
	void parse(WPXInputStream *input, WP5Listener *listener);
};

#endif /* WP5PARSER_H */
