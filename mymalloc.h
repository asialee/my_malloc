/*************************************************************************
	> File Name: mymalloc.h
	> Author: liyazhou
	> Mail: liyazhou@ncic.ac.cn
	> Created Time: 2015年03月27日 星期五 09时30分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>



#define SPACE_IN_USE 0
#define SPACE_AVAILABLE 1
#define MINIMUM_SBRK_SPACE	8192

#define align8(size)\
	size = (((size - 1)>>3)<<3) + 8
void* my_malloc(size_t size);
void my_free(void* ptr);
void* free_list_begin();
void* free_list_next(void *node);
void coalesce_free_list();

void* free_list_head;
