Copyright © 2015 by Purvi Misal
All rights reserved. This book or any portion thereof
may not be reproduced or used in any manner whatsoever
without the express written permission of the publisher
except for the use of brief quotations in a book review.

#include<stdio.h>
#include<stdlib.h>

struct Date{
	int dd;
	int mm;
	int yy;
};
struct Date date;

struct Reminder{
	int dd;
	int mm;
	char note[50];
};
struct Reminder R;

//checks whether the year passed is leap year or not
int check_leapYear(int year){ 
	if(year % 400 == 0 || (year % 100!=0 && year % 4 ==0))
		return 1;
    	return 0;
}

//increase the month by one
void increase_month (int *mm,  int *yy){ 
    	++*mm;
    	if(*mm > 12){
    	    	++*yy;
		*mm = *mm - 12;
	}
}

//decrease the month by one
void decrease_month (int *mm,  int *yy){ 
    	--*mm;
    	if(*mm < 1){
        	--*yy;
        	if(*yy<1600){
        		printf("No record available");
            		return;
        	}
	*mm = *mm + 12;
	}
}

//returns the number of days in given month and year
int getNumberOfDays(int month,int year){ 
	switch(month){                         
      		case 1 : 
			return(31);
      		case 2 : 
			if(check_leapYear(year)==1)
				return(29);
	       		else
		 		return(28);
		case 3 : 
			return(31);
		case 4 : 
			return(30);
		case 5 : 
			return(31);
		case 6 : 
			return(30);
		case 7 : 
			return(31);
		case 8 : 
			return(31);
		case 9 : 
			return(30);
		case 10: 
			return(31);
		case 11: 
			return(30);
		case 12: 
			return(31);
		default: 
			return(-1);
   }
}

//returns the name of the day
char *getName(int day){ 
   	switch(day){
      		case 0 :
			return("Sunday");
      		case 1 :
			return("Monday");
      		case 2 :
			return("Tuesday");
      		case 3 :
			return("Wednesday");
      		case 4 :
			return("Thursday");
      		case 5 :
			return("Friday");
      		case 6 :
			return("Saturday");
      		default:
			return("Error in getName() module.Invalid argument passed");
	}
}

//prints the name of month and year
void print_date(int mm, int yy) { 
	printf("\n------------------------------------------------------------------\n");
    	switch(mm){
        	case 1: 
			printf("January"); 
			break;
        	case 2: 
			printf("February"); 
			break;
        	case 3: 
			printf("March"); 
			break;
        	case 4: 
			printf("April"); 
			break;
        	case 5: 
			printf("May"); 
			break;
        	case 6: 
			printf("June"); 
			break;
        	case 7: 
			printf("July"); 
			break;
        	case 8: 
			printf("August"); 
			break;
        	case 9: 
			printf("September"); 
			break;
        	case 10: 
			printf("October"); 
			break;
        	case 11: 
			printf("November"); 
			break;
        	case 12: 
			printf("December"); 
			break;
	}
    	printf(" , %d", yy);
    	printf("\n-------------------------------------------------------------------\n");
}


//retuns the day number
int getDayNumber(int day,int mon,int year){ 
    	int res = 0, t1, t2, y = year;
    	year = year - 1600;
    	while(year >= 100){
        	res = res + 5;
        	year = year - 100;
	}
    	res = (res % 7);
    	t1 = ((year - 1) / 4);
    	t2 = (year-1)-t1;
    	t1 = (t1*2)+t2;
    	t1 = (t1%7);
    	res = res + t1;
    	res = res%7;
    	t2 = 0;
    	for(t1 = 1;t1 < mon; t1++){
        	t2 += getNumberOfDays(t1,y);
	}
    	t2 = t2 + day;
    	t2 = t2 % 7;
    	res = res + t2;
    	res = res % 7;
    	if(y > 2000)
        	res = res + 1;
    		res = res % 7;
    		return res;
}


char *getDay(int dd, int mm, int yy){
    	int day;
    	if(!(mm>=1 && mm<=12)){
        	return("Invalid month value");
    	}
    	if(!(dd>=1 && dd<=getNumberOfDays(mm,yy))){
        	return("Invalid date");
    	}
    	if(yy>=1600){
        	day = getDayNumber(dd,mm,yy);
        	day = day%7;
        	return(getName(day));
	}
	else {
        	return("Please give year more than 1600");
    	}
}

int checkNote(int dd, int mm){
    	FILE *fp;
    	fp = fopen("note.dat","rb");
    	if(fp == NULL){
        	printf("Error in Opening the file");
    	}
    	while(fread(&R,sizeof(R),1,fp) == 1){
        	if(R.dd == dd && R.mm == mm){
            		fclose(fp);
            		return 1;
        	}
    	}
    	fclose(fp);
    	return 0;
}

