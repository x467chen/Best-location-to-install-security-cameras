#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <unistd.h>


int main(int argc,char* argv[]) {
    char t;
    int r= open("/dev/urandom", O_RDONLY);
    int k;
    int a,b,c,d,a1,z1;
    int i,j,z,n;
    int x1,y1,x2,y2,x3,y3,x,y;
    double distance;
    char **st_name;
    int **coordinate;
    int loop_time,lt;
    int stnum,speed,xn,yn;
    
    read(r,&stnum,sizeof(int));
    a=stnum%9+2;   //number of st
    b=5;   //number of edge
    c=5;       //regenerate speed
    d=20;      //value of x,y
    
    for(i=1;i<argc;i+=2){
        if (strcmp(argv[i], "-s")==0) {
            strcpy(temp, argv[i+1]);
            k=atoi(temp);
            a=stnum%(k-1)+2;
        }else if(strcmp(argv[i],"-n")== 0){
            strcpy(temp, argv[i+1]);
            k=atoi(temp);
            b=k;
        }else if(strcmp(argv[i],"-l")== 0){
            strcpy(temp, argv[i+1]);
            k=atoi(temp);
            read(r,&speed,sizeof(int));
            c=speed%(k-4)+5;
        }else if(strcmp(argv[i],"-c")== 0){
            strcpy(temp, argv[i+1]);
            k=atoi(temp);
            d=k;
        }
    }
    
    st_name=(char **)malloc(a*sizeof(char*));
    for (j=0;j<a;j++){
        st_name[j] = (char *) malloc(sizeof(char) * 10);
    }
    
    coordinate= (int **) malloc(sizeof(int*) * a);
    for (j=0;j<a;j++){
        coordinate[j]= (int *) malloc(sizeof(int) * 2*b);
    }
    

    lt=0;
    loop_time=0;


    int sn=0;
    for(i=0;i<a;i++){
        printf("a \"");
        for(j=0;j<10;j++){
            read(r, &sn, sizeof(int));
            st_name[i][j]=abs(sn%26)+65;
            printf("%c",st_name[i][j]);
        }
        printf("\" ");

        read(r,&edgenum,sizeof(int));
        edgenum=abs(edgenum%b)+1;
        
        z=0;
        for(z=0;z<edgenum;){
            read(r,&xn,sizeof(int));
            read(r,&yn,sizeof(int));
            x=xn%(2*d+1)-d;
            y=yn%(2*d+1)-d;

            if(a==0 && z==0){
                coordinate[0][0]=x;
                coordinate[0][1]=y;
                z=z+2;
                lt=0;
            }else if(a==0 && z==2){
                if((x!=coordinate[0][0]||y!=coordinate[0][1])||(y!=coordinate[0][0]||x!=coordinate[0][1])){
                    coordinate[0][2]=x;
                    coordinate[0][3]=y;
                    z=z+2;
                    lt=0;
                }
                else{
                    z=z;
                    lt=lt+1;
                    if(lt>=26){
                        printf("Fail to generate map");
                        break;
                    }
                }
            }
            else{
                a1=a;
                z1=z;
                for(;a1>=0;a1--){
                    for(;z1-4>=0;){
                        x1=coordinate[a1][z1-4];
                        y1=coordinate[a1][z1-3];
                        x2=coordinate[a1][z1-2];
                        y2=coordinate[a1][z1-1];
                        x3=x;
                        y3=y;
                        distance=sqrt((x1-x2)^2+(y1-y2)^2)-(sqrt((x1-x3)^2+(y1-y3)^2)+sqrt((x3-x2)^2+(y3-y2)^2));
                        if(distance==0){
                            z=z;
                            loop_time=loop_time+1;
                            if(loop_time>=26){
                                printf("Fail to generate map");
                                break;
                            }
                            continue;
                        }
                        else{
                            z1=z1-2;
                        }
                    }
                    z1=2*b;
                }
                loop_time=0;
                coordinate[a][z]=x;
                coordinate[a][z+1]=y;
            }
        }
        for(n=0;n<b;n+=2){
            printf("(%d,%d) ",coordinate[a][n],coordinate[a][n+1]);
        }
        printf("\n");
    }
    free(coordinate);   //need loop to free
    free(st_name);
    printf("g\n");
    sleep(c);
    return 0;
}

            
            
            
            
            

