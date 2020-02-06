#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>
#include <windows.h>
#include <conio.h>
#include "Color_Definations.h"
#include "_header.h"
/*******************************************************************
VERSION 1.0.6
                ************CHANGES************

                changed file retrieval system

******************************************************************/
typedef struct{
    char ID[100];
    char file_location[100];
    char scores_file_location[100];
}Shell;
typedef struct{
    char Name[30];
    char score[4];
}Players;
typedef struct{
    char question[500];
    char course_Name[100];
    char q_difficulty[3];
    char Answer;
} Questions;                    //Questions
typedef struct{
    int difficulty;
    char seconds[3];
}Q_difficulty;
Q_difficulty Difficulty[3] = {{1,"10"},{2,"15"},{3,"20"}};
//FILE RETRIEVAL1
Questions _questions[MAX_Q];
Shell subjects[MAX_SUBJECTS];       //Subjects
Players player[50];
/**FUNCTIONS......*/
void NEW_subject();
void remove_sbj(int *lines);
void main_menu();
int open_and_readfile(char *to_open,char my_str[][MAXQ_LEN]);
int tokenize(Shell *subj_or_loc,char arr[][MAXQ_LEN],char *file_to_tokenize);
char file_Retriever(char passed_value[]);
void record_Score(int Q_answered,int number_of_Q,char course_Name[],int user_seconds_left,int all_seconds);
void Add_Q(char passed_value[],char sbj_name[]);
void Display_Scores();
void Q_maker(char Sbj_name[],char file_to_write_to[],char *open_mode);
void _delete_line(char og[],char temp_loc[],int *ine_to_delete);
/**QUESTION FUNCTIONS*/
void multiple_choice_Questions_func(int *lines);
void populateAND_Randomize(int arr[],int n);
void Randomize(int arr[],int n);
const char *wait_forInput(int seconds);
/**HELPER FUNCTIONS.........*/
void Search(Shell *arr,char *_search,int n,int first,char retrieved_loc[]);
void Sort(Shell *arr,int n);
void file_seeker(char retrieved_LOC[],char _Search[]);
char End_of_line_Remover(char *line);
int spaces(int longest,int _index);
int Score_spaces(int longest,int _index);
void print_X(int n,char x);
int largest(int lines);
int longest_name_Scores(int lines);
void first_letter_tupr(char *plname,char *nplname);
void reset_Score();
void back();
void Sort_Scores(Players *arr,int n);
void restrictions();
int Random_Color();
void Manual();
//GLOBAL VARIABLES
int static score= 0, num_questions= 0;
char file_loc[100],score_file_loc[100],sbj_name[100];
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
int main(){
    srand(time(NULL));
    _Colors(Random_Color());
    printf("\n\n\t_____________________________________________\n");
    printf("\t|                                           ^|\n");
    _Colors(Random_Color());
    printf("\t| QUIZ GAME                                 ^|\n");
    RESET();
    printf("\t|                                           ^|\n");
    _Colors(Random_Color());
    printf("\t|TEST YOUR KNOWLEDGE IN VARIOUS TOPICS      ^|\n");
    _Colors(Random_Color());
    printf("\t|____________________________________________/\n");
    RESET();
    // Reset to zero
    memset(subjects,0,sizeof(subjects));
    memset(_questions,0,sizeof(_questions));
    memset(file_loc,0,sizeof(file_loc));
    memset(player,0,sizeof(player));
    memset(score_file_loc,0,sizeof(score_file_loc));
    reset_Score();
    main_menu();
    return 0;
}
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
void Manual(){
    _Colors(Random_Color());
    printf("\n\n\t\t| WELCOME ^-^  |\n\n\n");
    RESET();
    printf("\t\t\t|INSTRUCTIONS FOR USE\n");
    printf("\t\t\t-----------------------\n");
    printf("\t\t\t|This Applications uses numbers and letters for the user to navigate i.e \" 1 , 4 , 5\" \"V,S,H\". \n\n");
    printf("\t\t\t|STEP BY STEP\n\t\t\t-----------------------\n\t\t\t|1.Choose the subject to take by Entering a number corresponding to that subject and hitting the \"Enter Button\".\n");
    printf("\t\t\t|2.Input a letter according to the path you wish to take.NB|| You do not have to press Enter\n");
    back();
}
int Random_Color(){  //TODO define in Colors.c
    int Color_s[11] = {4,12,1,3,10,13,6,14,7,2,9};
        int randNum = (rand() % 6) +1; //generate a random number
        return Color_s[randNum]; //return value stored on index randnum from Color_s
}
void restrictions(){
    system("cls"); //clear screen
    char user_password[10];
    YELLOW();
    printf("\n\n\n\n\t\t\t\tPASSWORD : ");
    gets(user_password);
    if((strcmp(Password,user_password)) != 0){ //check if password correct
        RED();
        printf("\n\t\tACCESS DENIED\a\n");
        back();
    }
    RESET();
    Sleep(1000); //wait for a second
    system("cls");
}
void Randomize(int arr[],int n){
        //Randomize.......
    for(int l = 0;l<n;l++){
        int temp = arr[l];
        int randomIndex = rand()% n;
        arr[l] = arr[randomIndex];
        arr[randomIndex] = temp;
    }
}
void back(){
        // Reset to zero
        memset(subjects,0,sizeof(subjects));  //clear
        memset(_questions,0,sizeof(_questions)); //clear
        memset(file_loc,0,sizeof(file_loc)); //clear
        memset(score_file_loc,0,sizeof(score_file_loc)); //clear
        _Colors(Random_Color());
        printf("\nPress any Key to continue.........");
        RESET();
        getchar();
        system("cls");
        main();
}
void reset_Score(){
    if(score != 0){score = 0;}
    if(num_questions != 0){num_questions = 0;}
}
int spaces(int longest,int _index){ //TODO avoid Code duplication
     int _size = (strlen(subjects[_index].ID)); //retrieve string length
     return _size;
}
int Score_spaces(int longest,int _index){ //TODO avoid Code duplication
     int _size = (strlen(player[_index].Name)); //retrieve string length
     return _size;
}
void print_X(int n,char x){
    LIGHT_BLUE();
    char _x[12] = {"---"};
    printf("\t\t\t%c",x);
    for(int y=0;y<n;y++){
        printf("%c",x);
    }
    printf("%s\n",_x);
    RESET();
}
int largest(int lines){  //TODO avoid Code duplication
    /**
    Algorithm returns longest strings length
    */
    int longest = strlen(subjects[0].ID); //first element in array
    for(int i=0;i<lines;i++){
            int first = strlen(subjects[i].ID);
            int second = strlen(subjects[i+1].ID);
        if(first < second){
            longest = second;
        }
    }
    return longest + 2;
}
int longest_name_Scores(int lines){ //TODO avoid Code duplication
    /**
    Algorithm returns longest strings length
    */
    int longest = strlen(player[0].Name);
    for(int i=0;i<lines;i++){
            int first = strlen(player[i].Name);
            int second = strlen(player[i+1].Name);
        if(first < second){
            longest = second;
        }
    }
    return longest + 4;
}
int open_and_readfile(char *to_open,char my_str[][MAXQ_LEN]){

    /**.........................
    NB first and last parameters require pointers.....
    ..................*/
          FILE* inp;
    //direct pass of  file location
    inp = fopen(to_open,"r");		//filename of your data file
    if(inp == NULL){
        printf("Could Not Open FILe\a\n");
        back();
    }
    char arr[MAX_NUofQS][MAXQ_LEN];			//max word length 200
    int i = 0;
    while(1){
        char r = (char)fgetc(inp);
        int k = 0;
        while(r!=',' && !feof(inp)){	//read till , or EOF
            arr[i][k++] = r;			//store in array
            r = (char)fgetc(inp);
        }
        arr[i][k]=0;		//make last character of string null
        if(feof(inp)){		//check again for EOF
            break;
        }
        i++;
    }
    for(int k =0;k<MAX_NUofQS;k++){
        for(int p=0;p<MAXQ_LEN;p++){
            my_str[k][p] = arr[k][p];
        }
    }
    fclose(inp);
    return i;
}
void main_menu(){
    char input[3],main_str[MAX_NUofQS][MAXQ_LEN];
    int lines;
    int *EXIT,_new_SBJ,_delete_sbj;
        lines = tokenize(subjects,main_str,SUBJECTS_NAMES);  //open file and token it,store number of lines in var lines
        int _lines_arr[lines];
        int longest = largest(lines); //store length of longest line
        char buff[longest];
        memset(buff,' ',longest); //an array of spaces
        buff[sizeof(buff)-1] = '\0'; //last character NUL
        CREAM();
        printf("\n\t\t\t\t\t\t\t\t\t\t\t\tEnter (0) for Help?\n");
        GREEN();
        printf("\n\t\t\t_______________CHOOSE A SUBJECT_________________\n");
        RESET();
        print_X(longest ,'-');
        for(int g=0;g< lines;g++){
                _lines_arr[g] = g+1; //store g values
                _Colors(Random_Color());
            printf("\t\t\t[%d] %s%s|\n",g+1,subjects[g].ID,&buff[spaces(longest,g)]); //print the user options
            if(g==lines-1){
                    print_X(longest,'-');
                    _new_SBJ = g+2;
                    _delete_sbj = g+3;
                    EXIT = g+4;
           }
        }
        CREAM();
        printf("\t\t\t\t\t| [%d]NEW SUBJECT\n",lines+1);
        PURPLE();
        printf("\t\t\t\t\t| [%d]REMOVE SUBJECT\n",lines+2);
        RED();
        printf("\t\t\t\t\t| [%d]EXIT APPLICATION\n",lines+3);
        RESET();
                      /**ROUTE HERE*/
    int route = 0;
    while(1){
        gets(input);
        route = atoi(input);//string to integer converter
        if(route == EXIT){
            RED();
            printf("Program Ended............");
            RESET();
            exit(0);
        }else if(route == _new_SBJ){
            system("cls");
            NEW_subject();
            break;
        }else if(route == _delete_sbj){
            system("cls");
            remove_sbj(lines);
        }else if(route == 0){
            system("cls");
            //function with instructions for use
            Manual();
        }else if((route > EXIT )|| (route < 0)){  //out of bounds
            YELLOW();
            printf("INVALID INPUT............Please pick a number within bounds i.e 1..3\n");
            RESET();
            Sleep(2000);
            system("cls");
            main_menu();
            }
        for(int s=0;s<lines;s++){
            if(route == _lines_arr[s]){ //a valid route
                    /**Populate file_loc,sbj_name and score_file_loc*/
                strcpy(sbj_name,subjects[s].ID);
                strcpy(file_loc,subjects[s].file_location);
                strcpy(score_file_loc,subjects[s].scores_file_location);
                system("cls");
                LIGHT_RED();
                printf("\n\t-----------------------------------------\n");
                printf("\t|-Subject : ");
                GREY();
                printf(" %s-----|\n",sbj_name);
                LIGHT_RED();
                printf("\t-----------------------------------------\n");
                RESET();
                BLUE_ISH();
                printf("\n\t\t\t|'H' High scores \n");
                CREAM();
                printf("\t\t\t----------------------------\n");
                GREEN();
                printf("\t\t\t|'S' Start \n");
                CREAM();
                printf("\t\t\t----------------------------\n");
                PURPLE();
                printf("\t\t\t|'A' Add question(s)\n");
                LIGHT_RED();
                printf("\t\t\t\t\t\t\t\t\t|'B'BACK|\n :");
                RESET();
                char path = getch();
                path = toupper(path);
                if(path =='H'){
                    Display_Scores();
                    back();
                }else if(path=='S'){
                    file_Retriever(file_loc);
                }else if(path == 'A'){
                        Add_Q(file_loc,sbj_name);
                        while((getchar()) != '\n');
                        back();
                }else if(path == 'B') {
                        back();
                }else{
                    RED();
                    printf("\t\t\t INVALID INPUT\n");
                    RESET();
                    Sleep(2000);
                    system("cls");
                    main();
            }
          }
        }
      }
    }
