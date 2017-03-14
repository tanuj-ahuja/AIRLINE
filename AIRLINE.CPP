#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<process.h>
#include<string.h>
#include<fstream.h>
#include<stdio.h>
fstream fcust,fman,ftemp,forder;  //'ftemp' variable for temp. ftemp,'fman' for manager
				 //'fcust' for customer 'forder' for collecting orders


class customer
{
int ph;
char name[50],podep[30],podes[30],add[100],email[60],date[15];
public:
void custgetdata()
{
cout<<"enter name\n";
cin>>name;
cout<<"enter phone number\n";
cin>>ph;
cout<<"enter emailid\n";
cin>>email;
cout<<"enter address\n";
cin>>add;
}
void show()
{           cout<<endl;
cout<<name<<"    "<<ph<<"    "<<email<<"    "<<add;
}
int retname(char z[])
{
if(strcmpi(name,z)==0)
return 1;
else
return -1;
}
}u;



class manager
{
int tno,price;
char apodes[50],apodep[50],adate[15],todep[15],toarr[15];
public:
void mangetdata()
{
cout<<"ENTER FLIGHT NUMBER\n";
cin>>tno;
cout<<"ENTER FLIGHT ARRIVAL DATE\n";
cin>>adate;
cout<<"ENTER TIME OF DEPARTURE\n";
cin>>todep;
cout<<"ENTER TIME OF ARRIVAL\n";
cin>>toarr;
cout<<
"ENTER PLACE OF DEPARTURE\n";
cin>>apodep;
cout<<"ENTER ENTER PLACE OF DESTINATION\n";
cin>>apodes;
cout<<"ENTER COST OF FLIGHT\n";
cin>>price;
}
void mandisplay()
{
cout<<tno<<"      "<<todep<<"     "<<toarr<<"     "<<adate<<"      "<<apodep<<"      "<<apodes<<"      "<<price<<endl;
}
int retpodep(char temppodep[])
{
	 if(strcmp(apodep,temppodep)==0)
		 return 1;
	 else
		 return -1;
}
int retpodes(char n[20])
{
	if (strcmpi(apodes,n)==0)
		 return 1;
	else
			return -1;
}
int rettodep(char s[])
{
	if(strcmpi(todep,s)==0)
		 return 1;
	else
		 return -1;
}
int rettoarr(char d[])
{
	if(strcmpi(toarr,d)==0)
		 return 1;
	else
		 return -1;
}

int retdate(char h[])
{  if(strcmpi(adate,h)==0)
			return 1;
	 else
			return -1;
}
int retprice()
{
return price;
}


}a;

void canceldata()
{
		 clrscr();
		 fman.open("admin.dat",ios::in);
		 ftemp.open("ttemp.dat",ios::out);
		 char n[20],s[15],d[15],h[15];
		 cout<<"\nENTER DESTINATION OF FLIGHT TO BE CANCELLED\n";
		 cin>>n;
			cout<<"\nENTER DATE OF FLIGHT TO BE CANCELLED\n";
		 cin>>h;
			cout<<"\nENTER TIME OF DEPARTURE OF FLIGHT TO BE CANCELLED\n";
		 cin>>s;
			cout<<"\nENTER TIME OF ARRIVAL OF FLIGHT TO BE CANCELLED\n";
		 cin>>d;
		 while(!fman.eof())
		 {
			 fman.read((char*)&a,sizeof(a));
			 if(fman.eof()) break;
			 if(a.retpodes(n)!=1&&a.retdate(h)!=1&&a.rettodep(s)!=1&&a.rettoarr(d)!=1)
			 ftemp.write((char*)&a,sizeof(a));
		 }
		 fman.close();
		 ftemp.close();
		 remove("admin.dat");
		 rename("ttemp.dat","admin.dat");
}




void modifydata()             //to modify manager data
{  clrscr();
	 fman.open("admin.dat",ios::out|ios::in);
		 int i=0;
		 char n[20];
		 cout<<"ENTER DESTINATION OF THE FLIGHT TO BE MODIFIED\n";
		 cin>>n;
		 while(!fman.eof())
		 {
			 fman.read((char*)&a,sizeof(a));
			 i++;
			 if(fman.eof()) break;
			 if(a.retpodes(n)==1)
			 { cout<<"\nENTER DATA FOR MODIFICATION\n";
				 a.mangetdata();
				 fman.seekg((i-1)*sizeof(a),ios::beg);
				 fman.write((char*)&a,sizeof(a));
		 }
			else
		 cout<<"not found";
		 }fman.close();
}


