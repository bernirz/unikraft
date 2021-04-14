#include <uk/futex.h>
#include <uk/syscall.h>
#include <uk/arch/atomic.h>
#include <uk/thread.h>
#include <uk/list.h>
#include <stdio.h>
#include <uk/assert.h>
#include <uk/print.h>
#include <errno.h>

// TODO: macro ok?
#define add_futex(addr, fthread) \
    struct uk_futex *f = uk_malloc(uk_alloc_get_default(), \
                                   sizeof(*f)); \
    f->futex = addr; \
    f->thread = fthread; \
    uk_list_add_tail(&f->list_node, &futex_list);

static UK_LIST_HEAD(futex_list);

static void mylistadd(uint32_t *addr, struct uk_thread* t)
{
    struct uk_futex *f = uk_malloc(uk_alloc_get_default(), sizeof(*f));
    // TODO: alloc can fail?

    f->futex = addr;
    f->thread = t;
    uk_list_add_tail(&f->list_node, &futex_list);
}

static int futex_wait(uint32_t *uaddr, uint32_t val, const struct timespec *tm)
{
    /* 
     * Check atomically if the futex word
     * contains val
     * TODO: atomic comparison ?? needed?
    */
    if (ukarch_load_n(uaddr) == val)
    {
        uk_pr_debug("Futex sleep\n");
        add_futex(uaddr, uk_thread_current());
        //mylistadd(uaddr, uk_thread_current());
        
        if (tm) 
            /* Block for at least x nanosecs */
            uk_thread_block_timeout(uk_thread_current(), tm->tv_nsec);
        else
            /* Block undefinitely */
            uk_thread_block(uk_thread_current());
        
        uk_sched_yield();

        /* Thread is no longer blocked */
        return 0;
    }

    /* futex word does not contain expected val */
    errno = EAGAIN;
    return -1;
}

static int futex_wake(uint32_t *uaddr, uint32_t val)
{
    int count = 0; // waken-up threads

    struct uk_list_head *i, *tmp;
    struct uk_futex *f;
    uk_list_for_each_safe(i, tmp, &futex_list) {

        /* Wakes at most val thread */
        if ((uint32_t)count >= val)
            break;

		f = uk_list_entry(i, struct uk_futex, list_node);

        if (f->futex == uaddr) {
            ++count;
            uk_thread_wake(f->thread);
            uk_list_del(i);
        }
	}

    return count;
}

static int futex_cmp_requeue(uint32_t *uaddr, uint32_t val,
    const struct timespec *timeout,
    uint32_t *uaddr2, uint32_t val3)
{
        /*For several blocking operations, the timeout argument is a
       pointer to a timespec structure that specifies a timeout for the
       operation.  However,  notwithstanding the prototype shown above,
       for some operations, the least significant four bytes of this
       argument are instead used as an integer whose meaning is
       determined by the operation.  For these operations, the kernel
       casts the timeout value first to unsigned long, then to uint32_t,
       and in the remainder of this page, this argument is referred to
       as val2 when interpreted in this fashion.*/
    // TODO: probably better to use val2 directly from call to futex
    unsigned long tmp = (unsigned long)(timeout->tv_nsec);
    uint32_t val2 =  tmp & 0xFFFFFFFF;

    if (!(val3 == ukarch_load_n(uaddr)))
    {
        errno = EAGAIN;
        return -1;
    }

    uint32_t ret = futex_wake(uaddr, val);
    // TODO:
    uint32_t waiters_uaddr2 = 0;
    
    /*Otherwise, the operation
              wakes up a maximum of val waiters that are waiting on the
              futex at uaddr.  If there are more than val waiters, then
              the remaining waiters are removed from the wait queue of
              the source futex at uaddr and added to the wait queue of
              the target futex at uaddr2.  The val2 argument specifies
              an upper limit on the number of waiters that are requeued
              to the futex at uaddr2.*/
    return 0;
}

long myfutex(uint32_t *uaddr, int futex_op, uint32_t val,
                 const struct timespec *timeout,
                 uint32_t *uaddr2, int val3)
{
    switch (futex_op) {

        case FUTEX_WAIT:
            return futex_wait(uaddr, val, timeout);
        
        case FUTEX_WAKE:
            return futex_wake(uaddr, val);

        case FUTEX_FD:
        case FUTEX_REQUEUE:
            errno = ENOSYS;
            return -1;

        case FUTEX_CMP_REQUEUE:
            return futex_cmp_requeue(uaddr, val, timeout, uaddr2, val3);
        
        default:
            errno = ENOSYS;
            return -1;
            // TODO: other operations?
    }
}

UK_SYSCALL_DEFINE(long, futex, uint32_t *, uaddr, int, futex_op, 
    uint32_t, val, const struct timespec *, timeout,
    uint32_t *, uaddr2, uint32_t, val3)
{
    ssize_t ret;

    ret = myfutex(uaddr, futex_op, val, timeout, uaddr2, val3);
    if (ret < 0) {
        errno = EFAULT;
        return -1;
    }
    return ret;
}