#include <iostream>
#include "Philosopher.h"
#include "Fork.h"
#include <pthread.h>

#define NUMBER 5

using namespace std;

int main()
{

	Philosopher ph [NUMBER];
	Fork * f = new Fork[NUMBER];
	pthread_t t[NUMBER];

	for (int i = 0; i < NUMBER; ++i)
	{
		ph[i].setId(i+1);
	}


	for (int i = 0; i < 10; ++i)
	{
		for (int i = 0; i < NUMBER; ++i)
		{
			t[i] = ph[i].doEating(&f[i],&f[(i+1)%NUMBER]);
		}
		for (int i = 0; i < NUMBER; ++i)
		{
			pthread_join(t[i],NULL);
		}
	}

}
