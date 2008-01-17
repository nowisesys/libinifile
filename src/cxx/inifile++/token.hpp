// ***********************************************************************
// libinifile - Small library to parse ini-style configuarion files.
// Copyright (C) 2008  Anders Lövgren
// ***********************************************************************
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// ***********************************************************************
// Send questions to: Anders Lövgren <lespaul@algonet.se>
// ***********************************************************************

#ifndef __LIBINIFILE_CXX_TOKEN_H__
#define __LIBINIFILE_CXX_TOKEN_H__

namespace inifile
{
	//
	// The tokenizer class.
	//
	class token
	{
	public:
		//
		// Charaters recognized.
		//
		enum symbol
		{
			NONE,			 // Dummy
			BSECT,			 // Section begin ('[')
			ESECT,			 // Section ends  (']')
			COMMENT,		 // Comment begin ('#')
			ASSIGN,			 // Keword assign ('=')
			WHITESP,		 // Any whitespace character
			QUOTE,			 // Quote character ('"' or ''')
			CDATA,			 // Data
			EOSTR			 // End of string
		};

		//
		// Character data classification.
		//
		enum classify
		{
			GLOBAL, SECTION, KEYWORD, VALUE
		};
		
		struct quote
		{
			char sch;
			char ech;
			unsigned int num;
			quote() : sch(0), ech(0), num(0) {}
		};
		
		struct data
		{
			std::string str;	 // The string data
			unsigned int pos;	 // Start position
			unsigned int line;	 // Line number
			symbol curr;		 // Current token
			symbol seen;		 // Saved token
			classify cls;            // Classification
			quote qstr;		 // Quote string
			data(std::string str, unsigned int line) 
				: str(str), pos(0), line(line), curr(NONE), seen(NONE), cls(GLOBAL) {}
		};
		
		static symbol get(data *data);
		static parser::entry * trim(parser::entry *ent);
	};
	
}       // namespace inifile

#endif  // __LIBINIFILE_CXX_TOKEN_H__
