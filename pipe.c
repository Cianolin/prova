#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main()
{
    int fd[2];
    int p, n;
    char buffer[BUFFER_SIZE];
     if(pipe(fd)==-1){
        printf("Errore nella creazione della pipe\n");
        exit(-1);
    }
    p=fork();
    
    if(p<0){
        printf("Errore genrazione\n");
    }
    if(p>0){
        printf("Sono il padre: il mio pid=%d,mio filgio ha pid=%d\n",getpid(),p);
        close(fd[0]);//padre chiude pipe in lettura
        const char* messaggio="Buona fortuna";//messaggio è un puntatore a caratteri
        if(write(fd[1],messaggio,strlen(messaggio))==-1){
            printf("Errore di scrittura della pipe");
            exit(-1);
        }
        close(fd[1]);
        wait();
    }
    else{
        printf("Sono il figlio:il mio pid=%d, mio padre=%d", getpid(),getppid());
        close(fd[1]);
        n=read(fd[0],buffer,BUFFER_SIZE);
        if(n==-1){
            printf("errore nella lettura dellam pipe");
            close(fd[0]);
            exit(-1);
        }
        else{
        buffer[n]='\0';
        }
        printf("Messaggio letto: %s", buffer);
        close(fd[0]);
         
    }
    return 0;
}
