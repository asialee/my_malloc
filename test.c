/*************************************************************************
	> File Name: test.c
	> Author: daijunkai
	> Mail: daijunkai@ncic.ac.cn
	> Created Time: 2015年03月27日 星期五 10时04分01秒
 ************************************************************************/

#include "mymalloc.h"


int main(int argc, char** argv)
{
	void *first, *second, *first_free_node;
	first = my_malloc(1000);
	printf("first %p, free_list_head:%p, %d, first_free_node:%p\n", first, free_list_head, *((int*)free_list_head), free_list_begin());
	int flag, size;
	size = *((int*)(first - 8));
	flag = *((int*)(first - 4));
	printf("first_space:%p, first space size:%d, first space flag:%d\n", first, size, flag);

	second = free_list_begin();
	size = *((int*)(second));
	flag = *((int*)(second + 4));
	printf("first free space:%p, first free space size:%d, first free space flag:%d\n", second, size, flag);


	second = my_malloc(1000);
	size = *((int*)(second - 8));
	flag = *((int*)(second - 4));
	printf("second_space:%p, second_space_size:%d, second_space_flag:%d\n", second, size, flag);

/*	second = free_list_begin();
	size = *((int*)(second));
	flag = *((int*)(second + 4));
	printf("first free space:%p, first free space size:%d, first free space flag:%d\n", second, size, flag);
*/	
	my_free(second);

	second = free_list_begin();
	size = *((int*)(second));
	flag = *((int*)(second + 4));
	printf("first free space:%p, first free space size:%d, first free space flag:%d\n", second, size, flag);


	second = free_list_next(second);
	size = *((int*)(second));
	flag = *((int*)(second + 4));
	printf("second free space:%p, second free space size:%d, second free space flag:%d\n", second, size, flag);
	
	coalesce_free_list();

	second = free_list_begin();
	size = *((int*)(second));
	flag = *((int*)(second + 4));
	printf("first free space:%p, first free space size:%d, first free space flag:%d\n", second, size, flag);


	second = my_malloc(10000);
	size = *((int*)(second - 8));
	flag = *((int*)(second - 4));
	printf("second_space:%p, second_space_size:%d, second_space_flag:%d\n", second, size, flag);

	size = 7;
	align8(size);
	printf("size:%d \n",size);
	size = 909;
	align8(size);
	printf("size:%d \n",size);
	return 0;
}