char End_of_line_Remover(char *line){           /**FUNCTION WORKING properly*/
    //Removing End of Line from user_Char_input
    int cch = strlen(line); //length of line
    if (cch > 1 && line[cch-1] == '\n'){// check for \n at the end of the string
    line[cch-1] = '\0';//if there replace with the null
   }
}
int tokenize(Shell *subj_or_loc,char arr[][MAXQ_LEN],char *file_to_tokenize){
    char *temp,*token;
    const char s[3] = "-\n";
    int lines = open_and_readfile(file_to_tokenize,arr); //open file and store data in arr
       /*TOKENIZING STRING*/
      for(int j = 0;j<=lines;j++){
        int static segment;
        temp = arr[j];
                /* get the first token */
                token = strtok(temp,s);
                /* walk through other tokens */
            while(token != NULL){
                segment++;
                    if(segment == 1){
                     strcpy(subj_or_loc[j].ID,token);
              }else if(segment == 2){
                   strcpy(subj_or_loc[j].file_location,token);
              }else if(segment == 3){
                    strcpy(subj_or_loc[j].scores_file_location,token);
                    segment = 0;                      //reset segment values
                }
                    token = strtok(NULL, s);
            }
    }
    return lines;
}
char file_Retriever(char passed_value[]){
    char *temp,*token;
    int Q_lines;
    char Q_arr[MAX_NUofQS][MAXQ_LEN];			//max word length 200
    Q_lines = open_and_readfile(passed_value,Q_arr); //open file and store data in Q_arr

                    /*check if arr is empty...........*/
            if((strcmp(Q_arr,""))==0){  /**TODO Find a better way*/
                printf("FILE EMPTY!\a\n");
                back();
        }
    /*TOKENIZING STRING*/
      for(int j = 0;j<=Q_lines-1;j++){
        int static segment;
        temp = Q_arr[j];
        const char s[2] = "-";
                /* get the first token */
                token = strtok(temp,s);
                /* walk through other tokens */
            while(token != NULL){
                segment++;
                    if(segment == 1){
                     strcpy(_questions[j].question,token);
              }else if(segment == 2){
                     strcpy(_questions[j].course_Name,token);
                }else if(segment == 3){
                    strcpy(_questions[j].q_difficulty,token);
                }else if(segment == 4){
                     _questions[j].Answer = token[0];
                     segment = 0;                      //reset segment values
                }
                    token = strtok(NULL, s);
        }
    }
    multiple_choice_Questions_func(Q_lines);
}
void NEW_subject(){
    char sbj_name[100],write_txtfile[150];
    char save_subjname[400],for_display[100],sbj_score_record[150];
    FILE * ptr_save_subj,*ptr_info;
    char open_mode[3] = {"w"};
    restrictions();
    CREAM();
    printf("\n\n\t\t\t---------Subject Name-----------\n  :");
    RESET();
    fgets(sbj_name,50,stdin);                                       //get subject name
    End_of_line_Remover(sbj_name);
                                                /**TODO  validate user input*/
      snprintf(write_txtfile,sizeof write_txtfile,"Subjects//%s.txt",sbj_name); //copy string
      system("cls");

      Q_maker(sbj_name,write_txtfile,open_mode); //call Q_maker

        snprintf(sbj_score_record,sizeof sbj_score_record,"Subjects//Highest_scores//%s.txt",sbj_name);  //make file directory
        ptr_info=fopen(sbj_score_record,"a+");
         if(ptr_info == NULL){
            printf("Failed to make high scores file");
            perror("Error is ");
            exit(1);
      }                                     //Open to change
        fclose(ptr_info);

          ptr_save_subj= fopen(SUBJECTS_NAMES,"a");
        if(ptr_save_subj == NULL){
            printf("Saving into Subject File failed");
            exit(1);
      }
      strcpy(for_display,sbj_name);
      strupr(for_display);
      snprintf(save_subjname,sizeof save_subjname,"%s-%s-%s,\n",sbj_name,write_txtfile,sbj_score_record);
      fputs(save_subjname,ptr_save_subj);
      fclose(ptr_save_subj);
        system("cls");
        printf("\n\n\n\t\t\t--------------------Subject added successfully-------------------------\n");
        while((getchar()) != '\n');
        back();
}
void Sort_Scores(Players *arr,int n){
    /**Sorting Algorithm in descending order*/
    Players swap;
    for(int a=0;a<n-1;a++){
        for(int b=0;b<n-a-1;b++){
            if(strncmp(arr[b].score,arr[b+1].score,3)<0){       //Descending Order
                swap = arr[b];
                arr[b] = arr[b+1];
                arr[b+1] = swap;
            }
        }
    }
  }
