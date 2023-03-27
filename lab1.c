#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char* program, char** arg_list)
{
    pid_t child_pid;
    
    child_pid = fork();
    
    if (child_pid != 0)
    {
        return child_pid;
    }
    else
    {
        execvp(program, arg_list);
        fprintf(stderr, "an error occured in execvp\n");
        abort();
    }
}

int main()
{
    char* arg_list1[] = {"shotwell", NULL};    
    spawn("shotwell", arg_list1);  
     
    char* arg_list2[] = {"atom", NULL};    
    spawn("atom", arg_list2);  
    
    char* arg_list3[] = {"emacs", NULL};    
    spawn("emacs", arg_list3); 
     
    char* arg_list4[] = {"gnome-calculator", NULL};    
    spawn("gnome-calculator", arg_list4);   
    
    printf("done with main program\n");    
    return 0;
}
