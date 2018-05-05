//#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>


int main(int atgc, char **argv)
{

    initscr();
    clear();

//these variables are set to 0. This will be useful when setting up the manual mode.
    int arr_length=0,arr_width=0,iter=0,speed=0;

//this is essentially a list of allowed arguments
if(argv[1]!=NULL && *argv[1]!='6' && *argv[1]!='g' && *argv[1]!='m' && *argv[1]!='h' && *argv[1]!='c'){
        endwin();
        printf("Invalid argument. Please, pass 'h' for more info.");
        return 1;
    };

//if nothing (or 'h' as in help) is passed, instructions on how to use the program will appear.
  if(argv[1]==NULL || *argv[1]=='h'){

      mvprintw(0,COLS/2-10,"Hello and welcome to");
      refresh();
      usleep(1000000);

      mvprintw(LINES/2-2,COLS/2-14,">>>CONWAY'S GAME OF LIFE<<<");
      refresh();
      usleep(1000000);
      mvprintw(LINES/2,COLS/2-20,"*please maximize your terminal window NOW*");
      //mvprintw(LINES/2+1,COLS/2-15,"*(gnome-terminal --set-fulscreen)*");
      mvprintw(LINES/2+2,COLS/2-20,"*if allready full screen, press any key*\n");
      refresh();
      getch();

      mvprintw(LINES/2+5,COLS/2-15,"---press any key to continue---\n");
      getch();

      clear();

      mvprintw(LINES/2+2,0,"In 1970 mathematician John Horton Conway devised a cellular automaton, using the following rules:\n");
      refresh();
      usleep(2000000);
      mvprintw(LINES/2+4,0,"Each empty or 'dead' cell bordering exactly three living cells will become alive in the next iteration.\n");
      refresh();
      usleep(3000000);
      mvprintw(LINES/2+5,0,"Each living cell bordering two or three other living cells will survive in the next iteration.\n");
      refresh();
      usleep(3000000);
      mvprintw(LINES/2+6,0,"Each living cell bordering less than three or more than four living cells will not survive in the next iteration.\n");
      refresh();
      usleep(3000000);
      mvprintw(LINES/2+8,COLS/2-15,"---press any key to continue---\n");
      refresh();
      getch();

      clear();
      mvprintw(LINES/2-4,COLS/2-32,"Pass the following arguments to run the game in different modes:");
      refresh();

      mvprintw(LINES/2-2,COLS/2-13,"    g    for glider mode");
      mvprintw(LINES/2,COLS/2-13,"    6    for six-by-six mode");
      mvprintw(LINES/2+2,COLS/2-13,"    m    for manual mode");
      mvprintw(LINES/2+4,COLS/2-13,"    c    for Corder engine mode");
      mvprintw(LINES/2+8,COLS/2-15,"---press any key to continue---");
      getch();

      endwin();
      return 0;
      };

    char mode=' ';

//if g is passed, program will enter glider mode
    if(*argv[1]=='g'){

        printw("You have chosen /G/L/I/D/E/R/ MODE!\n");
        printw("\n");
        printw("---press any key to continue---\n");
        refresh();
        getch();
        mode='g';

        };

//if this argument is passed, program wil enter 'six-by-six' mode
    if(*argv[1]=='6'){

        printw("You have chosen SIX*BY*SIX mode!\n");
        printw("\n");
        printw("---press any key to continue---\n");

        refresh();
        getch();
        mode='6';

        };

//if this argument is passed, program will enter Corder engine mode
    if(*argv[1]=='c'){

        mode='c';

        printw("You have chosen C~O~R~D~E~R ~ E~N~G~I~N~E mode.\n");
        printw("Corder engine is a special structure that replicates itself every 48 iterations\n");
        printw("\n");
        printw("---press any key to continue---\n");

        refresh();
        getch();

        }

    //array dimensions, speed of screen refreshing and number of iterations depend on whether program is in manual mode, or in other modes.
    if(mode=='g'||mode=='6')arr_length=LINES,arr_width=COLS,iter=LINES+(LINES/2),speed=500000;
    if(mode=='c')arr_length=LINES,arr_width=COLS,iter=200,speed=500000;

  //manual mode lets the user customize the game. Rest of the code for manual mode is below the code for arrays initialisation
    if(*argv[1]=='m'){

        mode='m';

        printw("You have chosen the [M][A][N][U][A][L] mode! This mode is for true conoisseurs because it alows you to customize the game to a much bigger extent.\n");
        printw("Please follow the instructions on terminal.\n");
        printw("\n");
        printw("---press any key to continue---\n");
        getch();

        clear();
        mvprintw(0,COLS/2-22,"What should the dimensions of your array be?\n");
        refresh();
        usleep(2000000);

        mvprintw(1,COLS/2-30,"Enter array width (cols, x axis) and length (rows, y axis).\n");
        refresh();
        usleep(2000000);

        mvprintw(2,COLS/2-32,"But #BEWARE#! If the dimensions exceed the size of your terminal,\n");
        mvprintw(3,COLS/2-20,"the game will not be displayed correctly.\n");
        while(arr_width==0 || arr_length==0){
            scanw(" %d %d",&arr_width,&arr_length);
            };

        mvprintw(4,COLS/2-24,"How many iterations should the program execute?\n");
        scanw(" %d",&iter);

        mvprintw(5,COLS/2-44,"How long should system at one state be displayed for? Enter the time (in microseconds)\n");
        while(speed==0){
            scanw(" %d",&speed);
        };

    };


    int M,N,x,y;
    N=arr_length,M=arr_width;
    int o[M][N],n[M][N];


    //a loop to initialise both old and new array
    int i,k;
    for(i=N-1;i>=0;i--){
        for(k=0;k<M;k++){
            o[k][i]=0,n[k][i]=0;
            };
    };

    //this cycle allows user to define the initial state of system manually
    if(mode=='m'){

        mvprintw(6,COLS/2-17,"Now define your own initial state:\n");
        refresh();
        usleep(2000000);

        mvprintw(7,COLS/2-39,"enter x and y coordinates of every cell that should be alive in the beginning.\n");
        refresh();
        usleep(2000000);

        mvprintw(8,COLS/2-20,"When done, press the Enter key t_w_i_c_e.\n");
        refresh();

//apparently, if user hits Enter key twice scanw() return ERR
        while(scanw(" %d %d",&x,&y)!=ERR){
            o[x][y]=1;
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

    if(mode=='c'){
        //now entering switch engine mode

        o[M/2-2][N/2-1]=1;
        o[M/2][N/2-1]=1;
        o[M/2-3][N/2]=1;
        o[M/2-2][N/2+1]=1;
        o[M/2+1][N/2+1]=1;
        o[M/2][N/2+2]=1;
        o[M/2+1][N/2+2]=1;
        o[M/2+2][N/2+2]=1;
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

			if(live_count==4){
				return live_count;
				break;
			};

		};

		if(o[x][y+1]==1)live_count++;
		if(o[x][y-1]==1)live_count++;

		return live_count;
	};


//#######################################################PRINTING TO OUTPUT############################################################


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

        clear();
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

        //the 'living' cells may not reach out of the array. If it happens, information be stored in variable 'state'.
				for(i=N-1;i>=0;i=i-(N-1)){
                    for(k=0;k<M;k++){
                        if(o[k][i]==1 || o[i][k]==1){
                        mvprintw(18,40,"* * * E N D * O F * A R R A Y * R E A C H E D * * *");
                        refresh();
                        getch();
                        endwin();

                        return 1;
                        };
                    };
                };

	};

    //this will inform the user whether the rpogram
    mvprintw(18,COLS/2-12,"* * * E N D * O F * I T E R A T I O N * * *");
    refresh();
    getch();
    endwin();
    return 0;

};

