#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

class customer
{
	char cname[50];
	char caddress[100];
	char stat[15];
	int cno;
	int nomem;
	char checkindate[30],checkoutdate[30];
	time_t checkin,checkout;
	char phoneno[20];
	long noday;
	int villa,family,couple,single,vip;
	int rtype,rno;
	public:
	customer();
	void unassignroomno();
	void bill();
	void enterinfo();
	void alottroom();
	void showinfo(int);
	void searchcus();
	void setdate(char *,time_t);
};
//STRUCTURE FOR ASSIGNINIG ROOM NOS. TO THE CUSTOMERS
struct rooms
{
	int roomno;
	int status;
};
rooms a[250];


//CONSTRUCTOR OF CUSTOMER CLASS
customer::customer()
{
	cname[0]='\0';
	caddress[0]='\0';
	stat[0]='\0';
	checkindate[0]='\0';
	strcpy(checkoutdate," NOT CHECKED OUT ");
	nomem=0;
	phoneno[0]='\0';
	rno=1;
	single=100;
	couple=101;
	family=151;
	villa=201;
	vip=226;
}


//FUNCTION TO CHANGE THE STATUS OF ARRAY FROM '0' TO '1'
int assignroom(int rtyp)
{
	int no;
	fstream file;
	file.open("customer.dat",ios::app|ios::in|ios::binary);
	int j;

	switch(rtyp)
	{
		case 1: //SINGLE ROOM
			for(j=1;j<101;j++)
			{
				if(a[j].status==0)
				{

					no=a[j].roomno;
					a[j].status=1;
					break;
				}
				else
					continue;


			}
			break;
		case 2: //COUPLE ROOM
			for(j=101;j<151;j++)
			{
				if(a[j].status==0)
				{

					no=a[j].roomno;
					a[j].status=1;
					break;
				}
				else
					continue;


			}
			break;
		case 3: //FAMILY ROOM
			for(j=151;j<201;j++)
			{
				if(a[j].status==0)
				{

					no=a[j].roomno;
					a[j].status=1;
					break;
				}
				else
					continue;


			}
			break;
		case 4: //PRESIDENTIAL SUITE
			for(j=201;j<226;j++)
			{
				if(a[j].status==0)
				{

					no= a[j].roomno;
					a[j].status=1;
					break;
				}
				else
					continue;


			}
			break;
		case 5: //V.I.P. ROOM
			for(j=225;j<250;j++)
			{
				if(a[j].status==0)
				{

					no=a[j].roomno;
					a[j].status=1;
					break;
				}
				else
					continue;


			}
			break;
	  }
	  cout<<"\nYOUR ROOM NO IS : "<<no<<endl;
	  getch();
	  file.close();
	  return no;

}

//FUNCTION TO CHANGE THE STATUS OF THE ARRAY FROM '1' TO '0'
void unalottroom(int r)
{
	a[r].status=0;
}



//TO ASK DETAILS OF THE CUSTOMER
void customer::enterinfo()
{
	fstream file;
	file.open("customer.dat",ios::app|ios::binary);
	time_t t;
	t = time(NULL);
	checkin=t;
	clrscr();
	cout<<"\nCURRENT DATE: "<<ctime(&t);
	cout<<"\nENTER NAME:";
	gets(cname);
	cout<<"\nENTER ADDRESS:";
	gets(caddress);
	cout<<"\nENTER STATUS:\n# VIP\n# NON VIP\n";
	gets(stat);
	cout<<"\nENTER NUMBER OF MEMBERS:";
	cin>>nomem;
	cout<<"\nENTER PHONE NUMBER:";
	for (int i=0;i<10;i++)
		phoneno[i]=getche();
	phoneno[i]='\0';

	alottroom();
	file.write((char *)this,sizeof(customer));
	file.close();
}

//TO ASSIGN THE CUSTOMER HIS/HER ROOM NO. BASED ON THE TYPE OF ROOM
void customer::alottroom()
{
	cout<<"\n\nENTER YOUR CHOICE \n";
	switch(nomem)
	{
		case 1:
				cout<<"\n1 SINGLE ROOM : INR 25999 PER DAY\n\n4 PRESIDENTIAL SUITE : INR 1099999 PER DAY\n";
				if(strcmpi(stat,"VIP")==0)
					cout<<"\n5 VIP ROOM : INR 599999 PER DAY"<<endl;
				cin>>rtype;
				break;
		case 2:
				cout<<"\n2 COUPLE ROOM : INR 59999 PER DAY\n\n4 PRESIDENTIAL SUITE : INR 1099999 PER DAY\n";
				if(strcmpi(stat,"VIP")==0)
					cout<<"\n5 VIP ROOM : INR 599999 PER DAY"<<endl;
				cin>>rtype;
				break;
		default:
				cout<<"\n3 FAMILY ROOM : INR 199999 PER DAY\n\n4 PRESIDENTIAL SUITE : INR 1099999 PER DAY\n";
				if(strcmpi(stat,"VIP")==0)
					cout<<"\n5 VIP ROOM : INR 599999 PER DAY";
					cout<<endl;
					cin>>rtype;
	}

	rno=assignroom(rtype);
}

