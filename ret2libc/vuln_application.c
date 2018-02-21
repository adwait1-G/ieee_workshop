#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void func(char *buffer);

int main(int argc , char **argv) {

	setuid(0);
	seteuid(0);
	setegid(0);

	int newgrp = 0;

	setgroups(1 , &newgrp);

	char *ptr = argv[0];
        int i = 1;
        while(1) {
                if(strcmp(ptr + i , "/bin/bash") == 0)
                        break;
                else
                        i++;
        }
        printf("Address of /bin/bash = %p , offset from argv[0] = %d\n" , ptr+i , i);

	printf("system = %p , exit = %p\n" , system , exit);

	func(argv[1]);
	return 0;
}

void func(char *buffer) {
	char copybuffer[50];
	strcpy(copybuffer , buffer);
	printf("%s\n" , copybuffer);

}
