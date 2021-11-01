#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int printdir(char *s, int tabs);
int main(); 

int main() {
	printdir("./",0);
	return 0;
}
int printdir(char *s, int tabs) {
	DIR *dirp = opendir(s);
	struct dirent *p = readdir(dirp);
	while (p) {
		int tabsleft = tabs;
		while(tabsleft > 0) {
		tabsleft--;
			printf("\t");
		}
		if (p->d_type == 4 && (strlen(p->d_name) > 2 || (!(strcmp(p->d_name,"..")  || strcmp(p->d_name,"."))))) {
			printf("%s:\n",p->d_name);
			
		} else {
			printf("%s\n",p->d_name);
		}
		p = readdir(dirp);
	}
	closedir(dirp);
	
	return 0;
}