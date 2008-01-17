/* libinifile - Small library to parse ini-style configuarion files.
 * Copyright (C) 2008  Anders Lövgren
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STDAFX_H
# include "stdafx.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "inifile.h"
#include "common.h"

/*
 * Initilize the parser. Returns 0 if successful and -1 on
 * failure. Use inifile_get_error() to get last error.
 */
int inifile_init(struct inifile *inf, const char *conf)
{
	memset(inf, 0, sizeof(struct inifile));
	
	inf->file = conf;
	inf->fs = fopen(inf->file, "r");
	if(!inf->fs) {
		inifile_set_error(inf, 0, 0, "failed open %s", inf->file);
		return -1;
	}
	
	inf->entry = malloc(sizeof(struct inient));
	if(!inf->entry) {
		inifile_set_error(inf, 0, 0, "failed alloc memory");
		return -1;
	}
	
	return 0;
}

/*
 * Return next parsed ini-file entry or NULL if last call 
 * failed (including end of file). Use inifile_get_error() 
 * to check the error condition.
 */
const struct inient * inifile_parse(struct inifile *inf)
{	
	return (struct inient *)parser_get_next(inf);
}

/*
 * Release memory allocated by the parser.
 */
void inifile_free(struct inifile *inf)
{
	if(inf->fs) {
		fclose(inf->fs);
		inf->fs = NULL;
	}
	if(inf->entry) {
		free(inf->entry);
		inf->entry = NULL;
	}
	if(inf->error) {
		free(inf->error);
		inf->error = NULL;
	}
}

/*
 * Get last error or NULL if no error occured.
 */
const struct inierr * inifile_get_error(struct inifile *inf)
{
	return inf->error;
}

/*
 * Write error message.
 */
void inifile_set_error(struct inifile *inf, 
		       unsigned int line, 
		       unsigned int pos,
		       const char *fmt, ...)
{
	int bytes;
	int size = 100;
	va_list ap;
	char *buff;
	
	if(!inf->error) {
		inf->error = malloc(sizeof(struct inierr));
		if(!inf->error) {
			return;
		}
		inf->error->msg = NULL;
	}
	
	inf->error->line = line;
	inf->error->pos  = pos;
		
	while(1) {
		/* 
		 * Try to print in the allocated space. 
		 */		
		va_start(ap, fmt);
		bytes = vsnprintf(inf->error->msg, size, fmt, ap);
		va_end(ap);
		
		/* 
		 * If that worked then we are done.
		 */
		if(bytes > -1 && bytes < size) {
			break;
		}
		
		/* 
		 * Realloc memory and try again.
		 */
		if(bytes > -1) {              /* glibc 2.1 */
			size = bytes + 1;     /* precisely what is needed */
		} else {                      /* glibc 2.0 */
			size *= 2;            /* twice the old size */
		}
		if((buff = realloc(inf->error->msg, size)) == NULL) {
			free(inf->error->msg);
			inf->error->msg = NULL;
			break;
		} else {
			inf->error->msg = buff;
		}
	}	
}

/*
 * Clear error object.
 */
void inifile_clear_error(struct inifile *inf)
{
	if(inf->error) {
		if(inf->error->msg) {
			free(inf->error->msg);
		}
		free(inf->error);
		inf->error = NULL;
	}
}
