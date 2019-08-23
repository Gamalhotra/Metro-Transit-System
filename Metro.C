#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
// fcloseall(); returns 0 if all files were successfully closed ..... returns EOF error to close them
int flag=0,top=-1;
int fare=0;
int front=-1,rear=-1;
int n=0;
FILE *fp1,*fp2,*fp3;
//node* arr[20];
/*struct statinfo
{
	char n[20];
	int tm;
	float d;
}ob;*/
struct personinfo
{
	char name[20];
	char pswd[20];
	int freq;
	int balc;
}od[30];
typedef struct node_type
{
	char st[30];
	float d; // dist us node aur agle vale node ke beeck ka
	int tm;
	char col[20];
	struct node_type *link;
}node;
void queueinst(node*);
void stackinst(node*);
node *start1=NULL,*start2=NULL,*start3=NULL,*start4=NULL,*start5=NULL,*start6=NULL;
char source[30],dest[30];
node* arr[20];
node* stack[20];
// insertion in the linked list ...... called 6 times frm main
node* insert(node* start,char nm[20],float a,int b,char d[20])
{
    node* temp,*t;
	temp=(node*)malloc(sizeof(node));
	strcpy(temp->st,nm);
	temp->d=a;
	temp->tm=b;
	strcpy(temp->col,d);
	temp->link=NULL;
	if(start==NULL)
	{
		start=temp;
		return start;
	}
	else
	{
		t=start;
		while(t->link!=NULL)
			t=t->link;
		t->link=temp;
		return start;
	}
}
// display the linked list
/*void display(node* start)        //have to pass a START pointer here
{
	node *t;
	if(start==NULL)
	printf("List is empty \n");
	else
	{
		t=start1;
		while(t!=NULL)
		{
			printf("\n name ::: %s",t->st);
			printf("\n time ::: %d",t->tm);
			printf("\n distance ::: %f",t->d);
			printf("\n");
			t=t->link;
		}
	}
}*/
void fun(node* start)
{
	//display();
	float dist=0;
	int time=0;
	node* t=start;
	if(flag==1)
	{
		while(strcmp(t->st,source)!=0)
		{
		t=t->link;
		}
		while(strcmp(t->st,dest)!=0)
		{
			time=time+t->tm;
			//printf("time %d \n ",time);
			dist=dist+t->d;
			//printf("dist %f \n ",dist);
			queueinst(t);
			t=t->link;
		}
		queueinst(t);
	}
	else
	{
		while(strcmp(t->st,dest)!=0)
		{
		t=t->link;
		}
		while(strcmp(t->st,source)!=0)
		{
			time=time+t->tm;
			//printf("time %d \n ",time);
			dist=dist+t->d;
			//printf("dist %f \n ",dist);
			stackinst(t);
			t=t->link;
		}
		stackinst(t);
	}
	fare=2*dist;
	printf("Fare=Rs%d\nDistance=%f Km\nTime=%d min\n",fare,dist,time);
}
// finding source and destination
int find(node* start)
{
	int l=0,r=0;
	node* temp=start;
	int s=0,de=0;
	while(temp!=NULL)
	{
		l++;
		if(strcmp(temp->st,source)==0)
		{
			s=1;
			break;
		}
		temp=temp->link;
	}
	temp=start;
	while(temp!=NULL)
	{
		r++;
		if(strcmp(temp->st,dest)==0)
		{
			de=1;
			break;
		}
		temp=temp->link;
	}
	// flag=1 source then dest .......... flag=2 dest then source
	if(l<r)
		flag=1;
	else
		flag=2;
	if(s==1&&de==1)
	return 1;
	else
	return 0;
}
//stack
void stackinst(node* ptr)
{
	top++;
	stack[top]=ptr;
}
void stackpop()
{
	int i;
	printf("\n");
	for(i=top;i>=0;i--)
	{
		printf("%s %s \n",stack[i]->st,stack[i]->col);
	}
}
//queue
void queueinst(node* ptr)
{
	if(front==-1&&rear==-1)
	{
		front=rear=0;
	}
	else
	rear++;
	arr[rear]=ptr;
}
void queuedisplay()
{
	int i;
	printf("\n");
	printf("LINE COLOUR\tSTATION\n");
	for(i=front;i<=rear;i++)
	{  if(arr[i]->col[0]=='R')
	   textcolor(RED);
	   if(arr[i]->col[0]=='Y')
	   textcolor(YELLOW);
	   if(arr[i]->col[0]=='B')
	   textcolor(BLUE);
	    cprintf("%s",arr[i]->col);
	    printf("\t\t");
		textcolor(WHITE);
		cprintf("%s",arr[i]->st);
		printf("\n");
	}
}
int smartcard()
{
	int td=0;
	int i=0;
	char username[40],pass[20],g,a[20],b[20];
	int r=0,c=0,d=0;
	fp1=fopen("sc.txt","r");
	while((fscanf(fp1,"%s %s %d %d",a,b,&c,&d))!=EOF)  // a-name b-password c-freq d-paise
	{
		strcpy(od[n].name,a);//n is global
		strcpy(od[n].pswd,b);
		od[n].freq=c;
		od[n].balc=d;
		n++;
	}
	printf("Do you have a Smartcard?(Y/N) ::: ");
	fflush(stdin);
	scanf("%c",&g);
	label4:
	printf("Enter your name ::: ");
	fflush(stdin);
	gets(username);
	if((g=='y')||(g=='Y'))
	{
		label3:
		printf("Enter your password ::: ");
		gets(pass);
		for(i=0;i<n;i++)
		{
			if(strcmp(od[i].name,username)==0)
			{
				if(strcmp(od[i].pswd,pass)==0)
				{
					printf("freq %d baln %d ",od[i].freq,od[i].balc);
					if(od[i].freq==5)
						{
							printf("You have travelled 5 times in a row !!!! \n");
							printf("Your fare is free !!!!!");
							od[i].freq=0;
							return 1;
						}
					else
						{
							od[i].freq++;
						}
					if(od[i].balc<fare)
						{
							printf("Your balance in the card is low \n");
							printf("Recharge money");
							scanf("%d",&r);
							od[i].balc=od[i].balc+r-fare;
							printf("Net balance left ::: %d ",od[i].balc);
						}
					else
						{
							od[i].balc=od[i].balc-fare;
							printf("The balance left in your card is ::: %d",od[i].balc);
						}
					return 1;
				}
				else
				{
					printf("Incorrect password \n");
					goto label3;
				}
			}
		}
				printf("Incorrect username \n");
				goto label4;
	}
	else
	{
		n=n+1;
		fp1=fopen("sc.txt","a");
		printf("Enter a valid password of characters ::: ");
		gets(pass);
		do
		{
		printf("Recharge of ??? ");
		scanf("%d",&d);
		td=td+d;
		}while(td<=fare);
		td=td-fare;
		printf("The balance left in yr card is ::: %d",td);
		fprintf(fp1,"%s %s %d %d \n",username,pass,1,td);
		fclose(fp1);
		return 0;
	}
}

