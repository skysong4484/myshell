#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



#define MAX_LEN_LINE    10
#define LEN_HOSTNAME   30


int main(void)
{
    char command[MAX_LEN_LINE];
    char *args[] = {command, NULL};
    int ret, status;
    pid_t pid, cpid;
  
    while (true) {
        char *s;
        char s_full[10][30];
        int len;
        int count_program=0; //입력받은 프로그램의 수;

        s = fgets(command, MAX_LEN_LINE, stdin);
        len = strlen(command);


        printf("다수의 프로그램을 실행하려면 a; b; c의 형식으로 입력하시오 \n");
        printf(" 종료를 하려면 exit를 입력하시오\n")

    //username@hostname $
        char hostname[LEN_HOSTNAME + 1];
        memset(hostname, 0x00, sizeof(hostname));
        gethostname(hostname, LEN_HOSTNAME);
            
        printf("username: %s\n", getpwuid(getuid())->pw_name );
        printf("hostname: " %s\n, hostname);


        //exit
        if(strcmp(s,"exit\n") == 0)
        {
            printf("Shell을 종료합니다. \n");
            break;
        }
         
        // a;b;c 프로그램 순차적 실행 

       for(int i =0;i<len;i++)
       {
          if( s[i] == ';')
           count_program++;
       }
        printf("%d 개의 프로그램이 순차적으로 실행됩니다.",count_program+1);

        count_program =0; 

        char *ptr = strtok(s,"; ");
        while(ptr != NULL)
        {
            printf("  %s \n" ,ptr);
            strcpy(s_full[count_program],ptr);
            count_program++;
            ptr = strtok(NULL,"; ");
        }
       

for(int i=0;i<count_program;i++)
{
    s = s_full[i];
    strcpy(command,s);
    
        
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
       

    len =strlen(command);
        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        
        printf("[%s]\n", command);
      
     

        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */
            ret = execve(args[0], args, NULL);
            if (ret < 0) {
                fprintf(stderr, "execve failed\n");   
                return 1;
            }
        } 
}
    
    }
    return 0;
}





