/* Author: Dave Hoatlin
   Class:  CIS 452
   Due:    Jan. 27 2011 

	This program prints out information about the user and the machine they are on.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <time.h>


void getInfo();
void printOthers(char lastChar);
void getPermissions(char *premissions, int mode);
void findAge();

int main()
{
    getInfo();
    return 0;
}

//This method prints out most of the information about the user
void getInfo()
{
    //structs we will be using
    struct passwd *pw;
    struct group *gr;
    struct stat st;
    struct hostent *ht;
    struct utsname un;

    //variables we will need
    char *user;
    char permissions[11];
    char hostname[1024];
    user = getenv("USER");
    char lastChar = user[strlen(user) - 1];

    //generating the structs
    pw = getpwnam(user);
    gr = getgrgid(pw->pw_gid);
    uname(&un);
    stat(pw->pw_dir, &st);
    gethostname(hostname, 1024);

    //finding the permissions for the user's home
    getPermissions(permissions, st.st_mode);

    //printing out the user's information
    printf("\nAbout Me\n");
    printf("========\n\n");

    printf("Unix User       : %s (%d)\n", pw->pw_name, pw->pw_uid);
    printf("Name            : %s\n", pw->pw_gecos);
    printf("Unix Group      : %s (%d)\n", gr->gr_name, gr->gr_gid);
    printf("Unix Home       : %s\n", pw->pw_dir);
    printf("Home Permission : %s\n", permissions);
    printf("Login Shell     : %s\n", pw->pw_shell);

    //finding the age of the user
    findAge();

    //finding the users that share the same last character
    printf("\nOther users that end with '%c':\n	", lastChar);
    printOthers(lastChar);

    //printing out information about the machine
    printf("\nAbout My Machine\n");
    printf("================\n\n");
    printf("host            : %s\n", hostname);
    printf("System          : %s %s\n", un.sysname, un.release);
}

//This method finds all the other users that share the same last character
//lastChar is the char we want to compare with the other users
void printOthers(char lastChar)
{
    struct passwd *pw;

    //infinite loop that quits once all users have been searched
    while (1) {
        pw = getpwent();

        //if pw contains information
        if (pw != NULL) {
            //compare last chars. if match then print out user's name                       
            char compareChar = pw->pw_name[strlen(pw->pw_name) - 1];
            if (compareChar == lastChar) {
                printf("%s ", pw->pw_name);
            }
        }
        //break when pw is null
        else {
            break;
        }
    }
    printf("\n");
}

//find the age of the user
void findAge()
{
    struct tm *tm;
    time_t now;
    char currentDate[100];
    int years;
    int months;
    int days;

    now = time(NULL);
    //putting current time in struct
    tm = localtime(&now);

    //find age in years
    years = tm->tm_year - 62;
    //find age in months    
    months = tm->tm_mon + 4;    //adding four for the remaining four months of the previous year.
    //find age in days
    days = tm->tm_mday - 1;     //subtracting 1 day because born on 

    //adjust years if before september
    if (tm->tm_mon < 9) {
        years--;
    }
    //adjust months if after september
    else {
        months = tm->tm_mon - 9;
    }

    //format and print out string
    strftime(currentDate, sizeof(currentDate), "On %Y-%b-%d,", tm);
    printf("%s I am %d years %d months %d days old\n", currentDate, years,
           months, days);
}

//get the permissions of the home directory
//*permissions is a char array that the string will be placed in
//mode is the permissions to decode
void getPermissions(char *permissions, int mode)
{
    permissions[0] = 'd';
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';

    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';

    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';

    permissions[10] = '\0';
}
