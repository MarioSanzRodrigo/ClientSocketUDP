/*
    Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

 
//#define SERVER "138.4.7.149"
#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    printf("########################################################\n");
    printf("##### Interfaz de control GAW - FFMPEG-Control-API #####\n");
    printf("########################################################\n");

    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message_recv[BUFLEN]="";
    char message[BUFLEN] = "";
    char message_1[BUFLEN] = "";
    char message_2[BUFLEN] = "";
    char message_2_1[BUFLEN] = "";
    char message_2_2[BUFLEN] = "";
    char message_3[BUFLEN] = "";
    char message_4[BUFLEN] = "";
    char message_5[BUFLEN] = "";
    char message_6[BUFLEN] = "";
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
 
    while(1)
    {

        printf("\nElija una opcion : \n 1. Modificar Quality Level (ql) \n 2. Modificar Frame Rate Output \n 3. Modificar Bit Rate Output \n 4. Modificar Gop Size \n 5. Modificar Width y Height Output \n 6. Cambiar codificador-decodificador\n 7. Proteccion de rectangulos \n 8. Block Gop \n 9. Down Mode \n 10. Skip Frames \n");

	gets(message_1);
	int aux = atoi(message_1);

	switch(aux){
		case 1:
			printf("Introduzca un valor para ql (%):\n");
			gets(message_2);
			int min = 0;
			int max = 100;
			int val = atoi(message_2);
			if (val>min && val<max){
			}else{
				printf("\nValor erroneo, introduzca valor entre 1-99 (%)\n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			break;
		case 2:
			printf("Introduzca un valor para Frame Rate Output:\n");
			gets(message_2);
			min = 0;
			max = 100;
			val = atoi(message_2);
			if (val>min && val<max){
			}else{
				printf("\nValor erroneo, introduzca valor entre 1-99 FPS\n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			break;
		case 3:
			printf("Introduzca un valor para Bit Rate Output [kbps]:\n");
			gets(message_2);
			min = 0;
			max = 600*1024;
			val = atoi(message_2)*1024;
			if (val>min && val<max){
			}else{
				printf("\nValor erroneo, introduzca valor entre 1-600 [kbps]\n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			break;
		case 4:
			printf("Introduzca un valor para Gop Size:\n");
			gets(message_2);
			min = 0;
			max = 100;
			val = atoi(message_2);
			if (val>min && val<max){
			}else{
				printf("\nValor erroneo, introduzca valor entre 1-99 \n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			break;
		case 5:
			printf("Introduzca un valor para Width Output:\n");
			gets(message_2);
			val = atoi(message_2);
			min = 0;
			max = 1080;
			if (val>min && val<max){
			}else{
				printf("\nValor erroneo, introduzca valor entre 1-1080 \n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			strcat(message_2,";");
			printf("Introduzca un valor para Height Output:\n");
			gets(message_3);
			val = atoi(message_3);
			if (val>min && val<max){
			}else{
				printf("\nValor erroneo, introduzca valor entre 1-1080 \n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			strcat(message_2,message_3);
			break;


		case 6:
			printf("Seleccione el tipo de codificador y decodificador:\n 1. MLHE \n 2. M2V \n 3. H264 \n");
			gets(message_2);
			int aux2 = atoi(message_2);
			switch(aux2){
				case 1:
					// ffmpeg_mlhe_enc y ffmpeg_mlhe_dec
					memset(message_2,'\0', BUFLEN);
					strncpy(message_2, "proc_name=ffmpeg_mlhe_enc",BUFLEN);
					break;
				case 2:
					// ffmpeg_m2v_enc y ffmpeg_mlhe_dec
        				memset(message_2,'\0', BUFLEN);
					strncpy(message_2, "proc_name=ffmpeg_m2v_enc",BUFLEN);
					break;
				case 3:
					// ffmpeg_x264_enc y ffmpeg_x264_dec
        				memset(message_2,'\0', BUFLEN);
					strncpy(message_2, "proc_name=ffmpeg_x264_enc",BUFLEN);
					break;
			}
			break;

		case 7:
			printf("Introduzca el valor de TTL: \n");
			gets(message_2);
			strcat(message_2,",");
			printf("Seleccionar Flag Protection (1-True / 0-False): \n");
			gets(message_2_1);
			strcat(message_2_1,",");
			strcat(message_2,message_2_1);
			printf("Introduzca la coordenada X ini:\n");
			gets(message_2_2);
			strcat(message_2_2,",");
			strcat(message_2,message_2_2);
			printf("Introduzca la coordenada X fin:\n");
			gets(message_3);
			strcat(message_3,",");
			strcat(message_2,message_3);
			printf("Introduzca la coordenada Y ini:\n");
			gets(message_4);
			strcat(message_4,",");
			strcat(message_2,message_4);
			printf("Introduzca la coordenada Y fin:\n");
			gets(message_5);
			strcat(message_2,message_5);
			printf("¿Quiere agregar otro rectangulo? (1-SI / 0-NO):\n");
			gets(message_6);
			int aux3 = atoi(message_6);

			if(aux3 == 0){
			}else{
				strcat(message_2,",");
			}
			
			while (aux3 != 0){
				printf("Seleccionar Flag Protection (1-True / 0-False): \n");
				gets(message_2_1);
				strcat(message_2_1,",");
				strcat(message_2,message_2_1);
				printf("Introduzca la coordenada X ini:\n");
				gets(message_2_2);
				strcat(message_2_2,",");
				strcat(message_2,message_2_2);
				printf("Introduzca la coordenada X fin:\n");
				gets(message_3);
				strcat(message_3,",");
				strcat(message_2,message_3);
				printf("Introduzca la coordenada Y ini:\n");
				gets(message_4);
				strcat(message_4,",");
				strcat(message_2,message_4);
				printf("Introduzca la coordenada Y fin:\n");
				gets(message_5);
				strcat(message_2,message_5);
				printf("¿Quiere agregar otro rectangulo? (1-SI / 0-NO):\n");
				gets(message_6);
				aux3 = atoi(message_6);
					
			}

			break;

		case 8:
			printf("Introduzca un valor para Block Gop: \n");
			gets(message_2);
			val = atoi(message_2);
			if (val>=0 && val<32000){
			}else{
				printf("\nValor erroneo, introduzca valor entre 0-32000 \n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			break;

		case 9:
			printf("Introduzca un valor para Down Mode:\n");
			gets(message_2);
			val = atoi(message_2);
			if (val>=0 && val<3){
			}else{
				printf("\nValor erroneo, introduzca valor entre 0-3 \n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			break;

		case 10:
			printf("Introduzca un valor para Skip Frames:\n");
			gets(message_2);
			val = atoi(message_2);
			if (val>=0 && val<=100){
			}else{
				printf("\nValor erroneo, introduzca valor entre 0-100 \n\n");
        			memset(message_1,'\0', BUFLEN);
        			memset(message_2,'\0', BUFLEN);
				goto nothing;
			}
			break;
			
	}


	strcat(message,message_1);
	strcat(message,"/");
	strcat(message,message_2);

	printf("\nDatos enviados: %s\n",message);
         
        //send the message
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        memset(message,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, message_recv, sizeof(message_recv), 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }

        puts(message_recv);

	nothing:
		continue;
    }
 
    close(s);
    return 0;
}
