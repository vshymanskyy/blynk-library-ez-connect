extern "C" {
  #include <wm_os.h>
  #include <wmstdio.h>
  #include <wmtime.h>
  #include <wmsdk.h>

  #include "runtime.h"
}

void *__dso_handle = 0;

/*
void* operator new(size_t size)
{
   return malloc(size);
}

void* operator new[](size_t size)
{
   return malloc(size);
}

void operator delete(void* ptr)
{
   free(ptr);
}

void operator delete[](void* ptr)
{
   free(ptr);
}

void operator delete(void* ptr, unsigned) // TODO: Check
{
   free(ptr);
}

void operator delete[](void* ptr, unsigned) // TODO: Check
{
   free(ptr);
}

extern "C" void __cxa_pure_virtual(void) __attribute__ ((__noreturn__));
extern "C" void __cxa_deleted_virtual(void) __attribute__ ((__noreturn__));
extern "C" void abort()
{
  pm_reboot_soc();
  for(;;);
}

extern "C" void _exit() { abort(); }
extern "C" void _kill(int) { }
extern "C" int _getpid() { return 0; }

void __cxa_pure_virtual(void) {
  abort();
}

void __cxa_deleted_virtual(void) {
  abort();
}
*/

extern "C" void _exit() { pm_reboot_soc(); }
extern "C" void _kill(int) { }
extern "C" int _getpid() { return 0; }

extern void (*__init_array_start)(void);
extern void (*__init_array_end)(void);

extern "C"
void do_global_ctors(void)
{
    void (**p)(void);
    for (p = &__init_array_start; p != &__init_array_end; ++p)
            (*p)();
}
