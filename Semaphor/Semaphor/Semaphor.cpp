#include <iostream>
#include <windows.h>
#include <conio.h>
#include"Semaphor.h"

using namespace std;

void Semaphor::Enter()
{
	countCS.Enter();
	if (Count++<maxCount)
	{
		countCS.Leave();
		return;
	}
	countCS.Leave();
	ev.Wait();
}

void Semaphor::Leave()
{
	countCS.Enter();
	if (--Count >= maxCount)
	{
		ev.Set();
	}
	countCS.Leave();
}
