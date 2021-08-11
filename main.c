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
    char *x;
    x=fgets(streamS,(sizeof(char) * 30),stdin);
    if(x);
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
    int done=0;
    unsigned long test[35];

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
            test[graphCount]=valueD;
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
            //free(streamS);
            int IV;
            int checks;
            if(graphCount<parsedInt[1])checks = graphCount;
            else checks =parsedInt[1];
            for(IV=0;IV<checks-1;IV++){
                    printf("%lu ",list[IV].id);
                    //printf("%lu ",list[IV].value);
            }
            printf("%lu",list[IV].id);
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
    unsigned long closedCount=0,closedCount2=0;
    unsigned long min=4294967295;
    int closed,check=1;
    int closedNodes[nodeNumber];
    if(*(graph)==0 && *(graph+1)==0 && *(graph+2)==0 && *(graph+3)==0)return 0;
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
                    else if(*(graph+row*nodeNumber+I)!=0 && *(costs+I)==0) *(costs+I)=sum+*(graph+row*nodeNumber+I);
                }
            }
            else{
                //iterates over row and chooses the closest node while updating paths
                if(min>*(graph+row*nodeNumber+I)&&*(graph+row*nodeNumber+I)!=0){
                    for(closed=0;closed<closedCount;closed++){
                        if(closedNodes[closed]==I) check=0;
                    }
                    if(check==1){
                        min=*(graph+row*nodeNumber+I);
                        *(nodeCache+closedCount) = I;
                        //update when finds closer
                    }
                }
                check=1;
                if(closedCount==0)*(costs+I)=*(graph+I);//Initialize costs
                else{ //Update costs if shorter paths are found (0 counts as infinite, so always update when 0)
                    if(*(graph+row*nodeNumber+I)!=0 && *(costs+I)> (sum + *(graph+row*nodeNumber+I))){
                        *(costs+I)=sum+*(graph+row*nodeNumber+I);
                    }
                    else if(*(graph+row*nodeNumber+I)!=0 && *(costs+I)==0) *(costs+I)=sum+*(graph+row*nodeNumber+I);
                }
            }
        }
            //min=100000;
            //save node and update row when current row is finished
            closedNodes[closedCount]=row;
            row = *(nodeCache+closedCount);
            closedCount++;
            if(closedCount<nodeNumber) sum+=min;
            if(min==42949672950){
                row=closedNodes[closedCount2-1];
                if(closedCount==0)break;
            }
            min=42949672950;
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

unsigned long dijkstra2(unsigned long *graph,int nodeNumber,unsigned long costs[],unsigned long nodeCache[]){
    unsigned long dist[nodeNumber],prev[nodeNumber],nodes[nodeNumber];
    int I,II,III,IV;
    int u=4294967295;
    int closedNum=0;
    int alt=0;
    int min=4294967295;
    for(I=0;I<nodeNumber;I++){
        dist[I]=*(graph+I);
    }
    for(II=0;II<nodeNumber;II++){
        prev[II]=-1;
    }
    for(III=0;III<nodeNumber;III++){
        nodes[III]=0;
    }
    //dist[0]=0;
    while(nodes[0]==0){
        for(I=0;I<nodeNumber;I++){
            if(min > dist[I] && dist[I]!=0){
                min = dist[I];
                u=I;
            }
        }
        nodes[u]=1;
        closedNum++;
        if(u==4294967295)break;
        for(IV=0;IV<nodeNumber;IV++){
            if(*(graph+(u*nodeNumber)+IV)!=0){
                alt=dist[u]+*(graph+(u*nodeNumber)+IV);
                if(alt<dist[IV]){
                    dist[IV]=alt;
                    prev[IV] = u;
                    //riordina
                }
            }
        }
        int sum,V;
        for(V=0;V<nodeNumber;V++){
            sum+=dist[V];
        }
        return sum;
    }
}


    int minDistance(int dist[], int nodes[],int nodeNumber){
        // Initialize min value
        int min = 4294967295, min_index;

        for (int v = 0; v < nodeNumber; v++)
            if (nodes[v] == 0 && dist[v] <= min)
                min = dist[v], min_index = v;

            return min_index;
    }


    void dijkstra3(unsigned long *graph,int nodeNumber){
        int i;
        int dist[nodeNumber]; // The output array.  dist[i] will hold the shortest
        // distance from src to i

        int nodes[nodeNumber]; // sptSet[i] will be true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized

        // Initialize all distances as INFINITE and stpSet[] as false
        for (int i = 0; i < nodeNumber; i++)
            dist[i] = 4294967295, nodes[i] = 0;

        // Distance of source vertex from itself is always 0
        dist[0] = *(graph);

        // Find shortest path for all vertices
        int count;
        for (int count = 0; count < nodeNumber - 1; count++) {
            // Pick the minimum distance vertex from the set of vertices not
            // yet processed. u is always equal to src in the first iteration.
            int u = minDistance(dist, nodes,nodeNumber);

            // Mark the picked vertex as processed
            nodes[u] = 1;

            // Update dist value of the adjacent vertices of the picked vertex.
            int v;
            for (int v = 0; v < nodeNumber; v++)

                // Update dist[v] only if is not in sptSet, there is an edge from
                // u to v, and total weight of path from src to  v through u is
                // smaller than current value of dist[v]
                if (!nodes[v] && *(graph+(nodeNumber*v)+u) && dist[u] != 4294967295
                && dist[u] + *(graph+(nodeNumber*v)+u) < dist[v])
                    dist[v] = dist[u] + *(graph+(nodeNumber*v)+u);
        }
    }




}