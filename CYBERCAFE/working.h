#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include<time.h>
//int count=0;
int i=0;
char cpy[20];
int cptt;
typedef struct S_USER {

	char name[10];
	 char PH[10];
	  char uniquekey[10];
		struct S_USER *next;
	struct S_USER *previous;
	
} user;
user *start = NULL;
typedef struct S_SYSTEM{
	int system;
	 char user[20];
	 int presence;
	  clock_t t;
	  struct S_SYTEM *next;
}sys;
sys *start1=NULL;
typedef struct S_Lower{
	int system;
	char user[20];
	 int presence;
	 clock_t t;
	 struct S_lower *next;
}low;
low *start2=NULL;
void setting_up(){
	
	if(start1==NULL)
	 {
	 	sys *new2=(sys *)malloc(sizeof(sys));
	 	 i++;
	 	  new2->system=i;
	 	   strcpy((new2->user),"NO ONE");
	 	   new2->presence=0;
	 	   new2->t=0;
	 	   new2->next=NULL;
	 	    start1=new2;
	 }
	 else
	  {
	  	 sys *new2=(sys *)malloc(sizeof(sys));
	  	  i++;
	  	   new2->system=i;
	  	    strcpy((new2->user),"NO ONE");
	  	    new2->presence=0;
	  	    new2->t=0;
	  	    new2->next=NULL;
	  	     sys *temp=start1;
	  	      while(temp->next!=NULL){
	  	      	temp=temp->next;
				}
			temp->next=new2;
	  }
}
void settinglower(){
	if(start2==NULL)
	 {
	 	low *new2=(low *)malloc(sizeof(low));
	 	 i++;
	 	  new2->system=i;
	 	   strcpy((new2->user),"NO ONE");
	 	   new2->presence=0;
	 	   new2->t=0;
	 	   new2->next=NULL;
	 	    start2=new2;
	 }
	 else
	  {
	  	 low *new2=(low *)malloc(sizeof(low));
	  	  i++;
	  	   new2->system=i;
	  	    strcpy((new2->user),"NO ONE");
	  	    new2->presence=0;
	  	    new2->t=0;
	  	    new2->next=NULL;
	  	     low *temp=start2;
	  	      while(temp->next!=NULL){
	  	      	temp=temp->next;
				}
			temp->next=new2;
	  }
}
void PrintList(user *start) {
	system("cls");
	printf("************************************************************************************************************************\n");
	user *cur = start;
	int count = 0;
	
	user *ahead = NULL;
	user *behind = NULL;
	
	while(cur != NULL) {
		count++;
		
		ahead = cur->next;
		behind = cur->previous;
		
		printf("\t\t\t\tENTRY:%d Name:%s Unique key:%s \n",count,
			cur->name,cur->uniquekey
			);
			printf("\n");
		cur = cur->next;
		ahead = NULL;
		behind = NULL;
	}	
	//printf("Total entry:%d\n",count);
	sleep(5);
}

user *newuser() {
	system("cls");
	printf("************************************************************************************************************************\n");
	printf("\t\t\t\t\tEnter Name,Phone Number,Unique: ");
	char input[50];
	fgets( input, 49, stdin);
	user *new1=malloc(sizeof(user));
	sscanf(input,"%s %s %s",new1->name,new1->PH,new1->uniquekey);
	new1->next = NULL;
	new1->previous = NULL;
	printf("\t\t\t\t\tadded the user succesfully.\n");
	 printf("\t\t\t\t\tRedirecting.\n");
	sleep(3);
	return new1;
	
}

user *AddToStart(user *startPtr) {
	user *new1 = newuser();
	if(startPtr != NULL) {
		startPtr->previous = new1;
		new1->next = startPtr;
	}
	
	return new1;
}

user *AddToEnd(user *startPtr) {
	user *returnPtr = startPtr;
	user *new1 = NULL;
	
	if(startPtr == NULL) {
		new1 = AddToStart(startPtr);
		returnPtr = new1;
	} else {
		user *index = startPtr;
		while (index->next != NULL) {
			index = index->next;
		}
		new1 = newuser();
		index->next = new1;
		new1->next = NULL;
		new1->previous = index;
	}
	return returnPtr;
}

