#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    int value;
}graphy;

int *parser(const char *stream,int *value,int *returnValues,int *graph,int w,int nodes);
void maxheapify(graphy A[],int position,int length);
void deleteMax(graphy A[],int length);
void insert(graphy A[],int length,int value,int id);
void buildMaxheapify(graphy A[],int length);
int dijkstra3(int *graph,int nodeNumber);
int dijkstra_pepe_hands(int *graph,int nodeNumber);
int nextNode(const int *graph,const int dist[], const int nodes[],int nodeNumber,int current);
int powers[12]={
        1,10,100,1000,10000,100000,1000000,10000000,100000000,100000000,1000000000};

int main() {
    //initialize values for parsing and d,k parameters
    int value[11]={0};
    int parsedInt[2]={0};
    int graphCount=0;
    char streamS[30];
    char *x;
    x=fgets(streamS,(sizeof(char) * 30),stdin);
    if(x);
    parser(streamS, value, parsedInt,NULL,0,0);
    graphy list[parsedInt[1]];
    list[0].id=-1;
    list[0].value=-1;
    char stream[4000];
    char input[20];
    int arr[parsedInt[0]*parsedInt[0]];
    int numbers[parsedInt[0]];
    int done=0;
    int IV;
    int checks;

    while (fgets(input, (sizeof(char) * 20), stdin) != NULL){
        //list of best graphs
        if(input[0]=='A') {
            //allocates memory for adjacency matrix
            int k;
            for(k=0;k<parsedInt[0];k++){
                //allocates memory for a row of numbers
                //reads input and parse
                x = fgets(stream,(int)(sizeof(int) * 3*parsedInt[0]),stdin);//inputString(parsedInt[0]);
                if(x);
                parser(stream,value,numbers,arr,k,parsedInt[0]);
                //copy parsed values in matrix
            }
            //apply dijsktra algorithm
            int valueD;
            valueD=dijkstra_pepe_hands(arr,parsedInt[0]);
            if(graphCount<parsedInt[1]){
                list[graphCount].value=valueD;
                list[graphCount].id=graphCount;
            }
            //replace if better score (if even leave oldest)
            else{
                if(done==0){
                    buildMaxheapify(list,(int)parsedInt[1]-1);
                    done=1;
                }
                if(valueD<list[0].value){
                    deleteMax(list,(int)parsedInt[1]);
                    insert(list,(int)parsedInt[1]-1,valueD,graphCount);
                }
            }
            graphCount++;
        }
        else{
            if(graphCount<parsedInt[1]){
                checks = graphCount;
            }
            else{
                checks = parsedInt[1];
            }
            if(checks==0){
                printf("\n");
            }
            else{
                for(IV=0;IV<checks-1;IV++){
                    printf("%d",list[IV].id);
                    printf(" ");

                }
                printf("%d",list[IV].id);
                printf("\n");
            }
        }
    }
    return 0;
}

int *parser(const char *stream,int *value,int *returnValues,int *graph,int w,int nodes){
    //reads char, assemble number
    int inCount=0,lengthNum=0,k,numOfReturn=0;
    //initializes value for parsing
    while(stream[inCount]!='\n'){
        if(stream[inCount]==' '||stream[inCount]==','){
            //done reading parse last number
            if(graph==NULL){
                for(k=0;k<lengthNum;k++){
                    returnValues[numOfReturn]+=value[k]*powers[lengthNum-k-1];
                }
                lengthNum=0;
                numOfReturn++;
            }
            else{
                *(graph+numOfReturn+nodes*w)=0;
                for(k=0;k<lengthNum;k++){
                    *(graph+numOfReturn+nodes*w)+=value[k]*powers[lengthNum-k-1];
                }
                lengthNum=0;
                numOfReturn++;
            }
        }
        else{
            value[lengthNum]=stream[inCount]-'0';
            lengthNum++;
        }
        inCount++;
    }
        if(graph==NULL){
            for(k=0;k<lengthNum;k++){
                returnValues[numOfReturn]+=value[k]*powers[lengthNum-k-1];
            }
        }
        else{
            *(graph+numOfReturn+nodes*w)=0;
            for(k=0;k<lengthNum;k++){
                *(graph+numOfReturn+nodes*w)+=value[k]*powers[lengthNum-k-1];
            }
        }
    return returnValues;
}

void buildMaxheapify(graphy A[],int length){
    int I;
    for(I=length/2;I>=0;I--){
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
    if((left<=length-1) && (A[left].value > A[position].value)){
        posmax=left;
    }
    else posmax=position;
    if((right<=length-1) && (A[right].value > A[posmax].value)){
        posmax=right;
    }
    if(posmax!=position){
        dummy=A[position];
        A[position]=A[posmax];
        A[posmax]=dummy;
        maxheapify(A,posmax,length);
    }
}

void deleteMax(graphy A[],int length){
    if(length<1)return;
    A[0]=A[length-1];
    length=length-1;
    maxheapify(A,0,length);
}

void insert(graphy A[],int length,int value,int id){
    int I;
    graphy dummy;
    length=length+1;
    A[length-1].value = value;
    A[length-1].id = id;
    I = length;
    while(I>0 && (A[(I-1)/2].value < A[I].value)){
        dummy=A[(I-1)/2];
        A[(I-1)/2]=A[I];
        A[I]=dummy;
        I = (I-1)/2;
    }
}

    int dijkstra_pepe_hands(int *graph,int nodeNumber){

    int nodes[nodeNumber];
    int dist[nodeNumber];
    int min = 2147483647;
    int empty_queue=0;
    int unreachable_nodes=0;
    int curr=0;
    dist[0] = 0;

    for (int i = 1; i < nodeNumber; i++){
        dist[i]=*(graph+i);
        nodes[i] = 0;
        if(dist[i]!=0) unreachable_nodes=1;
    }
    if(unreachable_nodes==0)return 0;

    while(empty_queue==0){
        int position = -1;
        min = 2147483647;
        for(int j = 1; j < nodeNumber; j++){
            if (*(nodes+j) == 0 && dist[j] <= min && *(graph+(curr*nodeNumber)+j)!=0 && j!=curr){
                min = dist[j];
                position = j;
            }
        }
        if(position==-1){
            for(int i = 0; i < nodeNumber; i++){
                empty_queue=1;
                if(nodes[i]!=1 && dist[i]!=0){
                    position=i;
                    empty_queue=0;
                    break;
                }
            }
        }
        if(empty_queue==1)break;
        curr=position;
        nodes[position] = 1;
        for (int j = 1; j < nodeNumber; j++){
            if ((*(graph+(nodeNumber*position)+j)!=0 && dist[j]==0)
            || (*(graph+(nodeNumber*position)+j) !=0 && (dist[position] + *(graph+(nodeNumber*position)+j) < dist[j]))){
                dist[j] = dist[position] + *(graph+(nodeNumber*position)+j);
            }
        }
    }
    int sum=0,V;
    for(V=0;V<nodeNumber;V++){
        sum+=dist[V];
    }
    return sum;
}





