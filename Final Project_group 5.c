/*Group 5:
1. Muhammad Ariq Nugroho (1706020282)
2. Rama Aryarakhito Wongso (1706020616)
link github: 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

struct node
{
    char infoPoint[90];// score
    struct node *ptr;
}*front,*front1,*rear,*temp;

void board();
void bombDisplay();
void enqueue();
void displayQ();
int checkboard(int choice);

char bombdetector[100][100],userName[100][100],nam[255];
int direction[100][100], bombplace[100][100], point=0, difficulty=0;

int main()
{
	int x=0, i, j, k, m, init=1, randomNum, choice, win,main,breaker=0,digit,namDigit=0;
	double duration;
	char username[10], temp[100]; 
	front = rear = NULL;
	
	FILE *fptr;// For scoreboard part number/score //declare fptr
   	
	fptr = fopen("scoreboard.txt","r"); // open file for number // r=read
   	while ( fgets ( nam, sizeof nam, fptr ) != NULL ) //cara ngambil data dr text
	{
		enqueue();// masukan data ke linkedlist (data = name, score & time)
	}
    fclose(fptr);// nutup
    
	system("color F3");
	
	
	OPENING:
	printf("\n\n\t\t\t\t-----------------\n");
   	printf("\t\t\t\t---MINESWEEPER---\n");
   	printf("\t\t\t\t-----------------\n");
	printf ("HELLO THERE.... Welcome to the best minesweeper game ever\n");
	printf ("PLEASE STAY AWAY FROM MINES IF YOU WANT TO WIN THE GAME\n");
	
	printf("[1]NEW GAME!\n[2]SCOREBOARD\n[3]EXIT\n");
	printf("\nChoose one number:");
	scanf("%d", &main);
	if (main==1)
	{
		printf("Please enter username (max 10 characters) : ");
		scanf("%s", &username);
		goto CHECKPOINT;
	}
	else if(main==2)
	{
		printf("USERNAME      Score        Time\n");
		displayQ();
		printf("\n");
		system ("pause");
		system ("cls");
		goto OPENING;
	}
	else if(main==3)
	{
		return 0;
	}
	else
	{
		printf("\nyou should enter a number between 1-3!\nTRY AGAIN\n");
		system("cls");
		goto OPENING;
	}
	CHECKPOINT:
	while (x==0)
	{		
		system("cls");
		printf("1. Easy (12 bombs)\n2. Medium (24 bombs)\n3. Hard (36 bombs)\n\n");
		printf ("HINT : In easy level, the score will multiplied by 1\n");
		printf ("       In medium level, the score will multiplied by 2\n");
		printf ("       In hard level, the score will multiplied by 3\n");
	
	
		printf("please select a difficulty:");
		scanf("%d", &difficulty);
		
		if(difficulty==1||difficulty==2||difficulty==3)
		{
			x++;
		}
		else
		{
			printf("you should enter a number between 1-3!");
			system("pause");
		}
	}
	/*init*/
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			direction[i][j] = init;
			bombdetector[i][j] = '0';
			bombplace[i][j] = 0;
			init++;
		}
	}
	
	srand(time(NULL));
	
	for(i=0; i<12*difficulty; i++)
	{
		/*init bomb*/
		randomNum=rand()%100;
		if(randomNum==0)
		{
			randomNum++;
		}
		
		/*place bomb*/
		for(k=0; k<10; k++)
	{
		for(j=0; j<10; j++)
		{
			if(direction[k][j] == randomNum)
			{
				if(bombplace[k][j] == 1)
				{
					breaker = 1;
					break;
				}
				else
				{
					bombplace[k][j] = 1;
				}
			}
		}
		if(breaker == 1)
		{
			breaker = 0;
			i--;
			break;
		}
	}
	}

	time_t begin = time(NULL);//start counting time
	board();
	do
	{
	back:
	system("cls");
	board();	
	printf ("HINT : a there are 1 bomb around\n");
	printf ("       b there are 2 bombs around\n");
	printf ("       c there are 3 bombs around etc.\n");
	printf ("input 0 to display bombs");
	printf("\n\nPlease input one of the number above: \n");
	scanf(" %d", &choice);
	if(choice<0 || choice>100)
	{
		printf("Invalid Input!");
		getch();
		system("cls");
		goto back;
	}
	else if(choice==0)
	{	
		bombDisplay();
		system("pause");
		goto back;
	}
	
	
	win = checkboard(choice);
	
	}while(win == -1);// kalo menang baru masuk while nya, 
	board();
	if(win==1)
	{
		switch(difficulty)
		{
			case 1:
			point += 12;
			break;
			
			case 2:
			point += 24;
			break;
			
			case 3:
			point+= 36;
			break;
			 
		}
		time_t end = time(NULL);//ngambil waktu dr laptop
		duration = (double)(end - begin);// durasi main
		printf("your playing time is = %.1f", duration);
		printf("\nYour Score is = %d\n", point);
		printf ("You win the game, %s!!!!!!!!!! ", username);
		
	}
	else
	{
		bombDisplay();
 
		printf("\n    _.-^^---....,,-- \n");
		printf("_--                  --_\n");
		printf("<                        >)\n");
		printf("<     BOOOOOOOMMMMM      >)\n");
		printf("|                         |\n");
		printf("   ```--. . , ; .--'''\n");
		printf("	| |   |       \n");
		printf("	| |   |             \n");
		printf("	| |   |  \n");
		printf("     .-=||  | |=-.\n");
		printf("     `-=#$%&%$#=-' \n");
		printf("	| ;  :| \n");
		printf("_____.,-#%&$@%#&#~,._____\n");
		time_t end = time(NULL);
		duration = (double)(end - begin);
		printf("\nYOU LOSE, %s!, you just stepped on the bomb\n\n", username);
		printf("your playing time is = %.1f seconds", duration);
		printf("\nYour Final Score is = %d\n", point);
	}
	
	
   	fptr = fopen("scoreboard.txt","w+");// bakal overwrite kalo udh ada isinya, ngeganti data yg lama jadi yg baru
	front1 = front;
	while(front1 != NULL)
    {
        fprintf(fptr,"%s",front1->infoPoint);// print data ke scoreboard text
        front1 = front1->ptr;//data 1 diganti ke data 2
    }
    fprintf(fptr,"\n%s\t\t%d\t%.1f seconds",username, point, duration);//print data terbaru
	fclose(fptr);
	
	system("pause");
	system("cls");
	return 0;
}

