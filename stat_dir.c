// stat_dir.c

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


struct dirent *dp;
struct stat statbuf;
struct passwd *pwd;
struct group *grp;
struct tm *tm;
char datestring[256];
DIR *dir;
char path[500];
char pathfile[500];

// Muestra atributos de archivo
char const * sperm( mode_t mode ) {
static char local_buff[16] = {0};
int i = 0;
//if is dir
if ((mode & S_IFDIR) == S_IFDIR) local_buff[i] = 'd';
else local_buff[i] = '-';
i++;
// user permissions
if ((mode & S_IRUSR) == S_IRUSR) local_buff[i] = 'r';
else local_buff[i] = '-';
i++;
if ((mode & S_IWUSR) == S_IWUSR) local_buff[i] = 'w';
else local_buff[i] = '-';
i++;
if ((mode & S_IXUSR) == S_IXUSR) local_buff[i] = 'x';
else local_buff[i] = '-';
i++;
// group permissions
if ((mode & S_IRGRP) == S_IRGRP) local_buff[i] = 'r';
else local_buff[i] = '-';
i++;
if ((mode & S_IWGRP) == S_IWGRP) local_buff[i] = 'w';
else local_buff[i] = '-';
i++;
if ((mode & S_IXGRP) == S_IXGRP) local_buff[i] = 'x';
else local_buff[i] = '-';
i++;
// other permissions
if ((mode & S_IROTH) == S_IROTH) local_buff[i] = 'r';
else local_buff[i] = '-';
i++;
if ((mode & S_IWOTH) == S_IWOTH) local_buff[i] = 'w';
else local_buff[i] = '-';
i++;
if ((mode & S_IXOTH) == S_IXOTH) local_buff[i] = 'x';
else local_buff[i] = '-';
return local_buff;
}


int main(int argc, char *argv[])
{


if (argc<2)
return -1;

strcpy(path, argv[1]);

printf("Ruta: %s\n", path );

if ((dir = opendir(path)) == NULL) {
printf("no se pudo abrir %s",path);
return -1;
}

/* Loop through directory entries. */
while ((dp = readdir(dir)) != NULL) {

/* Build file path*/
strcpy(pathfile, path);
strcat(pathfile, "/");
strcat(pathfile, dp->d_name );

/* Get entry's information. */
if (stat(pathfile, &statbuf) == -1)
continue;

// if (dp->d_type!=DT_REG) 
// continue;

/* Print out type, permissions, and number of links. */
printf("%10.10s", sperm (statbuf.st_mode));
printf("%4d", statbuf.st_nlink);


/* Print out owner's name if it is found using getpwuid(). */
if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
printf(" %-8.8s", pwd->pw_name);
else
printf(" %-8d", statbuf.st_uid);


/* Print out group name if it is found using getgrgid(). */
if ((grp = getgrgid(statbuf.st_gid)) != NULL)
printf(" %-8.8s", grp->gr_name);
else
printf(" %-8d", statbuf.st_gid);


/* Print size of file. */
printf(" %9jd", (intmax_t)statbuf.st_size);


tm = localtime(&statbuf.st_mtime);


/* Get localized date string. */
strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);


printf(" %s %s\n", datestring, dp->d_name);
}

return 0;
}

