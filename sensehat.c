#include "fb.h"
#include "metodos.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "anima.h"
#include "5x5_font.h"


#define CHAR_WIDTH (sizeof(font) / 96)
#define CHAR_HEIGHT 8
#define SCROLL_DELAY 100
#define LETTER_SPACE 1
#define LETTER_WIDTH (CHAR_WIDTH + LETTER_SPACE)



void draw(char c,int x,int y,sense_color_t color,sense_bitmap_t bitmap);
const unsigned char* character(char c);


int main(){
    int opcion;
    char *texto[80];
    char *a[10];
    a[1] = "Hola";
    a[2] = "Adios";
    a[3] = "Programacion avanzada";
    a[4] = "Lenguaje C";
    a[5] = "Rafa";
    a[6] = "C es el mejor lenguaje";
    a[7] = "ITC";
    a[8] = "JAVA";
    a[9] = "C++";
    a[10] = "C";

    printf("Ingresa la opción que deseas:\n");
    printf("1. Mostrar hora actual\n");
    printf("2. Seleccionar mensajes guardados\n");
    printf("3. Animación\n");
    printf("4. Ingresar texto\n");
    scanf("%d", &opcion);

    if(opcion == 1){

        int hours, minutes, seconds; 
        char tiempo[80];
        char hoursC[30], minutesC[30], secondsC[30];
        
        time_t now; 
        time(&now);

        struct tm *local = localtime(&now);
        hours = local->tm_hour;
        minutes = local->tm_min;
        seconds = local->tm_sec;

        sprintf(hoursC, "%d", hours);
        sprintf(minutesC, "%d", minutes);
        sprintf(secondsC, "%d", seconds);

        strcpy(tiempo, hoursC);
        strcat(tiempo, ":");
        strcat(tiempo, minutesC);
        strcat(tiempo, ":");
        strcat(tiempo, secondsC);
        printf("Tiempo: %s\n", tiempo);
        texto[1] =tiempo;


    }else if(opcion == 2){
	    int i = 0;
        printf("////////////////////////////\n");
        printf("Selecciona el mensaje que quieres desplegar:\n");
        printf("1.- Hola:\n");
        printf("2.- Adios\n");
        printf("3.- Programacion avanzada\n");
        printf("4.- Lenguaje C\n");
        printf("5.- Rafa\n");
        printf("6.- C es el mejor lenguaje\n");
        printf("7.- ITC\n");
        printf("8.- JAVA\n");
        printf("9.- C++\n");
        printf("10.- C\n");
    	scanf("%d", &i);
    	texto[1]=a[i];


    }else if(opcion == 3){
    	int anim;
    	printf("////////////////////////////\n");
        printf("Selecciona la animacion:\n");
        printf("1.- Perrito:\n");
        printf("2.- Pacman\n");
     	scanf("%d", &opcion);
    	mainnew(opcion);


    }else if(opcion == 4){
	    char input[80];
        printf("////////////////////////////\n");
        printf("Ingresa el mensaje que quieres desplegar:\n");
        fgets(input, 80, stdin);
	    //printf("%s\n",input);
	    //scanf("%s", &input);
    	gets(input);
    	texto[1] = input;

    }else{
        texto[1] = "";
        printf("Opción no encontrada, intentalo de nuevo\n");
    }


    sense_bitmap_t fb = sense_alloc_fb();
    if (!fb){
        fprintf(stderr,"Could not allocate framebuffer: %s\n",sense_strerror(sense_errno()));
        exit(1);
    }
    sense_color_t color = sense_make_color_rgb(0xff,0xff,0);
    sense_bitmap_t buffer = sense_alloc_bitmap();
    char* word = texto[1];
    int idx;
    int len = strlen(word);
    for (int x=0;x<len*LETTER_WIDTH;++x){
        sense_bitmap_paint(buffer,0);
        idx = x/LETTER_WIDTH;
        draw(word[idx],0 - x % LETTER_WIDTH,0,color,buffer);
        if ((idx + 1) < len){
            draw(word[idx+1],LETTER_WIDTH - x % LETTER_WIDTH,0,color,buffer);
        }
        sense_bitmap_cpy(fb,buffer);
        
        usleep(SCROLL_DELAY*1000);
    }

    // clear display
    sense_bitmap_paint(fb,0);
    sense_free_bitmap(fb);
    sense_free_bitmap(buffer);
    return 0;
}

const unsigned char* character(char c){
    c = c & 0x7F;
    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }
    return font[c];
}


void draw(char c,int x,int y,sense_color_t color,sense_bitmap_t bitmap) {
    int i,j;
    const unsigned char* chr = character(c);
    for (j=0 + ((LETTER_SPACE+x)<0?(1+x)*-1:0); j<CHAR_WIDTH && (1+j+x) < SENSE_BITMAP_WIDTH; ++j) {
        for (i=0 + (y<0?y*-1:0); i<CHAR_HEIGHT && (i+y < SENSE_BITMAP_HEIGHT); ++i) {
            if (chr[j] & (1<<i)) {
                sense_bitmap_set_pixel(bitmap,LETTER_SPACE +j+x, i+y,color);
            }
        }
    }
}