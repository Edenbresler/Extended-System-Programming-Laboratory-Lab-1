#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* map(char *array, int array_length, char (*f) (char)){
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));

  for (int i = 0; i < array_length; i++)
  {
      mapped_array[i] = f(array[i]);
  }
  free(array);
  return mapped_array;
}
/* Ignores c, reads and returns a character from stdin using fgetc. */
char my_get(char c){ 
  return fgetc(stdin);
}


/* If c is a number between 0x20 and 0x7E, cprt prints the character of ASCII value c followed by a new line. Otherwise, cprt prints the dot ('.') character. After printing, cprt returns the value of c unchanged. */

char cprt(char c){

    if (c >= 0x20 && c <= 0x7E) {
        printf("%c\n", c);
    } else {
        printf("%c\n", '.');
    }
    return c;
}

/* Gets a char c and returns its encrypted form by adding 1 to its value. If c is not between 0x20 and 0x7E it is returned unchanged */
char encrypt(char c){
if (c >= 0x20 && c <= 0x7E) {
  c =(c+1);

}
return c;
}


/* Gets a char c and returns its decrypted form by reducing 1 from its value. If c is not between 0x20 and 0x7E it is returned unchanged */
char decrypt(char c){
if (c >= 0x20 && c <= 0x7E) {
  c =(c-1);

}
return c;

}
char xprt(char c) {
    printf("%x\n", c);
    return c;
}


/* pointers to the functions */
char (*pointer_my_get) (char) = &my_get;
char (*pointer_cprt) (char) = &cprt;
char (*pointer_encrypt) (char) = &encrypt;
char (*pointer_decrypt) (char) = &decrypt;
char (*pointer_xprt) (char) = &xprt;

struct fun_desc {
    char *name;
    char (*fun)(char);
};

int main(int argc, char **argv){
    
    char *carray = (char*)malloc(5 * sizeof(char));
    carray[0] = '\0';


    struct fun_desc menu[] = { { "Get string", pointer_my_get }, { "Print string", pointer_cprt }, { "Encrypt", pointer_encrypt }, { "Decrypt", pointer_decrypt }, { "Print Hex", pointer_xprt }, { NULL, NULL } };
    
    fprintf(stdout,"Select operation from the following menu:\n");
    int i = 0;

    //print the options
    while(menu[i].name != NULL){
        fprintf(stdout,"%d) %s\n",i,menu[i].name);
        ++i;
    }
    printf("Option : ");
    char input_buffer[5];  
    char *the_input = fgets(input_buffer, sizeof(input_buffer), stdin);

        while(the_input != NULL){

            int num_input =atoi(the_input);
            if(num_input >=0 && num_input<5){
                fprintf(stdout,"Within bounds\n");

                char* new_array = map(carray, 5 ,menu[num_input].fun);
                free(carray);
                carray= new_array;
                printf("DONE.\n");
                
            }
            else{
                fprintf(stdout,"Not within bounds\n");
                free(carray);
                exit(0);
            }
            fprintf(stdout,"Select operation from the following menu:\n");
            int i = 0;
            //print the options
            while(menu[i].name != NULL){
                fprintf(stdout,"%d) %s\n",i,menu[i].name);
                ++i;
            }
            printf("Option : ");
            the_input = fgets(input_buffer, sizeof(input_buffer), stdin);
            

        }
        free(carray);
        

        return 0;
    
}