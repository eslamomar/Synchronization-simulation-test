#include <pthread.h>

struct station {

int wait_passengers;     // count numbers of passengers in the station
pthread_mutex_t lock;           // lock to make critical section
pthread_cond_t Flag_train;    //  indicate that the train in station
pthread_cond_t at_seat;            //signal to indicate that passenger seat in train
};
void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
