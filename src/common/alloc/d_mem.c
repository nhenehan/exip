/*
 * "Copyright (c) 2008, 2009 The Regents of the University  of California.
 * All rights reserved."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "d_mem.h"

uint8_t heap[D_MEM_HEAP_SIZE];

uint16_t memUsage = 0;

/* An all-zero heap has a zero-length first block, on which the block walks below never
 * advance: initialise before the first use */
static int d_mem_ready = 0;

void d_malloc_init(void) {
  bndrt_t *b = (bndrt_t *)heap;
  *b = D_MEM_HEAP_SIZE  & D_MEM_LEN;
  d_mem_ready = 1;
}

static void d_mem_ensure_init(void) {
  if (!d_mem_ready)
    d_malloc_init();
}

uint16_t getMemUsage(void)
{
	uint16_t tmpUsg = memUsage;
	memUsage = 0;
	return tmpUsg;
}

void* d_malloc(size_t req) {
  bndrt_t* cur = (bndrt_t*) heap;
  uint16_t sz;
  d_mem_ensure_init();
  /* block = header + payload + next header, aligned; larger requests cannot be represented */
  if (req > D_MEM_LEN - sizeof(bndrt_t) * 2 - D_MEM_ALIGN)
    return NULL;
  sz = (uint16_t) req;
  sz += sizeof(bndrt_t) * 2;
  sz += (sz % D_MEM_ALIGN);

  while (((*cur & D_MEM_LEN) < sz || (*cur & D_MEM_INUSE) != 0)
         && (uint8_t *)cur - heap < D_MEM_HEAP_SIZE) {
    cur = (bndrt_t *)(((uint8_t *)cur) + ((*cur) & D_MEM_LEN));
  }

  if ((uint8_t *)cur < heap + D_MEM_HEAP_SIZE) {
	  bndrt_t oldsize = *cur & D_MEM_LEN;
    bndrt_t *next;
    sz -= sizeof(bndrt_t);
    next = ((bndrt_t *)(((uint8_t *)cur) + sz));

    *cur = (sz & D_MEM_LEN) | D_MEM_INUSE;
    *next = (oldsize - sz) & D_MEM_LEN;

    if(memUsage < D_MEM_HEAP_SIZE - d_malloc_freespace())
    {
    	memUsage = D_MEM_HEAP_SIZE - d_malloc_freespace();
    }
    return cur + 1;
  } else return NULL;
}

void d_free(void *ptr) {
  bndrt_t *prev = NULL, *cur, *next = NULL;
  d_mem_ensure_init();
  if (ptr == NULL)
    return;
  cur = (bndrt_t *)heap;

  while (cur + 1 != ptr && (uint8_t *)cur - heap < D_MEM_HEAP_SIZE) {
    prev = cur;
    cur = (bndrt_t *)(((uint8_t *)cur) + ((*cur) & D_MEM_LEN));
  }
  if (cur + 1 == ptr) {
    next = (bndrt_t *)((*cur & D_MEM_LEN) + ((uint8_t *)cur));

    *cur &= ~D_MEM_INUSE;
    if ((((uint8_t *)next) - heap) < D_MEM_HEAP_SIZE &&
        (*next & D_MEM_INUSE) == 0) {
      *cur = (*cur & D_MEM_LEN) + (*next & D_MEM_LEN);
    }
    if (prev != NULL && (*prev & D_MEM_INUSE) == 0) {
      *prev = (*prev & D_MEM_LEN) + (*cur & D_MEM_LEN);
    }
  }
}

uint16_t d_malloc_freespace(void) {
  uint16_t ret = 0;
  bndrt_t *cur = (bndrt_t *)heap;
  d_mem_ensure_init();

  while ((uint8_t *)cur - heap < D_MEM_HEAP_SIZE) {
    if ((*cur & D_MEM_INUSE) == 0)
      ret += *cur & D_MEM_LEN;
    cur = (bndrt_t *)(((uint8_t *)cur) + ((*cur) & D_MEM_LEN));
  }
  return ret;
}

void* d_realloc(void *ptr, size_t size)
{
	void* p_ptr;
	size_t old_size;

	if(ptr == NULL)
		return d_malloc(size);

	p_ptr = d_malloc(size);
	if(p_ptr == NULL)
		return NULL;

	/* the old payload: its block length less the two headers d_malloc counted */
	old_size = (size_t) ((*((bndrt_t *)ptr - 1) & D_MEM_LEN) - sizeof(bndrt_t));
	memcpy(p_ptr, ptr, old_size < size ? old_size : size);

	d_free(ptr);
	return p_ptr;
}
