#include <stdio.h>
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
	struct stat stp;
	unsigned int total_size = 0;
	
	printf("Stats for directory %s\n",s);
	printf("\nDirectories:\n\n");
	struct dirent *p = readdir(dirp);
	while (p) {
		if (p->d_type == 4) {
		stat(p->d_name,&stp);
		printf("%ho %s\n",stp.st_mode % 01000,p->d_name);
		total_size += stp.st_size;
		}
		p = readdir(dirp);
	}
	rewinddir(dirp);
	p = readdir(dirp);
	printf("\nFiles:\n\n");
	while (p) {
		if (p->d_type == 8) {
		stat(p->d_name,&stp);
		printf("%ho %d %s\n",stp.st_mode % 01000,stp.st_size,p->d_name);
		total_size += stp.st_size;
		}
		p = readdir(dirp);
	}
	closedir(dirp);
	printf("\nTotal Size: %u\n",total_size);
	return total_size;
}
