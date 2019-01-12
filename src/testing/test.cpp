/* lab2 uppg1 - Andre Lundkvist */

/* includes */
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>

/* define constants */
const char *test1 = "Jiisuki";
const char *filename = "conf.txt";
int size = 2;
int mode = 1;


int writeconf(){

  FILE *fp;
  if( (fp = fopen(filename,"w")) == NULL ){
    printf("Error opening file for write.\n");
    return 1;
  }
  printf("Writing Configuration File.\n");

  fprintf(fp,"NAME %s\n",test1);
  fprintf(fp,"SIZE %i\n",size);
  fprintf(fp,"MODE %i\n",mode);

  printf("Completed.\n");

  fclose(fp);

  return 0;
}

int readconf(){

  FILE *fp;
  if( (fp = fopen(filename,"r")) == NULL ){
    printf("Error opening file for read.\n");
    return 1;
  }

  char tag[32] = {0};
  char tmp[32] = {0};
  int tmp2;

  int i;
  for( i = 0; i < 3; i++ ){
    fscanf(fp,"%s",tag);
    if( strcmp(tag,"NAME") == 0 ){
      fscanf(fp,"%s",tmp);
      printf("Tag found (%s) with data: %s\n",tag,tmp);
    }
    if( strcmp(tag,"SIZE") == 0 ){
      fscanf(fp,"%i",&tmp2);
      printf("Tag found (%s) with data: %i\n",tag,tmp2);
    }
    if( strcmp(tag,"MODE") == 0 ){
      fscanf(fp,"%i",&tmp2);
      printf("Tag found (%s) with data: %i\n",tag,tmp2);
    }
  }
  return 0;
}



/* start main routine main() */
int main(void){
  
  FILE *fp;

  if( (fp = fopen(filename,"r") ) == NULL ){
    printf("Error opening for read.\n");
    writeconf();
  } else {
    fclose(fp);
    printf("Will try to read the file.\n");
    readconf();
  }
  

  /* quit and return 0 */
  return 0;
}

