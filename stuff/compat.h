#ifndef _COMPAT_H
#define _COMPAT_H

#include <sys/time.h>

#define DOS_CLK_TCK 0x10000

extern time_t dos_clock(void);
extern void _splitpath(const char *src, char *drive, char *path, char *file, char *ext);
extern void _makepath(char *dst /* PATH_MAX+1 */, const char *drive, const char *path, const char *file, const char *ext);

#ifndef HAVE_STRUPR
extern char *strupr(char *src);
#else
#include <string.h>
#endif

extern size_t filelength(int fd);
extern size_t _filelength(const char *path);
extern int memicmp(const void *s1, const void *s2, size_t n);

#ifndef HAVE_VSNPRINTF
#include <stdarg.h> /* for va_list */
extern int vsnprintf(char *buff, size_t bufsiz, const char *fmt, va_list ap);
#endif

#ifndef HAVE_SNPRINTF
extern int snprintf(char *buff, size_t bufsiz, const char *fmt, ...);
#endif /* HAVE_SNPRINTF */

#ifndef HAVE_STRERROR
extern char *strerror(int errnum);
#endif /* HAVE_STRERROR */

/* There is no prototype of usleep() on Solaris. Why? */
#if !defined(HAVE_USLEEP) || defined(SOLARIS)
extern int usleep(unsigned int usec);
#endif

#ifdef __W32__
#define sleep(time) Sleep(time)
#else
#ifndef HAVE_SLEEP
#define sleep(s) usleep((s) * 1000000)
#endif /* HAVE_SLEEP */
#endif

#ifndef HAVE_STRDUP
extern char *strdup(const char *s);
#endif /* HAVE_STRDUP */

#ifndef HAVE_GETCWD
extern char *getcwd(char *buf, size_t size);
#endif /* HAVE_GETCWD */

#ifndef HAVE_STRSTR
#define strstr(s,c)	index(s,c)
#endif /* HAVE_STRSTR */

#ifndef HAVE_STRNCASECMP
extern int strncasecmp(char *s1, char *s2, unsigned int len);
#endif /* HAVE_STRNCASECMP */

#ifndef HAVE_MKSTEMP
extern int mkstemp(char *template);
#endif /* HAVE_MKSTEMP */

#ifndef HAVE_SYS_STAT_H
#ifdef __W32__
#include <sys/stat.h>          /* they have. */
#elif defined(__MACOS__)
#define S_IFDIR 1
#define S_ISDIR(m)   ((m) & S_IFDIR)
struct stat {
	short st_mode;
	short st_dev;
	long st_ino;
	unsigned long st_size;
	unsigned long st_mtime, st_ctime, st_btime;
};
int stat(const char *filename, struct stat *st);
#endif /* __W32__ */
#else
#include <sys/stat.h>
#endif /* HAVE_SYS_STAT_H*/

#endif

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode)&0xF000) == 0x4000)
#endif /* S_ISDIR */

#ifndef HAVE_STRLCPY
#include <stddef.h>
extern size_t strlcpy(char *dst, const char *src, size_t size);
#endif

#ifndef HAVE_STRLCAT
#include <stddef.h>
extern size_t strlcat(char *dst, const char *src, size_t size);
#endif
