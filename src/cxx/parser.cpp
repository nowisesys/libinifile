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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STDAFX_H
# include "stdafx.h"
#endif

#ifdef HAVE_STL_STRING
# include <string>
#endif
#ifdef HAVE_STL_IOSTREAM
# include <iostream>
#endif
#ifdef HAVE_STL_FSTREAM
# include <fstream>
#endif
#ifdef HAVE_STL_SSTREAM
# include <sstream>
#endif

#include "parser.hpp"
#include "token.hpp"
#include "lexer.hpp"

//
// Set DEBUG_PARSER to enable debug output.
//
#if defined(DEBUG)
# define DEBUG_PARSER 1
#endif

namespace inifile
{
	
	//
	// Get next entry from opened configuration file.
	//
	const parser::entry * parser::next()
	{
#if defined(DEBUG_PARSER) && DEBUG_PARSER == 1
		static const char *strtoken[] = {
			"NONE",   "BSECT",   "ESECT", "COMMENT", 
			"ASSIGN", "WHITESP", "QUOTE", "CDATA", 
			"EOSTR"
		};
		static const char *strclass[] = {
			"GLOBAL", "SECTION", "KEYWORD", "VALUE"
		};
#endif

		//
		// Label where we continue if EOS is found.
		//
		next:
		
		//
		// Reset scan data.
		//
		ent.key = "";
		ent.val = "";
		
		//
		// Get next line from input stream.
		//
		std::string in;
		while(std::getline(fs, in))
		{
			//
			// Count up one more line.
			//
			++ent.line;
			
			//
			// Skip empty and commented lines.
			//
			if(in.empty() || in[0] == '#')
			{
				continue;
			}
			
			//
			// Fill line scanning data object.
			//
			token::data data(in, ent.line);
			
			//
			// Tokenize input string.
			//
			while(token::get(&data))
			{	
#if defined(DEBUG_PARSER) && DEBUG_PARSER == 1
				std::cerr << "(" << data.line << ":" << data.pos << "):"
					<< "\tchar = '" << (isprint(data.str[data.pos]) ? data.str[data.pos] : ' ') << "'"
					<< "\tseen = " << strtoken[data.seen]
					<< "\tcurr = " << strtoken[data.curr]
					<< "\tclass = " << strclass[data.cls]
					<< std::endl;
#endif
				//
				// Validate input
				//
				lexer::check(&data);
				
				switch(data.curr)
				{
				case token::BSECT:				// Begin section
					ent.sect = "";
					break;
				case token::ESECT:				// End section
					break;
				case token::COMMENT:			// We are done!
				case token::EOSTR:
					if(data.seen != token::ESECT)
					{
						//
						// Only returns entries where keyword is set.
						// 
						token::trim(&ent);
						if(ent.key.length())
						{
							return &ent;
						}
					}
					//
					// Jump to next line.
					// 
					goto next;
					break;
				case token::CDATA:
				case token::WHITESP:
					if(data.seen == token::BSECT)
					{
						data.cls = token::SECTION;
						ent.sect += data.str[data.pos];
					}
					else if(data.seen == token::ASSIGN ||
						data.seen == token::QUOTE)
					{
						data.cls = token::VALUE;
						ent.val += data.str[data.pos];
					}
					else
					{
						data.cls = token::KEYWORD;
						ent.key += data.str[data.pos];
					}
					break;
				case token::NONE:				// Ignore
				case token::ASSIGN:				// Ignore
				case token::QUOTE:				// Ignore
					break;
				}
				
				//
				// Save last seen token thats not CDATA.
				//
				if(data.curr != token::CDATA && data.curr != token::WHITESP)
				{
					data.seen = data.curr;
				}
				
				//
				// Move to next char.
				// 
				++data.pos;
			}
		}
		
		//
		// Nothing found.
		//
		return 0;
	}
	
}       // namespace inifile
