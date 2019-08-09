/*Welcome to Telephone Directory in C++
  Made by:
	  RITHIK KANT TRIPATHI
	  KETAN SHAH
	  PARIKSHIT RATHORE
  Class: XII-B
*/
/*        HEADER FILES        */
#include<fstream.h>
#include<graphics.h>
#include<process.h>
#include<io.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
/*     class telephone and it's Member Functions  */
class telephone
{ char name[25];
  char address[20];
  char colony[40];
  char phoneno[15];
  char autono[20];
  public:
  telephone(){ }   //Default Constructor
/*   Function for Inserting Record    */
  void getData()
  {
    textcolor(WHITE);
    cprintf("Enter Record-\n\r");
    cprintf("Name    : "); gets(name);
    cprintf("Address : "); gets(address);
    cprintf("Colony  : "); gets(colony);
    cprintf("PhoneNo : "); gets(phoneno);
    cprintf("AutoNo  : "); gets(autono);
  }
/*    Function to Display Record     */
  void Display()
  { textcolor(BLACK);
    cprintf("Record\n\r");
    cprintf("Name    : %s\n\r",name);
    cprintf("Address : %s\n\r",address);
    cprintf("Colony  : %s\n\r",colony);
    cprintf("PhoneNo : %s\n\r",phoneno);
    cprintf("AutoNo  : %s\n\r",autono);
  }
  char namch()
  { return name[0]; }
  char* getName() { return name; }
  char* getAdd() { return address; }
  char* getphon() { return phoneno; }
  char* getcol() { return colony; }
  char* getaut() { return autono; }
};
/*  Insert Function   */
void Insert()
{ telephone t;
  char choice;
  t.getData();
  ofstream file ;
  file.open("teldirt.txt",ios::binary|ios::app);
  file.write((char*)&t,sizeof(telephone));
  cprintf("Insertion Completed\n\r");
  file.close();
  cout<<"\nDo you Want to Insert More Records(Y/N)?"<<endl;
  cin>>choice;
  if(choice=='Y'||choice=='y')
    { Insert(); }
}
/*   Function to display Records colony wise   */
void Dispcol()
{ clrscr();
  telephone telp;
  char colnam[50];
  ifstream file;
  textcolor(BLACK);
  cprintf("**Colonywise Display**\n\r");
  cprintf(" Anukiran Colony \n\r");
  cprintf(" Anupratap Colony\n\r");
  cprintf(" Anutara Colony  \n\r\n\r");
  cprintf("  Enter the Colony Name:- ");
  textcolor(WHITE);
  gets(colnam);
  if(strcmp(colnam,"Anukiran")==0||strcmp(colnam,"Anupratap")==0||strcmp(colnam,"Anutara")==0)
  {int gd=DETECT,gm;
   int i=30;
   initgraph(&gd,&gm,"C:\\tc\\bgi");
   file.open("teldirt.txt",ios::binary|ios::in);
   file.seekg(0,ios::beg);
   cleardevice();
   outtextxy(40,10,"NAME");
   outtextxy(160,10,"ADDRESS");
   outtextxy(295,10,"COLONY");
   outtextxy(450,10,"PHONE No.");
   outtextxy(575,10,"AUTO No.");
   while(file.read((char*)&telp,sizeof(telephone)))
   {
    if(strcmp(telp.getcol(),colnam)==0)
    {
       for(int j=10;j<=500; )
       {
	 outtextxy(j,i,telp.getName());
	 j=j+150;
	 outtextxy(j,i,telp.getAdd());
	 j=j+125;
	 outtextxy(j,i,telp.getcol());
	 j=j+160;
	 outtextxy(j,i,telp.getphon());
	 j=j+140;
	 outtextxy(j,i,telp.getaut());
	}
       delay(500);
      i=i+20;
      if(i>=getmaxy())
	{ cleardevice(); }
    }
   }
  }
  else
    cprintf("Wrong Input!!!Enter a valid Colony Name\n\r");
  file.close();
  delay(3000);
  getch();
  closegraph();
  _setcursortype(_NOCURSOR);
}
/*   Function to Delete a record from the File  */
void Delete()
{ telephone tel1;
  ifstream file ;
  char nam[25],nam1[25];
  cprintf("Enter the Full Name of the record to be Deleted : ");
  gets(nam);
  file.open("teldirt.txt",ios::binary|ios::in);
  ofstream temp;
  temp.open("temp.txt",ios::binary|ios::out);
  file.seekg(0,ios::beg);
  int flag=0;
  while(file.read((char*)&tel1,sizeof(telephone)))
  { if(strcmp(tel1.getName(),nam)==0)
    { flag=1;
      break;
    }
    else
     temp.write((char*)&tel1,sizeof(telephone));
  }
  if(!flag)
  { cprintf("Record not Found\n\r");
  }
  else
  { tel1.Display();
    cprintf("Record Deleted\n\r");
  }
  while(file.read((char*)&tel1,sizeof(telephone)))
  { temp.write((char*)&tel1,sizeof(telephone));
  }
  file.close() ;
  temp.close() ;
  remove("teldirt.txt");
  rename("temp.txt","teldirt.txt");
}
/*   Function to Update a Record  */
void Update()
{ telephone tel1;
  ifstream fin("teldirt.txt",ios::binary);
  ofstream fout("temp.txt",ios::binary);
  char nam[25];
  cprintf("Enter the Name to be Updated: ");
  gets(nam);
  int flag=0;
  while(fin.read((char*)&tel1,sizeof(telephone)))
  { if(strcmp(tel1.getName(),nam)!=0)
     fout.write((char*)&tel1,sizeof(telephone));
    else
    { flag=1;
      cprintf("Enter Modified Record : \n\r");
      tel1.getData();
      fout.write((char*)&tel1,sizeof(telephone));
      break;
    }
  }
  while(fin.read((char*)&tel1,sizeof(telephone)))
   {
    fout.write((char*)&tel1,sizeof(telephone));
   }
  fin.close();
  fout.close();
  if(!flag) cprintf("Record not Found\n\r");
  else      cprintf("Record Modified\n\r");
  remove("teldirt.txt");
  rename("temp.txt","teldirt.txt");
}
/*   Function to Search Record by Name   */
void Searchnam()
{ ifstream file;
  telephone tel1;
  int i=0;
  char nam[25];
  file.open("teldirt.txt",ios::binary);
  cprintf("Enter Full Name to be Searched: ");
  gets(nam);
  file.seekg(0,ios::beg);
  while(file.read((char *) &tel1, sizeof(telephone)))
  { if(strcmpi(tel1.getName(),nam)==0)
    { i=1;
      tel1.Display();
      break ;
    }
  }
  file.close();
  char small;
  if(islower(nam[0])!=0)
    {  small=toupper(nam[0]);  }
  if(i==0)
  { file.open("teldirt.txt",ios::binary);
    file.seekg(0,ios::beg);
    cprintf("Record not Found \n\r");
    cprintf("\nPossible Results as per your search:\n\r");
    while(file.read((char*)&tel1,sizeof(telephone)))
    {
     if(tel1.namch()==nam[0]||tel1.namch()==small)
       {
	 tel1.Display();
	 getch();
       }
    }
  }
  file.close();
}
/*  Function to Search Record by Phone no.  */
void Searchphon()
{
  ifstream file;
  telephone tel2;
  int i=0,choic,a;
  char Phno[25];
  file.open("teldirt.txt",ios::binary);
  cprintf("Enter the Phone No.to be Searched: ");
  gets(Phno);
  file.seekg(0,ios::beg);
  while(file.read((char *) &tel2, sizeof(telephone)))
  { if(strcmp(tel2.getphon(),Phno)==0)
    { i=1;
      tel2.Display();
      break ;
    }
  }
  if(!i)
  { cprintf("Record not Found \n\r"); }
}
/*  Pointer function for selecting options from Menu  */
void Pointer(int cx,int cy,int mod)
{ if(mod==1)
   { textcolor(RED); }
  else
   { textcolor(LIGHTGRAY); }
  gotoxy(cx,cy);
  cprintf("%c",16);
}
/*  Function for Menu  */
int Menu(int Op,char str[][50])
{ textcolor(BLUE);
  textbackground(LIGHTGRAY);
  for(int k=0;k<80;k++)
  {
     for(int l=0;l<40;l++)
      { cprintf(".     "); }
      delay(5);
   cprintf("\r\n");
  }
  textcolor(BLACK);
  for(int i=0;i<Op;++i)
  { gotoxy(28,10+i);
    cprintf("%s",str[i]);
  }
  int ch=0,I=1;
  int cx=26,cy=11;
  Pointer(cx,cy,1);
  while(ch!=13)
  { if(kbhit())
    { ch=getch();
      switch(ch)
      { case 72 : if(I>1)
		  { Pointer(cx,cy,0);
		     --cy; --I;
		     Pointer(cx,cy,1);
		  }
		  break;
	case 80 : if(I<Op-1)
		  { Pointer(cx,cy,0);
		     ++cy; ++I;
		    Pointer(cx,cy,1);
		  }
		  break;
      }
    }
  }
  return I;
}
void thnq()
{ int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\tc\\bgi");
  cleardevice();
  setcolor(YELLOW);
  settextstyle(0,0,3);
  outtextxy(100,100,"THANK YOU");
  delay(2000);
  closegraph();
}
/*  Main Function   */
void main()
{ clrscr();
  int i;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"C:\\tc\\bgi");
  setcolor(WHITE);
  settextstyle(0,0,2);
  for(i=0;i<200;i+=10)
  { outtextxy(10+i,50,"WELCOME TO OUR PROJECT");
    delay(50);
    cleardevice();
  }
  outtextxy(10+i,50,"WELCOME TO OUR PROJECT");
  delay(1000);
  setcolor(MAGENTA);
  settextstyle(0,0,2);
  outtextxy(50,100,"TOPIC:-TELEPHONE DIRECTORY IN C++");
  delay(500);
  setcolor(YELLOW);
  delay(500);
  outtextxy(50,150,"GUIDED BY:-RAJVEER TANWAR SIR");
  delay(500);
  setcolor(LIGHTGRAY);
  outtextxy(50,200,"MADE BY:-");
  delay(500);
  setcolor(LIGHTRED);
  outtextxy(150,250,"RITHIK KANT TRIPARTHI");
  delay(500);
  setcolor(WHITE);
  outtextxy(200,300,"PARIKSHIT RATHORE");
  delay(500);
  setcolor(GREEN);
  outtextxy(250,350,"KETAN SHAH");
  delay(3000);
  closegraph();
  telephone tel;
  int ch,ca,cs;
  _setcursortype(_NOCURSOR);
  char frnt[][50]={"TELEPHONE DIRECTORY",  //Options for Main Menu
		   "1. Search",
		   "2. Modifications",
		   "3. Colonywise Employee records",
		   "4. EXIT"
		  };
  char str[][50]={ "MODIFICATIONS  :-",    //Options for Modifications
		   "A. Insert New Record",
		   "B. Delete Old Record",
		   "C. Update a Record",
		   "D. Return to Main Menu"
		 };
  char srnt[][50]={ "SEARCH BY:",         //Options for Search
		    "A. Search by Name",
		    "B. Search by PhoneNo.",
		    "C. Return to Main Menu"
		  };
  do
  { clrscr();
    ch=Menu(5,frnt);
    clrscr();
    gotoxy(1,1);
    textcolor(WHITE);
    switch(ch)
    {
      case 1 : cs=Menu(4,srnt);
	       clrscr();
	       gotoxy(1,1);
	       textcolor(WHITE);
	       switch(cs)
	       { case 1 : Searchnam(); break;
		 case 2 : Searchphon(); break;
		 case 3 : break;
	       }
		break;
      case 2 : ca=Menu(5,str);
	       clrscr();
	       gotoxy(1,1);
	       textcolor(WHITE);
	       switch(ca)
	       { case 1 : Insert(); break;
		 case 2 : Delete(); break;
		 case 3 : Update(); break;
		 case 4 : break;
	       }
		break;
      case 3 : Dispcol();  break;
      case 4 : thnq();return;
      default : cout<<"Wrong Input   \n"; break;
    }
    getch();
   }while(1);
}





















