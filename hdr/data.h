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
	pthread_mutex_t          lock;
	size_t                   size;
	uint8_t                  data[0];
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
data_t  * w_data(  void * data_ptr, size_t nbytes );
ll_t    * w_ll(    void * data_ptr, size_t nbytes );
queue_t * w_queue( void * data_ptr, size_t nbytes );

// print (assumed) ASCII Data
void p_data( data_t * data );

//########################
//# Function Definitions #
//########################

// Helpers

void mv_data( void * src, void * dst, size_t nbytes )
{
	size_t i;
	for ( i = 0; i < nbytes; i++)
	{
		((uint8_t *) src)[i] = ((uint8_t *) dst)[i];
	}
	return;
}



// Creators

queue_t * c_queue()
{
	queue_t * new_queue     = (queue_t *) malloc(sizeof(queue_t));

	pthread_mutex_init( &new_queue->consume_lock, NULL );
	pthread_mutex_init( &new_queue->push_lock,    NULL );

	return new_queue;

}

ll_t * c_ll()
{
	ll_t * new_ll = (ll_t *) malloc(sizeof(ll_t));

	pthread_mutex_init( &new_ll->lock, NULL );

	return new_ll;
}


data_t * c_data( size_t max_size )
{
	data_t * new_data = (data_t *) malloc(sizeof(data_t) + max_size);
	
	pthread_mutex_init( &new_data->lock, NULL );
	new_data->size    = max_size;

	return new_data;
}

// Writers

data_t * w_data( void * data_ptr, size_t nbytes )
{
	data_t * new_data  = c_data(nbytes);

	mv_data( data_ptr, new_data->data, nbytes);

	return 	new_data;
	
}

//Printers

void p_data( data_t * data)
{
	char *buffer = (char *) malloc(data->size + 1);
	
	pthread_mutex_lock( &data->lock );
	mv_data( data->data, buffer, data->size );
	pthread_mutex_unlock( &data->lock );	
	
	buffer[data->size] = '\0';
	printf("%s",buffer);

	return;
}


#endif
