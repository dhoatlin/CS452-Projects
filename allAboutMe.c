/* Author: Dave Hoatlin
   Class:  CIS 452
   Due:    Jan. 27 2011 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/utsname.h>


void getInfo();
void printOthers(char lastChar, char** members);
void getPermissions(char* premissions, int mode);

int main()
{
	//printf("explicite user selection\n");	

	getInfo();
	//printf("user selection via getpwent\n");
	//getEntInfo();
	return 0;
}

void getInfo()
{
	struct passwd *pw;
	struct group *gr;
	struct stat st;
	struct hostent *ht;
	struct utsname un;

	char *user;
	char permissions[9];
	char hostname[1024];

	user = getenv("USER");
	char lastChar = user[strlen(user) - 1];
	
	pw = getpwnam(user);
	gr = getgrgid(pw->pw_gid);
	uname(&un);
	stat(pw->pw_dir, &st);
	gethostname(hostname, 1024);

	getPermissions(permissions, st.st_mode);

	printf("\nAbout Me\n");
	printf("========\n\n");	

	printf("Unix User       : %s (%d)\n", pw->pw_name, pw->pw_uid);
	printf("Name            : %s\n", pw->pw_gecos);
	printf("Unix Group      : %s (%d)\n", gr->gr_name, gr->gr_gid);
	printf("Unix Home       : %s\n", pw->pw_dir);
	printf("Home Permission : %s\n", permissions);
	printf("Login Shell     : %s\n", pw->pw_shell);

	printf("\nOther users that end with '%c':\n	", lastChar);
	printOthers(lastChar, gr->gr_mem);

	printf("\nAbout My Machine\n");
	printf("================\n\n");
	printf("host            : %s\n", hostname);
	printf("System          : %s %s\n", un.sysname, un.release);
}

void printOthers(char lastChar, char** members)
{
	int i = 0;
	int i2 = 0;

	printf("inside the function at least");
	while(1)
	{
		if(members != NULL)
		{			
			printf("found user");
		}
		else
		{
			break;
		}
		i++;
	}
}

void getPermissions(char* permissions, int mode)
{
	//currently this is the best way i can think of doing this
	permissions[0] = (mode & S_IRUSR) ? 'r' : '-';
	permissions[1] = (mode & S_IWUSR) ? 'w' : '-';
	permissions[2] = (mode & S_IXUSR) ? 'x' : '-';
	
	permissions[3] = (mode & S_IRGRP) ? 'r' : '-';
	permissions[4] = (mode & S_IWGRP) ? 'w' : '-';
	permissions[5] = (mode & S_IXGRP) ? 'x' : '-';

	permissions[6] = (mode & S_IROTH) ? 'r' : '-';
	permissions[7] = (mode & S_IWOTH) ? 'w' : '-';
	permissions[8] = (mode & S_IXOTH) ? 'x' : '-';

	permissions[9] = '\0';
}