void custsearch()
{      clrscr();
	int tickets,cost=0;
char tempdate[15],temppodep[30],temppofdes[30],c,n[30],h[30],z[20];

cout<<"ENTER PREFFERD DATE OF FLIGHT\n";
cin>>h;
cout<<"ENTER PLACE OF DEPARTURE\n";
cin>>temppodep;
cout<<"ENTER PLACE OF DESTINATION\n";
cin>>n;
cout<<"ENTER YOUR NAME\n";
cin>>z;

fman.open("admin.dat",ios::in);
forder.open("or.dat",ios::app);
fcust.open("userr.dat",ios::in);
while(!fman.eof()&&!forder.eof())
{
fman.read((char*)&a,sizeof(a));
if(fman.eof())break;
fcust.read((char*)&u,sizeof(u));
if(fcust.eof())break;
if(a.retdate(h)==1 && a.retpodep(temppodep)== 1 && a.retpodes(n)==1 && u.retname(z)==1)
{a.mandisplay();
cout<<"ENTER NO OF PASSENGERS\n";
cin>>tickets;
cost=tickets*a.retprice();
cout<<"\nPRESS 'b' TO BOOK TICKETS AND PRESS 'R'TO RETURN TO MAIN MENU \n";
cout<<"COST ="<<cost;
cin>>c;
if(c=='b')
{forder.write((char*)&a,sizeof(a));
forder.write((char*)&u,sizeof(u));
cout<<"YOUR FLIGHTS HAVE BEEN CONFIRMED  ";
gotoxy(25,17);cout<<"HAVE A SAFE JOURNEY!!!!!!!!";
gotoxy(25,18);cout<<"****VISIT AGAIN****";getch();}
else if(c=='r')
return;


}}
fman.close();
forder.close();
fcust.close();
}


void order()
{
   clrscr();
forder.open("or.dat",ios::in);
while(!forder.eof())
{
 forder.read((char*)&a,sizeof(a));
 if(forder.eof())break;
 forder.read((char*)&u,sizeof(u));
 if(fcust.eof())break;
 a.mandisplay();
 u.show();
}
forder.close();
}


void cwritedata()
{
fcust.open("userr.dat",ios::app);
u.custgetdata();
fcust.write((char*)&u,sizeof(u));
fcust.close();
}

void awritedata()
{
fman.open("admin.dat",ios::app);
a.mangetdata();
fman.write((char*)&a,sizeof(a));
fman.close();
}


void areaddata()
{   clrscr();
fman.open("admin.dat",ios::in);
while(!fman.eof())
{
 fman.read((char*)&a,sizeof(a));
 if(fman.eof())break;
 a.mandisplay();
}
fman.close();
}



void manmenu()
{
char choice;
do
{
cout<<"\n\n\n1.ADD FLIGHT DETAILS\n2.DISPLAY FLIGHT DETAILS\n3.MODIFY FLIGHT DETAILS\n4.CANCEL A FLIGHT\n5.DISPLAY ORDERS\n6.BACK TO MAIN MENU\n";
cout<<"ENTER CHOICE\n";
cin>>choice;
switch(choice)
{
case '1':awritedata();
				 clrscr();
				 break;

case '2':areaddata();
				 break;

case '3':modifydata();
				 break;

case '4':canceldata();
				 clrscr();
				 break;

case '5':order();

				 break;
case '6':clrscr();
				 return;
}
}while(choice!='6');
}


void custmenu()
{
char cho;
do
{
cout<<"\n1.ENTER DETAILS\n2.SEARCH FLIGHTS\n3.BACK TO MAIN MENU\n";
cout<<"ENTER CHOICE\n";
cin>>cho;
switch(cho)
{
case '1':cwritedata();
				 break;
case '2':custsearch();
				 break;
case '3':clrscr();
				 return;
}
}while(cho!='3');
}

void main()
{
clrscr();
fstream fman,fcust;
int i=0;
char ch,pass[20],x;
do
{
gotoxy(20,1);cprintf("w       w  e e e  l      c c c  o o o  m m m  e e e");
gotoxy(20,2);cprintf(" w  w  w   e e    l      c      o   o  m m m  e e  ");
gotoxy(22,3);cprintf(  "w  w     e e e  l l l  c c c  o o o  m   m  e e e");


gotoxy(10,6);cprintf ("                    *                     ");
gotoxy(10,7);cprintf  ("                  *                      ");
 gotoxy(10,8);cprintf ("             * * *                       ");
 gotoxy(8,9);cprintf ("                 * *                      ");
 gotoxy(16,10);cprintf("	       *  *                      ");
 gotoxy(15,11);cprintf("	      *                          ");
 gotoxy(15,12);cprintf("	    *  *                         ");
 gotoxy(15,13);cprintf("	  *     *                        ");
 gotoxy(15,14);cprintf("  ***INDIGO***                       ");



//gotoxy(10,3);cprintf("        WELOME        TO          JET     AIRWAYS");
gotoxy(35,10);
cprintf("1.MANAGER MODE");
gotoxy(35,11);
cprintf("2.CUSTOMER MODE");
gotoxy(35,12);
cprintf("3.EXIT");
gotoxy(35,13);
cprintf("ENTER CHOICE");
cout<<endl;
gotoxy(35,14);
cin>>ch;
switch(ch)
{
	case'1':
	clrscr();

	 cout<<"enter password\n";
	 do
	 {
	 x=getch();
	 cout<<"*";
	 pass[i]=x;
	 i++;
	 }
	 while(x!=13);
	 pass[i-1]='\0';
	 if(strcmp(pass,"tanuj")==0)

	 {
	 cout<<"\n\nwelcome";
	 delay(1000);
	 manmenu();
	 }
	 else
	 cout<<"wrong password";
	 break;
	 case '2': clrscr();
						custmenu();
						break;
	 case '3':  exit(0);
						break;
}
}while(ch!='3');

getch();
}

