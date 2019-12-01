#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>
#include <stdlib.h>

//#############
//# Datatypes #
//#############

#define T_NULL 0
#define T_RAW  1
#define T_LL   2
#define T_DLL  3

//#########################
//# Structure Definitions #
//#########################

struct DATA_HDR
{
	size_t size;
	char   data[0];
};

struct LINKED_LIST_HDR
{
	pthread_mutex_t          lock;
	struct DATA_HDR        * element;
	struct LINKED_LIST_HDR * next;
};

struct QUEUE_HDR
{
	pthread_mutex_t          consume_lock;
	struct LINKED_LIST_HDR * first;
	pthread_mutex_t          push_lock;
	struct LINKED_LIST_HDR * last;
};

//#####################
//# Type Declarations #
//#####################

typedef struct DATA_HDR         data_t;
typedef struct LINKED_LIST_HDR  ll_t;
typedef struct QUEUE_HDR        queue_t;

//#########################
//# Function Declarations #
//#########################

// create Datatypes
data_t  * c_data( size_t data_max_size );
ll_t    * c_ll();
queue_t * c_queue();

// write to Datatypes
data_t  * w_data( void * data_ptr, size_t nbytes );

//########################
//# Function Definitions #
//########################

// Creators

queue_t * c_queue()
{
	queue_t * new_queue     = (queue_t *) malloc(sizeof(queue_t));

	new_queue->consume_lock = PTHREAD_MUTEX_INITIALIZER;
	new_queue->push_lock    = PTHREAD_MUTEX_INITIALIZER;

	return new_queue;

}

ll_t * c_ll()
{
	ll_t * new_ll = (ll_t *) malloc(sizeof(ll_t));

	new_ll->lock  = PTHREAD_MUTEX_INITIALIZER;

	return new_ll;
}


data_t * c_data( size_t max_size )
{
	data_t * new_data = (data_t *) malloc(sizeof(data_t) + max_size);
	
	new_data->size    = max_size;

	return new_data;
}

// Writers

data_t * w_data( void * data_ptr, size_t nbytes )
{
	data_t * new_data  = c_data(nbytes);
// writing not implemented
	return 	new_data;
	
}



#endif
