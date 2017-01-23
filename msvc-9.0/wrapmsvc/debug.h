/*
    Debugging macros
    Copyright 2009 Ambroz Bizjak <ambrop7@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fprintf(stderr, ...) doesn't work with winelib
#define DEBUG(...) { fprintf(stderr, "%s: ", __FUNCTION__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); }
#define ASSERT_FORCE(e) { if (!(e)) { fprintf(stderr, "%s:%d Assertion failed\n", __FILE__, __LINE__); abort(); } }
*/
#define DEBUG(...) { printf("%s: ", __FUNCTION__); printf(__VA_ARGS__); printf("\n"); }
#define ASSERT_FORCE(e) { if (!(e)) { printf("%s:%d Assertion failed\n", __FILE__, __LINE__); abort(); } }

#ifdef NDEBUG
#define ASSERT(e) 
#define ASSERT_EXECUTE(e) { e; }
#else
#define ASSERT(e) ASSERT_FORCE(e)
#define ASSERT_EXECUTE(e) ASSERT_FORCE(e)
#endif

#endif
