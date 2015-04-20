#pragma once

#include "Fork.h"

#include <pthread.h>
#include <iostream>
#include <time.h>


enum PhilosopherStatus
{
	EATING = 0,
	THINKING = 1
};


class Philosopher
{
public:
	//static pthread_mutex_t writer;

	Philosopher()
	{
		// pthread_mutex_init(& Philosopher::writer,NULL);
		status = THINKING;
	}

	PhilosopherStatus getStatus()
	{
		return status;
	}
	int getId()
	{
		return id;
	}

	void setId(int _id)
	{
		id = _id;
	}

	void setStatus(PhilosopherStatus s , bool isFinished = false)
	{
		status = s;

		// pthread_mutex_lock(& Philosopher::writer);
		// std::cout << "Philosopher "<<getId()<<" ";
		// if(isFinished)
		// 	std::cout << "again started ";
		// else 
		// 	std::cout << "is now ";

		// switch(status)
		// {
		// 	case THINKING:
		// 		std::cout << "Thinking";
		// 		break;

		// 	case EATING:
		// 		std::cout << "Eating";
		// 		break;
		// }
		// std::cout << "\n";
		// pthread_mutex_unlock(& Philosopher::writer);

		std::string sts , job;

		if(isFinished)
			sts =  "again started ";
		else 
			sts =  "is now ";
		
		switch(status)
		{
			case THINKING:
				job =  "Thinking";
				break;

			case EATING:
				job = "Eating";
				break;
		}

		printf("Philosopher %d %s %s\n",getId(),sts.c_str(),job.c_str()); // printf works at one level

	}

	void * eat()
	{
		setStatus(THINKING);//aval fekr mikone

		fork1->pick();//fork 1 ro bar midare
		fork2->pick();// fork 2 ro bar midare
		


		setStatus(EATING);// shoroo mikone be khordan
		
 		//khordan tool mikeshe
	    clock_t goal = 3000000 + clock();
	    while (goal > clock());

	    //changal haro azad mikone
	    setStatus(THINKING,true);//baad khordan dobare fekr mikone

		fork2->release();
		fork1->release();
		

		return NULL;

	}


	//dar cpp chon zaban tamam compileri hast baad link shodan har tabe ye address moshakhas dare ama tavabe gheyre static class intor nistan
	static void *eatHelper(void *context) // in func vase sakht thread hast chon function class ye chize moskakhas nist bayad ye tabe static bezarim ke darzaman ejra betoone address link tabe marboote ro bede.
    {
        return ((Philosopher *)context)->eat();
    }

	pthread_t doEating(Fork* f1 , Fork * f2) // fork haye class meghdar dehi mishe va thread sakhte mishe
	{
		fork1 = f1;
		fork2 = f2;
		pthread_create(&thread, NULL, &Philosopher::eatHelper, this);
		return thread;
	}

private:
	PhilosopherStatus status;
	pthread_t thread;
	Fork * fork1;
	Fork * fork2;
	int id;

};