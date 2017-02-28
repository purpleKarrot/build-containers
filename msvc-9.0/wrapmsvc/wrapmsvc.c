/*
    Wrappers for running the MSVC compiler and related tools through Wine
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

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <unistd.h>

#define MAX_CMDLINE_LEN 65536
#define MT_MAGIC 1090650113
#define MT_MAGIC_CONV 187
#define WCHAR_CONVERT_CP CP_UNIXCP

#if defined(WRAP_CL)
    #define CMD_ENVVAR "CL_CMD"
#elif defined(WRAP_LINK)
    #define CMD_ENVVAR "LINK_CMD"
#elif defined(WRAP_RC)
    #define CMD_ENVVAR "RC_CMD"
#elif defined(WRAP_MT)
    #define CMD_ENVVAR "MT_CMD"
#else
    #error UNKNOWN PROGRAM TO WRAP
#endif

#define CMDLINE_BUF_LEN (MAX_CMDLINE_LEN + 1)

static void fail (char *msg)
{
    printf("WRAPPER ERROR: %s\n", msg);
    exit(1);
}

static int begins_with (const char *str, const char *needle, int *len)
{
    int i;
    for (i = 0; ; i++) {
        if (needle[i] == '\0') {
            if (len) {
                *len = i;
            }
            return 1;
        }
        if (str[i] != needle[i]) {
            return 0;
        }
    }
}

static int begins_with_ci (const char *str, const char *needle, int *len)
{
    int i;
    for (i = 0; ; i++) {
        if (needle[i] == '\0') {
            if (len) {
                *len = i;
            }
            return 1;
        }
        if (toupper(str[i]) != toupper(needle[i])) {
            return 0;
        }
    }
}

void print_a (char *str, int len)
{
    if (len < 0) {
        len = strlen(str);
    }

    write(2, str, len);
}

void print_w (WCHAR *w, int len)
{
    if (len < 0) {
        len = wcslen(w);
    }

    if (len == 0) {
        return;
    }

    int alen = WideCharToMultiByte(CP_UNIXCP, 0, w, len, NULL, 0, NULL, NULL);
    if (alen == 0) {
        fail("WideCharToMultiByte failed");
    }

    char *a = HeapAlloc(GetProcessHeap(), 0, alen * sizeof(char));
    if (!a) {
        fail("HeapAlloc failed");
    }

    WideCharToMultiByte(CP_UNIXCP, 0, w, len, a, alen, NULL, NULL);

    write(2, a, alen);

    HeapFree(GetProcessHeap(), 0, a);
}

int main (int argc, char **argv)
{
    char *cl_cmd = getenv(CMD_ENVVAR);
    if (!cl_cmd) {
        fail(CMD_ENVVAR" not set");
    }

    #ifndef WINTEST
    LPWSTR (*CDECL wine_get_dos_file_name_ptr)(LPCSTR);
    wine_get_dos_file_name_ptr = (void *)GetProcAddress(GetModuleHandleA("KERNEL32"), "wine_get_dos_file_name");
    if (!wine_get_dos_file_name_ptr) {
        fail("cannot get wine_get_dos_file_name");
    }
    #endif

    WCHAR cmdline[CMDLINE_BUF_LEN];
    int cmdline_len = 0;

    void append_char (WCHAR c)
    {
        if (1 > MAX_CMDLINE_LEN - cmdline_len) {
            fail("out of command line buffer");
        }

        cmdline[cmdline_len] = c;
        cmdline_len++;
    }

    int arg_writing = 0;

    void start_argument ()
    {
        assert(!arg_writing);

        if (cmdline_len == 0) {
            append_char('"');
        } else {
            append_char(' ');
            append_char('"');
        }

        arg_writing = 1;
    }

    void write_argument_w (WCHAR *data, int len)
    {
        assert(arg_writing);
        assert(len >= 0);

        int i;
        for (i = 0; i < len; i++) {
            if (data[i] == '"') {
                int j;
                for (j = cmdline_len - 1; cmdline[j] == '\\'; j--) {
                    append_char('\\');
                }
                append_char('\\');
                append_char(data[i]);
            } else {
                append_char(data[i]);
            }
        }
    }

    void end_argument ()
    {
        assert(arg_writing);

        int j;
        for (j = cmdline_len - 1; cmdline[j] == '\\'; j--) {
            append_char('\\');
        }
        append_char('"');

        arg_writing = 0;
    }

    void write_argument_a (char *data, int len)
    {
        assert(arg_writing);
        assert(len >= 0);

        if (len == 0) {
            return;
        }

        int wc_len = MultiByteToWideChar(WCHAR_CONVERT_CP, 0, data, len, NULL, 0);
        if (wc_len == 0) {
            fail("MultiByteToWideChar failed");
        }

        WCHAR *wc = HeapAlloc(GetProcessHeap(), 0, wc_len * sizeof(WCHAR));
        if (!wc) {
            fail("HeapAlloc failed");
        }

        MultiByteToWideChar(WCHAR_CONVERT_CP, 0, data, len, wc, wc_len);

        write_argument_w(wc, wc_len);

        HeapFree(GetProcessHeap(), 0, wc);
    }

    void write_argument_path (char *path, int len)
    {
        assert(arg_writing);
        assert(len >= 0);

        if (len == 0) {
            return;
        }

        // cmake is broken and may give gives unix style paths with backshashes
        char *fixed = HeapAlloc(GetProcessHeap(), 0, len + 1);
        if (!fixed) {
            fail("HeapAlloc failed");
        }
        int i;
        for (i = 0; i < len; i++) {
            if (path[i] == '\\') {
                fixed[i] = '/';
            } else {
                fixed[i] = path[i];
            }
        }
        fixed[i] = '\0';

        // convert to windows path
        WCHAR *conv_path = wine_get_dos_file_name_ptr(fixed);
        if (!conv_path) {
            fail("cannot convert path");
        }

        write_argument_w(conv_path, wcslen(conv_path));

        HeapFree(GetProcessHeap(), 0, fixed);
        HeapFree(GetProcessHeap(), 0, conv_path);
    }

    // Appends an argument to the command line. Parameters:
    // str - zero terminated input argument to be appended
    // prefix - all characters of the input argument after
    //          that many bytes will be treated as a path
    void add_arg (char *str, int prefix_len)
    {
        assert(prefix_len >= 0);;
        assert(prefix_len <= strlen(str));;

        int path_len = strlen(str + prefix_len);

        start_argument();
        write_argument_a(str, prefix_len);
        write_argument_path(str + prefix_len, path_len);
        end_argument();
    }

    // parse CL_CMD
    char *ch = cl_cmd;
    char *current_arg = ch;
    while (*ch) {
        if (*ch == ';') {
            *ch = '\0';
            add_arg(current_arg, strlen(current_arg));
            current_arg = ch + 1;
        }
        ch++;
    }
    add_arg(current_arg, strlen(current_arg));

    // Parse arguments.
    // Some of this is guessing, because an argument starting with /
    // could always be a file rather than an option.
    // Handle this so that when given an argument beginning with /,
    // and such a file exits on the system, interpret it as a path.

    int i = 1;

    #if defined(WRAP_CL)
    while (i < argc) {
        // take argument
        char *arg = argv[i];
        int len = strlen(arg);
        i++;

        // parse as option?
        if (
            len >= 2 && (
                arg[0] == '-' ||
                (arg[0] == '/' && access(arg, F_OK) < 0)
            )
        ) {
            int optlen;

            // arguments with paths
            if (len >= 3 && arg[1] == 'F') {
                // path optional
                if (
                    arg[2] == 'a' || arg[2] == 'd' || arg[2] == 'm' ||
                    arg[2] == 'R' || arg[2] == 'r'
                ) {
                    add_arg(arg, 3);
                    continue;
                }
                // path required
                if (
                    arg[2] == 'p' || arg[2] == 'e' || arg[2] == 'o' ||
                    arg[2] == 'I' || arg[2] == 'U'
                ) {
                    add_arg(arg, 3);
                    // if no path is given, use next argument
                    if (arg[3] == '\0' && i < argc) {
                        add_arg(argv[i], 0);
                        i++;
                    }
                    continue;
                }
            }
            // /AI<dir>
            if (len >= 3 && arg[1] == 'A' && arg[2] == 'I') {
                add_arg(arg, 3);
                // if no value is given, use next argument
                if (arg[3] == '\0' && i < argc) {
                    add_arg(argv[i], 0);
                    i++;
                }
                continue;
            }
            // /I<dir>
            if (arg[1] == 'I') {
                add_arg(arg, 2);
                // if no value is given, use next argument
                if (arg[2] == '\0' && i < argc) {
                    add_arg(argv[i], 0);
                    i++;
                }
                continue;
            }
            // /doc[file]
            if (len >= 4 && arg[1] == 'd' && arg[2] == 'o' && arg[3] == 'c') {
                add_arg(arg, 4);
                continue;
            }
            // /Tc<file>, /Tp<file>
            if (
                begins_with(arg + 1, "Tc", &optlen) ||
                begins_with(arg + 1, "Tp", &optlen)
            ) {
                add_arg(arg, 1 + optlen);
                if (arg[1 + optlen] == '\0' && i < argc) {
                    add_arg(argv[i], 0);
                    i++;
                }
                continue;
            }
            // /D...
            if (arg[1] == 'D') {
                add_arg(arg, strlen(arg));
                // if no value is given, use next argument
                if (arg[2] == '\0' && i < argc) {
                    add_arg(argv[i], strlen(argv[i]));
                    i++;
                }
                continue;
            }

            // all arguments beginning with this are passed literally
            if (
                arg[1] == 'O' || arg[1] == 'G' || arg[1] == 'E' || arg[1] == 'Q' ||
                arg[1] == 'Z' || arg[1] == 'H' || arg[1] == 'W' || arg[1] == 'w' ||
                arg[1] == 'Y' || arg[1] == 'L' || arg[1] == 'M' || arg[1] == 'U'
            ) {
                add_arg(arg, len);
                continue;
            }

            // /fp:..
            if (len >= 4 && !memcmp(arg + 1, "fp:", 3)) {
                add_arg(arg, len);
                continue;
            }

            // /RTC...
            if (len >= 4 && !memcmp(arg + 1, "RTC", 3)) {
                add_arg(arg, len);
                continue;
            }

            // /clr[:option]
            if (len >= 4 && !memcmp(arg + 1, "clr", 3)) {
                add_arg(arg, len);
                continue;
            }

            // /F<num> set stack size
            if (arg[1] == 'F' && len > 2) {
                char *endptr;
                strtol(arg + 2, &endptr, 10);
                if (*endptr == '\0') {
                    add_arg(arg, len);
                    continue;
                }
            }

            // flags with no arguments
            if (
                !strcmp(arg + 1, "showIncludes") ||
                !strcmp(arg + 1, "nologo") ||
                !strcmp(arg + 1, "bigobj") ||
                !strcmp(arg + 1, "help") ||
                !strcmp(arg + 1, "?") ||
                !strcmp(arg + 1, "openmp") ||
                !strcmp(arg + 1, "c") ||
                !strcmp(arg + 1, "Fx") ||
                !strcmp(arg + 1, "FC") ||
                !strcmp(arg + 1, "C") ||
                !strcmp(arg + 1, "E") ||
                !strcmp(arg + 1, "P") ||
                !strcmp(arg + 1, "u") ||
                !strcmp(arg + 1, "X") ||
                !strcmp(arg + 1, "J") ||
                !strcmp(arg + 1, "TC") ||
                !strcmp(arg + 1, "TP")
            ) {
                add_arg(arg, len);
                continue;
            }

            if (!strcmp(arg + 1, "link")) {
                add_arg(arg, len);
                // linker options follow
                break;
            }

            // assume it's a file
            add_arg(arg, 0);
            continue;
        }

        // @<file>
        if (len >= 1 && arg[0] == '@') {
            add_arg(arg, 1);
            continue;
        }

        // assume it's a file
        add_arg(arg, 0);
        continue;
    }
    #endif

    #if defined(WRAP_LINK) || defined(WRAP_CL)
    while (i < argc) {
        // take argument
        char *arg = argv[i];
        int len = strlen(arg);
        i++;

        // parse as option?
        if (
            len >= 2 && (
                arg[0] == '-' ||
                (arg[0] == '/' && access(arg, F_OK) < 0)
            #ifdef WRAP_LINK
                || (arg[0] == '/' && !strcasecmp(arg + 1, "lib"))
            #endif
            )
        ) {
            int optlen;

            // options without arguments
            if (
                !strcasecmp(arg + 1, "DEBUG") ||
                !strcasecmp(arg + 1, "DLL") ||
                !strcasecmp(arg + 1, "IGNOREIDL") ||
                !strcasecmp(arg + 1, "MAP") ||
                !strcasecmp(arg + 1, "NOASSEMBLY") ||
                !strcasecmp(arg + 1, "NOENTRY") ||
                !strcasecmp(arg + 1, "NOLOGO") ||
                !strcasecmp(arg + 1, "PDB:none") ||
                !strcasecmp(arg + 1, "PDBSTRIPPED:none") ||
                !strcasecmp(arg + 1, "PROFILE") ||
                !strcasecmp(arg + 1, "RELEASE")
            #ifdef WRAP_LINK
                || !strcasecmp(arg + 1, "LIB")
            #endif
            ) {
                add_arg(arg, len);
                continue;
            }

            // options with literal arguments
            if (
                begins_with_ci(arg + 1, "ALIGN:", &optlen) ||
                begins_with_ci(arg + 1, "ALLOWBIND", &optlen) ||
                begins_with_ci(arg + 1, "ALLOWISOLATION", &optlen) ||
                begins_with_ci(arg + 1, "ASSEMBLYDEBUG", &optlen) ||
                begins_with_ci(arg + 1, "ASSEMBLYLINKRESOURCE:", &optlen) || // ?
                begins_with_ci(arg + 1, "ASSEMBLYMODULE:", &optlen) || // ?
                begins_with_ci(arg + 1, "ASSEMBLYRESOURCE:", &optlen) || // ?
                begins_with_ci(arg + 1, "BASE:", &optlen) ||
                begins_with_ci(arg + 1, "CLRIMAGETYPE:", &optlen) ||
                begins_with_ci(arg + 1, "CLRSUPPORTLASTERROR", &optlen) ||
                begins_with_ci(arg + 1, "CLRTHREADATTRIBUTE:", &optlen) ||
                begins_with_ci(arg + 1, "CLRUNMANAGEDCODECHECK", &optlen) ||
                begins_with_ci(arg + 1, "DEF:", &optlen) ||
                begins_with_ci(arg + 1, "DEFAULTLIB:", &optlen) ||
                begins_with_ci(arg + 1, "DELAY:", &optlen) ||
                begins_with_ci(arg + 1, "DELAYLOAD:", &optlen) ||
                begins_with_ci(arg + 1, "DELAYSIGN", &optlen) ||
                begins_with_ci(arg + 1, "DRIVER", &optlen) ||
                begins_with_ci(arg + 1, "DYNAMICBASE", &optlen) ||
                begins_with_ci(arg + 1, "ENTRY:", &optlen) ||
                begins_with_ci(arg + 1, "ERRORREPORT:", &optlen) ||
                begins_with_ci(arg + 1, "EXPORT:", &optlen) ||
                begins_with_ci(arg + 1, "FIXED", &optlen) ||
                begins_with_ci(arg + 1, "FORCE", &optlen) ||
                begins_with_ci(arg + 1, "FUNCTIONPADMIN", &optlen) ||
                begins_with_ci(arg + 1, "HEAP:", &optlen) ||
                begins_with_ci(arg + 1, "IDLOUT:", &optlen) ||
                begins_with_ci(arg + 1, "IMPLIB:", &optlen) ||
                begins_with_ci(arg + 1, "INCLUDE:", &optlen) ||
                begins_with_ci(arg + 1, "INCREMENTAL", &optlen) ||
                begins_with_ci(arg + 1, "KEYCONTAINER:", &optlen) ||
                begins_with_ci(arg + 1, "KEYFILE:", &optlen) ||
                begins_with_ci(arg + 1, "LARGEADDRESSAWARE", &optlen) ||
                begins_with_ci(arg + 1, "LTCG", &optlen) ||
                begins_with_ci(arg + 1, "MACHINE:", &optlen) ||
                begins_with_ci(arg + 1, "MANIFEST", &optlen) ||
                begins_with_ci(arg + 1, "MANIFESTDEPENDENCY:", &optlen) ||
                begins_with_ci(arg + 1, "MANIFESTFILE:", &optlen) ||
                begins_with_ci(arg + 1, "MANIFESTUAC", &optlen) ||
                begins_with_ci(arg + 1, "MAPINFO:", &optlen) ||
                begins_with_ci(arg + 1, "MERGE:", &optlen) ||
                begins_with_ci(arg + 1, "NODEFAULTLIB", &optlen) ||
                begins_with_ci(arg + 1, "NXCOMPAT", &optlen) ||
                begins_with_ci(arg + 1, "OPT:", &optlen) ||
                begins_with_ci(arg + 1, "SAFESEH", &optlen) ||
                begins_with_ci(arg + 1, "SECTION:", &optlen) ||
                begins_with_ci(arg + 1, "STACK:", &optlen) ||
                begins_with_ci(arg + 1, "SUBSYSTEM:", &optlen) ||
                begins_with_ci(arg + 1, "SWAPRUN:", &optlen) ||
                begins_with_ci(arg + 1, "TLBID:", &optlen) ||
                begins_with_ci(arg + 1, "TSAWARE", &optlen) ||
                begins_with_ci(arg + 1, "VERBOSE", &optlen) ||
                begins_with_ci(arg + 1, "VERSION:", &optlen) ||
                begins_with_ci(arg + 1, "WX", &optlen)
            ) {
                add_arg(arg, len);
                continue;
            }

            // options with path arguments
            if (
                begins_with_ci(arg + 1, "LIBPATH:", &optlen) ||
                begins_with_ci(arg + 1, "MAP:", &optlen) ||
                begins_with_ci(arg + 1, "MIDL:", &optlen) ||
                begins_with_ci(arg + 1, "ORDER:", &optlen) ||
                begins_with_ci(arg + 1, "OUT:", &optlen) ||
                begins_with_ci(arg + 1, "PDB:", &optlen) ||
                begins_with_ci(arg + 1, "PDBSTRIPPED:", &optlen) ||
                begins_with_ci(arg + 1, "PGD:", &optlen) ||
                begins_with_ci(arg + 1, "STUB:", &optlen) ||
                begins_with_ci(arg + 1, "TLBOUT:", &optlen)
            ) {
                add_arg(arg, 1 + optlen);
                continue;
            }
        }

        // @response_file
        if (len >= 1 && arg[0] == '@') {
            add_arg(arg, 1);
            continue;
        }

        // TODO: check semantics of this
        // if a file of that name exists, assume it's a path
        if (len > 0 && access(arg, F_OK) == 0) {
            add_arg(arg, 0);
            continue;
        }

        // do not change
        add_arg(arg, len);
        continue;
    }
    #endif

    #if defined(WRAP_RC)
    while (i < argc) {
        // take argument
        char *arg = argv[i];
        int len = strlen(arg);
        i++;

        // parse as option?
        if (
            len >= 2 && (
                arg[0] == '-' ||
                (arg[0] == '/' && access(arg, F_OK) < 0)
            )
        ) {
            // read options
            int j = 1;
            while (j < len) {
                int optlen;

                // multi-letter options with no arguments
                if (
                    j == 1 && (
                        !strcasecmp(arg + j, "nologo") ||
                        !strcasecmp(arg + j, "g1")
                    )
                ) {
                    add_arg(arg, len);
                    goto next_arg;
                }

                // multi-letter options with path arguments
                if (
                    j == 1 && (
                        begins_with_ci(arg + j, "fm", &optlen) ||
                        begins_with_ci(arg + j, "fo", &optlen)
                    )
                ) {
                    j += optlen;
                    add_arg(arg, j);
                    if (arg[j] == '\0' && i < argc) {
                        add_arg(argv[i], 0);
                        i++;
                    }
                    goto next_arg;
                }

                // single-letter options with no arguments
                if (
                    begins_with_ci(arg + j, "?", &optlen) ||
                    begins_with_ci(arg + j, "h", &optlen) ||
                    begins_with_ci(arg + j, "n", &optlen) ||
                    begins_with_ci(arg + j, "r", &optlen) ||
                    begins_with_ci(arg + j, "v", &optlen) ||
                    begins_with_ci(arg + j, "x", &optlen) ||
                    begins_with_ci(arg + j, "y", &optlen) ||
                    begins_with_ci(arg + j, "w", &optlen)
                ) {
                    j += optlen;
                    continue;
                }

                // single-letter options with literal arguments
                if (
                    begins_with_ci(arg + j, "c", &optlen) ||
                    begins_with_ci(arg + j, "d", &optlen) ||
                    begins_with_ci(arg + j, "j", &optlen) ||
                    begins_with_ci(arg + j, "k", &optlen) ||
                    begins_with_ci(arg + j, "l", &optlen) ||
                    begins_with_ci(arg + j, "u", &optlen) ||
                    begins_with_ci(arg + j, "g", &optlen)
                ) {
                    j += optlen;
                    add_arg(arg, len);
                    if (arg[j] == '\0' && i < argc) {
                        add_arg(argv[i], strlen(argv[i]));
                        i++;
                    }
                    goto next_arg;
                }

                // single-letter with path arguments
                if (
                    begins_with_ci(arg + j, "I", &optlen) ||
                    begins_with_ci(arg + j, "q", &optlen)
                ) {
                    j += optlen;
                    add_arg(arg, j);
                    if (arg[j] == '\0' && i < argc) {
                        add_arg(argv[i], 0);
                        i++;
                    }
                    goto next_arg;
                }

                // unknown option, assume it's a path
                goto assume_path;
            }

            // options without arguments, add literally
            add_arg(arg, len);
            continue;
        }

        // assume its is a path

assume_path:
        add_arg(arg, 0);
        continue;

next_arg:;
    }
    #endif

    #if defined(WRAP_MT)
    while (i < argc) {
        // take argument
        char *arg = argv[i];
        int len = strlen(arg);
        i++;

        // parse as option?
        if (
            len >= 2 && (
                arg[0] == '-' ||
                (arg[0] == '/' && access(arg, F_OK) < 0)
            )
        ) {
            int optlen;

            // options with no value
            if (
                !strcasecmp(arg + 1, "manifest") ||
                !strcasecmp(arg + 1, "nologo") ||
                !strcasecmp(arg + 1, "notify_update") ||
                !strcasecmp(arg + 1, "hashupdate") ||
                !strcasecmp(arg + 1, "makecdfs") ||
                !strcasecmp(arg + 1, "validate_manifest") ||
                !strcasecmp(arg + 1, "canonicalize") ||
                !strcasecmp(arg + 1, "check_for_duplicates") ||
                !strcasecmp(arg + 1, "nologo")
            ) {
                add_arg(arg, len);
                continue;
            }

            // options with literal value
            if (
                begins_with_ci(arg + 1, "identity:", &optlen) ||
                begins_with_ci(arg + 1, "dll:", &optlen)
            ) {
                add_arg(arg, len);
                continue;
            }

            // options with path value
            if (
                begins_with_ci(arg + 1, "rgs:", &optlen) ||
                begins_with_ci(arg + 1, "tlb:", &optlen) ||
                begins_with_ci(arg + 1, "replacements:", &optlen) ||
                begins_with_ci(arg + 1, "managedassemblyname:", &optlen) ||
                begins_with_ci(arg + 1, "out:", &optlen) ||
                begins_with_ci(arg + 1, "hashupdate:", &optlen) ||
                begins_with_ci(arg + 1, "validate_file_hashes:", &optlen)
            ) {
                add_arg(arg, 1 + optlen);
                continue;
            }

            // options with path value and optional resource ID
            if (
                begins_with_ci(arg + 1, "inputresource:", &optlen) ||
                begins_with_ci(arg + 1, "outputresource:", &optlen) ||
                begins_with_ci(arg + 1, "updateresource:", &optlen)
            ) {
                int j;
                for (j = len - 1; j >= 1 + optlen; j--) {
                    if (arg[j] == ';') {
                        break;
                    }
                }
                if (j >= 1 + optlen) {
                    start_argument();
                    write_argument_a(arg, 1 + optlen);
                    write_argument_path(arg + (1 + optlen), j - (1 + optlen));
                    write_argument_a(arg + j, len - j);
                    end_argument();
                } else {
                    add_arg(arg, 1 + optlen);
                }
                continue;
            }
        }

        // assume its is a path
        add_arg(arg, 0);
        continue;
    }
    #endif

    // zero terminate command line
    cmdline[cmdline_len] = '\0';

    if (getenv("VERBOSE") != NULL) {
        print_a("Running: ", -1);
        print_w(cmdline, cmdline_len);
        print_a("\n", -1);
    }

    // setup startup options
    STARTUPINFOW si;
    GetStartupInfoW(&si);
    si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    // start process
    PROCESS_INFORMATION pi;
    if (!CreateProcessW(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        fail("CreateProcessW failed");
    }

    DWORD res = WaitForMultipleObjects(1, &pi.hProcess, FALSE, INFINITE);
    assert(res == WAIT_OBJECT_0);

    DWORD exit_code;
    if (!GetExitCodeProcess(pi.hProcess, &exit_code)) {
        fail("GetExitCodeProcess failed");
    }

    #if defined(WRAP_MT)
    if (exit_code == MT_MAGIC) {
        exit_code = MT_MAGIC_CONV;
    }
    #endif

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return exit_code;
}
