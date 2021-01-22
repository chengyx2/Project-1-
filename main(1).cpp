
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define CMDLINE_MAX 512

struct Command{
  int argc;
  char *argv[];

};

int Parse(char *cmd, struct Command *s){
  int i = 0;
  char delimiter[] = " >|";
  char*symbol = strtok(cmd,delimiter);
  while(symbol!=NULL){
    s.argv[i] = symbol;
    symbol = strtok(NULL,delimiter);
    i ++;
  }
  return 0;
}
int parsing(char *cmd, struct Command *s){
  char *tem = malloc(CMDLINE_MAX);
  strcpy(tem,cmd);
  int i = 0;
  s.argv[0] = strtok(tem," |>");
  while(s.argv[i]!=NULL){
    s.argv[i+1]=strtok(NULL," ");
    i = i+1;
  }
  s.argv[i+1] = NULL;
}
void reDirection(struct Command *s){
  int fd;

  fd = open (s.argv[0],O_WRONLY|O_CREAT,0644);
  dup2(fd,1);
  close(fd);
}

int sytm(struct Command *s){
  pid_t pid;
  pid = fork();
  int status
  if (pid == 0) {
/* Child */
    execvp(s.argv[0],s.argv);
    perror("execvp");
    exit(1);
  }  else if (pid > 0) {
/* Parent */
    waitpid(pid,&status,0);
    WEXITSTATUS(status);
  } else {
    perror("fork");
    exit(1);
  }
  fprintf(stderr,s.argv);
  return 0;
}

int main(void) {
  char cmd[CMDLINE_MAX];

  while (1) {
    struct Command s;
    char* nl;
    int retval;

    /* Print prompt */
    printf("sshell$ ");
    fflush(stdout);
    /* Get command line */
    fgets(cmd, CMDLINE_MAX, stdin);


   

    //Parse(cmd,&s);
    parsing(cmd,&s);

    /* Print command line if stdin is not provided by terminal */
    if (!isatty(STDIN_FILENO)) {
      printf("%s", cmd);
      fflush(stdout);
    }

    /*Check whether the command line include redirection*/
    if (strchr(cmd, '>') != NULL) {
      reDirection(&s);
    }


    sytm(cmd);

    /* Remove trailing newline from command line */
    nl = strchr(cmd, '\n');
    if (nl)
      *nl = '\0';

    /* Builtin command */
    if (!strcmp(s.argv[0], "exit")) {
      fprintf(stderr, "Bye...\n");
      fprintf( % 0);
      break;
    }
    /* Builtin command */
    if (!strcmp(s.argv[0], "cd")) {
      chdir(s.argv[1]);
    }
    /* Builtin command */
    if (!strcmp(s.argv[0], "pwd")) {
      fprintf(stderr, getcwd(, sizeof(buf)));

      /* Regular command */
      retval = system(cmd);
      fprintf(stdout, "Return status value for '%s': %d\n",
              cmd, retval);
    }

    return EXIT_SUCCESS;
  }
}






/*int parsing(char *cmd, struct Command *s){
  char *tem = malloc(CMDLINE_MAX);
  char *word;
  strcpy(tem,cmd);
  int i = 0;
  s->argv[0] = strtok(tem," |>");
  while(s->argv[i]!=NULL){
    s->argv[i+1]=strtok(NULL," ");
    i = i+1;
  }
  s->argv[i+1] = NULL;
}*/

  /*void redirection(char*argv[]){
    int fd ;
    fd = open("file.txt",O_WRONLY);
    dup2(fd,STDOUT_FILENO)£ª
        close(fd);
    sytm(argv);

  }*/
