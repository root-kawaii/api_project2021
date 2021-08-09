#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
    unsigned long id;
    unsigned long value;
}graphy;

//#define CUR_MAX 4294967295

//char *inputChar();
//char *inputString();
unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues);
unsigned long power(unsigned long base,unsigned long esp);
unsigned long dijkstra(unsigned long *graph,int nodeNumber,unsigned long costs[],unsigned long nodeCache[]);
void maxheapify(graphy A[],int length,int position);
void deleteMax(graphy A[],int length);
void insert(graphy A[],int length,unsigned long value,unsigned long id);
void buildMaxheapify(graphy A[],int length);

int main() {
    //initialize values for parsing and d,k parameters
    unsigned long value[11];
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
    unsigned long parsedInt[2];
    //parsedInt = (unsigned long*) malloc(sizeof(unsigned long) * 2);
    parsedInt[0]=0;
    parsedInt[1]=0;
    unsigned long graphCount=0;
    char streamS[30];
    char *stream=NULL;
    fgets(streamS,(sizeof(char) * 30),stdin);
    parser(streamS, value, parsedInt);
    //free(streamS);
    graphy list[parsedInt[1]];
    list[0].id=-1;
    list[0].value=-1;
    //int V;
    //for(V=0;V<parsedInt[1];V++){
    //    list[V].id=-1;
    //    list[V].value=-1;
    //}
    //buildMaxheapify(list,1);
    stream = (char*) malloc((sizeof(unsigned long) * 3*parsedInt[0]));
    char input[20];
    unsigned long arr[parsedInt[0]*parsedInt[0]];
    //arr = (unsigned long *)malloc(parsedInt[0] *parsedInt[0]* sizeof(unsigned long));
    unsigned long numbers[parsedInt[0]];
    //numbers = (unsigned long*) malloc(sizeof(unsigned long) * parsedInt[0]);
    unsigned long costs[parsedInt[0]];
    unsigned long nodeCache[parsedInt[0]];

    while (fgets(input, (sizeof(char) * 20), stdin) != NULL){
        //streamS = fgets(streamS,(sizeof(unsigned long) * 3*1),stdin);
        //list of best graphs
        if (strncmp(input,"A",1)!=0 && strncmp(input,"T",1)!=0 && strncmp(input,"B",1)!=0) {
            //free(streamS);
            //should remove ??
        }
        else if(strncmp(input,"AggiungiGrafo\n",2)==0) {
            //free(streamS);
            //allocates memory for adjacency matrix
            int k,y,w;
            for(k=0;k<parsedInt[0];k++){
                //allocates memory for a row of numbers

                //initialize to 0
                for(w=0;w<parsedInt[0];w++){
                    numbers[w]=0;
                }
                //reads input and parse
                //free(streamS);
                stream = fgets(stream,(sizeof(unsigned long) * 3*parsedInt[0]),stdin);//inputString(parsedInt[0]);
                parser(stream,value,numbers);
                //copy parsed values in matrix
                for(y=0;y<parsedInt[0];y++){
                    arr[k*parsedInt[0]+y]=numbers[y];
                }
                //free(numbers);
            }
            //apply dijsktra algorithm
            unsigned long valueD;
            valueD=dijkstra(arr,parsedInt[0],costs,nodeCache);
            //memorize first k graphs with their score
            int done=0;
            if(graphCount<parsedInt[1]){
                list[graphCount].value=valueD;
                list[graphCount].id=graphCount;
                //insert(list,graphCount,valueD,graphCount);
            }
            //replace if better score (if even leave oldest)
            else{
                if(done==0){
                    buildMaxheapify(list,(int)parsedInt[1]);
                    done=1;
                }
                if(valueD<list[0].value){
                    deleteMax(list,(int)parsedInt[1]);
                    insert(list,(int)parsedInt[1],valueD,graphCount);
                }
            }
            graphCount++;
        } else if (strncmp(input, "TopK\n",2)==0) {
            //free(streamS);
            int IV;
            int checks,tree=0;
            if(graphCount<parsedInt[1])checks = graphCount;
            else checks =parsedInt[1];
            for(IV=0;IV<checks;IV++){
                    if(list[IV].value!=-1)printf("%lu ",list[IV].id);

            }
            printf("\n");
            //IV++;
            //if(*(list+IV)!=-1)printf("%lu\n",*(list+IV));
            //do stuff

        }
        //if(returning==1){
            //free(streamS);
            //free(list);
            //free(parsedInt);
            //return 0;

    }
    //free(list);
    //free(parsedInt);
    free(stream);
    //free(streamS);
    //free(input);
    //free(arr);
    return 0;
}

char *inputString(int multiply){
    char *buffer=NULL;
    buffer = (char*) malloc((sizeof(unsigned long) * 3*multiply)); // allocate buffer.
    buffer = fgets(buffer,(sizeof(unsigned long) * 3*multiply),stdin);
    return buffer;
}

unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues){
    //reads char, assemble number
    int inCount=0,lengthNum=0,k,numOfReturn=0;
    //initializes value for parsing
    while(1){
        switch(stream[inCount]){
            case '\n':
                //done reading parse last number
                for(k=0;k<lengthNum;k++){
                    returnValues[numOfReturn]+=value[k]*power(10,lengthNum-k-1);
                    //printf("\n%lu\n", returnValues[numOfReturn]);
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
            case ' ':
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

unsigned long dijkstra(unsigned long *graph,int nodeNumber,unsigned long costs[],unsigned long nodeCache[]){
    int I;
    unsigned long sum=0;
    unsigned long row=0;
    unsigned long closedCount=0;
    unsigned long min=4294967295;
    //unsigned long *costs = (unsigned long *)malloc(sizeof (unsigned long)*nodeNumber);
    //unsigned long *nodeCache = (unsigned long *)malloc(sizeof (unsigned long)*nodeNumber);

    while(closedCount<nodeNumber){
        //while not finished...
        for(I=0;I<nodeNumber;I++){
            if(row==I){
                if(closedCount==0)*(costs+I)=*(graph+I);//Initialize costs
                else{ //Update costs if shorter paths are found (0 counts as infinite, so always update when 0)
                    if(*(graph+row*nodeNumber+I)!=0 && *(costs+I)> (sum + *(graph+row*nodeNumber+I))){
                        *(costs+I)=sum+*(graph+row*nodeNumber+I);
                    }
                    else if(*(graph+row*nodeNumber+I)==0) *(costs+I)=sum+*(graph+row*nodeNumber+I);
                }
            }
            else{
                //iterates over row and chooses the closest node while updating paths
                if(min>*(graph+row*nodeNumber+I)){
                    min=*(graph+row*nodeNumber+I);
                    *(nodeCache+closedCount) = I;
                    //update when finds closer
                }
                if(closedCount==0)*(costs+I)=*(graph+I);//Initialize costs
                else{ //Update costs if shorter paths are found (0 counts as infinite, so always update when 0)
                    if(*(graph+row*nodeNumber+I)!=0 && *(costs+I)> (sum + *(graph+row*nodeNumber+I))){
                        *(costs+I)=sum+*(graph+row*nodeNumber+I);
                    }
                    else if(*(graph+row*nodeNumber+I)==0) *(costs+I)=sum+*(graph+row*nodeNumber+I);
                }
            }
        }
            //min=100000;
            //save node and update row when current row is finished
            row = *(nodeCache+closedCount);
            closedCount++;
            if(closedCount<nodeNumber) sum+=min;
            min=4294967295;
    }
    //printf("bro %lu",min);
    unsigned long result;
    int III=0;
    result=0;
    for(III=0;III<nodeNumber;III++){
        result+=*(costs+III);
    }
    //free(costs);
    //free(nodeCache);
    return result;
}

void buildMaxheapify(graphy A[],int length){
    int I;
    for(I=length/2;I>0;I--){
        maxheapify(A,I,length);
    }
}

void maxheapify(graphy A[],int position,int length){
    int I=position;
    graphy dummy;
    int left,right,posmax;
    left=(2*I)+1;
    if(left>length-1)left=length-1;
    right=(2*I)+2;
    if(right>length-1)right=length-1;
    if((left<=length) && (A[left].value > A[position].value)){
        posmax=left;
    }
    else posmax=right;
    if((right<=length) && (A[right].value > A[posmax].value)){
        posmax=right;
    }
    if(posmax!=position){
        dummy.value=A[position].value;
        dummy.id=A[position].id;
        A[position].value = A[posmax].value;
        A[position].id = A[posmax].id;
        A[posmax].value = dummy.value;
        A[posmax].id = dummy.id;
        maxheapify(A,posmax,length);
    }
}

void deleteMax(graphy A[],int length){
    int I,max;
    if(length<1);
    max=A[0].value;
    A[0].value=A[length].value;
    A[0].id=A[length].id;
    A[length].value=A[length-1].value;
    A[length].id=A[length-1].id;
    maxheapify(A,0,length);
}

void insert(graphy A[],int length,unsigned long value,unsigned long id){
    int I,max;
    graphy dummy;
    A[length].value=A[length+1].value;
    A[length].id=A[length+1].id;
    A[length].value = value;
    A[length].id = id;
    I = length;
    while(I>0 && (A[(I-1)/2].value < A[I].value)){
        dummy.value=A[(I-1)/2].value;
        dummy.id=A[(I-1)/2].id;
        A[(I-1)/2].value = A[I].value;
        A[(I-1)/2].id = A[I].id;
        A[I].value = dummy.value;
        A[I].id = dummy.id;
        I = (I-1)/2;
    }
}

