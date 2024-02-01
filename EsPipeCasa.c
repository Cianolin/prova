#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define n 5
int main(int argc, char *argv[])
{
    int p;
    int fd[2]; 
    int arreyN[n];
    int moltiplicatore;
    int status;

    if (pipe(fd) == -1)//errore nella crezione della pipe restituisce -1
    {
        printf("errore creazione pipe\n");
        exit(-1);
    }
    p = fork();
    if (p < 0)
    {
        printf("errore generazione figlio\n");
    }
    if (p > 0)
    {
        printf("\nsono il padre: il mio pid è %d, mio figlio ha pid %d\n\n", getpid(), p);
        close(fd[1]); 
        int copiaArr[n];
        read(fd[0],copiaArr,sizeof(copiaArr));
        close(fd[0]);
        printf("Per qunato vuoi moltiplicare i numeri dell'array?\n");
        scanf("%d",& moltiplicatore);
        for(int i=0;i<5;i++){
            copiaArr[i]=copiaArr[i]*moltiplicatore;
            printf("%d\n", copiaArr[i]);
        }
        wait(&status);
    }
    else 
    {
        printf("sono il figlio: il mio pid è %d, mio padre ha pid %d\n", getpid(), getppid());
        close(fd[0]);
        for(int i=0;i<5;i++){
            printf("Inserire il n° %d dell'array\n",i+1);
            scanf("%d",& arreyN[i]);
        }
        if(write(fd[1],arreyN, sizeof(arreyN))==-1){
            printf("errore nel passaggio dell'array al padre\n");
            close(fd[1]);
            exit(-1);
        }
        close(fd[1]);
    }

    return 0;
}
