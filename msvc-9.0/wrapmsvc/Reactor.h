/*
    Lightweight reactor for Windows
    Copyright (C) Ambroz Bizjak, 2009

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

#ifndef REACTOR_H
#define REACTOR_H

#include <windows.h>

#include "debug.h"

#define REACTOR_MAX_HANDLES 32

typedef void (*Reactor_handler) (void *user);

struct reactor_entry {
    Reactor_handler handler;
    void *user;
};

typedef struct {
    int quit;
    int num_handles;
    HANDLE handles[REACTOR_MAX_HANDLES];
    struct reactor_entry entries[REACTOR_MAX_HANDLES];
} Reactor;

static void Reactor_Init (Reactor *r);
static void Reactor_Quit (Reactor *r);
static void Reactor_Exec (Reactor *r);
static int Reactor_AddHandle (Reactor *r, HANDLE handle, Reactor_handler handler, void *user);

void Reactor_Init (Reactor *r)
{
    r->quit = 0;
    r->num_handles = 0;
}

void Reactor_Quit (Reactor *r)
{
    r->quit = 1;
}

void Reactor_Exec (Reactor *r)
{
    while (!r->quit) {
        if (r->num_handles == 0) {
            Sleep(INFINITE);
        } else {
            DWORD res = WaitForMultipleObjects(r->num_handles, r->handles, FALSE, INFINITE);
            ASSERT_FORCE(res >= WAIT_OBJECT_0 && res <= WAIT_OBJECT_0 + r->num_handles - 1)
            int n = res - WAIT_OBJECT_0;
            struct reactor_entry re = r->entries[n];
            if (n != r->num_handles - 1) {
                r->handles[n] = r->handles[r->num_handles - 1];
                r->entries[n] = r->entries[r->num_handles - 1];
            }
            r->num_handles--;
            re.handler(re.user);
        }
    }
}

int Reactor_AddHandle (Reactor *r, HANDLE handle, Reactor_handler handler, void *user)
{
    if (r->num_handles == REACTOR_MAX_HANDLES) {
        return 0;
    }
    r->handles[r->num_handles] = handle;
    r->entries[r->num_handles].handler = handler;
    r->entries[r->num_handles].user = user;
    r->num_handles++;
    return 1;
}

#endif
