#include <pthread.h>
#include "caltrain.h"


void
station_init(struct station *station)
{
//station->Flag=0;
pthread_mutex_init(&station->lock,NULL);             // initialize of mutex and condition variables
pthread_cond_init(&station->Flag_train,NULL);         
pthread_cond_init(&station->at_seat,NULL);
station->wait_passengers=0;
}
////////////////////////////////////////////////////////////////////////////////////
void
station_load_train(struct station *station, int count)
{
pthread_mutex_lock(&station->lock);

if(count > station->wait_passengers)                   // to take #passengers = to free seats in train
count=station->wait_passengers;
		
while(count !=0)
{
 pthread_cond_signal(&station->Flag_train);
 pthread_cond_wait(&station->at_seat,&station->lock);                 // every passenger seat signal train 
 count--;
}
pthread_mutex_unlock(&station->lock);
}
///////////////////////////////////////////////////////////////////////////////////
void
station_wait_for_train(struct station *station)
{
pthread_mutex_lock(&station->lock);

station->wait_passengers++;                      // count the #passengers arrive the station
pthread_cond_wait(&station->Flag_train,&station->lock);              //wait fo train signal (arrival of train )

pthread_mutex_unlock(&station->lock);
}
////////////////////////////////////////////////////////////////////////////////////
void
station_on_board(struct station *station)
{
pthread_mutex_lock(&station->lock);
station->wait_passengers--;                        //passenger seat 
pthread_cond_signal(&station->at_seat);                //send signal to train to know 
pthread_mutex_unlock(&station->lock);
}

