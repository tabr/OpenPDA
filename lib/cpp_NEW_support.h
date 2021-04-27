/*
 * cpp_NEW_support.h
 *
 * Created: 2015-06-08 19:01:31
 *  Author: tabr
 */ 


#ifndef CPP_NEW_SUPPORT_H_
#define CPP_NEW_SUPPORT_H_


/*
void * operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	free(ptr);
}
*/
// C++  helpers /////////////////////
void * operator new(size_t size);
//void operator delete(void * ptr);
void * operator new(size_t size)
	{
	//hui();
	//return malloc(size);
//	return MemoryManager.allocate(size);
	return MemoryManagerClass::Allocate(size);
	}
void * operator new[](size_t size)
	{
	//return malloc(size);
//	return MemoryManager.allocate(size);
	return MemoryManagerClass::Allocate(size);
	}
/*
void operator delete(void * ptr)
	{
	//free(ptr);
	//MemoryManager.deallocateFromTop()
	}*/
#ifdef ATMEL_STUDIO
__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
int __cxa_guard_acquire(__guard *g)
{
	return !*(char *)(g);
}
void __cxa_guard_release (__guard *g)
{
	*(char *)g = 1;
}
void __cxa_guard_abort (__guard *)
{
}
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void)
{
}
#endif


#endif /* CPP_NEW_SUPPORT_H_ */