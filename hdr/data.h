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
	pthread_rwlock_t          lock;
	// keeps track of links to this
	// if 0 it can be modified; if != 0 treat as constant
	unsigned int             links; 

	size_t                   size;
	char                     data[0];
};

//#####################
//# Type Declarations #
//#####################

typedef struct DATA_HDR         data_t;

//#########################
//# Function Declarations #
//#########################

data_t * c_data(     size_t   data_size );
data_t * init_data(  void   * data_ptr, size_t n );
void     link_data(  data_t * ptr );
void     print_data( data_t * data ); // print (assumed) ASCII Data
void     info_data(  data_t * data );

//########################
//# Function Definitions #
//########################


data_t * c_data( size_t data_size )
{
	data_t * new_data = (data_t *) malloc(sizeof(data_t) + data_size);
	
	pthread_rwlock_init( &new_data->lock, NULL );
	new_data->links = 0;
	new_data->size  = data_size;

	return new_data;
}


void link_data( data_t * ptr)
{
	pthread_rwlock_wrlock( &ptr->lock );
	ptr->links++;
	pthread_rwlock_unlock( &ptr->lock );

	return;
}


data_t * init_data( void * src, size_t n )
{
	data_t * new_data = c_data( n );

	memcpy( &new_data->data, src, n );

	return 	new_data;
}


void free_data( data_t * ptr)
{
	pthread_rwlock_wrlock(&ptr->lock);
	if (ptr->links != 0)
	{	
		ptr->links--;
		pthread_rwlock_unlock(&ptr->lock);
		return;
	}
	pthread_rwlock_destroy(&ptr->lock);
	free(ptr);
}


void p_data( data_t * src )
{
	char *buffer = (char *) malloc(src->size + 1);
	
	pthread_rwlock_rdlock( &src->lock );
	memcpy( buffer, &src->data, src->size );
	pthread_rwlock_unlock( &src->lock );	
	
	buffer[src->size] = '\0';
	printf("(%p)->data = \"%s\"\n", src, buffer );

	return;
}

void info_data( data_t * src )
{
	pthread_rwlock_rdlock( &src->lock );
	printf("data_t (%p)->mutex\n"           , src );
	printf("       (%p)->links = %d\n", &src->links, src->links);
	printf("       (%p)->size  = %d\n", &src->size,  (int) src->size);
	printf("       (%p)->data  = %s\n", &src->data,  src->data);
	pthread_rwlock_unlock( &src->lock );
}




#endif
