#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define CUR_MAX 10240

char *inputChar();
char *inputString();
int *parser();
int power();

int main(int argc, char **argv) {
    //int i=1;
    /*char *stream=inputChar();
    char ch=stream[0];
    printf("%s",streamS);
    while( (ch != '\n') && (ch != EOF) ){
        printf("%c",ch);
        ch=stream[i];
        i++;
    }
    */
    int value[CUR_MAX];
    char *streamS=inputString();
    value[0]=-1;
    int parsedInt[CUR_MAX];
    parser(streamS,value,parsedInt);
    if(value[0]==-1){
        if(strcmp(streamS,"AggiungiGrafo")){

        }
        else if(strcmp(streamS,"TopK")){

        }
    }
    else printf("%d",parsedInt[1]);
    return 0;
}

/*
char *inputChar(){
    int size=CUR_MAX;
    char *buffer = (char*) malloc(sizeof(char) * size); // allocate buffer.
    int length = 0;
    char ch;
    while ( (ch != '\n') && (ch != EOF) ) {
        if(length ==CUR_MAX) { // time to expand ?
            size *= 2; // expand to double the current size of anything similar.
            buffer = realloc(buffer, size); // re allocate memory.
        }
        ch = getc(stdin); // read from stream.
        buffer[length] = ch; // stuff in buffer.
        length++;
    }
    return buffer;
    }
*/

char *inputString(char *buffer){
    buffer = (char*) malloc(sizeof(char) * CUR_MAX); // allocate buffer.
    fgets(buffer,CUR_MAX,stdin);
    return buffer;
}

int *parser(char *stream,int *value,int *returnValues){
    int inCount=0,lengthNum=0,k,numOfReturn=0;
    while(stream[inCount]!='\n'){
        switch(stream[inCount]){
            case ',':
                for(k=0;k<lengthNum;k++){
                    returnValues[numOfReturn]+=value[k]*power(10,lengthNum-k-1);
                }
                lengthNum=0;
                numOfReturn++;
                break;
            case '1':
                value[lengthNum]=1;
                lengthNum++;
                break;
            case '2':
                value[lengthNum]=2;
                lengthNum++;
                break;
            case '3':
                value[lengthNum]=3;
                lengthNum++;
                break;
            case '4':
                value[lengthNum]=4;
                lengthNum++;
                break;
            case '5':
                value[lengthNum]=5;
                lengthNum++;
                break;
            case '6':
                value[lengthNum]=6;
                break;
            case '7':
                value[lengthNum]=7;
                lengthNum++;
                break;
            case '8':
                value[lengthNum]=8;
                lengthNum++;
                break;
            case '9':
                value[lengthNum]=9;
                lengthNum++;
                break;
            case '0':
                value[lengthNum]=0;
                lengthNum++;
                break;
            default:
                break;
        }
        inCount++;
    }
    return returnValues;
}

int power(int base,int esp){
    int k,value=base;
    if(esp==0)return 1;
    for(k=1;k<esp;k++){
        value*=base;
    }
    return value;
}