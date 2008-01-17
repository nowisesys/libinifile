/* Monitors and restarts a crashed child process.
 * Copyright (C) 2007 Anders Lövgren
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
 */

/*
 * This is an drop-in replacement for system missing getdelim(3).
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <unistd.h>

#include "alived.h"

#ifdef BUFFER_ALLOC_CHUNK
# undef BUFFER_ALLOC_CHUNK
#endif
#define BUFFER_ALLOC_CHUNK 128

/*
 * Reads next line from file stream and store in buff. The buffer 
 * is dynamic resized to fit a complete line. The size argument holds
 * the buffer size. Returns 0 if successful and -1 on failure.
 */
ssize_t rpl_getdelim(char **buff, size_t *size, int delim, FILE *stream)
{
	int c;
	size_t n = 0;
	
	if(feof(stream)) {
		debug("EOF on stream");
		errno = EINVAL;
		return -1;
	}
	
	if(!size) {
		debug("size is NULL");
		errno = EINVAL;
		return -1;
	}
	
	if(!*buff && *size != 0) {
		debug("buffer NULL, but size is non-zero");
		*size = 0;
	}
	if(*size == 0 && *buff) {
		debug("size is zero, but buffer is not NULL");
		free(*buff);
		*buff = NULL;
	}
	
	while((c = getc(stream)) != EOF) {
		if(n == (*size + 1) || *size == 0) {
			debug("realloc (size=%d, pos=%d)", *size, n);
			ungetc(c, stream);
			*size += BUFFER_ALLOC_CHUNK;
			*buff = realloc(*buff, *size);     
			if(!*buff) {
				errno = ENOMEM;
				return -1;
			}
			continue;      /* retry */
		}
		if(c == delim) {
			debug("found delimiter at position %d", n);
			(*buff)[n++] = c;
			(*buff)[n] = '\0';
			break;
		}
		(*buff)[n++] = c;
	}
	
	return (n == 0 && c == EOF) ? -1 : n;
}
