<<<<<<< HEAD
#ifndef __UK_SIGNAL_H__
#error Do not include this header directly
#endif

=======
/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors:  Mihai Pogonaru <pogonarumihai@gmail.com>
 *		     Teodora Serbanescu <teo.serbanescu16@gmail.com>
 *		     Felipe Huici <felipe.huici@neclab.eu>
 *		     Bernard Rizzo <b.rizzo@student.uliege.be>
 *
 * Copyright (c) 2021, University Politehnica of Bucharest.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
>>>>>>> upstream/staging
#ifndef __UK_SIGSET_H__
#define __UK_SIGSET_H__

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
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
=======
/* TODO: do we have gnu statement expression?  */
/* internal use */
#define uk_sigemptyset(ptr)	(*(ptr) = 0)
#define uk_sigfillset(ptr)  (*(ptr) = ~((__sigset_t) 0))
#define uk_sigaddset(ptr, signo) (*(ptr) |= (1 << ((signo) - 1)))
#define uk_sigdelset(ptr, signo) (*(ptr) &= ~(1 << ((signo) - 1)))
#define uk_sigcopyset(ptr1, ptr2) (*(ptr1) = *(ptr2))
#define uk_sigandset(ptr1, ptr2)  (*(ptr1) &= *(ptr2))
#define uk_sigorset(ptr1, ptr2)	  (*(ptr1) |= *(ptr2))
#define uk_sigreverseset(ptr)	  (*(ptr) = ~(*(ptr)))
>>>>>>> upstream/staging
#define uk_sigismember(ptr, signo) (*(ptr) & (1 << ((signo) - 1)))
#define uk_sigisempty(ptr) (*(ptr) == 0)

#ifdef __cplusplus
}
#endif

#endif /* __UK_SIGSET_H__ */