user *Delete(user *startPtr) {

	printf("Enter Name To Delete:");
	char input[16];
	fgets(input, 15, stdin);
	
	user *Ref = startPtr;
	user *Delete = NULL;
	
	while(Ref != NULL) {
	
		if(strncmp(input, Ref->name, strlen(Ref->name)) == 0) {
			Delete = Ref;
			break;
		}
		
		Ref = Ref->next;
	}
	
	if(startPtr != NULL && Delete == startPtr) {
		if(Delete->next != NULL) {
		 Delete->next->previous = NULL;
			startPtr = Delete->next;
		} else {
			startPtr = NULL;
		}
	} else {
		if(Delete != NULL) {
			if(Delete->previous != NULL) {
				Delete->previous->next = Delete->next;
			}
			
			if(Delete->next != NULL) {
				Delete->next->previous = Delete->previous;
			}
		}
	}
	
	if(Delete != NULL) {
		Delete = NULL;
		free(Delete);
	}
	
	return startPtr;
	
}
void CleanUp(user *start) {
	
	user *freeMe = start;
	user *holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = freeMe->next;
		printf("Free Name:%s age:%d\n",
			freeMe->name
			);
		free(freeMe);
		freeMe = holdMe;
	}	
}

void WriteListToFile(user *start) {
	FILE *pFile;
	pFile = fopen("user.txt", "wb");
	
	if(pFile != NULL) {
		user *cur = start;
		
		user *holdNext = NULL;
		user *holdPrevious = NULL;
		
		while(cur != NULL) {
			holdNext = cur->next;
			holdPrevious = cur->previous;
			
			cur->next = NULL;
			cur->previous = NULL;
			
			fseek(pFile, 0, SEEK_END);
			fwrite(cur, sizeof(user), 1, pFile);
			
			printf("Writing:%s to file\n",cur->name);
			
			cur->next = holdNext;
			cur->previous = holdPrevious;
			
			holdNext = NULL;
			holdPrevious = NULL;
			
			cur = cur->next;
		}
		fclose(pFile);
		pFile = NULL;
	} else {
		printf("FILE OPEN ERROR\n");
	}
	
}

user *ReadNextFromFile(user *start, FILE *pFile) {
	size_t returnValue;
	if(start == NULL) {
		start = malloc(sizeof(user));
		returnValue = fread(start, sizeof(user), 1, pFile);
		start->next = NULL;
		start->previous = NULL;
	} else {
		user *index = start;
		user *new1 = malloc(sizeof(user));
		while(index->next != NULL) {
			index = index->next;
		}
		returnValue = fread(new1, sizeof(user), 1, pFile);
		index->next = new1;
		new1->next = NULL;
		new1->previous = index;
	}
	return start;
}

user *ReadListIn(user *start) {
	
	FILE *pFile;
	pFile = fopen("user.txt", "r");
	if(pFile != NULL) {
	
		CleanUp(start);
		start = NULL;
		
		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		rewind(pFile);
		
		int numEntries = (int)(fileSize / (sizeof(user)));
		printf("numEntries:%d\n",numEntries);
		
		int loop = 0;
		for(loop = 0; loop < numEntries; ++loop) {
			fseek(pFile, (sizeof(user) * loop), SEEK_SET);
			start = ReadNextFromFile(start, pFile);
		}
	}  else {
		printf("FILE OPEN ERROR FOR READ\n");
	}
	
	return start;

}

void stats(){
	int op=1;
	while(!kbhit()||scanf("%d",&op)){
	system("cls");
	printf("************************************************************************************************************************\n");
	sys *temp=start1;
	printf("\t\t\t\t\t\t:Higher bandwidth system:\n");
	 while(temp!=NULL)
	  {
	  	if((temp->presence)==1){
	  	printf("System No:%d\n Occupied by Name/uniq:%s\n\n",temp->system,temp->user);
	  	printf("time:%d min %d sec",(((clock()-(temp->t))/CLOCKS_PER_SEC)/60),(((clock()-(temp->t))/CLOCKS_PER_SEC)%60));
	  	 if(((clock()-(temp->t))/CLOCKS_PER_SEC)>=180)
	  	  printf("\nWARNING.Time limit crossed\n");
	  	 printf("\n");
	  }
	  else{
	   printf("System No:%d\n Occupied by Name/uniq:%s\n\n",temp->system,temp->user);
	  	printf("time:%d",temp->t);
	  	 printf("\n");
	  }
	  	temp=temp->next;
	  }
	  low* temp1=start2;
	  printf("\t\t\t\t\t\t:Lower bandwidth system:\n");
	  while(temp1!=NULL){
	  	if((temp1->presence)==1){
	  	printf("System No:%d\n Occupied by Name/uniq:%s\n",temp1->system,temp1->user);
	  	printf("time:%d min %d sec",(((clock()-(temp1->t))/CLOCKS_PER_SEC)/60),(((clock()-(temp1->t))/CLOCKS_PER_SEC)%60));
	  }
	  else{
	  	printf("\nSystem No:%d\n Occupied by Name/uniq:%s\n",temp1->system,temp1->user);
	  	printf("time:%d",temp1->t);
	  	 printf("\n");
	  }
	  	temp1=temp1->next;
	  }
	   printf("ENTER 0 TO EXIT:");
	     if(op==0)
	       break;
	       sleep(1);
}	  
}
int search(char *x){
	user *temp=start;
	 while(temp!=NULL){
	 	if(strcmp((temp->uniquekey),x)==0)
	 	 return 1;
	 	temp=temp->next;
	 }
	 if(temp==NULL)
	  return 0;
}
void systemprint(){
	sys *temp=start1;
	printf("\t\t\t\t\t\t  :SYSTEM IN THE CAFE:\n");
	printf("\n");
	  while(temp!=NULL){
	  	if((temp->presence)==0){
	  		printf("\t\t\t\t\t    System no %d Is Free for use.\n",temp->system);
	  		 printf("\n");
		  }
		  temp=temp->next;
	  }
}

