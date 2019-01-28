// ***********************************************************************
// libinifile - C/C++ library for parsing ini-style configuration files.
// 
// Copyright (C) 2008-2018  Anders Lövgren, BMC-IT, Uppsala University
// Copyright (C) 2018-2019  Anders Lövgren, Nowise Systems
// 
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
// Send questions to: Anders Lövgren <andlov@nowise.se>
// ***********************************************************************

//
// Tests the C++ language version of the library (libinifile++).
//

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STDAFX_H
# include "stdafx.h"
#endif

#ifdef HAVE_STL_IOSTREAM
# include <iostream>
#endif
#ifdef HAVE_STL_FSTREAM
# include <fstream>
#endif

#ifdef HAVE_BASENAME
#include <libgen.h>
#else
#define basename(p) (p)
#endif

#include <inifile++.hpp>

using namespace inifilepp;

int main(int argc, char **argv)
{
	const char *prog = basename(argv[0]);
	const char *conf;
	
	if(argc != 2) {
		std::cerr << "usage: " << prog << " <ini-file>\n";
		return 1;
	} else {
		conf = argv[1];
	}
	
	try {
		parser p(conf);
		const parser::entry *ent;
		
		// 
		// Same options as the C library test:
		// 
		p.setopt(INIFILE_ASSIGN_INSIDE, 1);
		p.setopt(INIFILE_ALLOW_QUOTE, 1);
		p.setopt(INIFILE_ALLOW_MULTILINE, 1);
		p.setopt(INIFILE_CHARS_COMMENT, "#");

		while((ent = p.next())) {
			std::cout << "sect='" << (ent->sect ? ent->sect : "") << "', " 
				  << "key='"  << (ent->key  ? ent->key  : "")  << "', " 
				  << "val='"  << (ent->val  ? ent->val  : "") << "'\n";
		}
	} catch(parser::exception &e) {
		std::cerr << prog << ": " << conf << "(" << e.line << ":" << e.cpos << "): " << e.msg << "\n";
		return 1;
	}
	
	return 0;
}
