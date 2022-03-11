//****************************************************************
//                   HEADER FILE USED IN PROGRAMME
//****************************************************************

#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<windows.h>
using namespace std;



//****************************************************************
//                   CLASS USED IN PROGRAMME
//****************************************************************

class student
{
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	double per;
	char grade;
	void calculate();	//function to calculate grade
public:
	void getdata();		//function to accept data from user
	void showdata() const;	//function to show data on screen
	void show_tabular() const;
	int retrollno() const;
}; //class ends here



//****************************************************************
//    	             function declaration
//****************************************************************

void write_student();	//write the record in binary file
void display_all();	//read all records from binary file
void display_sp(int);	//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();		//display result menu
void intro();           //display welcome screen
void entry_menu();	//display entry menu on screen
void Password();        // secure the edit menu
void IRONMAN();         //menu of the program




void student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>cs_marks;
	calculate();
}



void student::calculate()
{
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=60)
		grade='A';
	else if(per>=50)
		grade='B';
	else if(per>=33)
		grade='C';
	else
		grade='F';
}



void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<p_marks;
	cout<<"\nMarks in Chemistry : "<<c_marks;
	cout<<"\nMarks in Maths : "<<m_marks;
	cout<<"\nMarks in English : "<<e_marks;
	cout<<"\nMarks in Computer Science :"<<cs_marks;
	cout<<"\nPercentage of student is  :"<<per <<"\n";
	cout<<"\nGrade of student is :"<<grade;
}



void student::show_tabular() const
{
	cout<<rollno<<setw(10)<<" "<<name<<setw(14)<<p_marks<<setw(10)<<c_marks<<setw(11)<<m_marks<<setw(13)
		<<e_marks<<setw(11)<<cs_marks<<setw(13)<<per<<setw(12)<<grade<<endl;
}



int  student::retrollno() const
{
	return rollno;
}



//****************************************************************
//    	function to write in file
//****************************************************************

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\n\t Student record Has Been Created ";
	cin.ignore();
	cin.get();
}



//****************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st) ,  sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n==========================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}




//****************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\n\t Record not exist";
	cin.ignore();
	cin.get();
}



//****************************************************************
//    	function to modify record of file
//****************************************************************

void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t Record Not Found ";
	cin.ignore();
	cin.get();
}



//****************************************************************
//    	function to delete record from file
//****************************************************************

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";       // can write " NO DATA " to display
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\t Record Deleted ..";
	cin.ignore();
	cin.get();
}



//****************************************************************
//    	function to display all students grade report
//****************************************************************

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\t\t\t\t ALL STUDENTS RESULT \n\n";
	cout<<"========================================================================================================\n";
	cout<<"R.No       Name            Phy        Che        Math        Eng        Cse        %age          Grade"<<endl;
	cout<<"========================================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}




//****************************************************************
//    	function to display result menu
//****************************************************************

void result()
{
	char ch;
	int rno;
        start:
	system("cls");
	cout<<"\n\n\n\t--RESULT MENU--";
	cout<<"\n\n\n\t1. Class Result :)";
	cout<<"\n\n\t2. Student Report Card :)";
	cout<<"\n\n\t3. Back to Main Menu :)";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	IRONMAN();
	default:	cout<<"\n\n\n\tWrong Input \n";break;
	}
         system("PAUSE");
        goto start;
}



void entry_menu()
{
	char ch;
	int num;
        start:
	system("cls");
	cout<<"\n\n\n\t--ENTRY MENU--";
	cout<<"\n\n\t1.CREATE STUDENT RECORD :)";
	cout<<"\n\n\t2.DISPLAY ALL STUDENT'S RECORDS :)";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD :)";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD :)";
	cout<<"\n\n\t5.DELETE STUDENT RECORD :)";
	cout<<"\n\n\t6.BACK TO MAIN MENU :)";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			delete_student(num);break;
	case '6':	IRONMAN();break;

	default:	cout<<"\n\n\n\tWrong Input \n";break;

	}
	 system("PAUSE");
     goto start;

}





//****************************************************************
//    	PASSWORD FUNCTION OF PROGRAM
//****************************************************************

void Password()
{
       system("cls");
     char pass[5];
     pass[4]='\0';
     int t=0;
     start:
     cout<<"\n\n\n\tENTER THE CODE: ";
     for(int i=0;i<4;++i)
     {
             pass[i]=getch();
             cout<<"*";
     }
     cout<<"\n\n";
     if(strcmpi(pass,"AAAA")==0)
     {
         cout<<"\tACCESS GRANTED";
         Sleep(1000);
         system("cls");
         entry_menu();
     }
     else
     {
         if(t==2)
         {
             cout<<"\tACCESS DENIED\n";
             system("PAUSE");
             system("cls");
             cout<<"\n\n\n";
         }
        cout<<"\tTRY AGAIN ONCE MORE";
         ++t;
         Sleep(1500);
         system("cls");
         goto start;
     }
}








//****************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	 cout<<"\n\n";
	 cout<<"\n\t PEROJECT :01 \n";
	 cout<<"\t=========================================================\n";
	 cout<<"\t=========================================================\n\n";
	 cout<<"\t\t{ STUDENT REPORT CARD HANDLING SYSTEM }\n\n";
	 cout<<"\t=========================================================\n";
     cout<<"\t=========================================================\n\n";
     cout<<"\t-------------[ GRAPHIC ERA HILL UNIVERSITY ]-------------\n\n";
     cout<<"\t=========================================================\n";
	 cout<<"\t MADE BY : PAWAN SINGH CHAUDHARY \n";
     cout<<"\t B.TECH. (3rd SEM)\n";

     Sleep(3000);
     system("cls");
     for(int i=1;i<=100;++i)
     {
         Sleep(5);
         system("cls");

         cout<<"\n\n\n\tLOADING... "<<i<<"%";
		// Sleep(20);
		 //system("cls");
         if(i==100)
         {
             Sleep(600);
         }
     }
     system("cls");
     cout<<"\n\n\n\t(:---WELCOME TO THE SYSTEM---:)";
     Sleep(2500);
}





//****************************************************************
//    	     MENU OF THE PROGRAM
//****************************************************************

void IRONMAN()
{
        system("cls");
		cout<<"\n\n\n\t--MAIN MENU--";
		cout<<"\n\n\t01. RESULT MENU :)";
		cout<<"\n\n\t02. ENTRY/EDIT MENU :)";
		cout<<"\n\n\t03. EXIT :)";
		cout<<"\n\n\tPlease Select Your Option (1-3) :";
                char ch;
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2' : Password();
                break;
			case '3':exit(0);

			default :cout<<"\n\n\n\tInvalid Input \n";break;
        }
}




//****************************************************************
//    	 THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
    system("COLOR 06");
    intro();
    IRONMAN();

return 0;
}


