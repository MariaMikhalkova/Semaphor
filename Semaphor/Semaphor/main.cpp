#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
int id;
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
	Event() { CreateEvent(NULL, TRUE, FALSE, NULL); };
	~Event() { Close(); }

	void Set() { SetEvent(hEvent); }
	void Reset(){ ResetEvent(hEvent); };

	void Wait(int ms) { WaitForSingleObject(hEvent, ms); };
	void Wait() { Wait(INFINITE); };

	void Close();
};

class Semaphore
{
	int maxCount;
	int Count;
	int c = 0;
	CS countCS;
	Event ev;
public:
	Semaphore(int _maxCount) : maxCount(_maxCount), Count(0)
	{
		countCS = CS();
		ev = Event();
	}
	~Semaphore()
	{
		countCS.Delete();
		ev.Close();

	}
	void Leave();
	void Enter();

};
void Semaphore::Enter()
{

	countCS.Enter();

	//cout << maxCount;
	if ((c != maxCount))
	{
		id = GetCurrentThreadId();
		c++;
		if (Count >= 15){ return; };
		Count++;
		cout << " thread =" << Count << "   ";
		std::cout << "Max tread = " << maxCount << " enter: thread id: " << id << " total number of threads: " << c << std::endl;

		countCS.Leave();

		return;

	}
	//std::cout << "Enter: CS is unlocked, total number of threads: " << Count << std::endl;

	countCS.Leave();
	ev.Wait();
	Sleep(5);


}
void Semaphore::Leave()
{


	countCS.Enter();

	//cout <<"                      pp                      "<< Count<<endl;
	if ((c != maxCount - 1))
	{

		ev.Set(); id = GetCurrentThreadId();
		c--;
		std::cout << "Leave: thread id: " << id << " total number of threads: " << c << std::endl;

	}
	countCS.Leave();
	Sleep(1000);

}
void Event::Close() { CloseHandle(hEvent); };



Semaphore *sem;

DWORD WINAPI foo(PVOID)
{
	int num = 15;
	for (int i = 0; i < num; ++i){
		sem->Enter();
		/*auto mas = new int[1000];
		for (int i = 0; i < 1000; i++) /// Цикл забива рандомными значениями
		{
		mas[i] = rand() % 1000 - 500;
		}
		bool changes = true;
		while (changes) /// Сортировка пузырьком. Полезная нагрузка
		{
		changes = false;
		for (int i = 0; i < 999; i++)
		if (mas[i] > mas[i + 1])
		{
		int a = mas[i];
		mas[i] = mas[i + 1];
		mas[i + 1] = a;
		changes = true;
		}
		Sleep(1);
		}
		delete[] mas;*/
		Sleep(10);
		sem->Leave();
		//Sleep(100);
	}


	return 0;
}

int main()
{
	int maxCount, num;
	std::cout << "Input maxCount for Semaphore -> ";
	std::cin >> maxCount;
	std::cout << "Input number of threads -> ";
	std::cin >> num;

	sem = new Semaphore(maxCount);
	HANDLE * thread = new HANDLE[num];

	for (int i = 0; i<num; ++i)
	{
		thread[i] = CreateThread(NULL, 0, foo, NULL, 0, NULL);
	}

	WaitForMultipleObjects(num, thread, TRUE, INFINITE);

	for (int i = 0; i<num; ++i)
		CloseHandle(thread[i]);

	std::cout << "Done ";


	return 0;
}

