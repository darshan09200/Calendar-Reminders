#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<fstream.h>
#include<dir.h>
#include<dirent.h>

#define size 100

struct file
{
	FILE *fp;
	char dirnameMain[size];
	char dirnameMeet[size];
	char dirnameAnni[size];
	char dirnameBday[size];
	char dirnameTime[size];
	char dateFile[size];
	char option[size];
	char event[size];
	char fileCheck[size];
	ofstream out;
	ifstream in;
}s;

void confirm()
{
	do
	{
		cout<<"\n \n \n \t \t Are you sure you want to confirm :";
		cout<<"\n \n \t \t 1. Yes \t \t 2. No ";
		cout<<"\n \n \t \t Enter your choice here : ";
		cin>>s.option;
		if((strcmp(s.option,"1"))==0)
		{
			strcpy(s.option,"Yes");
		}
		else if((strcmp(s.option,"2"))==0)
		{
			strcpy(s.option,"invalid");
		}
		else
		{
			strcpy(s.option,"wrong");
		}
	}while((strcmp(s.option,"wrong"))==0);
}

class CheckDate
{
	char date_s[2],month_s[2],year_s[4];
	public:
		char arr[10],full[20];
		int dateEnd;
		CheckDate()
		{
			strcpy(arr,"");
			strcpy(full,"");
			strcpy(date_s,"");
			strcpy(month_s,"");
			strcpy(year_s,"");
			dateEnd=0;
		}
		void getDate();
		void copyDate()
		{
			date_s[0]=full[0];
			date_s[1]=full[1];
			date_s[2]='\0';
			strcpy(arr,date_s);
		}
		void copyMonth()
		{
			month_s[0]=full[5];
			month_s[1]=full[6];
			month_s[2]='\0';
			strcpy(arr,month_s);
		}
		void copyYear()
		{
			arr[0]=year_s[0]=full[10];
			arr[1]=year_s[1]=full[11];
			arr[2]=year_s[2]=full[12];
			arr[3]=year_s[3]=full[13];
			arr[4]='\0';
		}
		int checkDate(int i);
		void showDate()
		{
			cout<<"\n \n \t \t Date : "<<full;
		}
		int toString();
		void saveDate()
		{
			chdir(s.dirnameMain);
			s.out.open("DATE.txt",ios::app);
				s.out<<"\n"<<full<<endl;
			s.out.close();
		}
		void checkFileDate();
};

void CheckDate::checkFileDate()
{
	char fileData[size];
	fileData[0]='\0';
	char ch='1';
	strcpy(s.dateFile,full);
	strcat(s.dateFile,".txt");
	chdir(s.dirnameMain);
	/*s.in.open("DATE.txt",ios::in);
		while(!s.in.eof())
		{
			getline(s.in,fileData);
		}
	s.in.close();*/
	int i;
	s.fp=fopen("DATE.txt","r");
		if(s.fp != NULL)
		{
			while(ch!=EOF)
			{
				i=0;
				do
				{
					ch=fgetc(s.fp);
					fileData[i]=ch;
					i++;
					if(ch==EOF)
					{
						break;
					}
				}while(ch!='\n');
				fileData[i-1]='\0';
				if((strcmp(full,fileData))==0)
				{
					strcpy(s.fileCheck,"yes");
					break;
				}
			}
		}
	fclose(s.fp);
}


void CheckDate::getDate()
{
	char extra[3];
	int i;
	char ch;
	strcpy(extra," - ");
	do
	{
		cout<<"\n Enter any date in dd/mm/yyyy format : ";
		i=0;
		do
		{
			ch=getch();
			if(!isdigit(ch))
			{
				printf("\n \t Please enter numbers only ");
				i=910;
				break;
			}
			else
			{
				full[i]=ch;
				cout<<full[i];
				if(i==1)
				{
					cout<<extra;
					full[i+1]='\0';
					strcat(full,extra);
					i+=3;
				}
				else if(i==6)
				{
					cout<<extra;
					full[i+1]='\0';
					strcat(full,extra);
					i+=3;
				}
				else if(i==13)
				{
					full[i+1]='\0';
					i=checkDate(i);
				}
				i++;
			}
		}while(i<14);
		getch();
	}while(i>=910);
}

