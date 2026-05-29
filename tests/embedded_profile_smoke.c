#include "procTypes.h"

#ifdef EXIP_SMOKE_CONTIKI
#include "d_mem.h"
#endif

int main(void)
{
#ifdef EXIP_SMOKE_CONTIKI
    d_malloc_init();
    if(d_malloc_freespace() == 0)
    {
        return 1;
    }
#endif

    return 0;
}
