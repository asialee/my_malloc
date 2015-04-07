/*************************************************************************
	> File Name: mymalloc.c > Author: Liyazhou
	> Mail: Liyazhou@ncic.ac.cn
	> Created Time: 2015年03月25日 星期三 19时58分26秒
 ************************************************************************/

#include "mymalloc.h"


void* free_list_begin()
{
	//if the head is null
	if(!free_list_head)
	{
		return NULL;
	}
	else
	{
		void* tmp = free_list_head;
		while(tmp != (void*)sbrk(0))
		{
			int* size = (int*)tmp;
			int* flag = (int*)(tmp+4);//the flag to indicate whether this space is in use
			if(*flag == SPACE_AVAILABLE)
			{
				return tmp;
			}
			else
			{
				tmp += *size;
			}
		}
		return NULL;
	}
}

void* free_list_next(void *node)
{
	if(!free_list_head || !node)
	{
		return NULL;
	}

	if(node < free_list_head || node > sbrk(0))
	{
		printf("illeagal address\n");
		return NULL;
	}
	int flag = 0;
	void *tmp = free_list_head;
	while(tmp < sbrk(0))
	{
		int* size = (int*)tmp;
		if(tmp == node)
		{
			tmp += *size;
			break;
		}
		tmp += *size;

	}
	if(tmp == sbrk(0))
	{
		return NULL;
	}
	while(tmp < sbrk(0))
	{
		int* size = (int*)tmp;
		int* flag = (int*)(tmp+4);
		if((*flag) == SPACE_AVAILABLE)
		{
			return tmp;
		}
		tmp += (*size);
	}
	return NULL;
}

void*  my_malloc_new(size_t size)
{
	size_t new_size = size;
	align8(new_size);
	new_size += 8;
	if(new_size >=  MINIMUM_SBRK_SPACE)
	{
		void* res = sbrk(new_size);
		if((void*)-1 == res)
		{
			printf("error occured when allocation space\n");
			return NULL;
		}
		*((int*)res) = new_size;
		*((int*)(res + 4)) = SPACE_IN_USE;
		return res;
	}
	else
	{
		size_t gap = MINIMUM_SBRK_SPACE - new_size;
		align8(gap);
		gap+=8;
		void* res = sbrk(gap + new_size);
		if((void*)-1 == res)
		{
			printf("error occured when allocating space\n");
			return NULL;
		}
		*((int*)res) = new_size;
		*((int*)(res + 4)) = SPACE_IN_USE;

		res += new_size;
		*((int*)res) = gap;
		*((int*)(res + 4)) = SPACE_AVAILABLE;
		res -= new_size;
		return res;
	}


}

void* my_malloc(size_t size)
{
	//create a new node
	if(NULL == free_list_begin())
	{
		void* res = my_malloc_new(size);
		free_list_head = res;
		return res + 8;
	}
	else
	{
		void* tmp = free_list_begin();
		
		size_t new_size = size; 
		align8(new_size);
		new_size += 8;
		

		while(tmp != NULL)
		{
			int cur_size = *((int*)tmp);
			if(cur_size >= new_size)
			{
				if(cur_size >= new_size + 12)
				{
					*((int*)tmp) = new_size;
					*((int*)(tmp + 4)) = SPACE_IN_USE;

					void* new_tmp = tmp + new_size;
					*((int*)(new_tmp)) = cur_size - new_size;
					*((int*)(new_tmp + 4)) = SPACE_AVAILABLE;
				}
				else
				{
					*((int*)(tmp + 4)) = SPACE_IN_USE;
				}
				
				return tmp + 8;
			}
			tmp = free_list_next(tmp);
		}
		
		void* res = my_malloc_new(size);
		return res + 8;
	}
}

void my_free(void *ptr)
{
	if(ptr < free_list_head || sbrk(0) < ptr)
	{
		printf("illegal pointer\n");
		return;
	}
	printf("free ptr:%p\n", ptr);
	int* flag = (int*)(ptr - 4);
	*flag = SPACE_AVAILABLE;
	return;
}

void coalesce_free_list()
{
	void *first, *second, *tail;
	first = free_list_begin();
	int tmp_size = *((int*)first);
	int size = tmp_size;
	second = first + tmp_size;
	tail = sbrk(0);

	while(second < tail && first < tail)
	{
		while(second < tail && *((int*)(second + 4)) == SPACE_AVAILABLE )
		{
			tmp_size = *((int*)second);
			size += tmp_size;
			second += tmp_size;
		}
		*((int*)first) = size;
		first = second;
		while(first < tail && *((int*)(first + 4)) == SPACE_IN_USE )
		{
			first += *((int*)first);
		}
		if(first == tail)
		{
			return;
		}
		else
		{
			size = *((int*)first);
			second = first + size;
		}
	}
	return;
}