int CheckDate::checkDate(int i)
{
	copyDate();
	int date=toString();

	copyMonth();
	int month=toString();

	copyYear();
	int yearFull=toString();

	if(yearFull < 1900 || yearFull > 2200 || month < 1 || month > 12 || date < 1 || date > 31)
	{
		cout<<"\n \n \t \t invalid";
		i=910;
	}
	else
	{
		if((( yearFull % 400 ==0 ) || ( yearFull % 4 ==0)) && ( month == 2 ))
		{
			if(date<=29)
			{
				i=92;
				dateEnd=29;
			}
			else
			{
				cout<<"\n \n \t \t invalid";
				i=910;
			}
		}
		else if(month == 2)
		{
			if(date<=28)
			{
				i=92;
				dateEnd=28;
			}
			else
			{
				cout<<"\n \n \t \t invalid";
				i=910;
			}
		}
		else if(month == 1 || month ==3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if(date <= 31)
			{
				i=92;
				dateEnd=31;
			}
			else
			{
				cout<<"\n \n \t \t invalid";
				i=910;
			}
		}
		else if (month == 4 || month ==6 || month == 9 || month == 11)
		{
			if(date <= 30)
			{
				i=92;
				dateEnd=30;
			}
			else
			{
				cout<<"\n \n \t \t invalid";
				i=910;
			}
		}
	}
	return i;
}

int CheckDate::toString()
{
	int c;
	int n;
	n = 0;
	for (c = 0; arr[c] != '\0'; c++)
	{
		if(arr[c]>=48 && arr[c]<=57)
		{
			n = n * 10 + arr[c]-'0';
		}
		else
		{
			n=0;
			break;
		}
	}
	return n;
}

class CheckDay:public CheckDate
{
	int yearPart2,yearCheck;
	int monthCheck[12];
	int final;
	char week[7][20];

	public:
		int yearFull,date,month;
		CheckDay()
		{
			yearPart2=yearFull=yearCheck=date=month=final=0;
			monthCheck[0]=4;
			monthCheck[1]=0;
			monthCheck[2]=0;
			monthCheck[3]=3;
			monthCheck[4]=5;
			monthCheck[5]=1;
			monthCheck[6]=3;
			monthCheck[7]=6;
			monthCheck[8]=2;
			monthCheck[9]=4;
			monthCheck[10]=0;
			monthCheck[11]=2;
			monthCheck[12]='\0';
			strcpy(week[0],"Sun");
			strcpy(week[1],"Mon");
			strcpy(week[2],"Tue");
			strcpy(week[3],"Wed");
			strcpy(week[4],"Thu");
			strcpy(week[5],"Fri");
			strcpy(week[6],"Sat");
		}
		void seperate()
		{
			copyDate();
			date=toString();

			copyMonth();
			month=toString();

			copyYear();
			yearFull=toString();
		}

		void calculateDay();
		void displayCalendar();
};
void CheckDay::displayCalendar()
{
	int i,dateDisp=1,count=1;
	cout<<"\n \n \t \t";
	for(i=0;i<7;i++)
	{
		cout<<week[i]<<"\t";
	}
	cout<<"\n \n \t \t";
	for(i=0;i<7;i++,count++)
	{
		if(i==final)
		{
			if(dateDisp==date)
			{
				cout<<" "<<dateDisp<<"*\t";
			}
			else
			{
				cout<<" "<<dateDisp<<" \t";
			}
			dateDisp++;
			if(count>6)
			{
				cout<<"\n \n \t \t";
				count=0;
			}
			break;
		}
		else
		{
			cout<<"   \t";
		}
	}
	for(count++,i++;dateDisp<=dateEnd;i++,dateDisp++,count++)
	{
		if(dateDisp==date)
		{
			cout<<" "<<dateDisp<<"*\t";
		}
		else
		{
			cout<<" "<<dateDisp<<"\t";
		}
		if(count>6)
		{
			cout<<"\n \n \t \t";
			count=0;
		}
	}

};



