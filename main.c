#include <stdio.h>


int main()
{
    int M,N,O,P,x,y;
    M=20,N=20,O=20,P=20;
    int o[M][N], n[O][P];
    
    //a loop to initialise both old and new array
    int i,k;
    for(i=N;i>=0;i--){
        for(k=0;k<N;k++){
            o[i][k]=0,n[i][k]=0;
        };
    };
    
    //now netering glider mode
    o[9][11]=1;
    o[10][10]=1;
    o[11][10]=1;
    o[9][9]=1;
    o[10][9]=1;
    
	//a function that checks whether a dead cell can become alive. Returns 1 if cell wil become alive.
	// Returns 0 if cell will remain dead.
	int chck_dead (int x, int y){
		int live_count,l,m;
		live_count=0;
		
		for(l=x-1,m=y-1;m<=y+1;m++){
			if(o[l][m]==1)live_count++;
		};
		
		for(l=x+1,m=y+1;m>=y-1;m--){
			if(o[l][m]==1)live_count++;
			if(live_count<=3){
				break;
				return 1;
			};
		};
		
		if(o[x][y+1]==1)live_count++;
		if(o[x][y-1]==1)live_count++;
		
		if(live_count>=3){
			return 1;
		};
		return 0;
	};
	
	//a function that counts
	
	//a loop to create new array
	
	for(y=N;y>=0;y--){
        for(x=0;x<M;x++){
			
			n[x][y]=o[x][y];
			
			if(o[x][y]==0){
				
				n[x][y]=chck_dead(x,y);
			};
			 
			if(o[x][y]==1){
				n[x][y]=o[x][y];
			};
			
        };
    };
	
	
    //a loop to print the array
    
    for(i=N;i>=0;i--){
        for(k=0;k<M;k++){
            if(n[k][i]==1)printf("@");
            if(n[k][i]==0)printf("°");
        };
        printf("\n");
    };
    
};
