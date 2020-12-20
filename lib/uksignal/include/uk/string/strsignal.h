#ifndef __UK_STRSIGNAL_H__
#define __UK_STRSIGNAL_H__

/*
 * TODO: not used - delete
 */

#ifdef __cplusplus
extern "C" {
#endif

extern const char * const sys_siglist[];
char *strsignal(int sig);

#ifdef __cplusplus
}
#endif

#endif /* __UK_STRSIGNAL_H__ */
