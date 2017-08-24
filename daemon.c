#include <stdio.h>
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
		int hue = setsid();
		char buf[100];
		while(1){
			FILE *fp = popen("top -bn2 | grep '%Cpu' | tail -1", "r");
			fread(buf,100,1, fp);
			write(archivo,buf,101);
			sleep(1);
		}
	}
	return 0;
}
