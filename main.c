#include <stdio.h>
#include <malloc.h>
#include <string.h>

//#define CUR_MAX 4294967295

//char *inputChar();
char *inputString();
unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues);
unsigned long power(unsigned long base,unsigned long esp);

int main() {
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
    unsigned long value[11];
    unsigned long *parsedInt;
    parsedInt = (unsigned long*) malloc(sizeof(unsigned long) * 2);
    parsedInt[0]=0;
    parsedInt[1]=0;
    value[0] = -1;

    while (1){

    char *streamS = inputString();

    unsigned long *dK;
    dK = parser(streamS, value, parsedInt);

    if (strncmp(streamS,"A",1)!=0 && strncmp(streamS,"T",1)!=0) {

    }
    if (strcmp(streamS,"AggiungiGrafo\n")==0) {
        unsigned long *arr = (unsigned long *)malloc(parsedInt[0] *parsedInt[0]* sizeof(unsigned long));
        int i, j,k,y;
        for(k=0;k<parsedInt[0];k++){
            unsigned long *numbers = (unsigned long*) malloc(sizeof(unsigned long) * parsedInt[0]);
            //free(streamS);
            char *streamS = inputString();
            printf("%s\n",streamS);
            parser(streamS,value,numbers);
            for(y=0;y<parsedInt[0];y++){
                *(arr+k*parsedInt[0]+y)=numbers[y];
                printf("%d\n",numbers[y]);
            }
            //free(numbers);
        }
        free(arr);
    } else if (strcmp(streamS, "TopK\n")==0) {

        //do stuff
        break;

    }
        printf("%lu\n",dK[0]);
        printf("%lu\n",dK[1]);
        printf("%lu\n",&dK[0]);
        printf("%lu",&dK[1]);
}
    printf("%lu\n",parsedInt[0]);
    printf("%lu",parsedInt[1]);
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

char *inputString(){
    char *buffer;
    buffer = (char*) malloc(sizeof(char)+(sizeof(unsigned long) * 2)); // allocate buffer.
    fgets(buffer,sizeof(char)+(sizeof(unsigned long) * 2),stdin);
    return buffer;
}

unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues){
    int inCount=0,lengthNum=0,k,numOfReturn=0;
    value[0]=0;
    value[1]=0;
    value[2]=0;
    value[3]=0;
    value[4]=0;
    value[5]=0;
    value[6]=0;
    value[7]=0;
    value[8]=0;
    value[9]=0;
    value[10]=0;
    value[11]=0;
    while(1){
        switch(stream[inCount]){
            case '\n':

                for(k=0;k<lengthNum;k++){
                    returnValues[numOfReturn]+=value[k]*power(10,lengthNum-k-1);
                    printf("%lu", returnValues[numOfReturn]);
                }
                lengthNum=0;
                numOfReturn++;

                break;
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
                lengthNum++;
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
        if(stream[inCount]=='\n')break;
        inCount++;

    }
    return returnValues;
}

unsigned long power(unsigned long base,unsigned long esp){
    unsigned long k,value=base;
    if(esp==0)return 1;
    for(k=1;k<esp;k++){
        value*=base;
    }
    return value;
}