void populateAND_Randomize(int arr[],int n){
    //Populate
    for(int k=0;k<n;k++){
        arr[k] = k;
    }
    //Randomize.......
    Randomize(arr,n);
}
void multiple_choice_Questions_func(int *lines){     /**FUNCTION UNSTABLE  ALWAYS (-_-)*/

    /**
    BUG

    Clear Input buffer to avoid overflow    (-_-)

    */
        system("cls");
        int _RS = lines;
        int seconds = 0,seconds_left=0,user_seconds_left=0,all_seconds =0,s_s;
        int N_nums[_RS];
        populateAND_Randomize(N_nums,lines);
        //For Multiple choice Questions......
    for(int i=0;i<_RS;i++){
       seconds = atoi(_questions[i].q_difficulty);
       s_s = seconds;
       char *user_input = '-';
       GREY();
       printf("\n\t\t%s\n",_questions[i].course_Name);
       LIGHT_BLUE();
       printf("\n\t\t\t\t----------YOU HAVE [");
       YELLOW();
       printf("%d",seconds);
       LIGHT_BLUE();
       printf("] seconds-----------\n\n");
       RED();
       printf("\t\t***********\n\t\t* 'Q' QUIT*\n\t\t***********\n");
       RED();
       RESET();
       DARK_GREEN();
       printf("\n\n\t\tQuestion [%d/%d] : %s \n\n\tANSWER : ",i+1,_RS,_questions[N_nums[i]].question);//print question
       RESET();
       while(1){
        if(kbhit()){
            user_input = getch();
            seconds_left = seconds;
            break;
        }
        Sleep(1000);
        --seconds;
        if(seconds == 0){
            break;
        }
       }
       user_input = toupper(user_input);//Change string to upper case
      if(user_input == 'Q'){
           system("cls");
           YELLOW();
           printf("\n\n\t\t\t-------------------You Forfeit -_-+ --------------------------\n");
           RESET();
           break;
       }else if(user_input == _questions[N_nums[i]].Answer){//compare with correct answer
            GREEN();
            printf("\n\t\tCORRECT ^-^ \n");
            RESET();
            score++;
            user_seconds_left+=seconds_left;
            Sleep(2000);
            system("cls");
       }else{
           if(user_input == '-'){
                RED();
                printf("\n\t\t--------OUT OF TIME-----------");
                RESET();
           }else{
                RED();
                printf("\n\t\tIncorrect -_-  \n");
                RESET();
           }
            Sleep(2000);
            if(seconds > 0 || seconds <0){
                seconds = 0;
            }
            system("cls");
       }
      num_questions++;
      all_seconds+=s_s;

   }
    printf("\t----------------------------------------------------------------------\n");
    CREAM();
    printf("\nYOU GOT [ %d / %d ] CORRECT\n",score,num_questions);
    RESET();
    record_Score(num_questions,_RS,_questions[0].course_Name,user_seconds_left,all_seconds);
}
void first_letter_tupr(char *plname,char *nplname){
    int j;
      for(j=0; plname[j]!='\0'; j++){ //to convert the first letter after space to capital
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' '){
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }else nplname[j]=plname[j];
    }
    nplname[j]='\0';
}
void record_Score(int Q_answered,int number_of_Q,char course_Name[],int user_seconds_left,int all_seconds){     /**FUNCTION WORKING properly*/
    char plname[20],nplname[20],cha,player_details[400],_score[15],retrieved_LOC[100];
    int point,user_points,all_points;
    double minimum,bar;
    /**Worthy to Record ?*/
    point = 2;
    all_points = floor(all_seconds * point);
    minimum = floor(((double)1/(double)3) * (double)number_of_Q);
    user_points = floor(user_seconds_left * point);
    bar = floor(((double)2/(double)3) * (double)all_points);
    if((user_points > bar) && (Q_answered > minimum)){
        GREEN();
        printf("\t\t------------------------------------------------------------------------\n");
        printf("\t\t|------------------Congratulations on getting a high score-------------|\n");
        printf("\t\t------------------------------------------------------------------------\n");
        file_seeker(retrieved_LOC,course_Name); //search for high score file
        FILE *ptr_info;
        ptr_info=fopen(retrieved_LOC,"a+");
        printf("Enter your name: ");
        scanf("%[^\n]",plname);
        first_letter_tupr(plname,nplname);
        snprintf(player_details,sizeof player_details,"%s-%d,",nplname,user_points);
        fputs(player_details,ptr_info);
        fclose(ptr_info);
        RESET();
        while((getchar()) != '\n');
        back();
  }
  back();
}
void Display_Scores(){
    system("cls");
    char *token,*temp;
    char buffer[MAX_NUofQS][MAXQ_LEN];			//max word length 200
    int lines;
    const char s[3] = "-";
        lines = open_and_readfile(score_file_loc,buffer);
               /*TOKENIZING STRING*/
      for(int j = 0;j<=lines;j++){
        int static segment;
        temp = buffer[j];
                /* get the first token */
                token = strtok(temp,s);
                /* walk through other tokens */
            while(token != NULL){
                segment++;
                    if(segment == 1){
                     strcpy(player[j].Name,token);
              }else if(segment == 2){
                    strcpy(player[j].score,token);
                    segment = 0;                      //reset segment value
            }
            token = strtok(NULL, s);
        }
      }
    Sort_Scores(player,lines); //Sort Scores From Highest to Lowest........................
        int longest = longest_name_Scores(lines);
        char buff[longest];
        memset(buff,' ',longest);
        buff[sizeof(buff)-1] = '\0';
        YELLOW();
        printf("\n\t-------------------------Subject : %s------------------------\n",sbj_name);
        printf("\n\tHIGHEST SCORES\n");
        printf("\t\t\t\tNAME\t\t\t\t\tSCORE\n\n");
        YELLOW();
        for(int g=0;g< 10;g++){ //only top 10 scores
            GREY();
            if(g<3){
                LIGHT_BLUE();
            }
            printf("\t\t\t\t%d %s %s \t\t\t%s\n",g+1,player[g].Name,&buff[Score_spaces(longest,g)],player[g].score);
            RESET();
        }
        back();
      }
