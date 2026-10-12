/* Smoke test for builds without the test suites: the libraries link, the
 * dmem allocator initialises, and the configured type widths are the ones in effect. */
#include "procTypes.h"

#ifdef EXIP_SMOKE_DMEM
#include <string.h>
#include "d_mem.h"

/* The d_mem fixes: use before d_malloc_init, oversized requests, realloc */
static int check_dmem(void)
{
    uint16_t empty;
    char* p;
    char* q;

    /* first use without d_malloc_init() (an all-zero heap used to loop forever) */
    p = d_malloc(16);
    if(p == NULL)
        return 1;
    d_free(p);
    empty = d_malloc_freespace();
    if(empty == 0)
        return 1;

    /* a request larger than a block can hold fails instead of being truncated */
    if(d_malloc(70000) != NULL || d_malloc(D_MEM_HEAP_SIZE) != NULL)
        return 1;

    /* realloc: NULL allocates; growing and shrinking keep the contents */
    p = d_realloc(NULL, 8);
    if(p == NULL)
        return 1;
    memcpy(p, "abcdefg", 8);
    q = d_realloc(p, 200);
    if(q == NULL || memcmp(q, "abcdefg", 8) != 0)
        return 1;
    p = d_realloc(q, 4);
    if(p == NULL || memcmp(p, "abcd", 4) != 0)
        return 1;
    d_free(p);
    d_free(NULL);
    if(d_malloc_freespace() != empty)
        return 1;

    d_malloc_init();
    return d_malloc_freespace() == 0;
}
#endif

int main(void)
{
#ifdef EXIP_SMOKE_DMEM
    if(check_dmem() != 0)
    {
        return 1;
    }
#endif
#ifdef EXIP_SMOKE_INTEGER_BYTES
    if(sizeof(UnsignedInteger) != EXIP_SMOKE_INTEGER_BYTES || sizeof(Integer) != EXIP_SMOKE_INTEGER_BYTES)
    {
        return 2;
    }
#endif
#ifdef EXIP_SMOKE_INDEX_BYTES
    if(sizeof(Index) != EXIP_SMOKE_INDEX_BYTES)
    {
        return 3;
    }
#endif
#ifdef EXIP_SMOKE_SMALL_INDEX_BYTES
    if(sizeof(SmallIndex) != EXIP_SMOKE_SMALL_INDEX_BYTES)
    {
        return 4;
    }
#endif
    {
        /* a negative float exponent must survive (plain char is unsigned on ARM) */
        Float f;
        f.exponent = -5;
        if(f.exponent != -5)
        {
            return 5;
        }
    }

    return 0;
}