//TO CALCULATE AND PRINT THE BILL
void customer::bill()
{
	int i=1;
	char name[30];
	double bamount;
	fstream file;
	long in,out;
	clrscr();
	file.open("outcus.dat",ios::app|ios::in|ios::binary);
	cout<<"\n ENTER CUSTOMER NAME: ";
	gets(name);
	while(file.read((char *)this,sizeof(customer)))
	{
		if((strcmpi(name,cname)==0)&&(strcmpi(checkoutdate," NOT CHECKED OUT ")!=0))
		{
			clrscr();
			long charge[5]={ 25999 , 59999 , 199999 , 1099999 , 599999 };
			in=checkin;
			out=checkout;
			noday=((out-in)/(24*60*60))+1;
			cout<<"\n\n                                    BILL \n";
			cout<<"CHARGES PER DAY : INR "<<charge[rtype-1]<<endl;
			cout<<"\n\nCHECKIN DATE : "<<ctime(&checkin);
			cout<<"\n\nCHECKOUT DATE : "<<checkoutdate;
			cout<<"\n\nNO OF DAYS : "<<noday;
			bamount=noday*charge[rtype-1];
			cout<<"\n\nTOTAL CHARGES: "<<bamount;
			break;
		}
		else
			i=0;

	}
	if(i==0)
		cout<<"	\n\nPLEASE CHECKOUT FIRST ";
	file.close();
	getch();

}

//TO SEARCH A PARTICULAR CUSTOMER BY NAME
void customer::searchcus()
{
	char sname[30];
	int i=0,j;
	fstream file,file1;
	file.open("customer.dat",ios::in|ios::binary);
	file1.open("outcus.dat",ios::in|ios::binary);
	clrscr();
	cout<<"\n ENTER NAME: ";
	gets(sname);
	while( file.read((char *)this,sizeof(customer)))
	{

	       if(strcmpi(sname,cname)==0)
		{
			clrscr();
			cout<<"\n NAME:"<<cname;
			cout<<"\n\n ADDRESS:"<<caddress;
			cout<<"\n\n STATUS:"<<stat;
			cout<<"\n\n NUMBER OF MEMBERS:"<<nomem;
			cout<<"\n\n PHONE NUMBER:";
			for (j=0;j<11;j++)
			cout<<phoneno[j];
			cout<<"\n\n ROOM NO.: "<<rno;
			cout<<"\n\n CHECKIN DATE:"<<ctime(&checkin);
			cout<<"\n\n CHECKOUT DATE:"<<checkoutdate;
			break;
		}
		else
		{
			while( file1.read((char *)this,sizeof(customer)))
			{
				if(strcmpi(sname,cname)==0)
				{
					clrscr();
					cout<<"\n NAME:"<<cname;
					cout<<"\n\n ADDRESS:"<<caddress;
					cout<<"\n\n STATUS:"<<stat;
					cout<<"\n\n NUMBER OF MEMBERS:"<<nomem;
					cout<<"\n\n PHONE NUMBER:";
					for (int j=0;j<11;j++)
					cout<<phoneno[j];
					cout<<"\n\n ROOM NO.: "<<rno;
					cout<<"\n\n CHECKIN DATE:"<<ctime(&checkin);
					cout<<"\n\n CHECKOUT DATE:"<<checkoutdate;
					break;
				}
				else
					i=2;
			}

		}

	}
	if(i==2)
		cout<<"\n NOT FOUND .....";
	getch();
	file.close();
	file1.close();
}

//TO SET THE CHECKOUT DATE
void customer::setdate(char date[50],time_t t)
{
	checkout=t;
	strcpy(checkoutdate,date);
	cout<<"\n CHECKOUT DATE : "<<checkoutdate<<endl;
}


//TO UNASSIGN A ROOM
void customer::unassignroomno()
{
	clrscr();
	int i,r;
	char name[30];
	fstream file,file1,file2;
	time_t t1;
	t1 = time(NULL);
	cout<<"\n CHECKOUT DATE : "<<ctime(&t1);
	file.open("customer.dat",ios::app|ios::in|ios::binary);
	file1.open("outcus.dat",ios::binary|ios::app);
	file2.open("delete.dat",ios::binary|ios::out);
	cout<<"\n ENTER CUSTOMER NAME: ";
	gets(name);
	while(file.read((char *)this,sizeof(customer)))
	{

		if(strcmpi(name,cname)==0)
		{
			r=rno;
			unalottroom(rno);
			cout<<" \nROOM UNALOTTED ";
			//to modify record i.e. to write checkoutdate in the record
			setdate(ctime(&t1),t1);
			file.seekp(-1*sizeof(customer),ios::cur);
			file.write((char *)this,sizeof(customer));
			file1.write((char *)this,sizeof(customer));
			i=1;
			break;
		}

	}
	if(i==1)
	{      	file.seekg(0,ios::beg);
		while(file.read((char *)this,sizeof(customer)))
		{

			file2.write((char *)this,sizeof(customer));
		}
	}
	else
		cout<<"\nNOT FOUND!!!";

	file1.close();
	file.close();
	file2.close();
	file.open("customer.dat",ios::binary|ios::out);
	file2.open("delete.dat",ios::binary|ios::in);
	while(!file2.eof())
	{
		file2.read((char *)this,sizeof(customer));
		if(rno!=r)
			file.write((char *)this,sizeof(customer));


	}
	file2.close();
	file.close();
	getch();

}

