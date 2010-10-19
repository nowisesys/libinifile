/* libinifile - C/C++ library for parsing ini-style configuration files.
 * Copyright (C) 2008-2010  Anders Lövgren, QNET/BMC Compdept, Uppsala University
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * ---
 * Send questions to: Anders Lövgren <lespaul@algonet.se>
 */

/*
 * Common defines for Visual Studio 2008 C/C++ (VC9)
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define ssize_t to large integer */
typedef long long ssize_t;

/* Disable warnings, this is bug free code anyway ;-) */
#define _CRT_SECURE_NO_WARNINGS 

/* Define to 1 if you have the C++ STL <iostream> header file. */
#define HAVE_STL_IOSTREAM 1

#endif  /* __CONFIG_H__ */
