#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#define FILEPATH "/dev/fb1"
#define NUM_WORDS 64
#define FILESIZE (NUM_WORDS * sizeof(uint16_t))

#define RED 0xF800
#define PINK 0xF81F
#define GREEN 0x07E0
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define BLACK 0x0000

void delay(int);

int mainnew(int opcion)
{
    int i;
    int fbfd;
    uint16_t *map;
    uint16_t *p;
    struct fb_fix_screeninfo fix_info;

    /* open the led frame buffer device */
    fbfd = open(FILEPATH, O_RDWR);
    if (fbfd == -1) {
	perror("Error (call to 'open')");
	exit(EXIT_FAILURE);
    }

    /* read fixed screen info for the open device */
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
	perror("Error (call to 'ioctl')");
	close(fbfd);
	exit(EXIT_FAILURE);
    }

    /* now check the correct device has been found */
    if (strcmp(fix_info.id, "RPi-Sense FB") != 0) {
	printf("%s\n", "Error: RPi-Sense FB not found");
	close(fbfd);
	exit(EXIT_FAILURE);
    }

    /* map the led frame buffer device into memory */
    map =
	mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (map == MAP_FAILED) {
	close(fbfd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }

    /* set a pointer to the start of the memory area */
    p = map;

    /* clear the led matrix */
    memset(map, 0, FILESIZE);

	if(opcion == 1){
		  /* flash white */
	    while (1) {
		delay(250);
		
		*(p + 50) = BLACK;
		
		*(p + 52) = BLACK;
		


		*(p + 8) = PINK;
		*(p + 17) = PINK;
		*(p + 20) = PINK;
		*(p + 22) = PINK;
		*(p + 25) = PINK;
		*(p + 26) = GREEN;
		*(p + 27) = GREEN;
		*(p + 28) = PINK;
		*(p + 29) = YELLOW;
		*(p + 30) = YELLOW;
		*(p + 33) = GREEN;
		*(p + 34) = GREEN;
		*(p + 35) = GREEN;
		*(p + 36) = YELLOW;
		*(p + 37) = WHITE;
		*(p + 38) = YELLOW;
		*(p + 39) = GREEN;
		*(p + 41) = GREEN;
		*(p + 42) = GREEN;
		*(p + 43) = GREEN;
		*(p + 44) = GREEN;
		*(p + 45) = YELLOW;
		*(p + 46) = YELLOW;
		*(p + 49) = GREEN;
		*(p + 51) = GREEN;
		*(p + 53) = GREEN;
	    	//prender();
		//memset(map, 0xFF, FILESIZE);
		delay(250);
		*(p + 49) = BLACK;
		*(p + 50) = GREEN;
		*(p + 51) = BLACK;
		*(p + 52) = GREEN;
		*(p + 53) = BLACK;
		//memset(map, 0, FILESIZE);
	    }
	}else{

		while(1){
			delay(450);
			memset(map, 0x24, FILESIZE);
			*(p + 0) = BLACK;
			*(p + 1) = BLACK;
			*(p + 6) = BLACK;
			*(p + 7) = BLACK;
			*(p + 8) = BLACK;
			*(p + 15) = BLACK;
			*(p + 48) = BLACK;
			*(p + 55) = BLACK;
			*(p + 56) = BLACK;
			*(p + 57) = BLACK;
			*(p + 62) = BLACK;
			*(p + 63) = BLACK;
			*(p + 19) = WHITE;
			delay(450);

			*(p + 23) = BLACK;
			*(p + 29) = BLACK;
			*(p + 30) = BLACK;
			*(p + 31) = BLACK;
			*(p + 36) = BLACK;
			*(p + 37) = BLACK;
			*(p + 38) = YELLOW;
			*(p + 39) = BLACK;
			*(p + 46) = BLACK;
			*(p + 47) = BLACK;
			*(p + 48) = BLACK;
			*(p + 56) = BLACK;
			*(p + 57) = BLACK;
			*(p + 63) = BLACK;


			*(p + 6) = GREEN;
			*(p + 15) = GREEN;
			*(p + 55) = GREEN;
			*(p + 62) = GREEN;
			
			
		}

	}
  
    delay(250);

    // limpiamos matriz 
    memset(map, 0, FILESIZE);

    // un-map y cerramos
    if (munmap(map, FILESIZE) == -1) {
	perror("Error un-mmapping the file");
    }
    close(fbfd);

    return 0;
}

void delay(int t)
{
    usleep(t * 1000);
}

