#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int printdir(char *s);
int main(int argc, char *argv[]); 

int main(int argc, char *argv[]) {
  char dir[256];

  unsigned short i;
  for (i = 0; i < 256; i++) {dir[i] = '\0';}
  
  if (argc > 1) {strncpy(dir,argv[1],256-1);}
  i = 0;
  while (printdir(dir) == -1) {
    if (i) {
      printf("%s: %s\n",dir,strerror(errno));
    }
    printf("Please enter a directory name: ");
    fgets(dir,255,stdin);
    dir[255] = '\0';
    char *newline = strrchr(dir,'\n');
    if (newline != NULL) {*newline = '\0';}
    i = 1;
  }
  return 0;
}
int printdir(char *s) {
  DIR *dirp = opendir(s);
  if (dirp == NULL) {return -1;}
  struct stat stp;
  long unsigned int total_size = 0;
	
  printf("Stats for directory %s\n",s);
  printf("\nDirectories:\n\n");
  struct dirent *p = readdir(dirp);
  while (p) {
    if (p->d_type == 4) {
      stat(p->d_name,&stp);
      printf("%ho %ld %s\n",stp.st_mode % 01000,stp.st_size,p->d_name);
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
      printf("%ho %ld %s\n",stp.st_mode % 01000,stp.st_size,p->d_name);
      total_size += stp.st_size;
    }
    p = readdir(dirp);
  }
  closedir(dirp);
  printf("\nTotal Size: %lu\n",total_size);
  return total_size;
}
