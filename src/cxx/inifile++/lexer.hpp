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

#ifndef __LIBINIFILE_CXX_LEXER_H__
#define __LIBINIFILE_CXX_LEXER_H__

namespace inifile
{
	
	//
	// The lexer class.
	//
	class lexer
	{
	public:
		struct exception
		{
			unsigned int line;	 // Line number
			unsigned int cpos;	 // Position
			exception(unsigned int line, unsigned int ppos) 
				: line(line), cpos(ppos) {}
		};
		static token::data * check(token::data *data);
	};

}       // namespace inifile

#endif  // __LIBINIFILE_CXX_LEXER_H__
