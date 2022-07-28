#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
 


char buf[500000];


void set_fl(int fd, int flags) /* flags are file status flags to turn on */
{
    int        val;

    if ( (val = fcntl(fd, F_GETFL, 0)) < 0)
        {
            printf("fcntl F_GETFL error");
            exit(1);
        }

    val |= flags;        /* turn on flags */
 //重新设置文件状态标志（val为新文件的文件状态标志）
    if (fcntl(fd, F_SETFL, val) < 0)
        {
            printf("fcntl F_SETFL error");
            exit(1);
        }
}

void clr_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) == -1)
    {
        perror("fcntl error!");
        exit(1);
    }
    val &= ~flags; /* turn flags off */

    if (fcntl(fd, F_SETFL, val) == -1)
    {
        perror("fcntl error!");
        exit(1);
    }
    return;
}

int main(void)
{
	int ntowrite,nwrite;
	char *ptr;
	
	ntowrite = read(STDIN_FILENO,buf,sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);
	
	set_fl(STDOUT_FILENO, O_NONBLOCK);
	
	ptr = buf;
	while(ntowrite > 0){
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stdout, "nwrite =%d, errno = %d\n",nwrite, errno);
	
		if(nwrite > 0){
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	
	clr_fl(STDOUT_FILENO, O_NONBLOCK);
	
	exit(0);

}

#if 0
int main(int argc,char *argv[])
{
    int ret = 0;
    
    for(int i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }






    return ret;
}
#endif

