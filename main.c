#include <stdio.h>
//#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int id;
    int value;
}graphy;

//#define CUR_MAX 4294967295

int *parser(const char *stream,int *value,int *returnValues,int *graph,int w,int nodes);
void maxheapify(graphy A[],int position,int length);
void deleteMax(graphy A[],int length);
void insert(graphy A[],int length,int value,int id);
void buildMaxheapify(graphy A[],int length);
int dijkstra3(int *graph,int nodeNumber);
int minDistance(const int dist[], const int nodes[],int nodeNumber,int current,const int *graph);
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
            valueD=dijkstra3(arr,parsedInt[0]);
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
                //printf("%lu\n",list[IV].id);
                //printf("\n");
            //printf(" %lu ",list[IV].value);
            //if(list[IV].id!=-1)printf("\n");
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



int minDistance(const int dist[], const int nodes[],int nodeNumber,int current,const int *graph){
        // Initialize min value
        int min = 2147483647;
        int min_index=-1;

        for (int v = 1; v < nodeNumber; v++){
            if (*(nodes+v) == 0 && dist[v] <= min && *(graph+(current*nodeNumber)+v)!=0 && v!=current){
                min = dist[v];
                min_index = v;
            }
        }
            return min_index;
    }


    int dijkstra3(int *graph,int nodeNumber){
        int check=0;
        int dist[nodeNumber]; // The output array.  dist[i] will hold the shortest
        // distance from src to i

        int nodes[nodeNumber]; // sptSet[i] will be true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized

        // Initialize all distances as INFINITE and stpSet[] as false
        for (int i = 0; i < nodeNumber; i++)
            dist[i]=*(graph+i), nodes[i] = 0;

        // Distance of source vertex from itself is always 0
        dist[0] = 0;
        int allZero=0;
        for (int i = 0; i < nodeNumber; i++){
            if(dist[i]!=0) allZero=1;
        }
        if(allZero==0) return 0;
        nodes[0] = 1;
        int current=0;

        // Find shortest path for all vertices
        while(check==0){
            // Pick the minimum distance vertex from the set of vertices not
            // yet processed. u is always equal to src in the first iteration.
            int u = minDistance(dist, nodes,nodeNumber,current,graph);
            if(u==-1){
                for(int i = 0; i < nodeNumber; i++){
                    check=1;
                    if(nodes[i]!=1 && dist[i]!=0){
                        u=i;
                        check=0;
                        break;
                    }
                }
            }
            if(check==1)break;
            current=u;
            // Mark the picked vertex as processed
            nodes[u] = 1;

            // Update dist value of the adjacent vertices of the picked vertex.
            for (int v = 1; v < nodeNumber; v++)

                // Update dist[v] only if is not in sptSet, there is an edge from
                // u to v, and total weight of path from src to  v through u is
                // smaller than current value of dist[v]
                if ((nodes[v]==0 && *(graph+(nodeNumber*u)+v) !=0
                && (dist[u] + *(graph+(nodeNumber*u)+v) < dist[v])) || (nodes[v]==0 && *(graph+(nodeNumber*u)+v)!=0 && dist[u] != 4294967295
                && dist[v]==0))
                    dist[v] = dist[u] + *(graph+(nodeNumber*u)+v);
        }
        int sum=0,V;
        for(V=0;V<nodeNumber;V++){
            sum+=dist[V];
        }
        return sum;
    }




