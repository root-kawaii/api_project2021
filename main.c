#include <stdio.h>
#include <malloc.h>
#include <string.h>

//#define CUR_MAX 4294967295

//char *inputChar();
char *inputString();
unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues);
unsigned long power(unsigned long base,unsigned long esp);
unsigned long dijkstra(unsigned long *graph,int nodeNumber);

int main() {
    //initialize values for parsing and d,k parameters
    unsigned long value[11];
    value[0] = -1;
    unsigned long *parsedInt;
    parsedInt = (unsigned long*) malloc(sizeof(unsigned long) * 2);
    parsedInt[0]=0;
    parsedInt[1]=0;

    while (1){

    char *streamS = inputString(1); // read d and k or instructions
    unsigned long *dK;
    dK = parser(streamS, value, parsedInt);

    if (strncmp(streamS,"A",1)!=0 && strncmp(streamS,"T",1)!=0) {
        //should remove this as it never enters this one
    }
    if (strcmp(streamS,"AggiungiGrafo\n")==0) {
        //allocates memory for adjacency matrix
        unsigned long *arr = (unsigned long *)malloc(parsedInt[0] *parsedInt[0]* sizeof(unsigned long));
        int i, j,k,y,w;
        for(k=0;k<parsedInt[0];k++){
            //allocates memory for a row of numbers
            unsigned long *numbers = (unsigned long*) malloc(sizeof(unsigned long) * parsedInt[0]);
            //initialize to 0
            for(w=0;w<parsedInt[0];w++){
                numbers[w]=0;
            }
            //reads input and parse
            char *streamS = inputString(parsedInt[0]);
            parser(streamS,value,numbers);
            free(streamS);
            //copy parsed values in matrix
            for(y=0;y<parsedInt[0];y++){
                *(arr+k*parsedInt[0]+y)=numbers[y];
                printf("%lu\n",numbers[y]);
            }
            free(numbers);
        }
        //apply dijsktra algorithm
        dijkstra(arr,parsedInt[0]);
        free(arr);
    } else if (strcmp(streamS, "TopK\n")==0) {

        //do stuff
        break;
    }
        printf("%lu\n",dK[0]);
        printf("%lu\n",dK[1]);
        free(streamS);
}
    free(parsedInt);
    return 0;
}

char *inputString(int multiply){
    char *buffer;
    buffer = (char*) malloc(sizeof(char)+(sizeof(unsigned long) * 2*multiply)); // allocate buffer.
    fgets(buffer,sizeof(char)+(sizeof(unsigned long) * 2),stdin);
    return buffer;
}

unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues){
    //reads char, assemble number
    int inCount=0,lengthNum=0,k,numOfReturn=0;
    //initializes value for parsing
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
                //done reading parse last number
                for(k=0;k<lengthNum;k++){
                    returnValues[numOfReturn]+=value[k]*power(10,lengthNum-k-1);
                    printf("%lu", returnValues[numOfReturn]);
                }
                lengthNum=0;
                numOfReturn++;

                break;
            case ',':
                //parse last read number
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

unsigned long dijkstra(unsigned long *graph,int nodeNumber){
    int I;
    unsigned long sum=0;
    unsigned long row=0;
    unsigned long closedCount=0;
    unsigned long column;
    unsigned long min=10;
    unsigned long *costs = (unsigned long *)malloc(sizeof (unsigned long)*nodeNumber);
    unsigned long *nodeCache = (unsigned long *)malloc(sizeof (unsigned long)*nodeNumber);

    while(closedCount<nodeNumber){
        //while not finished...
        for(I=0;I<nodeNumber;I++){
            //iterates over row and chooses the closest node while updating paths
            if(min>*(graph+row*nodeNumber+I)){
                min=*(graph+I);
                sum+=min;
                *(nodeCache+closedCount) = I;
                //update when finds closer
            }
            if(closedCount==0)*(costs+I)=*(graph+I);//Initialize costs
            else{ //Update costs if shorter paths are found (0 counts as infinite, so always update when 0)
                if(*(graph+row*nodeNumber+I)!=0 && *(costs+I)> (sum + *(graph+row*nodeNumber+I))){
                    *(costs+I)=sum+*(graph+row*nodeNumber+I);
                }
                else if(*(graph+row*nodeNumber+I)!=0) *(costs+I)=sum+*(graph+row*nodeNumber+I);
            }
        }
        //save node and update row when current row is finished
        row = *(nodeCache+closedCount);
        closedCount++;
    }
    //printf("bro %lu",min);
}