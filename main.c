#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"include/matchedit.h"
#include"include/matchedit.c"

#define LINE_SIZE	(256)
int changes=0;
void steps(char str1[],char str2[]);
int main(){
	int resp,resp2,rtn=1;
	char loc[100];
	char eeloc[100];
printf("::::::::::::::::::::::::::::::TEXT ANALYSIS IN PURE C::::::::::::::::::::::::::::::\n\n\n");
printf("This is an open-source program created by students of Computer Science and Engineering of Chandigarh University consisting of four members. Each module of this program has been built by different members of this group. Edit Distance and Steps-of-Conversion by Danish Shakeel, Matching by Karan Arora, and Entity Extraction by Bhargav Sharma and Priyanshu Jain. Supervision, compilation, adaptation and debugging by Danish Shakeel. \n\n");
printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
printf("\n");

/*MainMenuUI*/
MainMenu:
printf("\n");
puts("Enter a choice:");
puts("1. Edit Distance/Levenshtein	2. Steps-of-Conversion		3. Matching and Text Prediction		4. Entity Extraction		5.Exit");
scanf("%d",&resp);
printf("\n");

/*Edit Distance*/
if(resp==1){
while(rtn==1){
char str1[100],str2[100];
puts("Enter first string:");
scanf("%s",&str1);
puts("Enter second string:");
scanf("%s",&str2);
printf("%d step(s) required for conversion\n\n\n",levenshtein(&str1,&str2));
puts("1. Calculate For Another Word		2. Main Menu		3. Exit Program");
scanf("%d",&resp2);
switch (resp2){

		case 1: rtn=1;
		break;
		case 2: goto MainMenu;
		break;
		case 3: exit(0);
		break;
		default: break;
}
}}	

/*Steps of Conversion*/
else if(resp==2){
	char prim[100],sec[100];
	while(rtn==1){
	changes=0;
	puts("Enter primary:");
	scanf("%s",&prim);
	puts("Enter secondary");
	scanf("%s",&sec);
	steps(prim,sec);
	puts("1. Show Steps For Another Conversion		2. Main Menu		3. Exit Program");
	scanf("%d",&resp2);
	switch (resp2){
		case 1: rtn=1;
		break;
		case 2: goto MainMenu;
		break;
		case 3: exit(0);
		break;
		default: break;
}
}}

/*Matching usin BK-trees*/
else if (resp==3){
printf("Enter dictionary file location: ");
scanf("%s",&loc);
matches(loc);
{
goto MainMenu;
}}


/*Entity Extraction*/
else if (resp==4){
printf("Enter text file location to search in:");
scanf("%s",&eeloc);
entityextract(eeloc);
puts("1. Search For Another Word		2. Main Menu		3. Exit Program");
scanf("%d",&resp2);
switch (resp2){

		case 1: rtn=1;
		break;
		case 2: goto MainMenu;
		break;
		case 3: exit(0);
		break;
		default: break;
}
}

/*Exit*/
else if(resp==5){
exit(0);}

else{
puts("Invalid Selection");
goto MainMenu;}}


