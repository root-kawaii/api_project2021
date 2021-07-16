#include <stdio.h>
#include <malloc.h>

char *inputChar();
char *inputString();
char *parser();

int main(int argc, char **argv) {
    int i=1;
    char *stream=inputChar();
    char *streamS=inputString();
    char ch=stream[0];
    printf("%s",streamS);
    while( (ch != '\n') && (ch != EOF) ){
        printf("%c",ch);
        ch=stream[i];
        i++;
    }
    parser(streamS);
    return 0;
}


char *inputChar(){
    int CUR_MAX = 4095;
    char *buffer = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.
    int length = 0;
    char ch;
    while ( (ch != '\n') && (ch != EOF) ) {
        if(length ==CUR_MAX) { // time to expand ?
            CUR_MAX *= 2; // expand to double the current size of anything similar.
            buffer = realloc(buffer, CUR_MAX); // re allocate memory.
        }
        ch = getc(stdin); // read from stream.
        buffer[length] = ch; // stuff in buffer.
        length++;
    }
    return buffer;
    }

char *inputString(char *buffer){
    int CUR_MAX = 1024*10;
    buffer = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.
    fgets(buffer,CUR_MAX,stdin);
    return buffer;
}

char *parser(char *stream){
    char check=stream[0];
    int i=0;
    while(check!="\n"){
        stream[i];
        i++;
    }
    while(){

    }
}