void CheckDay::calculateDay()
{
	seperate();

	if(yearFull < 1900 || yearFull > 2200)
	{
		cout<<"invalid";
		strcpy(s.option,"invalid");
	}
	else
	{
		/*Calculate Year Started Here*/
		/*Century Check -> Start*/
		if(yearFull >= 1990 && yearFull < 2000)
		{
			yearPart2=yearFull-1990;
			final=3;
		}
		else if(yearFull >= 2000 && yearFull < 2100)
		{
			yearPart2=yearFull-2000;
			final=2;
		}
		else if(yearFull >= 2100 && yearFull < 2200)
		{
			yearPart2=yearFull-2100;
			final=0;
		}
		/*Century Check -> End*/
		yearCheck=0;
		yearCheck+=(yearPart2/4);
		yearCheck+=yearPart2;
		yearCheck%=7;
		/*Year Added to Final*/
		final+=yearCheck;
		/*Calculate Month Started Here*/
		int i;
		for(i=0;i<12;i++)
		{
			if(month==i+1)
			{       /*Month Added Here*/
				final+=monthCheck[i];
				/*If Leap Year Then -1 Day if the month is Jan or Feb*/
				if(((yearFull%400==0) || (yearFull%4==0)) && (i==0 || i==1))
				{
					final-=1;
				}
				break;
			}
		}
		/*Date Added Here*/
		int firstDate=1; //To check the first day of the month
		final+=(firstDate%7);
		do
		{
			final%=7;
		}while(final>6);
		displayCalendar();
		/*The remainder here is the day number on which the date is there*/
/*		cout<<endl;
		char input[size];
		strcpy(input,"\n \t The Day of the weeek on the given Date is  : ");
		cout<<input<<week[final];*/
	}
}

class AddReminder
{
	char meetName[size],person[size];
	char person_male[size],person_female[size];
	public:
		void getMeetDetails()
		{
			cout<<"\n Enter Meeting Name : ";
			gets(meetName);
		}
		void getBdayDetails()
		{
			cout<<"\n Enter Name of the person : ";
			gets(person);
		}
		void getAnniDetails()
		{
			cout<<"\n Enter Name of the husband: ";
			gets(person_male);
			cout<<"\n Enter Name of the wife: ";
			gets(person_female);
		}
		void check()
		{
			if((strcmp(meetName,""))==0)
			{
				strcpy(meetName,"No Title");
			}
			if((strcmp(person,""))==0)
			{
				strcpy(person,"No Title");
			}
			if((strcmp(person_male,""))==0)
			{
				strcpy(person_male,"No Title");
			}
			if((strcmp(person_female,""))==0)
			{
				strcpy(person_female,"No Title");
			}
		}
		void showMeetDetails()
		{
			cout<<"\n Meeting Name : "<<meetName;
		}
		void showBdayDetails()
		{
			cout<<"\n Birthday of : "<<person;
		}
		void showAnniDetails()
		{
			cout<<"\n Anniversary of couple : "<<person_male<<" & "<<person_female;
		}
		void saveMeet()
		{
			ofstream out;
			chdir(s.dirnameMeet);
			out.open(s.dateFile,ios::app);
				out<<"\n Name of the meeting : "<<meetName<<endl;
			out.close();
		}
		void saveBday()
		{
			chdir(s.dirnameBday);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Name of the person : "<<person<<endl;
			s.out.close();
		}
		void saveAnni()
		{
			chdir(s.dirnameAnni);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Name of the couple : "<<person_male<<" & "<<person_female<<endl;
			s.out.close();
		}
		void fileMeetDetails();
		void fileBdayDetails();
		void fileAnniDetails();
};

void AddReminder::fileMeetDetails()
{
	char ch='1';
	chdir(s.dirnameMeet);
	s.fp=fopen(s.dateFile,"r");
		if(s.fp!=NULL)
		{
			while(ch!=EOF)
			{
				ch=fgetc(s.fp);
				cout<<ch;
			}
		}
		else
		{
			cout<<"\n \n No Meeting Reminders.... ";
		}
	fclose(s.fp);
}

void AddReminder::fileBdayDetails()
{
	char ch='1';
	chdir(s.dirnameBday);
	s.fp=fopen(s.dateFile,"r");
		if(s.fp!=NULL)
		{
			while(ch!=EOF)
			{
				ch=fgetc(s.fp);
				cout<<ch;
			}
		}
		else
		{
			cout<<"\n \n No Birthday Reminders.... ";
		}
	fclose(s.fp);
}

