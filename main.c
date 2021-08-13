#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
    unsigned long id;
    unsigned long value;
}graphy;

//#define CUR_MAX 4294967295

unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues,unsigned long *graph,int k,int nodes);
unsigned long power(unsigned long base,unsigned long esp);
unsigned long dijkstra(unsigned long *graph,int nodeNumber,unsigned long costs[],unsigned long nodeCache[]);
void maxheapify(graphy A[],int length,int position);
void deleteMax(graphy A[],int length);
void insert(graphy A[],int length,unsigned long value,unsigned long id);
void buildMaxheapify(graphy A[],int length);
unsigned long dijkstra3(unsigned long *graph,int nodeNumber);
int minDistance(unsigned long dist[], int nodes[],int nodeNumber,int current,unsigned long *graph);
unsigned long dijkstra2(unsigned long *graph,int nodeNumber,unsigned long costs[],unsigned long nodeCache[]);
unsigned long powers[12]={
        1,10,100,1000,10000,100000,1000000,10000000,100000000,100000000,1000000000,10000000000};

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
    parsedInt[0]=0;
    parsedInt[1]=0;
    unsigned long graphCount=0;
    char streamS[30];
    char *x;
    x=fgets(streamS,(sizeof(char) * 30),stdin);
    if(x);
    parser(streamS, value, parsedInt,NULL,0,0);
    graphy list[parsedInt[1]];
    list[0].id=-1;
    list[0].value=-1;
    //for(V=0;V<parsedInt[1];V++){
    //    list[V].id=-1;
    //    list[V].value=-1;
    //}
    //buildMaxheapify(list,1);
    //stream = (char*) malloc((sizeof(unsigned long) * 3*parsedInt[0]));
    char stream[4000];
    char input[20];
    unsigned long arr[parsedInt[0]*parsedInt[0]];
    unsigned long numbers[parsedInt[0]];
    int done=0;
    while (fgets(input, (sizeof(char) * 20), stdin) != NULL){
        //list of best graphs
        if (strncmp(input,"A",1)!=0 && strncmp(input,"T",1)!=0 && strncmp(input,"B",1)!=0) {
            //should remove ??
        }
        else if(strncmp(input,"AggiungiGrafo\n",2)==0) {
            //allocates memory for adjacency matrix
            int k,y;
            for(k=0;k<parsedInt[0];k++){
                //allocates memory for a row of numbers
                //reads input and parse
                x = fgets(stream,(sizeof(unsigned long) * 3*parsedInt[0]),stdin);//inputString(parsedInt[0]);
                if(x);
                parser(stream,value,numbers,arr,k,parsedInt[0]);
                //copy parsed values in matrix
                //for(y=0;y<parsedInt[0];y++){
                //    arr[k*parsedInt[0]+y]=numbers[y];
                //}
            }
            //apply dijsktra algorithm
            unsigned long valueD;
            valueD=dijkstra3(arr,parsedInt[0]);
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
                    insert(list,(int)parsedInt[1]-1,valueD,graphCount);
                }
            }
            graphCount++;
        } else if (strncmp(input, "TopK\n",2)==0) {
            int IV;
            int checks;
            if(graphCount<parsedInt[1])checks = graphCount;
            else checks =parsedInt[1];
            for(IV=0;IV<checks-1;IV++){
                    if(list[IV].id!=-1)printf("%lu ",list[IV].id);
                    //printf("%lu ",list[IV].value);
            }
            if(list[IV].id!=-1)printf("%lu",list[IV].id);
            //printf("%lu ",list[IV].value);
            printf("\n");
            //IV++;
            //if(*(list+IV)!=-1)printf("%lu\n",*(list+IV));
        }
    }
    //free(stream);
    return 0;
}

