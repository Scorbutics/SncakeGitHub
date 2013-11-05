#include "define_platform.h"

#ifdef _Win32
#include <windows.h>
#endif

#ifdef _Unix
#include <pthread.h>
#endif



struct PortableThread
{
	#ifdef _Win32
		HANDLE handle;
	#else
		pthread_t handle;
	#endif
};
typedef struct PortableThread PortableThread;

struct PortableMutex
{
	#ifdef _Win32
		CRITICAL_SECTION* handle;
	#else
		pthread_mutex_t handle;
	#endif
};
typedef struct PortableMutex PortableMutex;

struct PortableTCondition
{
	#ifdef _Win32
		int flag;
	#else
		pthread_cond_t flag;
	#endif
};
typedef struct PortableTCondition PortableTCondition;



PortableThread* PortableThreadCreate(void* function, void* data);
void PortableThreadWait(PortableThread* th);
void PortableThreadFree(PortableThread* th);


PortableMutex* PortableMutexCreate();
void PortableMutexLock(PortableMutex* mut);
void PortableMutexUnlock(PortableMutex* mut);
void PortableMutexFree(PortableMutex* mut);

PortableTCondition* PortableTConditionCreate();
void PortableTConditionSignal(PortableTCondition* ptc);
void PortableTConditionWait(PortableMutex* mut, PortableTCondition* ptc);
void PortableTConditionFree(PortableTCondition* ptc);
