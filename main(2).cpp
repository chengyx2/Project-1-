
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define CMDLINE_MAX 512

struct Command{
  char *argv[CMDLINE_MAX];
  char cmd[CMDLINE_MAX];

};

int Parse(struct Command *s){

  int i = 0;
  char delimiter[] = " >|";
  char *symbol = strtok(s->cmd,delimiter);
  while(symbol!=NULL){
    s->argv[i] = symbol;
    symbol = strtok(NULL,delimiter);
    i ++;
  }
  return 0;
}

void reDirection(struct Command *s){
  int i =0;
  while(s->argv[i]!=NULL) {
    if (strcmp(s->argv[i],">")==0) {
      int fd = open(s->argv[i+1], O_WRONLY | O_CREAT, 0644);
      dup2(fd, 1);
      close(fd);
      break;
    } i++;
  }

}

int sytm(struct Command *s){
  int status;
  pid_t pid;
  pid = fork();
  if (pid == 0) {
/* Child */
    execvp(s->argv[0],s->argv);
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
  //fprintf(stderr,s->argv[0]);
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


    /* Print command line if stdin is not provided by terminal */
    if (!isatty(STDIN_FILENO)) {
      printf("%s", cmd);
      fflush(stdout);
    }

    strcpy(s.cmd,cmd);

    Parse(&s);

    /*Check whether the command line include redirection*/
    if (strchr(cmd, '>') != NULL) {
      reDirection(&s);
    }




    /* Remove trailing newline from command line */
    nl = strchr(cmd, '\n');
    if (nl)
      *nl = '\0';

    /* Builtin command */
    if (strcmp(s.argv[0], "exit")==0) {
      fprintf(stderr, "Bye...\n");
      exit(0);
    }
    /* Builtin command */
    else if (strcmp(s.argv[0], "cd")==0) {
      chdir(s.argv[1]);
    }
    /* Builtin command */
    else if (strcmp(s.argv[0], "pwd")==0) {
      //fprintf(stderr, getcwd(s.argv[1], size));

      /* Regular command */
      retval = system(cmd);
      fprintf(stdout, "Return status value for '%s': %d\n",
              cmd, retval);

    }
    else {
      sytm(&s);
    }
  }

}


int buildin(struct Command *s){
 //pwd
  if (!strcmp(s->argv[0], "pwd")) {

  }

 //cd
  if (!strcmp(s->argv[0], "cd")) {}
 //exit
  if (!strcmp(s->argv[0], "exit")) {
    fprintf(stderr,"bye...\n");

  }
  return 0;

}



/*int parsing(char *cmd, struct Command *s){
  char *tem = malloc(CMDLmake INE_MAX);
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
