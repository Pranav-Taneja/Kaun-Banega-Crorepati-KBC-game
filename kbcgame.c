//KBC game using C
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fp1;//file position pointer to ques file
FILE *fp2;//file position ptr to 5050 ques file

int i=0;//serves as question counter
int prize=0;//prize money counter
int lbprize=0;//level base prize earned
int chk=1;//sets to zero when a user answers wrong

char uans[30];//string entered by user as the ans

//initialising counters that record if a lifeline has been used
int avail50=1;
int availflip=1;

//declaration and initialisation of an array of question structures
struct ques
{
	char que[100];//question string
	char opta[30],optb[30],optc[30],optd[30];//option strings
};

struct ques q[13];//12 questions to be played, 13th element for the provision of ques flip
struct ques q5050[13];//array of question structures with wrong options replaced by blank

char ans[13]={'d','c','c','b','a','b','c','d','b','a','a','d','b'};//array of correct choices

void cont();//continues the game on pressing 'enter'
void alloclb();//allocates level base prize earned
void initques();//initialises the array of question structures
void initques5050();//initialises questions with two options set to blank
void showques();//presents the questions in game
void life50();//facilitates 50-50 lifeline 
void quesflip();//facilitates flip the question lifeline
void checkans();//checks the user input and executes suitable functions to continue the game
void game();//logically assembles the constituent functions to form the game 
void congrat();//prints congratulating message on completing the game

int main()
{
	printf("\t\t\tWelcome to KBC\n\n\n");

	printf("\tThe game comprises of 12 questions\n");
	printf("\tEach question carries a prize money of 10 lac rupees\n");
	printf("\tThe questions are divided into 3 levels\n");
	printf("\tIf you answer any question wrong,\n");
	printf("\tYou will take back the level base prize only\n");
	printf("\tQ4 is the base for level-2, Q8 for level-3\n");
	printf("\tAnswering wrong in level-1 fetches no prize\n");
	printf("\tYou have two lifelines, 50-50 and question-flip\n");
	printf("\t50-50 will remove two wrong options\n");
	printf("\tquestion-flip will change the ques\n");
	printf("\tYou can only use them once each\n\n\n");
	
	printf("\t\tPress enter key to continue\n\n");
    
    cont();
    
    printf("\t\tGameplay Instructions\n\n");
    
    printf("\tTo answer, input the option index and press enter\n");
    printf("\tfor example, to choose option a\n"); 
    printf("\tpress 'a' followed by enter\n");
    printf("\tInputting a string of characters is not supported\n");
    printf("\tOnly answer by chosing options as told above\n");
    printf("\tThe lifelines are given as option e and f\n\n");
    
    printf("\t\tPress enter key to continue\n\n");
    
	cont();
	
	initques();//filling the question structure array from ques file
	initques5050();//filling the 5050 ques structure array
	
	game();//starts the game
	
	if(chk!=0)//chk would remain non zero after game if all are answered correct
		congrat();
    
	return 0;
	
}
//This function forces the user to press enter to continue
void cont()
{
    char *ptr;
    ptr=(char*)malloc(sizeof(char));
    *ptr=getchar();//waits for input and continues on pressing enter
    free(ptr);//to free the allocated memory for efficiency
    ptr=NULL;//to avoid dangling pointer issue
}

void game()
{
	while(chk!=0&&i<12)//stay in game unless all correct or a wrong ans
	{
		alloclb();//allocating level base prize for different intermediate levels
		showques();//present question
		fgets(uans,sizeof(uans),stdin);//fgets takes user ans as input and prevents overflow of uans array
		checkans();//check the user input to see what is to be done
	}

}
	
void alloclb()
{
	if(i>=4&&i<8)
		lbprize=4000000;
	else if(i>=8&&i<12)
		lbprize=8000000;
	else if(i==12)
		lbprize=1200000;
}