//prints month with all days
void printMonth	(int mon, int year, int x, int y){ 
    	int nod, day, da, cnt, d = 1, x1 = x, y1 = y, isNote = 0;
    	if(!(mon>=1 && mon<=12)){
        	printf("INVALID MONTH");
        	getchar();
        	return;
    	}
    	if(!(year>=1600)){
        	printf("INVALID YEAR");
        	getchar();
        	return;
    	}
    	print_date(mon,year);
    	y += 3;
    	printf("S       M       T       W       T       F       S   \n");
    	y++;
    	nod = getNumberOfDays(mon, year);
    	day = getDayNumber(d, mon, year);
    	switch (day) { //locates the starting day in calender
        	case 0 :
			x=x;
			cnt=1;
            		break;
		case 1 :
            		x = x + 4;
            		cnt = 2;
            		break;
        	case 2 :
            		x = x + 8;
            		cnt = 3;
           		break;
        	case 3 :
            		x = x + 12;
            		cnt = 4;
            		break;
        	case 4 :
            		x = x + 16;
            		cnt = 5;
            		break;
        	case 5 :
            		x = x + 20;
            		cnt = 6;
            		break;
        	case 6 :
            		x = x + 24;
            		cnt = 7;
            		break;
        	default :
            		printf("INVALID DATA FROM THE getOddNumber()MODULE");
            		return;
    	}
    	printf("%02d \t",d);
    	if (d % 7 == 0) {
		 printf("\n");
	}
    	for(d = 2; d <= nod; d++) {
        	if(cnt%7==0){
            		y++;
            		cnt = 0;
            		x = x1-4;
        	}
        	x = x+4;
        	cnt++;
        printf("%02d \t",d);
        if (d % 7 == 0) {
		printf("\n");}
    	}
    	printf("\nPress 'n'  to Next, Press 'p' to Previous , Press 's' to View Note and 'q' to Quit\n");
}

void AddNote() {
	FILE *fp;
	int da;
	fp = fopen("note.dat","ab+");
	system("clear");
	printf("Enter the date (DD MM): ");
	scanf("%d%d", &R.dd, &R.mm);
	printf("Enter the Note(50 character max): ");
	fflush(stdin);
	scanf("%s", &R.note);
	fwrite(&R, sizeof(R), 1, fp);
	printf("\n Press any key............\n");
	fclose(fp);
}

void showNote (int mm) {
	FILE *fp;
	int i = 0, isFound = 0 , da;
	system("clear");
	fp = fopen("note.dat","rb");
	if(fp == NULL) {
        	printf("Error in opening the file");
    	}
    	while(fread(&R,sizeof(R),1,fp) == 1){
        	if(R.mm == mm) {
			printf("Note %d Day = %d: %s", i+1, R.dd,  R.note);
            		isFound = 1;
            		i++;
        	}	
    	}
    	if(isFound == 0){
        	printf("This Month contains no note");
    	}
    	printf("\n Press any key to back.......\n ");
    	scanf("%d", &da); 
}

int main() {
    	int choice , da;
    	char ch = 'a';
    	while(1) {
        	system("clear");
        	printf("1. Find Out the Day\n");
        	printf("2. Print all the day of month\n");
		printf("3. Add Note\n");
		printf("4. EXIT\n");
		printf("ENTER YOUR CHOICE : ");
		scanf("%d",&choice);
        	switch(choice) {
            		case 1:
                		printf("Enter date (DD MM YYYY) : ");
                		scanf("%d %d %d",&date.dd,&date.mm,&date.yy);
                		printf("Day is : %s",getDay(date.dd,date.mm,date.yy));
                		printf("\nwill Display for 5 Seconds, Press any key to continue......\n");
                		sleep(5);
                		break;
            		case 2 :
                		printf("Enter month and year (MM YYYY) : ");
                		scanf("%d %d",&date.mm,&date.yy);
                		system("clear");
                    		printMonth(date.mm,date.yy,20,5);
                		while(ch!='q'){
                    			scanf("%c",&ch);
                    			if(ch == 'n'){
						increase_month(&date.mm,&date.yy);
						system("clear");
						printMonth(date.mm,date.yy,20,5);
                    			}
					else if(ch == 'p') {
	                        		decrease_month(&date.mm,&date.yy);
	                        		system("clear");
	                        		printMonth(date.mm,date.yy,20,5);
                    			}
					else if(ch == 's') {
						showNote(date.mm);
                        			system("clear");
                    			}
                		}
                		break;
            		case 3:
                		AddNote();
                		break;
            		case 4 :
                		exit(0);
        	}
	}
    	return 0;
}