void AddReminder::fileAnniDetails()
{
	char ch='1';
	chdir(s.dirnameAnni);
	s.fp=fopen(s.dateFile,"r");
		if(s.fp!=NULL)
		{
			while(ch!=EOF)
			{
				ch=fgetc(s.fp);
				cout<<ch;
			}
		}
		else
		{
			cout<<"\n \n No Anniversary Reminders.... ";
		}
	fclose(s.fp);
}


class Describe
{
	char describe[size];
	public:
		void describeReminder()
		{
			cout<<"\n\n Enter Description below : ";
			gets(describe);
			if((strcmp(describe,""))==0)
			{
				strcpy(describe,"No Title");
			}
		}
		void showReminder()
		{
			cout<<"\n Decription : "<<describe;
		}
		void saveReminderMeet()
		{
			chdir(s.dirnameMeet);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Description : "<<describe<<endl;
			s.out.close();
		}
		void saveReminderBday()
		{
			chdir(s.dirnameBday);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Description : "<<describe<<endl;
			s.out.close();
		}
		void saveReminderAnni()
		{
			chdir(s.dirnameAnni);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Description : "<<describe<<endl;
			s.out.close();
		}
};


class InputTime:public CheckDay
{
	char extra[3];
	char hour[2],min[2],fullTime[10];
	char ch;
	char ogTime[10];
	public:
		int i,hourConvert,minConvert;
		InputTime()
		{
			strcpy(extra," : ");
			extra[3]='\0';
		}
		void getTime();
		void checkTime();
		void todayDate();
		void todayTime();
		void showTime()
		{
			cout<<"\n Reminder Time : "<<ogTime;
		}
		void saveTime()
		{
			chdir(s.dirnameTime);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n"<<ogTime;
			s.out.close();
		}
		void saveMeetTime()
		{
			chdir(s.dirnameMeet);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Reminder Time : "<<ogTime<<endl;
			s.out.close();
		}
		void saveBdayTime()
		{
			chdir(s.dirnameBday);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Reminder Time : "<<ogTime<<endl;
			s.out.close();
		}
		void saveAnniTime()
		{
			chdir(s.dirnameTime);
			s.out.open(s.dateFile,ios::app);
				s.out<<"\n Reminder Time : "<<ogTime<<endl;
			s.out.close();
		}
};

void InputTime :: todayDate()
{
	struct date d;
	getdate(&d);
	if(d.da_year==yearFull)
	{
		if(d.da_mon==month)
		{
			if(d.da_day==date)
			{
				todayTime();
			}
		}
	}
}

void InputTime::todayTime()
{
	struct  time t;
	gettime(&t);
	if(t.ti_hour==hourConvert)
	{
		if(t.ti_min==minConvert)
		{
			i=910;
			cout<<"\n Current Date and Time is not accepted";
		}
	}
}

void InputTime::getTime()
{
	do
	{
		cout<<"\n\n Enter any time in hh:mm (24 hr) format : ";
		i=0;
		do
		{
			ch=getch();
			if(!isdigit(ch))
			{
				printf("\n \t Please enter numbers only ");
				i=910;
				break;
			}
			else
			{
				fullTime[i]=ch;
				cout<<fullTime[i];
				if(i==1)
				{
					cout<<" : ";
					fullTime[2]='\0';
					strcat(fullTime," : ");
					i+=3;
				}
				else if(i==6)
				{
					fullTime[i+1]='\0';
					strcpy(ogTime,fullTime);
					checkTime();
				}
				i++;
			}
		}while(i<7);
	}while(i>=910 );
}

void InputTime::checkTime()
{
	hour[0]=fullTime[0];
	hour[1]=fullTime[1];
	hour[2]='\0';
	strcpy(arr,hour);
	hourConvert=toString();
	min[0]=fullTime[5];
	min[1]=fullTime[6];
	min[2]='\0';
	strcpy(arr,min);
	minConvert=toString();
	if(!((hourConvert>=0) && (hourConvert<=24) && (minConvert>=0) && (minConvert<60)))
	{
		cout<<"\n Invalid ";
		i=910;
	}
	else
	{
		todayDate();
	}
}

class Event:public AddReminder, public Describe, public InputTime
{
	char option[size];
	public:
		void select();
};

