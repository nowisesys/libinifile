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

#ifdef HAVE_STDAFX_H
# include "stdafx.h"
#endif

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string.h>
#include <ctype.h>

#include "common.h"

/*
 * Remove leading and trailing whitespace characters from
 * string pointed to by str.
 */
static char * token_trim_str(char *str)
{
	size_t start = 0;
	size_t length = 0;
	size_t size = strlen(str);
	register char *pp = str;
	
	if(size == 0) {
		return str;
	}
	
	while(*pp && isspace(*pp)) {
		start++;
		++pp;
	}
	while(*pp && !isspace(*pp)) {
		length++;
		++pp;
	}
	
	memmove(str, str + start, length);
	memset(str + length, '\0', size - length);

	return str;
}

/*
 * Remove leading and trailing whitespace.
 */
parser_entry * token_trim(parser_entry *entry)
{
	if(entry->sect) {
		token_trim_str(entry->sect);
	}
	if(entry->key) {
		token_trim_str(entry->key);
	}
	if(entry->val) {
		token_trim_str(entry->val);
	}
	
	return entry;
}

/*
 * Returns next token from input data.
 */
int token_get(token_data *data)
{	
	if(data->quote.sch) {
		/*
		 * Parsing quoted string.
		 */
		switch(data->str[data->pos]) {
		case '"':
		case '\'':
			/*
			 * Matched end quote character.
			 */
			data->curr = QUOTE;
			data->quote.ech = data->str[data->pos];
			data->quote.num++;
			break;
		default:
			/*
			 * Treat all input as data inside quoted string.
			 */
			if(!strlen(data->str) || data->pos == strlen(data->str)) {
				data->curr = EOSTR;
			} else if(isspace(data->str[data->pos])) {
				data->curr = WHITESP;
			} else {
				data->curr = CDATA;
			}
			break;
		}
	} else {
		switch(data->str[data->pos]) {
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
			data->quote.sch = data->str[data->pos];
			data->quote.num++;
			break;
		default:
			if(!strlen(data->str) || data->pos == strlen(data->str)) {
				data->curr = EOSTR;
			} else if(isspace(data->str[data->pos])) {
				data->curr = WHITESP;
			} else {
				data->curr = CDATA;
			}
			break;
		}
	}
	return data->curr;
}
