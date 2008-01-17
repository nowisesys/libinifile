// libinifile - Small library to parse ini-style configuarion files.
// Copyright (C) 2008  Anders Lövgren
// 
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
// ---
// Send questions to: Anders Lövgren <lespaul@algonet.se>
//

//
// Parse configuration file. The entries in the file should be
// on standardform KEY = VAL with '#' defining the beginning of
// a comment. Optional sections [SECT] may be used.
//

#ifndef __LIBINIFILE_CXX_PARSE_H__
#define __LIBINIFILE_CXX_PARSE_H__

namespace inifile
{
	
	//
	// The configuration file parser.
	//
	class parser
	{
	public:
		struct entry
		{
			unsigned int line;	 // line number
			std::string sect;	 // the section name.
			std::string key;	 // the keyword.
			std::string val;	 // the (optional) value.
		};
	private:
		entry ent;
		std::ifstream fs;
	public:
		parser(const char *path) : fs(path) { ent.line = 0; }
		const entry * next();		 // Get next key/val pair
	};
	
}       // namespace inifile

#endif  // __LIBINIFILE_CXX_PARSER_H__
