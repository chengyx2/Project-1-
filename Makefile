# yum install gcc-c++
sshell:     sshell.o     
          gcc -g  -o sshell sshell.o

sshell.o:   sshell.c
            gcc -g  -c -Wall -Werror sshell.c

cleanall:     
            rm -f sshell sshell.o
