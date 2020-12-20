#ifndef __UK_SIGNAL_H__
#error Do not include this header directly
#endif

#ifndef __UK_SIGSET_H__
#define __UK_SIGSET_H__

#ifdef __cplusplus
extern "C" {
#endif

#define SIG_BLOCK     0
#define SIG_UNBLOCK   1
#define SIG_SETMASK   2

typedef unsigned long __sigset_t;
typedef __sigset_t sigset_t;

int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
int sigismember(const sigset_t *set, int signo);

/* TODO: do we have gnu statement expression?  */
/* internal use */
#define uk_sigemptyset(ptr)	\
		do {	\
			*(ptr) = 0;	\
		} while (0)
#define uk_sigfillset(ptr)	\
		do {	\
			*(ptr) = ~((__sigset_t) 0);	\
		} while (0)
#define uk_sigaddset(ptr, signo)	\
		do {	\
			*(ptr) |= (1 << ((signo) - 1));	\
		} while (0)
#define uk_sigdelset(ptr, signo)	\
		do {	\
			*(ptr) &= ~(1 << ((signo) - 1));	\
		} while (0)
#define uk_sigcopyset(ptr1, ptr2)	\
		do {	\
			*(ptr1) = *(ptr2);	\
		} while (0)
#define uk_sigandset(ptr1, ptr2)	\
		do {	\
			*(ptr1) &= *(ptr2);	\
		} while (0)
#define uk_sigorset(ptr1, ptr2)	\
		do {	\
			*(ptr1) |= *(ptr2);	\
		} while (0)
#define uk_sigreverseset(ptr)	\
		do {	\
			*(ptr) = ~(*(ptr));	\
		} while (0)
#define uk_sigismember(ptr, signo) (*(ptr) & (1 << ((signo) - 1)))
#define uk_sigisempty(ptr) (*(ptr) == 0)

#ifdef __cplusplus
}
#endif

#endif /* __UK_SIGSET_H__ */
