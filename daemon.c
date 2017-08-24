#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	int id = fork();

	if(id == 0){
		printf("Este es el prcoceso hijo.");
		umask(0);
		int archivo = open("log_cpu.log",O_WRONLY|O_CREAT|O_TRUNC);
		if(archivo<0){
			printf("Error abriendo archivo");
			return 0;
		}
		if(close(0) < 0||close(1)<0||close(2)<0){
			printf("Error cerrando cosas estándar.");
        	return 0;
		}
		setsid();		
		while(1){
			char buf[100] = {0};
			FILE *fp = popen("top -bn2 | grep '%Cpu' | tail -1", "r");
			fread(buf,100,1, fp);
			write(archivo,buf,strlen(buf));
			sleep(1);
			pclose(fp);
		}
	}
	return 0;
}
