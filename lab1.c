#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

#define READ_BUF_SIZE 512
#define READ_PPID 6

int spawn(char* program, char** arg_list)
{
    pid_t child_pid;
    
    child_pid = fork();
    
    if (child_pid != 0) { return child_pid; }
    else
    {
        execvp(program, arg_list);
        fprintf(stderr, "an error occured in execvp\n");
        abort();
    }
}

void get_pid_and_ppid(const char* pname)
{
    char filename_status[READ_BUF_SIZE];
    char buffer[READ_BUF_SIZE];
    char name[READ_BUF_SIZE];
    char ppid[READ_PPID];

    FILE* status;

    DIR *dir;
    struct dirent *next;    

    dir = opendir("/proc");
    if (!dir)
    {
        perror("Cannot open /proc");
        exit(-1);
    }

    printf("Name: %s\t", pname);

    while ((next = readdir(dir)) != NULL)
    {
        if (strcmp(next -> d_name, "..") == 0) { continue; }
        if (!isdigit(*next -> d_name)) { continue; }

        sprintf(filename_status, "/proc/%s/status", next -> d_name);
        status = fopen(filename_status, "r");

        fgets(buffer, READ_BUF_SIZE - 1, status);
        sscanf(buffer, "%*s %s", name);        

        if (strcmp(pname, name) != 0) { continue; }
        else
        {            
            printf("PID: %s\t", next -> d_name);
            
            while (fgets(buffer, READ_BUF_SIZE - 1, status) != NULL)
            {
                if (strstr(buffer, "PPid") != NULL)
                {
                    sscanf(buffer, "%*s %s", name);
                    sscanf(buffer, "%*s %s", ppid);
                    printf("PPID: %s\t", name);
                    break;
                }
            }
        }
    }
    fclose(status);

    sprintf(filename_status, "/proc/%s/status", ppid);
    status = fopen(filename_status, "r");

    fgets(buffer, READ_BUF_SIZE - 1, status);
    sscanf(buffer, "%*s %s", name); 
    printf("Name of parent process: %s", name);
    printf("\n");
}

int main()
{        

    char* arg_list2[] = {"atom", NULL};    
    spawn("atom", arg_list2);  
    get_pid_and_ppid("atom");
    
    char* arg_list3[] = {"emacs", NULL};    
    spawn("emacs", arg_list3);
    get_pid_and_ppid("emacs");    
    
    printf("\ndone with main program\n");    
    return 0;
}