void initques()
{
	fp1=fopen("ques.txt","r");//opening question file
	if(fp1==NULL)//to check if file has been opened
		printf("ques file opening error");
	else
	{
		for(i=0;i<13;i++)//initialise question structures from file
		{
			//reading the file line by line to fill the structures
			fgets(q[i].que,100,fp1);
			fgets(q[i].opta,30,fp1);
			fgets(q[i].optb,30,fp1);
			fgets(q[i].optc,30,fp1);
			fgets(q[i].optd,30,fp1);
		}
		i=0;//to ensure the while in game fxn works well
	}
	fclose(fp1);//closing the ques file after initialisation
}

void initques5050()
{
	fp2=fopen("ques5050.txt","r");//opening 5050 question file
	if(fp2==NULL)//to check if file has been opened
		printf("ques file opening error");
	else
	{
		for(i=0;i<13;i++)//initialise question structures from file
		{
			//reading the file line by line to fill the structures
			fgets(q5050[i].que,100,fp1);
			fgets(q5050[i].opta,30,fp1);
			fgets(q5050[i].optb,30,fp1);
			fgets(q5050[i].optc,30,fp1);
			fgets(q5050[i].optd,30,fp1);
		}
		i=0;//to ensure the while in game fxn works well
	}
	fclose(fp2);//closing the ques file after initialisation
}
void showques()
{
	//print statements to present ques and opts
	printf("\tQ%d-%s\n\n\t(a)%s\t(b)%s",i+1,q[i].que,q[i].opta,q[i].optb);
	printf("\t(c)%s\t(d)%s\t(e)50-50\n\t(f)question-flip\n\n",q[i].optc,q[i].optd); 
	if(uans[0]=='e'&&avail50==0)//to execute following print only when options are removed
		printf("\tselecting a removed option will count as a wrong answer\n\n");
}

void checkans()
{
	if(strlen(uans)==2)//filters when the user answers a single character,len=2 due to fgets
	{
		switch(uans[0])//to reduce the if-else ladder to only check amongst offered options
		{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':	
				
				if(uans[0]==ans[i])//the case of a correct ans
				{
					prize=prize+1000000;
					printf("\tCorrect ans! You win rupees %d\n\n",prize);
					i++;		
				}
				else if(uans[0]=='e'&&avail50>0)//chosing 50-50 when available
				{
					life50();
					game();//recursive call to game after removing wrong opts
				}
				else if(uans[0]=='e'&&avail50<1)//trying to chose 50-50 when unavailable
				{
					printf("\tYou can only use this lifeline once\n\n");
					avail50--;//to make sure the conditional print in showques works 
				}
				else if(uans[0]=='f'&&availflip>0)//chosing flip the ques when available
				{
					quesflip();
					game();//recursive call to game after changing present ques
				}
				else if(uans[0]=='f'&&availflip<1)//trying to chose flip the ques when unavailable
					printf("\tYou can only use this lifeline once\n\n");	
				else //entering a wrong ans
				{
					chk=0;//to exit while loop and hence the game function 
					printf("\tWrong Answer! You take back rupees %d\n\n",lbprize);	
				}
				
				break;
			
		//default case being an input not amongst the offered options
		default :
			printf("\tPlease enter a valid option only\n\n");
		}
	}
	else//when a string longer than one char is input
		printf("\tPlease enter a valid option only\n\n");
}

void life50()
{ 
	q[i]=q5050[i];//change the i^th ques with i^th 50-50 removed ques
	avail50--;//make 50-50 unavailable after use
}

void quesflip()
{
	q[i]=q[12];//changing the present ques with buffer ques(13th element)
	q5050[i]=q5050[12];//doing the same change for 50-50 removed ques
	ans[i]=ans[12];//changing the correct ans accordingly
	availflip--;//make flip the ques unavailable after use
}

void congrat()
{
	printf("\t\tCongratulations, You've answered all correct\n");
	printf("\t\tYou take back rupees 1.2 Crore!!!\n");
}

