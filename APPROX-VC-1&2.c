#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int vexnumber;
int *e;
int en;

void CreatG(void){
    int i,j,k,a,vn,save,flag;
    
    scanf("%d",&vn);
    vexnumber=vn;
    
    
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
}

void *VC1(){
    int i,j,temp;
    int c1[2][vexnumber];
    int t;
    int p[15];
    int e1[2*en];
    
    for(i=0;i<en*2;i++){
        e1[i]=e[i];
    }
    
    for(i=0,j=0;j<vexnumber;j++){
        c1[i][j]=j;
    }
  
    for(i=1,j=0;j<vexnumber;j++){
        c1[i][j]=0;
    }
        
    for(i=0;i<2*en;i++){
        c1[1][e1[i]]=c1[1][e1[i]]+1;     //算出每个点的重复数
    }
    
    

    
    
    for (i = 0; i < (vexnumber - 1); i++)       //冒泡排序
    {
        for (j = 0; j < vexnumber - 1 - i; j++)
        {
            if (c1[1][j] < c1[1][j + 1])
            {
                temp = c1[0][j + 1];
                c1[0][j + 1] =c1[0][j];
                c1[0][j] = temp;
                
                temp = c1[1][j + 1];
                c1[1][j + 1] =c1[1][j];
                c1[1][j] = temp;
            }
        }
    }
    
    t=en;
    int time=0;
    int w;
    for(i=0;i< vexnumber;i++){
        for(j=0;j<en*2;j+=2){
            if(((c1[0][0]==e1[j]) || (c1[0][0]==e1[j+1])) && !((e1[j]==0) && (e1[j+1]==0))&& t>0){
                t=t-1;
                e1[j]=0;
                e1[j+1]=0;
                if(t==0){
                    for(w=0;w<time;w++)
                        printf("%d ",p[w]);
                    printf("%d ",c1[0][0]);
                    printf("\n");
                    return NULL;
                }
            }
        }
        p[time]=c1[0][0];
        time=time+1;
        
        
        int i1,j1;
        for(i1=1,j1=0;j1<vexnumber;j1++){
            c1[i1][j1]=0;
        }
        
        for(i1=0,j1=0;j1<vexnumber;j1++){
            c1[i1][j1]=j1;
        }
        
        int x,z,z1;
        for(x=0;x<en*2;x+=2){
            if(!((e1[x]==0) && (e1[x+1]==0))){
                c1[1][e1[x]]=c1[1][e1[x]]+1;
                c1[1][e1[x+1]]=c1[1][e1[x+1]]+1;
            }
        }

        for ( z = 0; z < (vexnumber - 1); z++)       //冒泡排序
        {
            for (z1 = 0; z1 < vexnumber - 1 - z; z1++)
            {
                if (c1[1][z1] < c1[1][z1 + 1])
                {
                    temp = c1[0][z1+ 1];
                    c1[0][z1 + 1] =c1[0][z1];
                    c1[0][z1] = temp;
                    
                    temp = c1[1][z1 + 1];
                    c1[1][z1 + 1] =c1[1][z1];
                    c1[1][z1] = temp;
                }
            }
        }
    }
    return NULL;
}

void *VC2(){
    int i,j,a,b,t;
    int e2[2*en];
    
    for(i=0;i<en*2;i++){
        e2[i]=e[i];
    }
    
    t=en;
    for(i=0;i< 2*en;i+=2){
        if(!((e2[i]==0) && (e2[i+1]==0))){
            a=e2[i];
            b=e2[i+1];
            printf("%d %d ",a,b);
            
            for(j=0;j<en*2;j+=2){
                if(((e2[j]==a)||(e2[j]==b)||(e2[j+1]==a) || (e2[j+1]==b)) && !((e2[j]==0) && (e2[j+1]==0))){
                    t=t-1;
                    e2[j]=0;
                    e2[j+1]=0;
                    if(t==0){
                        printf("\n");
                        return NULL;
                    }
                
                }
            }
        }
    }
    return NULL;
}


int main(){
    int t;
    int test;
    int ret;
    pthread_t id_2,id_3;
    while (1){
        t=0;
        test=getchar();
        if (test=='V'){
            if (t!=0){
                free(e);
                e=NULL;
            }
            t++;
            CreatG();

            ret=pthread_create(&id_2,NULL,VC1,NULL);
            if(ret!=0)
            {
                printf("Create pthread error!\n");
                return -1;
            }
            pthread_join(id_2,NULL);
            
            ret=pthread_create(&id_3,NULL,VC2,NULL);
            if(ret!=0)
            {
                printf("Create pthread error!\n");
                return -1;  
            }
            pthread_join(id_3,NULL);
        }
    }
    return 0;
}



