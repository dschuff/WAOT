#include <errno.h>
#include <stdlib.h>
#include "wart_trap.h"

/* For now, only support having one running module at a time. We expect the
   generated spec script code to instantiate the module by calling
   __wasm_allocate_memory and tear it down with __wasm_free_memory.
*/
const size_t kPageSize =
    64 * 1024;  // NaCl uses 64k, it should work everywhere.

size_t __wasm_page_size() {
  return kPageSize;
}

void __wasm_allocate_memory(void** base, size_t initial_size) {
  if (!base)
    return;
  if (!initial_size) {
    /* posix_memalign does not specify whether a real pointer or NULL
       is returned in this case, so we just set base to NULL. */
    *base = NULL;
    return;
  }
  int ret = posix_memalign(base, kPageSize, initial_size);
  if (ret == ENOMEM) {
    __wasm_report_error("Out of memory allocating heap of %zd bytes\n",
                        initial_size);
    __wasm_trap(kOutOfMemory);
  }
  if (ret != 0) {
    __wasm_report_error(
        "Error allocating heap of %zd bytes with aligment %zd\n", initial_size,
        kPageSize);
    __wasm_trap(kUnknownInternalError);
  }
}

void __wasm_grow_memory(size_t delta) {
  if ((delta & (kPageSize - 1)) != 0) {
    __wasm_report_error(
        "grow_memory delta %zd is not a multiple of page size %zd\n", delta,
        kPageSize);
    __wasm_trap(kInvalidArgument);
  }
}

void __wasm_free_memory(void** base) {
  if (base)
    free(*base);
}