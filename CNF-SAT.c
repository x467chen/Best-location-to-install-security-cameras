#include <stdio.h>
#include "SAT.h"
#include <stdlib.h>
#include <string.h>
#define TRUE 1



int vexnumber;
int *e;
int en;

void CreatG(){
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


void CNFSAT(){
    int n,k;
    int i,j,x;
    n=vexnumber;
    k=vexnumber;
    
    SAT_Manager mgr = SAT_InitManager();
    SAT_SetNumVariables(mgr, n*k);
    
    int c[n];
    for(i=0;i<k;i++){
        for(j=1;j<=n;j++){
            for(x=0;x<n;x++){
                c[x]=((i*k+j)<<1);
            }
        }
        SAT_AddClause(mgr,c,n);
    }
    
    
    for(i=0;i<n;i++){
        for(j=1;j<k;j++){
            for(x=1;x<=(k-j);x++){
                c[0]=((i*k+j)<<1)+1;
                c[1]=((i*k+j+x)<<1)+1;
                SAT_AddClause(mgr,c, 2);
            }
        }
        
    }
    
    for(i=1;i<=k;i++){
        for(j=0;j<n;j++){
            for(x=1;x<(n-j);x++){
                c[0]=((i+j*k)<<1)+1;
                c[1]=((i+j*k+x*k)<<1)+1;
                SAT_AddClause(mgr,c, 2);
            }
        }
    }
    
  
    int c1[2*k];
    for(i=0;i<en;){
        for(j=1;j<=k;j++){
            c1[j-1]=((e[i]*k+j)<<1);
            c1[j-1+k]=((e[i+1]*k+j)<<1);
        }
        SAT_AddClause(mgr,c,2*k);
        i=i+2;
    }
    
    int result = SAT_Solve(mgr);
    dup2(bak, STDOUT_FILENO);
    if(result == SATISFIABLE) {
        printf("sat: "); fflush(stdout);
        int n = SAT_NumVariables(mgr);
        
        for(i = 1; i <= n; i++) {
            int a = SAT_GetVarAsgnment(mgr, i);
            if(a == 1) {
                printf("%d ", i); fflush(stdout);
            }
            else if(a == 0) {
                printf("%d ", -1*i); fflush(stdout);
            }
            else {
                printf("Error!"); fflush(stdout);
            }
        }
        printf("\n"); 
    }
    else {
        printf("unsat.\n"); fflush(stdout);
    }
}

int main(){
    int t;
    int test;
    while (TRUE){
        t=0;
        test=getchar();
        if (test=='V'){
            if (t!=0){
                free(e);
                e=NULL;
            }
            t++;
            CreatG();
            CNFSAT();
        }
    }
    return 0;
}
