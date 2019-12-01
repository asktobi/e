#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>
#include <stdlib.h>


#define T_NULL 0
#define T_RAW  1
#define T_LL   2
#define T_DLL  3






struct DATA_HDR
{
	unsigned int     datatype;
	size_t           size;
	pthread_mutex_t  lock;
	char             data[0];
};

typedef DATA_HDR data_t;


void cp()


data_t * c_data( size_t data_max_size );
data_t * create_data( void * data_ptr, size_t nbytes );


data_t * create_data( void * data_ptr, size_t nbytes )
{
	data_t * new_hdr  = c_data(nbytes);
	
	&(new_hdr->data)

}


data_t * c_data( size_t max_size )
{
	data_t * new_hdr  = (data_t *) malloc(sizeof(data_t) + max_size);
	
	new_hdr->datatype = TYPE_NULL;
	new_hdr->size     = max_size;
	new_hdr->lock     = PTHREAD_MUTEX_INITIALIZER;

	return new_hdr;
}





#endif
