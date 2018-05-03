#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>


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
		};

		if(o[x][y+1]==1)live_count++;
		if(o[x][y-1]==1)live_count++;

		if(live_count==3){
			return 1;
		};
		return 0;
	};

	//a function that counts all living cells around a specific position in old array
	int count_cells(int x, int y){

		int live_count,l,m;
		live_count=0;

		for(l=x-1,m=y-1;m<=y+1;m++){
			if(o[l][m]==1)live_count++;
		};

		for(l=x+1,m=y+1;m>=y-1;m--){
			if(o[l][m]==1)live_count++;
			if(live_count==4){
				return live_count;
				break;
			};
		};

		if(o[x][y+1]==1)live_count++;
		if(o[x][y-1]==1)live_count++;

		return live_count;
	};

    initscr();


     //the original array has to be printed in order to show state of system at t=0
        for(i=N;i>=0;i--){
                for(k=0;k<M;k++){
                    if(o[k][i]==1)mvaddch(i,k,'#');
                    else(mvprintw(i,k,"/"));
                };
            };

        refresh();
        getch();

//###################################LET'PARTY##############################################################
    int a;
	for(a=0;a<20;a++){

		//a loop to create new array
		for(y=N;y>=0;y--){
			for(x=0;x<M;x++){

				if(o[x][y]==0){
					n[x][y]=chck_dead(x,y);

				};

				if(o[x][y]==1){
					int cells;
					cells=count_cells(x,y);

					if(cells<=1 || cells>=4)n[x][y]=0;
					else(n[x][y]=1);
				};

			};
		};


		//a loop to print new array

        for(i=N;i>=0;i--){
            for(k=0;k<M;k++){

                addch(' '|A_REVERSE);
                if(n[k][i]==1){move(i,k);addch('#');}
                else(mvprintw(i,k," "));

            };

        };

		//new array is now the old one
		for(y=N;y>=0;y--){
			for(x=0;x<M;x++){
				o[x][y]=n[x][y];
			};
		};

		//getch();
		refresh();
        usleep(100000);

	};

	endwin();
    return 0;
};



