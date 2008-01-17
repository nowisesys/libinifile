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

#define _GNU_SOURCE

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STDAFX_H
# include "stdafx.h"
#endif

#ifdef HAVE_GETLINE
# include <stdio.h>
#endif
#include <string.h>

#include "common.h"

/*
 * Set DEBUG_PARSER to enable debug output.
 */
#if defined(DEBUG)
# define DEBUG_PARSER 1
#endif

#define PARSE_ERROR 1
#define PARSE_NEXT  2
#define PARSE_DONE  3

static int parser_tokenize(struct inifile *inf, token_data *data, parser_entry *entry)
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
	
	/*
	 * Tokenize input string.
	 */
	while(token_get(data)) {
		
#if defined(DEBUG_PARSER) && DEBUG_PARSER == 1
		fprintf(stderr, "(%d:%d): char=%c, seen=%s, curr=%s, class=%s\n",
			data->line, data->pos, 
			data->str[data->pos], 
			strtoken[data->seen],
			strtoken[data->curr],
			strclass[data->cls]);
#endif
		/*
		 * Validate input
		 */
		if(!lexer_check(inf, data)) {
			return PARSE_ERROR;
		}
				
		switch(data->curr)
		{
		case BSECT:				/* Begin section */
			entry->sect = NULL;
			break;
		case ESECT:				/* End section */
			break;
		case COMMENT:			        /* We are done */
		case EOSTR:
			if(data->seen != ESECT) {
				/*
				 * Only returns entries where keyword is set.
				 */ 
				token_trim(entry);
				if(entry->key && strlen(entry->key)) {
					return PARSE_DONE;
				}
			}
			/*
			 * Jump to next line.
			 */
			return PARSE_NEXT;
			break;
		case CDATA:
		case WHITESP:
			if(data->seen == BSECT) {
				data->cls = SECTION;
				entry->sect += data->str[data->pos];
			} else if(data->seen == ASSIGN ||
				  data->seen == QUOTE) {
				data->cls = VALUE;
				entry->val += data->str[data->pos];
			} else {
				data->cls = KEYWORD;
				entry->key += data->str[data->pos];
			}
			break;
		case NONE:				/* Ignore */
		case ASSIGN:				/* Ignore */
		case QUOTE:				/* Ignore */
			break;
		}
				
		/*
		 * Save last seen token thats not CDATA.
		 */
		if(data->curr != CDATA && data->curr != WHITESP) {
			data->seen = data->curr;
		}
		
		/*
		 * Move to next char.
		 */
		data->pos++;
	}
	
	return PARSE_NEXT;
}

/*
 * Parse next entry from ini-file.
 */
const parser_entry * parser_get_next(struct inifile *inf)
{
	char *buff = NULL;
	size_t size = 0;
	
	/*
	 * Label where we continue if EOS is found.
	 */
	next:
		
	/*
	 * Reset scan data.
	 */
	inf->entry->key = NULL;
	inf->entry->val = NULL;
		
	/*
	 * Get next line from input stream.
	 */
	while(getline(&buff, &size, inf->fs) != -1) {
		token_data data;
					
		/*
		 * Count up one more line.
		 */
		inf->entry->line++;
			
		/*
		 * Skip empty and commented lines.
		 */
		if(buff[0] == '\n' || buff[0] == '#') {
			continue;
		}

		/*
		 * Fill line scanning data object.
		 */
		data.str  = buff;
		data.pos  = 0;
		data.line = inf->entry->line;
		data.curr = NONE;
		data.seen = NONE;
		data.cls  = GLOBAL;
		
		switch(parser_tokenize(inf, &data, inf->entry)) {
		case PARSE_ERROR:
			return NULL;
		case PARSE_NEXT:
			goto next;
		case PARSE_DONE:
			return inf->entry;
		}
			
	}
		
	/*
	 * Nothing found.
	 */
	return NULL;
}
