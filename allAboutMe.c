
//about me
//============
//unix user
//name
//unix group
//unix home
//home permission
//login shell
//print date and fine age
//other userids sharing last char

//about machine
//============
//host
//system

/* Author: Dave Hoatlin
   Class:  CIS 452
   Due:    Jan. 27 2011 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

void getUserInfo();
void getEntInfo();
void getPermissions(char* premissions, int mode);

int main()
{
	//printf("explicite user selection\n");	
	printf("\nAbout Me\n");
	printf("========\n\n");	
	getUserInfo();

	//printf("user selection via getpwent\n");
	//getEntInfo();
	return 0;
}

void getUserInfo()
{
	struct passwd *pw;
	struct group *gr;
	struct stat st;

	char *user;
	char permissions[8];

	user = getenv("USER");
	
	pw = getpwnam(user);
	gr = getgrgid(pw->pw_gid);
	stat(pw->pw_dir, &st);

	getPermissions(permissions, st.st_mode);

	printf("Unix User       : %s (%d)\n", pw->pw_name, pw->pw_uid);
	printf("Name            : %s\n", pw->pw_gecos);
	printf("Unix Group      : %s (%d)\n", gr->gr_name, gr->gr_gid);
	printf("Unix Home       : %s\n", pw->pw_dir);
	printf("Home Permission : %s\n", permissions);
	printf("Login Shell     : %s\n", pw->pw_shell);
}

void getPermissions(char* permissions, int mode)
{
	//currently this is the best way i can think of doing this

	//read write execute for user	
	if(mode & S_IRUSR){
		strcat(permissions, "r");
	}
	else{
		strcat(permissions, "-");
	}
	if(mode & S_IWUSR){
		strcat(permissions, "w");
	}
	else{
		strcat(permissions, "-");
	}
	if(mode & S_IXUSR){
		strcat(permissions, "x");
	}
	else{
		strcat(permissions, "-");
	}

	//read write execute for group
	if(mode & S_IRGRP){
		strcat(permissions, "r");
	}
	else{
		strcat(permissions, "-");
	}
	if(mode & S_IWGRP){
		strcat(permissions, "w");
	}
	else{
		strcat(permissions, "-");
	}
	if(mode & S_IXGRP){
		strcat(permissions, "x");
	}
	else{
		strcat(permissions, "-");
	}

	//read write execute for others
	if(mode & S_IROTH){
		strcat(permissions, "r");
	}
	else{
		strcat(permissions, "-");
	}
	if(mode & S_IWOTH){
		strcat(permissions, "w");
	}
	else{
		strcat(permissions, "-");
	}
	if(mode & S_IXOTH){
		strcat(permissions, "x");
	}
	else{
		strcat(permissions, "-");
	}
}


//this is starting with root. probably cycles through all users
//will need for showing sharing end char.
void getEntInfo()
{
	struct passwd *pw;

	pw = getpwent();

	printf("Unix User: %s (%d)\n", pw->pw_name, pw->pw_uid);
}

