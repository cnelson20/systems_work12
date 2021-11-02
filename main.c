#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>

int printdir(char *s, int tabs);
int main(); 

int main() {
	printdir("./",1);
	return 0;
}
int printdir(char *s, int tabs) {
	DIR *dirp = opendir(s);
	struct dirent *p = readdir(dirp);
	struct stat *stp;
	int total_size = 0;
	printf("\nFiles:\n\n");
	while (p) {
		if (p->d_type == 8) {
			stat(p->d_name,stp);
			char *t = ctime(&stp->st_mtime);
			*(strchr(t,'\n')) = '\0';
			printf("%ho %d %s\t%s\n",stp->st_mode % 01000,stp->st_size,t,p->d_name);
			total_size += stp->st_size;
		}
		p = readdir(dirp);
	}
	closedir(dirp);
	dirp = opendir(s);
	p = readdir(dirp);
	printf("\nDirectories:\n\n");
	while (p) {
		if (p->d_type == 4) {
			stat(p->d_name,stp);
			char *t = ctime(&stp->st_mtime);
			printf("%hho %d %s %s\n",stp->st_mode,stp->st_size,ctime(&stp->st_mtime),p->d_name);
			total_size += stp->st_size;
		}
		p = readdir(dirp);
	}
	closedir(dirp);
	printf("\nTotal Size: %d\n",total_size);
	return 0;
}