void Event::select()
{
	do
	{
		cout<<"\n \t \t 1. Meetings \t 2. Birthday \t 3. Anniversary";
		cout<<"\n \t Enter your choice here : ";
		cin>>option;
		if((strcmp(option,"1"))==0)
		{
			strcpy(s.event,"meeting");
			getMeetDetails();
			getTime();
			describeReminder();
			cout<<"\n \n \n \t Press any key to procceed";
			getch();
			clrscr();
			check();
			showDate();
			showMeetDetails();
			showReminder();
			showTime();
			cout<<"\n \n \n \t Press any key to procceed";
			getch();
		}
		else if((strcmp(option,"2"))==0)
		{
			strcpy(s.event,"bday");
			getBdayDetails();
			getTime();
			describeReminder();
			cout<<"\n \n \n \t Press any key to procceed";
			getch();
			clrscr();
			check();
			showDate();
			showBdayDetails();
			showReminder();
			showTime();
			cout<<"\n \n \n \t Press any key to procceed";
			getch();
		}
		else if((strcmp(option,"3"))==0)
		{
			strcpy(s.event,"anni");
			getAnniDetails();
			getTime();
			describeReminder();
			cout<<"\n \n \n \t Press any key to procceed";
			getch();
			clrscr();
			check();
			showDate();
			showAnniDetails();
			showReminder();
			showTime();
			cout<<"\n \n \n \t Press any key to procceed";
			getch();
		}
		else
		{
			strcpy(option,"invalid");
		}
	}while((strcmp(option,"invalid"))==0);
}

class FileData:public Event
{
	public:
		void checkFileInput();
};

void FileData::checkFileInput()
{
	strcpy(s.fileCheck,"");
	checkFileDate();
	if((strcmp(s.fileCheck,"yes"))==0)
	{
		cout<<"\n \n Previous reminder details on current date : \n ";
		fileMeetDetails();
		fileBdayDetails();
		fileAnniDetails();
	}
	else
	{
		cout<<"\n \n \n \t \t \t No Reminders ..... ";
	}
}


class Start:public FileData
{
	char option[size];
	public:
		void ask();
		void currentReminder();
};

void Start::currentReminder()
{
	char ch='1';
	char fileData[200],hour[3],min[3],fullTime[20];
	int i=0;
	int count=0;
	struct  time t;
	gettime(&t);
	struct date d;
	getdate(&d);
	chdir(s.dirnameMain);
	s.fp=fopen("DATE.txt","r");
		if(s.fp != NULL)
		{
			while(ch!=EOF)
			{
				count++;
				i=0;
				do
				{
					ch=fgetc(s.fp);
					fileData[i]=ch;
					i++;
					if(ch==EOF)
					{
						break;
					}
				}while(ch!='\n');
				if((strcmp(fileData,"\n"))==0)
				{
					continue;
				}
				else if(ch!=EOF)
				{
					fileData[i-1]='\0';
					strcpy(full,fileData);
					seperate();

					if(d.da_year==yearFull)
					{
						if(d.da_mon==month)
						{
							if(d.da_day==date)
							{
								fclose(s.fp);
								cout<<"\n \n Reminder details on current date : \n ";
								strcpy(s.dateFile,fileData);
								strcat(s.dateFile,".txt");
								cout<<"\n \n Meeting Details : \n ";
								fileMeetDetails();
								cout<<"\n \n Birthday Details : \n ";
								fileBdayDetails();
								cout<<"\n \n Anniversary Details : \n ";
								fileAnniDetails();
								break;


								/*int timeLine=0;
								chdir(s.dirnameTime);
								strcat(fileData,".txt");
								s.fp=fopen(fileData,"r");
									if(s.fp!=NULL)
									{
										while(ch!=EOF)
										{
											i=0;
											do
											{
												ch=fgetc(s.fp);
												fileData[i]=ch;
												i++;
											}while(ch!='\n');
											fileData[i-1]='\0';
											if((strcmp(fileData,"\n"))==0)
											{
												timeLine++;
												continue;
											}
											else if(timeLine==count)
											{
											hour[0]=fullTime[0];
											hour[1]=fullTime[1];
											hour[2]='\0';
											strcpy(arr,hour);
											hourConvert=toString();
											min[0]=fullTime[5];
											min[1]=fullTime[6];
											min[2]='\0';
											strcpy(arr,min);
											minConvert=toString();
											if(t.ti_hour==hourConvert)
											{
												if(t.ti_min==minConvert)
												{
													i=910;
													cout<<"\n Current Date and Time is not accepted";
												}
											}
										}
										}
									}                                 */
							}
						}
					}
				}
			}
		}
	fclose(s.fp);
}


