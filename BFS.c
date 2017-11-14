
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1



typedef int Elemtype;
typedef struct QueueN{
        Elemtype data;
        struct QueueN *next;
    }QN;

typedef struct QFR{
    QN *front, *rear;
    }QFR;


void INITIALQueue(QFR *q){
    q->front=q->rear=(QN *)malloc(sizeof(QN));
    if (! q->front)
        exit(0);
    q->front->next=NULL;
    }

void INSERTQueue(QFR *q,Elemtype e){
    QN *p;
    p=(QN *)malloc(sizeof(QN));
    if(p == NULL)
        exit(0);
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
}

void DELETEQueue(QFR *q, Elemtype *e){
    
    QN *p;
    if (q->front == q->rear)
        return;
    p= q->front->next;
    *e = p->data;
    q->front->next = p-> next;
    if(q->rear==p)
        q->rear=q->front;
    free(p);
//要把每次的p-data save
}


void CLEANQueue(QFR* q){         //clear at the end
    while(q->front){
        q->rear=q->front->next;
        free( q->front);
        q->front=q->rear;
    }
}

int EMPTYQueue(QFR *q){        
    if (q->front==q->rear){
        return 1 ;
    }
    else{
        return 0 ;
    }
}


typedef struct Graph{
   int *vex;
   int **adj;
   int vexnumber;
}Graph;

Graph g;

typedef struct Path{
    int starN;
    int endN;
}Path;

void CGraph(){
    int i,j,k,a,vn,en,save,flag;
    int *e;
    
    scanf("%d",&vn);
    g.vexnumber=vn;
    

    getchar();
    k=0;
    a=0;
    j=0;
    flag=1;
    save=0;
    en=1;
    e = (int*) malloc (50*sizeof(int));
    for(i=0;k!='}';i++)
    {
        k=getchar();
        if (k=='<')
        {
            a++;
            en=a;
        }

        if(k>=48 && k<=57){
            if(flag==1){
                save=k-48;
            }
            if(flag==0){
                save=save*10+k-48;
            }
            flag=0;
        }
        else{
            if(flag==0){
                *(e+j)=save;
                e = (int *)realloc(e,2*en*sizeof(int)+1000);  
                save=0;
                j=j+1;
            }
            flag=1;
        }
    }
    
    g.vex=(int *)malloc(vn*sizeof(int));
    for(i=0;i<vn;i++){
        g.vex[i]=i;
    }
    
    g.adj=(int **)malloc(vn*sizeof(int*));
    for (j=0;j<vn;j++){
         g.adj[j] = (int *) malloc(sizeof(int) * vn);
    } 

    for(i=0;i<vn;i++){
        for(j=0;j<vn;j++){
            g.adj[i][j]=0;
        }
    }
    
    for (int a = 0; a <(2*en); ){
           i=e[a];
           j=e[a+1];
           *(*(g.adj+i)+j)=1;
           *(*(g.adj+j)+i)=1;
           a=a+2;
       }
    for(int m=0;m<vn;m++){
        for(int n=0;n<vn;n++){
            printf("%d ",g.adj[m][n]);
        }
        printf("\n");
    }
    }


void BFS(Graph g)
{                    
    int i,j,w;
    QFR Q;
    int *v;
    int *f;
    int path[g.vexnumber];
    Path p;
    
    scanf("%d",&p.starN);
    scanf("%d",&p.endN);

    v=(int *)malloc(g.vexnumber*sizeof(int));
    for(i=0;i<g.vexnumber;i++)
    {
        v[i]=FALSE;
    }
    
    f=(int *)malloc(g.vexnumber*sizeof(int));
   
    
    INITIALQueue(&Q);
    w=0;

    i=p.starN;
    if(!v[i]){
        v[i]=TRUE;
        INSERTQueue(&Q,i);

        
        while(!EMPTYQueue(&Q))
        {
            DELETEQueue(&Q,&i);
            for(j=0; j<g.vexnumber;j++){
                if(g.adj[i][j]==1 && !v[j])
                {
                    v[j]=TRUE;
                    f[j]=i;
                    //printf("f=%d,j=%d\n",f[j],j);
                    INSERTQueue(&Q,j);
                    if(j==p.endN){
                        path[w]=j;
                        w++;
                        //printf("path=%d",path[w]);
                        while(j!=p.starN){
                            path[w]=f[j];
                            j=f[j];
                            w++;
                            //printf("pathw=%d,j=%d,f=%d",path[w],j,f[j]);
                        } 
                        //path[w]=p.starN;
                        for(i=w-1;i>0;i--){
                            //printf("w=%d",w);
                            printf("%d",path[i]);
                            printf("%c",'-');
                        }
                        printf("%d",path[0]);
                        CLEANQueue(&Q);
                        return;
                    }
                }
            }
        }
    }
}

int main() 
{
    int t;
    int test;
    int i;
    while (TRUE){
        t=0;
        test=getchar();
        if (test=='V'){
            if (t!=0){
                for(i=0;i<g.vexnumber;++i)
                    free(g.adj[i]);
                free(g.adj);
                free(g.vex);
                g.adj=NULL;
                g.vex=NULL;
            }
            t++;
            CGraph();
        }
        if (test=='s'){
            BFS(g);
        }
    
    }
    return 0;
}
