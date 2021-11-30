#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "working.h"
int main(){
	 int x=6;
	while(x--){
 	setting_up();
 }
 int j=3;
  while(j--){
  	settinglower();
  }
	int op=0;
	start = ReadListIn(start);
	while(!kbhit()||scanf("%d",&op)){
		sleep(1);
		system("cls");
		printf("************************************************************************************************************************\n");
	  printf("\n\t\t\t\t\t\t   :CYBER CAFE:\n");
	   printf("\n\t\t\t\t\t\t   1.CONTROL PANEL.\n");
	    printf("\n\t\t\t\t\t\t   2.Registered User.\n");
	     printf("\n\t\t\t\t\t\t   3.Guest Login.\n");
	      warning();
	       printf("\n\t\t\t\t\t\t   ENTER OPTION:");
	       switch(op){
	       	case 1:ch();break;
	       	 case 2:check_user();break;
	       	  case 3:guest();break;
	       	  case 4:exit(0);break;
		   }
		   op=0;
	   }
	   return 0;
}
