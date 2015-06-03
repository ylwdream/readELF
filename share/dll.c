/*
 * =====================================================================================
 *
 *       Filename:  dll.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/17/2015 01:25:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  WYL (502), ylwzzu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "stdio.h"
#include "dlfcn.h"

int main(int agrc, char *argv[])
{
	void *handle;
	double (*func)(double);
	char* error;

	handle = dlopen(argv[1], RTLD_NOW);
	if(handle == NULL)
	{
		printf("Open library %s error: %s\n", argv[1], dlerror());
		return -1;
	}

	func = dlsym(handle, "sin");

	if((error = dlerror()) != NULL)
	{
		printf("Symbol sin not found :%s\n", error);
		goto exit_runso;
	}

	printf("function addr: %08x %f \n", func, func(3.1415926 /2));
exit_runso:
	dlclose(handle);
}
