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

/*
 * Tests the C language version of the library (libinifile).
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STDAFX_H
# include "stdafx.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <inifile.h>

static void die(struct inifile *inf)
{
	const struct inierr *error = inifile_get_error(inf);
	fprintf(stderr, "%s(%d:%d): %s\n", inf->file, error->line, error->pos, error->msg);
	exit(1);
}

int main(int argc, char **argv)
{
	struct inifile inf;
	const struct inient *ent;
	char *prog;
	
	prog = basename(argv[0]);
	
	if(argc != 2) {
		fprintf(stderr, "usage: %s <ini-file>\n", prog);
		exit(1);
	}
	
	if(inifile_init(&inf, argv[1]) == 0) {
		if(!inifile_get_option(&inf, INIFILE_ASSIGN_INSIDE)) {
			inifile_set_option(&inf, INIFILE_ASSIGN_INSIDE, 1);
		}
		while((ent = inifile_parse(&inf))) {
			printf("sect='%s', key='%s', val='%s'\n",
			       ent->sect, ent->key, ent->val);
		}
		if(inifile_get_error(&inf)) {
			die(&inf);
		}
	} else {
		die(&inf);
	}
	
	inifile_free(&inf);
	return 0;
}
