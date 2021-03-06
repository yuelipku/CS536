// simple shell example using fork() and execlp()

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

#define CMD "ps"

int main(void)
{
pid_t k;
char buf[100];
int status;
int len;

int fd;
int cfd;

char cbuf[500];

// client create the cfifopid
char cfifo[sizeof "cfifo11111"];
sprintf(cfifo,"cfifo%d",getpid());
char *cf = cfifo;
mkfifo(cf,0666);


// the server's fifo
char *scf = "cmdfifo";
char msg[100];
sprintf(msg,"$%d$%s",getpid(),CMD);
printf("msg %s\n",msg);
// open cmdfifo
fd = open(scf,O_WRONLY);
//cfd = open(cfifo,O_RDONLY);             //open client fifo file					
// write $clientpid$command to cmdfifo 
int wid = write(fd,msg,sizeof(msg));
close(fd);

printf("wid %d,Try to open cfifo %s \n",wid,cfifo);
cfd = open(cf,O_RDONLY);             //open client fifo file					
//perror("open:");
printf("cfifo = %d \n",cfd);

if (-1 == cfd)			//print the content in cfifo
{
printf("Failed to open and read the file.\n");
exit(1);
}

printf("Try to read cfifo \n");

read(cfd,cbuf,500);
perror("Read:");

close(cfd);


printf("received msg \n");
printf("%s \n",cbuf);
//unlink(scf);


return 0;

}
