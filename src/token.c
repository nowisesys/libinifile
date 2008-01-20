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
 * Remove leading and trailing whitespace.
 */
parser_entry * token_trim(parser_entry *entry)
{
	if(entry->sect) {
		inifile_trim_str(entry->sect);
	}
	if(entry->key) {
		inifile_trim_str(entry->key);
	}
	if(entry->val) {
		inifile_trim_str(entry->val);
	}
	
	return entry;
}

/*
 * Returns next token from input data.
 */
int token_get(struct inifile *inf, token_data *data)
{	
	if(data->quote.sch) {
		/*
		 * Parsing quoted string.
		 */
		switch(inf->str[data->pos]) {
		case '"':
		case '\'':
			/*
			 * Matched end quote character.
			 */
			data->curr = QUOTE;
			data->quote.ech = inf->str[data->pos];
			data->quote.num++;
			break;
		default:
			/*
			 * Treat all input as data inside quoted string.
			 */
			if(!strlen(inf->str) || data->pos == inf->len) {
				data->curr = EOSTR;
			} else if(isspace(inf->str[data->pos])) {
				data->curr = WHITESP;
			} else {
				data->curr = CDATA;
			}
			break;
		}
	} else {
		switch(inf->str[data->pos]) {
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
			data->quote.sch = inf->str[data->pos];
			data->quote.num++;
			break;
		default:
			if(!strlen(inf->str) || data->pos == inf->len) {
				data->curr = EOSTR;
			} else if(isspace(inf->str[data->pos])) {
				data->curr = WHITESP;
			} else {
				data->curr = CDATA;
			}
			break;
		}
	}
	return data->curr;
}