void allocsys(int op,char *x){
	sys *temp=start1;
	 while(temp!=NULL){
	 	if((temp->system)==op){
	 		int i=1;
		   temp->presence=i;
	 		 strcpy((temp->user),x);
	 		  temp->t=clock();
	 		 break;
		 }
		 temp=temp->next;
	 }
}
void alloc(char *x){
	int op;
	system("cls");
	printf("************************************************************************************************************************\n");
	printf("\t\t\t\t\t       :HIGHERBANDWIDTH SYSTEMS:\n");
	printf("\n");
	 systemprint();
	  printf("\t\t\t\t\t  Enter system no to be allocated:");
	   scanf("%d",&op);
	    allocsys(op,x);
		  printf("System has been alloted to the user with the unique key:%s",x);
		   printf("please wait...");
		   sleep(3);
}
void check_user(){
	char uniq[5];
	system("cls");
	printf("************************************************************************************************************************\n"); 
	 printf("\t\t\t\t Enter the Unique Key of the user:");
	  scanf("%s",uniq);
	   if(search(uniq)==1){
	   	 alloc(uniq);
	   }
	   else
	    printf("user doesnt exist.\n");
	    sleep(2);
	return ;
}
//int bill(int x){
	
//}
void guest(){
	char a[20];
	int op;
	system("cls");
	   printf("************************************************************************************************************************\n");
	    printf("\t\t\t\t\t\t:GUEST ALLOCATION:\n");
		 printf("\n\t\t\t\t\t\tENTER THE NAME OF THE USER:");
		  scanf("%s",a);
		   printf("\t\t\t\t\t\t:PLEASE WAIT.....");
		    sleep(3);
			  system("cls");
	   printf("************************************************************************************************************************\n");
	   	printf("\t\t\t\t\t\t:HIGHERBANDWIDTH SYSTEMS:\n");
	 systemprint();
	  printf("\t\t\t\t\t  Enter system no to be allocated:");
	   scanf("%d",&op);
	     allocsys(op,a);
		  printf("System has been alloted to the user with the NAME:%s\n",a);
		   printf("please wait...");
		   sleep(3);
}
void billing(int i,char *j,int k){
	system("cls");
	   printf("************************************************************************************************************************\n");
	    printf("\t\t\t\t\t\t  :->BILLING PAGE<-:\n\n");
	     printf("\t\t\t\t\t             SYSTEM NO:%d\n\n",k);
	      printf("\t\t\t\t\t TOTAL TIME SPENT BY THE USER:%d hr %d m %d s\n\n",(i/3600),(i/60),(i%60));
	      i/=60;
	       printf("\t\t\t\t\t          USER/UNIQUE KEY:%s\n\n",j);
	        printf("\t\t\t\t\t\t     BILLING SCHEME:\n\n\t\t\t\t              WITHIN THE TIME LIMIT(3min)-RS 3/-\n\n");
	         printf("\t\t\t\t      EXCEDDING THE TIME LIMIT 'EVERY 1 MIN'-RS 0.5/-\n\n");
	          printf("\t\t\t\t\t\tTOTAL AMOUNT:%f\n\n",(i<3)?3:((i-3)*0.5)+3);
	           printf("\t\t\t\t        PLEASE VISIT THE COUNTER TO PAY THE AMOUNT.\n");
	            sleep(5);
}
int remove1(int op){
	int tt;
	char bill[20];
	sys *temp=start1;
	while(temp!=NULL){
	       	 if((temp->system)==op&&(temp->presence)==1){
	       	 	 temp->presence=0;
	       	 	 strcpy(bill,(temp->user));
	       	 	 strcpy((temp->user),"NO ONE");
	       	 	  tt=(clock()-(temp->t))/CLOCKS_PER_SEC;
	       	 	  printf("Total time spent by the user:%d sec",tt);
	       	 	  temp->t=0;
	       	 	  billing(tt,bill,op);
	       	 	  return 1;
				}
				temp=temp->next;
		   }
		   if(temp==NULL){
		   	printf("\t\t\t\t\t\tSYSTEM HAS NO USER TO IT.\n\n");
		   }
}
int remove2(int op){
	int tt;
	char bill[20];
	 low *temp=start2;
	  while(temp!=NULL){
	  	if((temp->system)==op&&(temp->presence)==1){
	       	 	 temp->presence=0;
	       	 	 strcpy(bill,(temp->user));
	       	 	 strcpy((temp->user),"NO ONE");
	       	 	  tt=(clock()-(temp->t))/CLOCKS_PER_SEC;
	       	 	  //printf("Total time spent by the user:%d sec",tt);
	       	 	  billing(tt,bill,op);
	       	 	  temp->t=0;
	       	 	  return 1;
				}
				temp=temp->next;
		   }
		   if(temp==NULL){
		   	return 0;
		   }
	  }
