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

#ifndef __LIBINIFILE_INIFILE_CXX_H__
#define __LIBINIFILE_INIFILE_CXX_H__

#ifdef __cplusplus

#if defined(__GNUC__) && ! defined(__NO_INLINE__)
# define INIFILE_API_INLINE static inline
#else
# define INIFILE_API_INLINE __inline
#endif

#if defined(WIN32) || defined(_WINDOWS) || defined(__CYGWIN__)
	/* Define LIBINIFILE_EXPORTS when building library on windows. */
# if defined(LIBINIFILE_EXPORTS)
#  if defined(__GNUC__)
#   define INIFILE_API_PUBLIC __attribute__((dllexport))
#  else
	/* Note: actually gcc seems to also supports this syntax. */
#   define INIFILE_API_PUBLIC __declspec(dllexport)
#  endif
# else
#  if defined(__GNUC__)
#   define INIFILE_API_PUBLIC __attribute__((dllimport))
#  else
	/* Note: actually gcc seems to also supports this syntax. */
#   define INIFILE_API_PUBLIC __declspec(dllimport) 
#  endif
# endif
# define INIFILE_API_HIDDEN
#else
# if __GNUC__ >= 4
#  define INIFILE_API_PUBLIC __attribute__ ((visibility("default")))
#  define INIFILE_API_HIDDEN __attribute__ ((visibility("hidden")))
# else
#  define INIFILE_API_PUBLIC
#  define INIFILE_API_HIDDEN
# endif
#endif

#define INIFILE_API_IMPORT
#include <string>
#include <inifile.h>

struct inifile;
struct inierr;

namespace inifilepp {
	
	class INIFILE_API_PUBLIC parser
	{
	private:
		inifile *inf;
	public:
		//
		// An ini-file entry.
		//
		struct entry
		{
			unsigned int line;      // line number.
			const char *sect;	// section name.
			const char *key;	// entry keyword.
			const char *val;	// entry value.
		};
		
		//
		// Parse exception.
		//
		struct exception
		{
			size_t line;
			size_t cpos;
			std::string msg;
			exception(inifile *, const inierr *);
		};
		
		//
		// option argument for getopt()/setopt():
		//
		enum {
			// 
			// int options:
			// 
			INIFPP_CHECK_SYNTAX    =   1,        // syntax check
			INIFPP_ALLOW_QUOTE     =   2,        // allow quoted strings
			INIFPP_ASSIGN_INSIDE   =   4,        // allow s1=s2 inside values
			INIFPP_ALLOW_MULTILINE =   8,        // allow multiline ('\')
			INIFPP_COMPACT_MLINE   =  16,        // eat whitespace in multiline
			// 
			// char * options:
			// 
			INIFPP_CHARS_COMMENT   = 256,        // get/set comment chars
			INIFPP_CHARS_ASSIGN    = 512         // get/set assignment chars
		};
		
		parser(const char *path);
		~parser();
		const entry * next() const;                  // throws parser::exception
		
		void getopt(int option, int &value);         // throws parser::exception
		void getopt(int option, char **value);       // throws parser::exception
		void setopt(int option, int value);          // throws parser::exception
		void setopt(int option, const char *value);  // throws parser::exception
	};
	
}      // namespace inifilepp

#endif // __cplusplus

#endif // __LIBINIFILE_INIFILE_CXX_H__
