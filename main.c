#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>


int main(int atgc, char **argv)
{

initscr();
clear();

    int arr_length,arr_width,iter,speed;

//if nothing (or 'h' as in help) is passed, instructions on how to use the program will appear.
  if(argv[1]==NULL || *argv[1]=='h'){
  printf("rtfm");
  endwin();
  return 0;
  };

    char mode=' ';

//if g is passed, program will enter glider mode
    if(*argv[1]=='g'){
12
        getch();
        printw("glider mode\n");
        refresh();
        getch();
        mode='g';

        };

//if this argument is passed, program wil enter 'six-by-six' mode
    if(*argv[1]=='6'){

        getch();
        printw("six by six mode\n");
        refresh();
        getch();
        mode='6';

        };

    if(argv[1]!=NULL && *argv[1]!='6' && *argv[1]!='g' && *argv[1]!='m'){
        endwin();
        printf("Invalid argument. Please, pass 'h' for more info.");
        return 1;
    };

//array dimensions and number of iterations depend on mode. the speed of screen refreshing is also set
    if(mode=='g')arr_length=50,arr_width=50,iter=50,speed=500000;
    if(mode=='6')arr_length=30,arr_width=30,iter=30,speed=500000;

    int M,N,x,y;
    M=arr_width,N=arr_length;
    int o[M][N],n[M][N];


    //a loop to initialise both old and new array
    int i,k;
    for(i=N-1;i>=0;i--){
        for(k=0;k<M;k++){
            o[i][k]=0,n[i][k]=0;
            };
    };

    if(mode=='g'){
        //now netering glider mode
        o[(M/2)-1][(N/2)+1]=1;
        o[M/2][N/2]=1;
        o[(M/2)+1][N/2]=1;
        o[(M/2)-1][(N/2)-1]=1;
        o[M/2][(N/2)-1]=1;
    };

    if(mode=='6'){
        //now entering six by six mode
        for(i=(N/2)+2;i>=(N/2)-2;i--){
            for(k=(M/2)-2;k<=(M/2)+2;k++){
                o[k][i]=1;
            };
        };
    };


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
			/*
			if(live_count==4){
				return live_count;
				break;
			};
			*/
		};

		if(o[x][y+1]==1)live_count++;
		if(o[x][y-1]==1)live_count++;

		return live_count;
	};


//###################################LET'PARTY##############################################################


    initscr();
    clear();

    //print the original array to show the state of system at t=0
    for(i=N;i>=0;i--){
            for(k=0;k<M;k++){
                if(o[k][i]==1)mvaddch(i,k,'*');
                else(mvaddch(i,k,' '));

                refresh();
            };
        };

    refresh();
    usleep(speed*2);

    int t;
	for(t=0;t<iter;t++){

    clear();

        if(t==N||t==M)break;

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

                if(n[k][i]==1)mvaddch(i,k,'*');
                else(mvaddch(i,k,' '));

            };

        };

        refresh();
        usleep(speed);
        //getch();


		//new array is now the old one
		for(y=N;y>=0;y--){
			for(x=0;x<M;x++){
				o[x][y]=n[x][y];
			};
		};


	};

    //clear();
    //getch();
    mvprintw(18,40,"* * * E N D * O F * A R R A Y * R E A C H E D * * *");
    refresh();
    getch();

    endwin();

    return 0;
};

