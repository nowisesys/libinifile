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

#ifdef HAVE_STDAFX_H
# include "stdafx.h"
#endif

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STL_STRING
# include <string>
#endif
#ifdef HAVE_STL_FSTREAM
# include <fstream>
#endif
#ifdef HAVE_STL_SSTREAM
# include <sstream>
#endif

#include "parser.hpp"
#include "token.hpp"

namespace 
{
	class trim
	{
	public:		
		static std::string & right(std::string &str);
		static std::string & left(std::string &str);
	};
	
	//
	// Remove triling whitespaces.
	//
	std::string & trim::right(std::string &str)
	{
		std::string::size_type pos = str.length();
		if(pos)
		{
			while(isspace(str[pos - 1])) --pos;
			str = str.substr(0, pos);
		}
		return str;
	}
	
	//
	// Remove leading whitespaces.
	//
	std::string & trim::left(std::string &str)
	{
		std::string::size_type pos = 0;
		while(isspace(str[pos])) ++pos;
		str = str.substr(pos);
		return str;
	}
}

namespace inifile
{
	
	//
	// Remove leading and trailing whitespace.
	//
	parser::entry * token::trim(parser::entry *ent)
	{
		trim::right(trim::left(ent->sect));
		trim::right(trim::left(ent->key));
		trim::right(trim::left(ent->val));
		
		return ent;
	}

	//
	// Returns next token from input data.
	//
	token::symbol token::get(token::data *data)
	{	
		if(data->qstr.sch)
		{
			//
			// Parsing quoted string.
			//
			switch(data->str[data->pos])
			{
			case '"':
			case '\'':
				//
				// Matched end quote character.
				//
				data->curr = QUOTE;
				data->qstr.ech = data->str[data->pos];
				data->qstr.num++;
				break;
			default:
				//
				// Treat all input as data inside quoted string.
				//
				if(data->str.empty() || data->pos == data->str.length())
				{
					data->curr = EOSTR;
				}
				else if(isspace(data->str[data->pos]))
				{
					data->curr = WHITESP;
				}
				else
				{
					data->curr = CDATA;
				}
				break;
			}
		}
		else
		{
			switch(data->str[data->pos])
			{
			case '[':
				data->curr = BSECT;
				break;
			case ']':
				data->curr = ESECT;
				break;
			case '#':
				data->curr = COMMENT;
				break;
			case '=':
				data->curr = ASSIGN;
				break;
			case '"':
			case '\'':
				data->curr = QUOTE;
				data->qstr.sch = data->str[data->pos];
				data->qstr.num++;
				break;
			default:
				if(data->str.empty() || data->pos == data->str.length())
				{
					data->curr = EOSTR;
				}
				else if(isspace(data->str[data->pos]))
				{
					data->curr = WHITESP;
				}
				else
				{
					data->curr = CDATA;
				}
				break;
			}
		}
		return data->curr;
	}
	
}       // namespace Config
