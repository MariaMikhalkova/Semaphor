#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Semaphor.h"
using namespace std;
int id;
void Semaphore::Enter()
{
		ev.Wait();
		countCS.Enter();
		if (c < maxCount)
		{
			cout << " thread =" << ++Count << "   ";
			c++;
			std::cout << "Max tread = " << maxCount << " enter: thread id: " << GetCurrentThreadId() << " total number of threads: " <<c << std::endl;
			if (c < maxCount)
				ev.Set();
			countCS.Leave();
			//Sleep(rand() % 2900 + 600);
			Sleep(1500);
			countCS.Enter();

		}		
			Leave();
			countCS.Leave();
		

}
void Semaphore::Leave()
{
	if (c == maxCount)
	{
		ev.Set();
	}
	c--;
	std::cout << "Leave: thread id: " << GetCurrentThreadId() << " total number of threads: " << c << std::endl;
}
void Event::Close() { CloseHandle(hEvent); };