void board()
{
	int i,j;
	system("cls");
	
	printf("\n\n\t\t\t\t-----------------\n");
    printf("\t\t\t\t---MINESWEEPER---\n");
    printf("\t\t\t\t-----------------\n");
	printf("       ");
	for(j=0; j<10; j++)
		{
    		printf("_____  "); 
    		if(j==9)
    		{
				printf("\n");
			}
		}
		
	for(i=0; i<10; i++)
	{
		printf("      |");
		for(j=0; j<10; j++)
		{
			if(direction[i][j] != 1000 && direction[i][j] < 10) /* if the number not 1000, it will print the direction based on its value (0-9) */
			{
				printf("  %d  | ", direction[i][j]);
    		}
    		
    		else if(direction[i][j] != 1000 && direction[i][j] < 100) /* if the number not 1000, it will print the direction based on its value (10-99) */
			{
				printf("  %d | ", direction[i][j]);
    		}
    		
    		else if(direction[i][j] != 1000 && direction[i][j] < 1000) /* if the number not 1000, it will print the direction based on its value (100) */
			{
				printf(" %d | ", direction[i][j]);
    		}
    		
    		else
    		{
    			printf("  %c  | ", bombdetector[i][j]); /* if the coordinate changes into 10000, it will print into bombdetector */
			}
		}
		printf("\n");
		printf("       ");
		for(j=0; j<10; j++)
		{
    		printf("_____  ");
    		if(j==9)
    		{
				printf("\n");
			}
		}
	}
}