void Add_Q(char passed_value[],char sbj_name[]){
    char open_mode[3] = {"a"};
    restrictions();
    //make a function dedicated to making questions from new_subject()................DONE
    Q_maker(sbj_name,passed_value,open_mode);
    while((getchar()) != '\n');
    back();
}
void Q_maker(char Sbj_name[],char file_to_write_to[],char *open_mode){
    char print_answer,row1_posble_Answr[200],row2_posble_Answr[200],print_question[200],append[500],seconds[4],_Qdifficulty[2];
    int  numof_Q;
    char ABCD[4][50];            //TODO change into constants
    char abcd_indexs[4][2]={{"A"},{"B"},{"C"},{"D"}};
    FILE *ptr_populate_file;
    ptr_populate_file = fopen(file_to_write_to,open_mode);
      if(ptr_populate_file == NULL){
            printf("Opening File failed");
            exit(1);
      }
      YELLOW();
      printf("\n\n\t\t\t--------NUMBER of Question(s)\n\t\t\t----MAXIMUM 5\n  :");
      RESET();
      scanf("%d",&numof_Q);
      if(numof_Q > 5){
            RED();
            printf("\t\t too many\n");
            BLUE_ISH();
            printf("\tDefaulting to (one)\n");
            RESET();
            numof_Q = 1;
      }
      while((getchar()) != '\n');
      for(int t=0;t<numof_Q;t++){                               //Write the questions to text File
          if(t > 0){
             while((getchar()) != '\n');
          }
        printf("\n\t[%d of %d]-----Question : ",t+1,numof_Q);
        gets(print_question);

        printf("\n\n\t-------Possible Answers i.e A,B,C,orD--------\n");
        for(int p=0;p<MAX_PosAnswers;p++){
             _Colors(Random_Color());
             printf("[%s] : ",abcd_indexs[p]);
             gets(ABCD[p]);
             if(p == 3){
                snprintf(row1_posble_Answr,sizeof row1_posble_Answr,"\n\t\t %s > %s  %s > %s\n",abcd_indexs[0],ABCD[0],abcd_indexs[1],ABCD[1]);
                snprintf(row2_posble_Answr,sizeof row2_posble_Answr,"\n\t\t %s > %s  %s > %s\n",abcd_indexs[2],ABCD[2],abcd_indexs[3],ABCD[3]);
             }
        }
        GREY();
        printf("[%d of %d]---Correct Answer     : ",t+1,numof_Q);          /**      ---TODO----- FORMATED INPUT AND OUTPUT ERROR HANDLING */
        RESET();
        while(1){
            print_answer = getchar();
            print_answer  = toupper(print_answer);//Change string to upper case
            if((print_answer == 'A') ||(print_answer == 'B') ||(print_answer == 'C') ||(print_answer == 'D')){
                break;
            }else{
                RED();
                printf("\t\tINVALID INPUT Either -_- A B C or D   \n");
                GREEN();
                while((getchar()) != '\n');
                continue;
            }
        }
             while((getchar()) != '\n');
             CREAM();
             printf("\n\t------------Question Difficulty (1) normal | (2) medium | (3) hard -------------------\n\t------- : ");
             RESET();
             fgets(_Qdifficulty,2,stdin);   /**BUG*/
             if(atoi(_Qdifficulty) > 3){
                 LIGHT_RED();
                 printf("\t\tOut of bounds\n");
                 DARK_GREEN();
                 printf("\t\tSetting to default (normal) -_- \n");
                 RESET();
                    strcpy(seconds,Difficulty[1].seconds);
                    Sleep(2000);
           }else{
                for(int d = 0;d<3;d++){
             if(atoi(_Qdifficulty)== Difficulty[d].difficulty){
                strcpy(seconds,Difficulty[d].seconds);
                break;
           }
       }
    }
        /**Subject to change...............*/
        if(open_mode == "w"){
          fprintf(ptr_populate_file,"%s\?.\n%s%s-%s-%s-%c,",print_question,row1_posble_Answr,row2_posble_Answr,strupr(Sbj_name),seconds,print_answer);
        }else{
            snprintf(append,sizeof append,"%s\?.\n%s%s-%s-%s-%c,",print_question,row1_posble_Answr,row2_posble_Answr,strupr(Sbj_name),seconds,print_answer);
            fputs(append,ptr_populate_file);
        }
        memset(seconds,0,sizeof(seconds));
        system("cls");
      }
      fclose(ptr_populate_file);
}
void remove_sbj(int *lines){  /**FUNCTION UNSTABLE  ALWAYS (-_-)*/
    int _RS = lines,flag=0,status_file1,status_file2,*line_to_delete = 0;
    char picked[10],raw_input[3];
    int *_back,roof;
    int user_input,choices[_RS];
    restrictions();
    printf("\n");
    LIGHT_RED();
    printf("\t__________________\n\t|\t\t |\n\t| DELETE SUBJECT |\n\t|________________|\n\n");
    roof = lines;
        for(int i=0;i<lines;i++){
            choices[i] = i+1;
            _Colors(Random_Color());
            printf("\t\t%d : %s \n",i+1,subjects[i].ID);
            _Colors(Random_Color());
            printf("\t\t______________________________________/\n");
            RESET();
            if(i == roof-1){
                _back = i+2;
            }
        }
        RED();
        printf("\t\t\t\t\t\t\t\t\t| ' %d ' back|\n",_back);
        RESET();
        while(1){
        printf("\n\nWhich 1 : ");
        gets(raw_input);
        user_input = atoi(raw_input);//string to integer converter
        if(user_input == _back){
            back();
        }
        if(user_input > lines+1){
            RED();
            printf("Out of bounds\n");
            RESET();
            Sleep(1000);
            system("cls");
            continue;
        }else{
          for(int s=0;s<lines;s++){
              if(user_input == choices[s]){
                 strcpy(picked,subjects[s].ID);
                 strcpy(file_loc,subjects[s].file_location);
                 strcpy(score_file_loc,subjects[s].scores_file_location);
                 line_to_delete= s+1;
                 flag = 1;
              }
           }
        }
        if(flag == 1){
            break;
        }
    }
    status_file1 = remove(file_loc);
    status_file2 = remove(score_file_loc);
    if((status_file1 == 0) && (status_file2 == 0)){
        printf("All Files deleted\n");
    }else{
        printf("\t\t\tUnable to  delete All files \n: %s\n: %s\n",file_loc,score_file_loc);
  }
    _delete_line(SUBJECTS_NAMES,SUBJECTS_NAMES_Dir,line_to_delete);
    line_to_delete = 0;
    back();
}
void _delete_line(char og[],char temp_loc[],int *line_to_delete){
     char temp_file_name[200],file_name[200],str[200];
     FILE *ptr_file,*ptr_file_temp;
     int temp =1;
     strcpy(file_name,og);
     strcpy(temp_file_name,temp_loc);
     ptr_file = fopen(file_name,"r");
  if(ptr_file == NULL){
        printf("Failed\n");
        exit(0);
  }
        rewind(ptr_file);
        ptr_file_temp = fopen(temp_file_name,"w");
          if(ptr_file_temp == NULL){
        printf("Failed to make replica\n");
        exit(0);
  }
  while((fgets(str,200,ptr_file) != NULL)){

        if(line_to_delete != temp){
            fputs(str,ptr_file_temp);
        }
        temp++;
  }
    fclose(ptr_file);
    fclose(ptr_file_temp);
    int s = remove(file_name);
    if(s != 0){
        printf("Failed\n");
        perror("Error");
    }
    rename(temp_file_name,file_name);
}
void Search(Shell *arr,char *_search,int n,int first,char retrieved_loc[]){
    int middle;
    int found = 0;
    int last = n;
    middle = (first+last)/2;
    while(first<=last){
        if(strcmp(_search,arr[middle].ID) > 0){
            first = middle+1;
        }else if(strcmp(_search,arr[middle].ID)< 0){
            last = middle -1;
        }else{
            found = 1;
            strcpy(retrieved_loc,arr[middle].scores_file_location);
            break;
        }
        middle = (first+last)/2;
    }
    if(!found){
        printf("FILE NOT FOUND!\n");
        perror("Error: ");
        back();
    }
}
void Sort(Shell *arr,int n){
    Shell swap;
    for(int a=0;a<n-1;a++){
        for(int b=0;b<n-a-1;b++){
            if(strncmp(arr[b].ID,arr[b+1].ID,3)>0){
                swap = arr[b];
                arr[b] = arr[b+1];
                arr[b+1] = swap;
            }
        }
    }
}
void file_seeker(char retrieved_LOC[],char _Search[]){
        Sort(subjects,MAX_SUBJECTS);
        Search(subjects,_Search,MAX_SUBJECTS,0,retrieved_LOC);
}
/**
Remove Questions
*/









