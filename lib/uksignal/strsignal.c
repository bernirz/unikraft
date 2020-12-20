/* taken from newlib */

#include <uk/uk_signal.h>

/*
 * TODO: not used - delete
 */

const char *sigstring[] = {
		"Hangup",
		"Interrupt",
		"Quit",
		"Illegal instruction",
		"Trace/breakpoint trap",
		"IOT trap",
		"EMT trap",
		"Floating point exception",
		"Killed",
		"Bus error",
		"Segmentation fault",
		"Bad system call",
		"Broken pipe",
		"Alarm clock",
		"Terminated",
		"Urgent I/O condition",
		"Stopped (signal)",
		"Stopped",
		"Continued",
		"Child exited",
		"Stopped (tty input)",
		"Stopped (tty output)",
		"I/O possible",
		"CPU time limit exceeded",
		"File size limit exceeded",
		"Virtual timer expired",
		"Profiling timer expired",
		"Window changed",
		"Resource lost",
		"User defined signal 1",
		"User defined signal 2"
};

char *strsignal(int sig)
{
	char *buffer;
	struct uk_signals_container *ptr;

	ptr = _UK_TH_SIG;
	buffer = UK_SIG_BUF(ptr);

	/*
	 * TODO: this assignment doesn't really do anything
	 * since we return buffer, but newlibc did this
	 */
	if (sig <= 0 || sig >= NSIG)
		*buffer = "Unknown signal";
	else
		*buffer = sigstring[sig - 1];

	return buffer;
}