void Start :: ask()
{
	do
	{
		clrscr();
		cout<<"\n \t \t \t CALENDAR";
		currentReminder();
		cout<<"\n \n \n \t \t 1. Add Reminder \n \n \t \t 2. View Reminder \n \n \t \t 3. Exit";
		cout<<"\n \n \t \t \t Enter your choice here : ";
		cin>>option;
		if((strcmp(option,"1"))==0)
		{
			do
			{
				clrscr();
				getDate();
				calculateDay();
				checkFileInput();
				cout<<"\n \n \n \t \t \t Add Event";
				select();
				confirm();
				strcpy(option,s.option);
			}while((strcmp(option,"invalid"))==0);
			strcpy(option,"1");
			saveDate();
			if((strcmp(s.event,"meeting"))==0)
			{
				saveMeetTime();
				saveMeet();
				saveReminderMeet();
			}
			else if((strcmp(s.event,"bday"))==0)
			{
				saveBdayTime();
				saveBday();
				saveReminderBday();
			}
			else if((strcmp(s.event,"anni"))==0)
			{
				saveAnniTime();
				saveAnni();
				saveReminderAnni();
			}
			saveTime();
		}
		else if((strcmp(option,"2"))==0)
		{
			do
			{
				clrscr();
				getDate();
				calculateDay();
				checkFileInput();
				confirm();
				strcpy(option,s.option);
			}while((strcmp(option,"invalid"))==0);
		}

		else if((strcmp(option,"3"))==0)
		{
			cout<<"\n \n Thanks for using our calendar ";
			for(int i=5;i>=0;i--)
			{
				clrscr();
				gotoxy(22,13);
				cout<<" You will leave this page in "<<i<<" seconds";
				delay(1000);
			}
			break;
		}
		else
		{
			strcpy(option,"invalid");
		}
	}while((strcmp(option,"3"))!=0);
}


class Install:public Start
{
	int n;
	DIR *dir;
	public:
		void load();
		void create();
};

void Install::load()
{
	int i=0;
	int j=0;

	sleep(1);
	do
	{
		clrscr();
		printf("\n \n \n \n \n \n \t \t \t \t Please wait... ");
		printf("\n \t \t \t Installing required files...");
		printf("\n \n \t \t \t \t \t %d %c\n \n \t \t \t ",j*10,37);
		for(j=1;j<i+1;j++)
		{
			printf("%c%c%c",176,176,176);
		}

		delay(n);
		i++;
	}while(i<=10);
}

void Install::create()
{


	dir=opendir(s.dirnameMain);
	if(dir)
	{
		dir=opendir(s.dirnameTime);
		if(dir)
		{
			dir=opendir(s.dirnameMeet);
			if(dir)
			{
				dir=opendir(s.dirnameBday);
				if(dir)
				{
					dir=opendir(s.dirnameAnni);
					if(dir)
					{
						 clrscr();
						 ask();
					}
					else
					{
						mkdir(s.dirnameAnni);
						n=100;
						load();
						create();
					}
				}
				else
				{
					mkdir(s.dirnameBday);
					n=100;
					load();
					create();
				}
			}
			else
			{
				mkdir(s.dirnameMeet);
				n=100;
				load();
				create();
			}
		}
		else
		{
			mkdir(s.dirnameTime);
			n=100;
			load();
			create();
		}
	}
	else
	{
		mkdir(s.dirnameMain);
		n=200;
		load();
		create();
	}
}

void main()
{
	strcpy(s.dirnameMain,"C:/CALENDAR");
	strcpy(s.dirnameMeet,"C:/CALENDAR/MEETING");
	strcpy(s.dirnameBday,"C:/CALENDAR/BDAY");
	strcpy(s.dirnameAnni,"C:/CALENDAR/ANNIVERSARY");
	strcpy(s.dirnameTime,"C:/CALENDAR/TIME");
	clrscr();
	Install i;
	i.create();
}

