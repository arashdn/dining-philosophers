#pragma once
#include <iostream>

class Fork
{
public:
	Fork()
	{
		pthread_mutex_init(&mutex,NULL);
	}

	void pick()
	{
		pthread_mutex_lock(&mutex);
		//std::cout << "Picked\n";
	}

	void release()
	{
		pthread_mutex_unlock(&mutex);
		//std::cout<<"Released\n";
	}
private:
	pthread_mutex_t mutex;
};