#include <stdio.h>
#include "PortableThread.h"


PortableThread* PortableThreadCreate(void* function, void* data)
{
	PortableThread* th = (PortableThread*) malloc(sizeof(PortableThread));
	if(th == NULL)
	{
		printf("Erreur lors de l'allocation d'un PortableThread.\n");
		return NULL;
	}

	#ifdef _Win32
		th->handle = CreateThread (NULL, 0UL, (LPTHREAD_START_ROUTINE)function, data, 0, NULL);
	#else
		th->handle = pthread_create(&th->handle, NULL, function, data);
	#endif

	return th;
}

void PortableThreadWait(PortableThread* th)
{
	#ifdef _Win32
		WaitForSingleObject(th->handle, INFINITE);
		CloseHandle(th->handle);
	#else
		pthread_join(th->handle, NULL);
	#endif
}

void PortableThreadFree(PortableThread* th)
{
	CloseHandle(th->handle);
	free(th);
}




PortableMutex* PortableMutexCreate()
{
	PortableMutex* mut = (PortableMutex*) malloc(sizeof(PortableMutex));
	if(mut == NULL)
	{
		printf("Erreur lors de l'allocation d'un PortableMutex.\n");
		return NULL;
	}

	#ifdef _Win32
	mut->handle = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
	if (mut->handle != NULL)
		InitializeCriticalSection(mut->handle);
	else
	{
		printf("Erreur lors de l'allocation d'une section critique.\n");
		return NULL;
	}
	#else
		pthread_mutex_init(&mut->handle, NULL);
	#endif

	return mut;

}

void PortableMutexLock(PortableMutex* mut)
{
	#ifdef _Win32
		EnterCriticalSection(mut->handle); // Lock
	#else
		pthread_mutex_lock(&mut->handle);
	#endif
}

void PortableMutexUnlock(PortableMutex* mut)
{
	#ifdef _Win32
		LeaveCriticalSection(mut->handle); // Unlock
	#else
		pthread_mutex_unlock(&mut->handle);
	#endif
	
}

void PortableMutexFree(PortableMutex* mut)
{
	#ifdef _Win32
		DeleteCriticalSection(mut->handle);
		free(mut->handle);
	#else
		pthread_mutex_destroy(&mut->handle);
	#endif

	free(mut);
}

PortableTCondition* PortableTConditionCreate()
{
	PortableTCondition* ptc = (PortableTCondition*) malloc(sizeof(PortableTCondition));
	if(ptc == NULL)
	{
		printf("Erreur lors de l'allocation d'une PortableTCondition.\n");
		return NULL;
	}

	#ifdef _Win32
	{}
	#else
		pthread_cond_init(&ptc->flag, NULL);
	#endif

	return ptc;
}

void PortableTConditionSignal(PortableTCondition* ptc)
{
	#ifdef _Win32
	{}
	#else
		pthread_cond_signal(&ptc->flag);
	#endif
}

void PortableTConditionWait(PortableMutex* mut, PortableTCondition* ptc)
{
	#ifdef _Win32
	{}
	#else
		pthread_cond_wait(&ptc->handle, &mut->handle);
	#endif
}

void PortableTConditionFree(PortableTCondition* ptc)
{
	#ifdef _Win32
	{}
	#else
		pthread_cond_destroy(&ptc->flag);
	#endif

	free(ptc);
}