struct timespec diff_time(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

/*Matching*/
int matches(char loc[]){
	struct bknode *new_node,ret_list,*temp;
	int ret,i,choice,wc=0;
	FILE *fp;
	char line[LINE_SIZE],*pos,search[LINE_SIZE];
	struct timespec prev,now,diff;
	fp = fopen(loc,"r");
	if(fp == NULL)
	{
		printf("Unable to open '%s'\n",loc);
		return -1;
	}
	
	ret = bk_init();
	if(ret < 0)
	{
		printf("Initialisation Failed\n");
		return -1;
	}

	clock_gettime(CLOCK_MONOTONIC,&prev);
	/*read the data file line by line*/
	while(fgets(line,sizeof(line),fp))
	{
/*		printf("%s:%d %s\n",__func__,__LINE__,line); */
		pos = strchr(line,'\n');
		*pos = '\0';
		bk_add(line);
		wc++;
	}
	clock_gettime(CLOCK_MONOTONIC,&now);
	diff = diff_time(prev,now);
	printf("Loaded %d words in %lu sec %lu nanosec\n\n",wc,diff.tv_sec,diff.tv_nsec);


	/*now searching can be done*/
	while(1){
		printf("1.Search		2.Print BK-Tree		3.Exit Program\n");
		scanf("%d",&choice);
		printf("Choice %d\n",choice);
		switch(choice){
			case 1:printf("Enter the string to search::\n");
			       getchar();
			       fflush(stdin);
			       fgets(search,LINE_SIZE,stdin);
			       pos = strchr(search,'\n');
			       *pos = '\0';
			       clock_gettime(CLOCK_MONOTONIC,&prev);
			       ret = bk_search_tree(search,&ret_list);  
			       clock_gettime(CLOCK_MONOTONIC,&now);
			       diff = diff_time(prev,now);
			       printf("Search time: %lu sec %lu nanos\n\n",diff.tv_sec,diff.tv_nsec);
			       TAILQ_FOREACH(temp,&ret_list.child,next);			       
		{
	printf("::::::::\t%s(distance: %d)\t ::::::::\n",temp->key_string,temp->lev_parent);
				       TAILQ_REMOVE(&ret_list.child,temp, next);
			       }
			       printf("\n\n");
			       break;
			case 2:
			       bk_print_tree();
			       break;
			
			case 3:
			       exit(0);
			       break;
			default:
			       break;
		}
	}

}

/*Entity Extract*/
int entityextract(char location[]) {
	char query[100];	
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	fp=fopen(location,"r");
	
	if((fp = fopen(location, "r")) == NULL) {
	printf("Unable to open file at %s\n",location);	
	return(-1);
	}
	else{
	printf("Enter a word to search for");
	scanf("%s",&query);
	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, query)) != NULL) {
			printf("\n*****A match found on line %d*****\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	/*Close the file if still open.*/
	if(fp) {
		fclose(fp);
	}
   	return(0);
}}

/*Steps-of-coversion:*/

void steps(char str1[],char str2[]){
	char* temp;
	temp=(char *)malloc((strlen(str2)));/*Buffer of size of string 2 to store string 1 */
	unsigned int length_1=strlen(str1);
	unsigned int length_2=strlen(str2);
int belongs,req;
strlwr(str1);
strlwr(str2);/*To avoid conversion of same letters but in different cases*/

/*Strings of equal length:		*/
if(strlen(str1)==strlen(str2)){
int i;
for(i=0;i<=strlen(str1);i++){
		/*Strings with no swapping possible:*/
		if(str2[i]!=str1[i]){
			++changes;
			printf("%d::SUBSTITUTION:: %c <--- %c\n",changes,str1[i],str2[i]);
			str1[i]=str2[i];
			printf("--->%s\n",str1);
		}}}

/*String 1 is longer than string 2, hence deletion:*/
if(strlen(str1)>strlen(str2)){
		int i;
	
		for(i=strlen(str1);i>=strlen(str2);i--){
				if(str1[i]==0){
				}
			else{
			++changes;
			printf("%d::DELETE:: %c\n",changes,str1[i]);
			str1[i]=0;
			printf("--->%s\n",str1);
		}}
	}
/*String 2 is longer than string 1, hence addition:*/
if(strlen(str1)<strlen(str2)){
		strcpy(temp,str1);
		int i;
		for(i=(strlen(str1));i<strlen(str2);i++){
			if (str2[i]=='\0'){
			}
		else{
			++changes;
		printf("%d::ADD:: %c\n",changes,str2[i]);
		*(temp+i)=str2[i];
		*(temp+1+i)=0;
		printf("-->%s\n",temp);
	}}
	char newstr[length_2];/*Use to store 'temp' and use in steps function again*/
	strcpy(newstr,temp);
	steps(newstr,str2);
	}	
free(temp);	}