//TO SHOW THE DETAILS OF THE CUSTOMER
void customer::showinfo(int i)
{
	gotoxy(1,i+1);
	cout<<rno;
	gotoxy(10,i+1);
	cout<<cname;
	gotoxy(25,i+1);
	cout<<ctime(&checkin);
	gotoxy(52,i+1);
	cout<<checkoutdate;
}

//TO SHOW THE LIST OF CUSTOMERS
void displayrecord(char choice)
{
	clrscr();
	int x=3;
	fstream file,file1;
	customer a;
	cout<<"ROOMNO   NAME           CHECKIN DATE & TIME        CHECKOUT DATE & TIME";
	switch(choice)
	{
		//TO SHOW THE LIST OF CURRENT CUSTOMERS
		case '1':
			file.open("customer.dat",ios::in|ios::binary);
			file.seekg(0,ios::beg);
			while(file.read((char*)&a,sizeof(a)))
			{
				if(file.eof())
				break;
				a.showinfo(x);
				cout<<"\n";
				x++;
			}
			file.close();
			break;
		//TO SHOW THE LIST OF OLD CUSTOMERS
		case'2':
			file1.open("outcus.dat",ios::in|ios::binary);
			file1.seekg(0,ios::beg);
			while(file1.read((char*)&a,sizeof(a)))
			{
				if(file1.eof())
				break;
				a.showinfo(x);
				cout<<"\n";
				x++;
			}
			file1.close();
			break;
		deafult:
			cout<<"\n\n INVALID CHOICE !!!";
			break;
	}
	getch();
}

void main()
{
	clrscr();
	cout<<"         ___________________________________________________________ \n";
	cout<<"        |                                                           |\n";
	cout<<"        |                PROJECT ON HOTEL MANAGEMENT                |\n";
	cout<<"        |                                                           |\n";
	cout<<"        |                          MADE BY                          |\n";
	cout<<"        |                                                           |\n";
	cout<<"        |                          RITIKA                           |\n";
	cout<<"        |                                                           |\n";
	cout<<"        |                                                           |\n";
	cout<<"        |                                                           |\n";
	cout<<"        |                 PRESS ANY KEY TO START                    |\n";
	cout<<"        |                                                           |\n";
	cout<<"        |                                                           |\n";
	cout<<"        |                           *****                           |\n";
	cout<<"        |___________________________________________________________|\n";
	getch();
	clrscr();
	customer c;
	char  ch,ch1;
	int i=0;

	clrscr();
	fstream file;

	for(i=1;i<=250;i++)
	{
		a[i].roomno=i;
		a[i].status=0;
	}
	file.open("room.dat",ios::binary|ios::in);
	if(file.read((char *)&a,sizeof(rooms))!=0)
	{
		for(i=1;i<=250;i++)
			file.read((char *) &a[i], sizeof (rooms));

	}
	file.close();
	do
	{
		clrscr();
		cout<<"\n\n1.NEW CUSTOMER\n\n2.CHECKOUT\n\n3.BILL\n\n4.SEARCH CUSTOMER\n\n5.CUSTOMER LIST\n\n6.EXIT\n";
		cout<<"\nENTER YOUR CHOICE : ";
		ch=getche();
		switch(ch)
		{
			case '1':
				c.enterinfo();

				break;
			case '2':
				c.unassignroomno();
				break;
			case '3':
				c.bill();
				break;
			case '4':
				c.searchcus();
				break;
			case '5':
				clrscr();
				cout<<"\n\nENTER CHOICE:\n\n1.CURRENT CUSTOMERS' LIST\n\n2.CHECKOUT CUSTOMERS' LIST\n";
				ch1=getche();
				displayrecord(ch1);
				break;
			case '6':
				break;
			default:
				cout<<"\n INVALID CHOICE!!! ";
				getch();
				continue;
		}
	}while(ch!='6');
	file.open("room.dat",ios::binary|ios::out);
	for(i=0;i<250;i++)
	{
		file.write((char *) &a[i], sizeof (rooms));
	}
	file.close();

}