int main()
{
int gd=DETECT,gm;
int i,u=0,c=0;
node *ref;
float b=0;
char a[20],d[20];
FILE *fp;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

setcolor(CYAN);
rectangle(200,10,400,30);
rectangle(200,35,400,55);
rectangle(200,60,400,80);
rectangle(200,85,400,105);
rectangle(200,110,400,130);
rectangle(200,135,400,155);
rectangle(200,160,400,180);
rectangle(200,185,400,205);
rectangle(200,210,400,230);
rectangle(200,235,400,255);
rectangle(200,260,400,280);
rectangle(200,285,400,305);
rectangle(200,310,400,330);
rectangle(200,335,400,355);
rectangle(200,360,400,380);
rectangle(200,385,400,405);
rectangle(200,410,400,430);
rectangle(200,435,400,455);
rectangle(200,460,400,480);
rectangle(0,460,170,480);
rectangle(430,10,630,30);
rectangle(430,35,630,55);
rectangle(430,60,630,80);
line(300,30,300,35);
line(300,55,300,60);
line(300,80,300,85);
line(300,105,300,110);
line(300,130,300,135);
line(300,155,300,160);
line(300,180,300,185);
line(300,205,300,210);
line(300,230,300,235);
line(300,255,300,260);
line(300,280,300,285);
line(300,305,300,310);
line(300,330,300,335);
line(300,355,300,360);
line(300,380,300,385);
line(300,405,300,410);
line(300,430,300,435);
line(300,455,300,460);
line(170,470,200,470);
line(400,20,430,20);
line(530,30,530,35);
line(530,55,530,60);

outtextxy(225,20,"RajendraPlace");
outtextxy(225,45,"KarolBagh");
outtextxy(225,70,"RKAshramMarg");
outtextxy(225,95,"Jhandewalan");
outtextxy(225,120,"RajivChowk");
outtextxy(225,145,"BarakhambaRoad");
outtextxy(225,170,"MandiHouse");
outtextxy(225,195,"PragatiMaidan");
outtextxy(225,220,"Indraprastha");
outtextxy(225,245,"YamunaBank");
outtextxy(225,270,"Akshardham");
outtextxy(225,295,"MayurVihar");
outtextxy(225,320,"MayurViharExt");
outtextxy(225,345,"NewAshokNagar");
outtextxy(225,370,"NoidaSec15");
outtextxy(225,395,"NoidaSec16");
outtextxy(225,420,"NoidaSec18");
outtextxy(225,445,"BotanicalGarden");
outtextxy(225,470,"GolfCourse");
outtextxy(20,470,"NoidaCityCenter");
outtextxy(480,20,"PatelNagar");
outtextxy(480,45,"ShadiPur");
outtextxy(480,70,"KirtiNagar");
setcolor(LIGHTRED);
rectangle(430,210,630,230);
rectangle(430,235,630,255);
rectangle(430,260,630,280);
rectangle(430,285,630,305);
rectangle(430,310,630,330);
rectangle(430,335,630,355);
rectangle(430,360,630,380);

line(400,220,430,220);
line(530,230,530,235);
line(530,255,530,260);
line(530,280,530,285);
line(530,305,530,310);
line(530,330,530,335);
line(530,355,530,360);

outtextxy(480,220,"LaxmiNagar");
outtextxy(480,245,"NirmanVihar");
outtextxy(480,270,"PreetVihar");
outtextxy(480,295,"Karkarduma");
outtextxy(480,320,"AnandVihar");
outtextxy(480,345,"Kaushambi");
outtextxy(480,370,"Vaishali");
setcolor(YELLOW);
rectangle(0,85,170,105);
rectangle(0,110,170,130);
rectangle(0,135,170,155);
rectangle(0,160,170,180);
rectangle(0,185,170,205);

line(170,95,200,95);
line(70,105,70,110);
line(70,130,70,135);
line(70,155,70,160);
line(70,180,70,185);
outtextxy(50,95,"NewDelhi");
outtextxy(50,120,"ChawriBazar");
outtextxy(50,145,"ChandniChowk");
outtextxy(50,170,"KashmeriGate");
outtextxy(50,195,"CivilLines");

getch();
closegraph();

	fp=fopen("a1.txt","r");
	while((fscanf(fp,"%s %f %d %s",a,&b,&c,d))!=EOF) // a-name b-distance c-time d-colour
	{
		start1=insert(start1,a,b,c,d);
	}
	fclose(fp);
	fp=fopen("a2.txt","r");
	while((fscanf(fp,"%s %f %d %s",a,&b,&c,d))!=EOF)
	{
		start2=insert(start2,a,b,c,d);
	}
	fclose(fp);
	fp=fopen("a3.txt","r");
	while((fscanf(fp,"%s %f %d %s",a,&b,&c,d))!=EOF)
	{
		start3=insert(start3,a,b,c,d);
	}
	fclose(fp);
	fp=fopen("a4.txt","r");
	while((fscanf(fp,"%s %f %d %s",a,&b,&c,d))!=EOF)
	{
		start4=insert(start4,a,b,c,d);
	}
	fclose(fp);
	fp=fopen("a5.txt","r");
	while((fscanf(fp,"%s %f %d %s",a,&b,&c,d))!=EOF)
	{
		start5=insert(start5,a,b,c,d);
	}
	fclose(fp);
	fp=fopen("a6.txt","r");
	while((fscanf(fp,"%s %f %d %s",a,&b,&c,d))!=EOF)
	{
		start6=insert(start6,a,b,c,d);
	}
	fclose(fp);
	label2:
		printf("WELCOME TO OUR METRO\n\n");
		printf("Enter Source ::: ");
		// globally declared src dest
		scanf("%s",source);
		printf("Enter Destination ::: ");
		scanf("%s",dest);
	i=find(start1);
	if(i==1)
		{
		ref=start1;
		goto label1;
		}
	i=find(start2);
		if(i==1)
		{
		ref=start2;
		goto label1;
		}
    i=find(start3);
		if(i==1)
		{
		ref=start3;
		goto label1;
		}
    i=find(start4);
		if(i==1)
		{
		ref=start4;
		goto label1;
		}
	i=find(start5);
		if(i==1)
		{
		ref=start5;
		goto label1;
		}
	i=find(start6);
		if(i==1)
		{
		ref=start6;
		goto label1;
		}
	label1:
	fun(ref);
	u=smartcard();
	if(u==1)
	{
	FILE *fp;
	fp=fopen("sc.txt","w");
	for(i=0;i<n;i++)
		fprintf(fp,"%s %s %d %d\n",od[i].name,od[i].pswd,od[i].freq,od[i].balc);
	fclose(fp);
	}
	if(flag==1)
		queuedisplay();
	else
		stackpop();
		getch();
		return 0;
}

