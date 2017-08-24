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
		int hue = setsid();
	}
	return 0;
}
