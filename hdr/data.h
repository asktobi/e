#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

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
	char                     data[0];
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

// initalize Datatypes
data_t * i_data( void * data_ptr, size_t nbytes );

// write to Datatypes
data_t * w_data( void * src, data_t * dst, size_t nbytes );

// print (assumed) ASCII Data
void p_data( data_t * data );

//########################
//# Function Definitions #
//########################

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

// Initalizers

data_t * i_data( void * src, size_t n )
{
	data_t * new_data  = c_data( n );

	memcpy( &new_data->data, src, n );

	return 	new_data;
	
}

//Writers

data_t * w_data( void * src, data_t * dst, size_t n )
{
	if ( dst->size < n )
		return NULL;
	
	memcpy( &dst->data, src, n );

	return dst;
}

//Printers

void p_data( data_t * src )
{
	char *buffer = (char *) malloc(src->size + 1);
	
	pthread_mutex_lock( &src->lock );
	memcpy( buffer, &src->data, src->size );
	pthread_mutex_unlock( &src->lock );	
	
	buffer[src->size] = '\0';
	printf("(%p)->data = \"%s\"", src, buffer);

	return;
}

void info_data( data_t * src )
{
	pthread_mutex_lock( &src->lock );
	printf("data_t (%p)->lock = %d\n", src, 1 /*pthread_mutex_trylock(&data->lock)*/ );
	printf("       (%p)->size = %d\n", &src->size, (int) src->size);
	printf("       (%p)->data = %s\n", &src->data, src->data);
	pthread_mutex_unlock( &src->lock );
}




#endif