void deallocate(int op){
	system("cls");
	   printf("************************************************************************************************************************\n"); 
	   printf("\t\t\t\t\t\t:DEALLOCATION:\n");
	   // printf("\t\t\t\t\t\t1.HIGHER BANDWIDTH SYSTEM\n");
	     //printf("\t\t\t\t\t\t2.LOWER BANDWISTH SYSTEM\n");
	      //printf("\t\t\t\t\t\tENTER CHOICE:");
	       //scanf("%d",&ch);
	       //if(ch==1){
	     //printf("\t\t\t\tEnter the system no to be deallocated:");
	      //scanf("%d",&op);
	      remove1(op);
		    sleep(5);
		///}
		 ///if(ch==2){
		 //	printf("\t\t\t\tEnter the system no to be deallocated:");
		 	////scanf("%d",&op);
		 	//(remove2(op)==1)?printf("\nSuccess"):printf("\nNO USER");
		 //	sleep(5);
		// }
		   
}
void deallocate2(){
 int ch;
	system("cls");
	   printf("************************************************************************************************************************\n"); 
	   printf("\t\t\t\t\t\t:DEALLOCATION:\n");
	   printf("\t\t\t\t\t\t.Enter the Higher SYSTEM no to be deallocated:");
	     //printf("\t\t\t\t\t\t2.LOWER BANDWISTH SYSTEM\n");
	      //printf("\t\t\t\t\t\tENTER CHOICE:");
	       scanf("%d",&ch);
	       //if(ch==1){
	     //printf("\t\t\t\tEnter the system no to be deallocated:");
	      //scanf("%d",&op);
	      remove1(ch);
		    sleep(5);
		///}
		 ///if(ch==2){
		 //	printf("\t\t\t\tEnter the system no to be deallocated:");
		 	////scanf("%d",&op);
		 	//(remove2(op)==1)?printf("\nSuccess"):printf("\nNO USER");
		 //	sleep(5);
		// }
		   
}
void deallocate1(){
	int op;
	system("cls");
	   printf("************************************************************************************************************************\n"); 
	   printf("\t\t\t\t\t\t:DEALLOCATION:\n");
	   // printf("\t\t\t\t\t\t1.HIGHER BANDWIDTH SYSTEM\n");
	     //printf("\t\t\t\t\t\t2.LOWER BANDWISTH SYSTEM\n");
	      //printf("\t\t\t\t\t\tENTER CHOICE:");
	       //scanf("%d",&ch);
	       //if(ch==1){
	     //printf("\t\t\t\tEnter the system no to be deallocated:");
	      //scanf("%d",&op);
	      //(remove1(op)==1)?printf("\nSuccess"):printf("\nNO USER");
		  //  sleep(5);
		///}
		 ///if(ch==2){
		 printf("\t\t\t\tEnter the LOWER system no to be deallocated:");
		scanf("%d",&op);
		 	(remove2(op)==1)?printf("\nSuccess"):printf("\nNO USER");
		 	sleep(5);
		// }
		   
}
void printlower(){
	low *temp=start2;
	 while(temp!=NULL){
	 	if((temp->presence)==0){
	 	printf("\t\t\t\t\tLOWER BANDWIDTH SYSTEM NO %d is free for reallocation.\n",temp->system );
	 	 printf("\n");
	 }
	 	temp=temp->next;
	 }
}
void change(int a,int b){
	sys *temp=start1;
	 while(temp!=NULL){
	 	if((temp->system)==a){
	 		if((temp->presence)==1){
	 		strcpy(cpy,(temp->user));
	 		 cptt=(temp->t);
	 		 temp->t=0;
	 		 temp->presence=0;
	 		 strcpy((temp->user),"NO ONE");
	 		  printf("\t\t\t\t\t\tSystem NO %d has been reallocated to Lower system no %d\n",a,b);
	 		   break;
	 	   }
		 
		 else if((temp->presence)==0)
		 	printf("\t\t\t\t\t\tNO SYSTEM ARE CURRENTLY OCCUPIED.\n");
		 	return ;
		 	 break;
		 }
		 temp=temp->next;
	 }
	 low *temp1=start2;
	  while(temp1!=NULL){
	  	if((temp1->system)==b){
	  		strcpy((temp1->user),cpy);
	  		 temp1->t=cptt;
	  		 temp1->presence=1;
	  		  break;
		  }
		  temp1=temp1->next;
	  }
	 sleep(5);
}
void reallocate(int b){
	int a;
	system("cls");
	 printf("************************************************************************************************************************\n");
	  printlower();
	   printf("ENTER THE SYSTEM NO TO BE USED FOR REALLOCATION:");
	    scanf("%d",&a);
	//	 printf("Enter the system no from the higher bandwidth to be reallocated:");
	//	  scanf("%d",&b); 
		  change(b,a); 
		  
}
void warning(){
	char ch;
	sys *temp=start1;
	 while(temp!=NULL){
	 	if((temp->t)==0&&(temp->presence)==0)
	 	  printf("");
	 	else if(((clock()-(temp->t))/CLOCKS_PER_SEC)>=30&&(temp->presence)==1){
	 		system("cls");
	 		printf("\t\t\tWARNING:SYSTEM NO %d Has reached the time limit of 60 secs.\n\n",temp->system);
	 		 printf("\t\t\t\tDOES THE USER WANT TO CONITNUE[Y/N]:");
	 		  scanf(" %c",&ch);
	 		   if(ch=='Y')
	 		    reallocate((temp->system));
	 		    else deallocate((temp->system));
		 }
		 temp=temp->next;
	 }
}
int ch() {	
	
	char command[50];
	char input[50];	

	while(1)  {
	system("cls");
	 printf("************************************************************************************************************************\n"); 
	  printf("\t\t\t\t\t\t: CONTROL PANEL:\n");
	   printf("\t\t\t\t\t\t1.'add'->to add new user.\n");
	    printf("\n\t\t\t\t\t\t2.'delete'->to delete the existing user.\n ");
	     printf("\n\t\t\t\t\t\t3.'quit'->to exit the panel.\n");
	      printf("\n\t\t\t\t\t\t4.'stats'->real time Statistics.\n");
	       printf("\n\t\t\t\t\t\t5.dealloc->freeing lower systems.\n");
	        printf("\n\t\t\t\t\t\t6.'hdealloc'->freeing higher systems before the time limit.");
	      printf("\n\t\t\t\t\t\tEnter the desired command:");
	      fgets( input, 49, stdin);
		sscanf(input,"%s",command);	
		if ( strncmp(command, "quit", 4) == 0) {
			printf("\n\nBreaking...\n");
			break;		
		} else if ( strncmp(command, "print", 5) == 0) {
			PrintList(start);
		} else if ( strncmp(command, "write", 5) == 0) {
			WriteListToFile(start);
		} else if ( strncmp(command, "read", 4) == 0) {
			start = ReadListIn(start);
		} else if ( strncmp(command, "addstart", 8) == 0) {
			start = AddToStart(start);
				
			//PrintList(start);
		} else if ( strncmp(command, "add", 3) == 0) {
			start = AddToEnd(start);
			//PrintList(start);
			WriteListToFile(start);
		} else if ( strncmp(command, "insert", 6) == 0) {
			if(start == NULL) {
				start = AddToStart(start);
			} 
		}//else if(strncmp(command,"new",3)==0)
				//newreport(start);
				else if(strncmp(command,"delete",6)==0){
				 Delete(start);
				 WriteListToFile(start);
				}
				else if(strncmp(command,"stats",4)==0)
				{			stats();
				 break;					 }				 
				else if(strncmp(command,"dealloc",7)==0){
				 deallocate1();
				 break;
			}
			else if(strncmp(command,"realloc",7)==0){
				//reallocate();
				 break;
			}
			else if(strncmp(command,"hdealloc",8)==0){
				deallocate2();
				break;
			}
		
			//PrintList(start);
		
	}
	//CleanUp(start);

	return 0;

}