unsigned long *parser(char *stream,unsigned long *value,unsigned long *returnValues,unsigned long *graph,int w,int nodes){
    //reads char, assemble number
    int inCount=0,lengthNum=0,k,numOfReturn=0;
    //initializes value for parsing
    while(1){
        switch(stream[inCount]){
            case ' ':
                //done reading parse last number
                if(graph==NULL){
                    for(k=0;k<lengthNum;k++){
                        returnValues[numOfReturn]+=value[k]*powers[lengthNum-k-1];
                        //printf("\n%lu\n", returnValues[numOfReturn]);
                    }
                    lengthNum=0;
                    numOfReturn++;
                    break;
                }
                else{
                    *(graph+numOfReturn+nodes*w)=0;
                    for(k=0;k<lengthNum;k++){
                        *(graph+numOfReturn+nodes*w)+=value[k]*powers[lengthNum-k-1];
                        //printf("\n%lu\n", returnValues[numOfReturn]);
                    }
                    lengthNum=0;
                    numOfReturn++;
                    break;
                }
            case '\n':
                //done reading parse last number
                if(graph==NULL){
                    for(k=0;k<lengthNum;k++){
                        returnValues[numOfReturn]+=value[k]*powers[lengthNum-k-1];
                        //printf("\n%lu\n", returnValues[numOfReturn]);
                    }
                    lengthNum=0;
                    numOfReturn++;
                    break;
                }
                else{
                    *(graph+numOfReturn+nodes*w)=0;
                    for(k=0;k<lengthNum;k++){
                        *(graph+numOfReturn+nodes*w)+=value[k]*powers[lengthNum-k-1];
                        //printf("\n%lu\n", returnValues[numOfReturn]);
                    }
                    lengthNum=0;
                    numOfReturn++;
                    break;
                }
            case ',':
                //parse last read number
                //done reading parse last number
                if(graph==NULL){
                    for(k=0;k<lengthNum;k++){
                        returnValues[numOfReturn]+=value[k]*powers[lengthNum-k-1];
                        //printf("\n%lu\n", returnValues[numOfReturn]);
                    }
                    lengthNum=0;
                    numOfReturn++;
                    break;
                }
                else{
                    *(graph+numOfReturn+nodes*w)=0;
                    for(k=0;k<lengthNum;k++){
                        *(graph+numOfReturn+nodes*w)+=value[k]*powers[lengthNum-k-1];
                        //printf("\n%lu\n", returnValues[numOfReturn]);
                    }
                    lengthNum=0;
                    numOfReturn++;
                    break;
                }
            default:
                value[lengthNum]=stream[inCount]-'0';
                lengthNum++;
                break;
        }
        if(stream[inCount]=='\n')break;
        inCount++;

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
        //dummy.value=A[position].value;
        //dummy.id=A[position].id;
        dummy=A[position];
        //A[position].value = A[posmax].value;
        //A[position].id = A[posmax].id;
        A[position]=A[posmax];
        //A[posmax].value = dummy.value;
        //A[posmax].id = dummy.id;
        A[posmax]=dummy;
        maxheapify(A,posmax,length);
    }
}

void deleteMax(graphy A[],int length){
    if(length<1);
    //A[0].value=A[length].value;
    //A[0].id=A[length].id;
    A[0]=A[length-1];
    //A[length].value=A[length-1].value;
    //A[length].id=A[length-1].id;
    length=length-1;
    maxheapify(A,0,length);
}

void insert(graphy A[],int length,unsigned long value,unsigned long id){
    int I;
    graphy dummy;
    //A[length].value=A[length+1].value;
    //A[length].id=A[length+1].id;
    length=length+1;
    A[length-1].value = value;
    A[length-1].id = id;
    I = length;
    while(I>0 && (A[(I-1)/2].value < A[I].value)){
        //dummy.value=A[(I-1)/2].value;
        //dummy.id=A[(I-1)/2].id;
        dummy=A[(I-1)/2];
        //A[(I-1)/2].value = A[I].value;
        //A[(I-1)/2].id = A[I].id;
        A[(I-1)/2]=A[I];
        //A[I].value = dummy.value;
        //A[I].id = dummy.id;
        A[I]=dummy;
        I = (I-1)/2;
    }
}



int minDistance(unsigned long dist[], int nodes[],int nodeNumber,int current,unsigned long *graph){
        // Initialize min value
        int min = 4294967294, min_index=-1;

        for (int v = 0; v < nodeNumber; v++){
            if (*(nodes+v) == 0 && dist[v]+*(graph+(current*nodeNumber)+v) <= min && *(graph+(current*nodeNumber)+v)!=0 && v!=current){
                min = dist[v];
                min_index = v;
            }
        }
            return min_index;
    }


    unsigned long dijkstra3(unsigned long *graph,int nodeNumber){
        int check=0;
        unsigned long dist[nodeNumber]; // The output array.  dist[i] will hold the shortest
        // distance from src to i

        int nodes[nodeNumber]; // sptSet[i] will be true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized

        // Initialize all distances as INFINITE and stpSet[] as false
        for (int i = 0; i < nodeNumber; i++)
            dist[i]=*(graph+i), nodes[i] = 0;

        // Distance of source vertex from itself is always 0
        dist[0] = 0;
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
            current=u;
            // Mark the picked vertex as processed
            nodes[u] = 1;

            // Update dist value of the adjacent vertices of the picked vertex.
            for (int v = 0; v < nodeNumber; v++)

                // Update dist[v] only if is not in sptSet, there is an edge from
                // u to v, and total weight of path from src to  v through u is
                // smaller than current value of dist[v]
                if ((nodes[v]==0 && *(graph+(nodeNumber*u)+v) !=0 && (dist[u] != 4294967295)
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




