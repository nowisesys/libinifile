// ***********************************************************************
// libinifile - library for parsing ini-style configuration files.
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

#include "parser.hpp"
#include "token.hpp"
#include "lexer.hpp"

namespace inifile
{
	
	//
	// Validate syntax.
	//
	token::data * lexer::check(token::data *data)
	{
		switch(data->curr)
		{
		case token::QUOTE:
			if(data->seen == token::QUOTE)
			{
				if(data->qstr.sch != data->qstr.ech)
				{
					//
					// Unbalanced quoted string.
					//
					throw lexer::exception(data->line, data->pos);
				}
			}
			break;
		case token::CDATA:
		case token::WHITESP:
		case token::NONE:
			break;
		case token::BSECT:
			if(data->seen != token::NONE)
			{
				//
				// Begin section inside
				//
				throw lexer::exception(data->line, data->pos);
			}
			break;
		case token::ESECT:
			if(data->seen != token::BSECT)
			{
				//
				// End section without begin section.
				//
				throw lexer::exception(data->line, data->pos);
			}
			break;
		case token::ASSIGN:
			if(data->seen != token::NONE)
			{
				//
				// Assignment to non-keyword.
				//
				throw lexer::exception(data->line, data->pos);
			}
			if(data->cls != token::KEYWORD)
			{
				throw lexer::exception(data->line, data->pos);
			}
			break;
		case token::EOSTR:
			if(data->seen != token::ASSIGN &&
			   data->seen != token::ESECT &&
			   data->seen != token::NONE &&
			   data->seen != token::QUOTE)
			{
				//
				// Unexpected EOS (end of string).
				//
				throw lexer::exception(data->line, data->pos);
			}
			if(data->seen == token::QUOTE)
			{
				if(!data->qstr.ech)
				{
					//
					// Unterminated quote.
					//
					throw lexer::exception(data->line, data->pos);
				}
				if(data->qstr.num % 2)
				{
					//
					// Unbalanced number of quotes.
					//
					throw lexer::exception(data->line, data->pos);
				}
			}
			break;
		case token::COMMENT:
			if(data->seen == token::ASSIGN ||
			   data->seen == token::BSECT)
			{
				if(data->cls != token::VALUE)
				{
					throw lexer::exception(data->line, data->pos);
				}
			}
			break;
		}
		
		return data;
	}
	
}      // namespace inifile
