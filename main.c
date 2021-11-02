#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>

int printdir(char *s);
int main(); 

int main() {
	printdir("./");
	return 0;
}
int printdir(char *s) {
	DIR *dirp = opendir(s);
	struct stat *stp;
	unsigned int total_size = 0;
	
	printf("\nFiles:\n\n");
	
	struct dirent *p = readdir(dirp);
	while (p) {
		if (p->d_type == 8) {
			stat(p->d_name,stp);
			printf("%ho %u %s\n",0,0,p->d_name);
			//total_size += stp->st_size;
		}
		p = readdir(dirp);
	}
	closedir(dirp);
	printf("\nDirectories:\n\n");
	printf("\nTotal Size: %u\n",total_size);
	return 0;
}