int checkboard(int choice)
{
	char a;
	int i,j,k=0,aman=0;
	for(i=0; i<10; i++) /* There are 2 loops bcs its multi dimentional */
	{
		for(j=0; j<10; j++)
		{
			
			if(direction[i][j] == choice) /* if our choice is the same like the directional then proceed to next step */
			{
				if(bombplace[i][j] == 1) /* Finding the bomb in the coordinate that we choose, this if used to if there is a bomb*/
				{
					bombdetector[i][j] = 'X';
					return 0;
				}
				
				else /* if there is no bomb */
				{
					direction[i][j] = 1000; /* There are will be no same coordinate bcs change to 1000 */
					bombdetector[i][j] = ' ';
					point += 1*difficulty;
					k=1;
				}
			}
			if(k == 1) /* Next if is to find if there is a bomb near the coordinate */
			{
			a='00';/* to show the hint ex:(a,b,c,d) */
			
				/*Cek Atas Kiri*/
				
				if(bombplace[i-1][j-1] == 1)
				{
					a++;
				}
				
				/*Cek Atas*/
				if(bombplace[i-1][j] == 1)
				{
					a++;
				}
				
				/*Cek Atas Kanan*/
				if(bombplace[i-1][j+1] == 1)
				{
					a++;
				}
				
				/*Cek Kiri*/
				if(bombplace[i][j-1] == 1)
				{
					a++;
				}
				
				/*Cek Kanan*/
				if(bombplace[i][j+1] == 1)
				{
					a++;	
				}
				
				/*Cek Bawah Kiri*/
				if(bombplace[i+1][j-1] == 1)
				{
					a++;
				}
				
				/*Cek Bawah*/
				if(bombplace[i+1][j] == 1)
				{
					a++;
				}
				
				/*Cek Bawah Kanan*/
				if(bombplace[i+1][j+1] == 1)
				{
					a++;
				}
				if(a=='`') /* if there are no bombs around the coordinate it will stay at " " */
				{
					a=00; /*  */
				}
				bombdetector[i][j] = a;
			 k=0;	
			}
			k=0;
			
		}
	}
	
	
	
	/*Cek win*/
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			if(direction[i][j] == 1000)
			{
				aman++;
			}
		}
	}
	
	if(aman == 88)
	{
		return 1;
	}
	
	return -1;
}

void bombDisplay()
{
	int i,j;
	system("cls");
	printf("       ");
	for(j=0; j<10; j++)
		{
    		printf("_____  "); 
    		if(j==9)
    		{
				printf("\n");
			}
		}
		
	for(i=0; i<10; i++)
	{
		printf("      |");
		for(j=0; j<10; j++)
		{
			if(bombplace[i][j] == 1)
    			printf("  X  | "); /* Display Bomb*/
    			
    		else
    		printf("     | ");
		}
		printf("\n");
		printf("       ");
		for(j=0; j<10; j++)
		{
    		printf("_____  ");
    		if(j==9)
    		{
				printf("\n");
			}
		}
	}
}

void enqueue()// nambahin data ke linked list
{
    if (rear == NULL)// gaada apa"
    {
        rear = (struct node *)malloc(1*sizeof(struct node));// ngasih alokasi memori ke rear
        rear->ptr = NULL;// rear pointer ngarahin ke null// linked list ditambah data baru
        strcpy(rear->infoPoint,nam);//copy dr kanan ke kiri
        front = rear;// udh keisi 
    }
    else// kalo udh ada data antrian nnti nambah ke belakang trus jd rear
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        strcpy(temp->infoPoint,nam);//
        temp->ptr = NULL;
        rear = temp;
    }
}

void displayQ()//utk display liked list n array
{
    front1 = front;
 
    if ((front1 == NULL) && (rear == NULL))
    {
        printf("Board is empty\n");
        return;
    }
    while (front1 != NULL)
    {
        printf("%s", front1->infoPoint);//print isi infopoint
        front1 = front1->ptr;
    }
}
