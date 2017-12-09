#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std; 

class CS
{
	CRITICAL_SECTION cs;
public:
	CS() { InitializeCriticalSection(&cs); }
	void Enter() { EnterCriticalSection(&cs); }
	void Leave() { LeaveCriticalSection(&cs); }
	void Delete() { DeleteCriticalSection(&cs); }
};

class Event
{
	HANDLE hEvent;
public:
	Event() {hEvent=CreateEvent(NULL, FALSE, FALSE, NULL); };
	~Event() { CloseHandle(hEvent); };

	void Set() { SetEvent(hEvent); }
	void Reset(){ ResetEvent(hEvent); };

	void Wait(int ms) 
	{
		 WaitForSingleObject(hEvent, ms); 
	};
	void Wait()
	{
		 Wait(INFINITE);
	};

	void Close();
};

class Semaphore
{
	int maxCount;
	int Count;
	int c;
	int count_all;
	CS countCS;
	Event ev;
	Event sem;
	
public:
	Semaphore(int _maxCount, int count) : maxCount(_maxCount), Count(0), c(0), count_all(count)
	{
		countCS = CS();
		ev.Set();
		sem.Reset();

	}
	~Semaphore()
	{
		countCS.Delete();
		ev.Close();

	}
	void Leave();
	void Enter();

};