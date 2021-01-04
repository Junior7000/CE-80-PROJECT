/**
 @b NAME       : @b MOHAMMED_AMMAR_ATA-ELFADEEL
 @b NICKNAME   : @b JUNIOR
 @b DEPARTMENT : @b COMPUTER
 @b CLASS      : @b SECOND_CLASS
*/

#include<fstream>
#include<string>
#include<iostream>
using namespace std;
 
class contact /*ClASS OF THE CONTACT*/
{
	/** @param parameters [Phone,Names,Address,E-Mail] */
	long ph;
	char FirstName[20],LastName[20],add[20],email[30];

	public:

	void create_contact()/*FUNCTION TO SET THE CONTACTS DETAILS*/
	{
		cout<<"Phone: ";
		cin>>ph;

		cout<<"First Name: ";
		cin.ignore();
		cin>>FirstName;

		cout<<"Last Name: ";
		cin.ignore();
		cin>>LastName;

		cout<<"Address: ";
		cin.ignore();
		cin>>add;

		cout<<"Email address: ";
		cin.ignore();
		cin>>email;
		
		cout<<"\n";
	}

	void show_contact() /*FUNCTION TO DISPLAY THE CONTACTS DETAILS*/
	{
		cout<<endl<<"Phone #: "<<ph;
		cout<<endl<<"First Name: "<<FirstName;
		cout<<endl<<"Last Name: "<<LastName;
		cout<<endl<<"Address: "<<add;
		cout<<endl<<"Email Address : "<<email;
	}
    /*GROUB OF FUNCTIONS THAT RETURNS PARAMETERS VALUES*/
	long getPhone()
	{
		return ph;
	}

	char* getFirstName()
	{
		return FirstName;
	}

	char* getLastName()
	{
		return LastName;
	}

	char* getAddress()
	{
		return add;
	}

	char* getEmail()
	{
		return email;
	}
};
 
fstream fp; /*OBJECT TO WORK WITH FILE*/
contact cont; /*OBJECT TO WORK WITH CONTACT CLASS*/

void save_contact() /*FUNCTION TO SAVE THE CONTACT ON THE FILE*/
{
	fp.open("contactBook.txt",ios::out|ios::app);
	cont.create_contact();
	fp.write((char*)&cont,sizeof(contact));
	fp.close();
	cout<<endl<<endl<<"Contact Has Been Sucessfully Created...\n\n";
	getchar();
}

void show_all_contacts() /*FUNCTION TO BRINGS AND DISPLAYING ALL CONTACTS THAT ON THE FILE*/
{
	cout << "\n\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\t\t\tLIST OF CONTACTS\n\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
	fp.open("contactBook.txt",ios::in);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		cont.show_contact();
		cout<<endl<<"================================================="<<endl;
	}
	fp.close();
}

void display_contact(int num) /*FUNCTION TO FIND SPECIFIC CONTACT FROM THE LIST OF CONTACTS AND THEN DISPLAY IT IF EXIST*/
{
	bool found;
	int ch;
	 
	found=false;
	fp.open("contactBook.txt",ios::in);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		if(cont.getPhone()==num)
		{
		cont.show_contact();
		found=true;
		}
	}
	fp.close();
	if(found == false){
	cout<<"\n\nNo record found...";}
	getchar();
}
  
void edit_contact() /*FUNCTION TO EDIT THE CONTACT AFTER SEARCHING AND FINDING IT*/
{
	int num;
	bool found=false;
	
	cout<<"Edit contact\n===============================\n\n\t::Enter the number of contact to edit:";
	cin>>num;
	fp.open("contactBook.txt",ios::in|ios::out);
	while(fp.read((char*)&cont,sizeof(contact)) && found==false)
	{
		if(cont.getPhone()==num)
		{
			cont.show_contact();
			cout<<"\nPlease Enter The New Details of Contact: "<<endl;
			cont.create_contact();
			long pos=-1*sizeof(cont);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&cont,sizeof(cont));
			cout<<endl<<endl<<"\t Contact Successfully Updated...\n\n";
			found=true;
		}
	}
	fp.close();
	if(found==false)
	cout<<endl<<endl<<"Contact Not Found...\n\n";	 
}
  
void delete_contact() /*FUNCTION TO DELETE ANY CONTACT FROM THE LIST OF CONTACTS BY PHONE NUMPER*/
{
	int num;
	cout<<endl<<endl<<"Please Enter The contact #: ";
	cin>>num;	
	fp.open("contactBook.txt",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.txt",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&cont,sizeof(contact)))
	{
		if(cont.getPhone()!=num)
		{
			fp2.write((char*)&cont,sizeof(contact));
		}
	}
	fp2.close();
	fp.close();
	remove("contactBook.txt");
	rename("Temp.txt","contactBook.txt");
	cout<<endl<<endl<<"\tContact Deleted...\n\n";
}
bool Dashboard() /*FUNCTION TO DISPLAY MAIN MENU [boolean for Infinite loop]*/
{
	/*JUST DESIGN*/
	cout << "\n\n\t\t\tMAIN MENU\n\t\t|^=*=*=*=*=*=*=*=*=*=*=^|\n\t\t [1] Add a new Contact\n\t\t [2] List all Contacts\n\t\t [3] Search for contact\n\t\t [4] Edit a Contact\n\t\t [5] Delete a Contact\n\t\t [0] Exit\n\t\t|^=*=*=*=*=*=*=*=*=*=*=^|\n\t\t";
	cout << "\n\t\t Enter the choice: ";
	return true;
}

int main() /*MAIN FUNCTION*/
{ 

	int i; /** @param to_use_it_on_While_function_and_Switch_function*/
	cout << "\n\n\t **** Welcome to Contact Management System ****";
	
	while(Dashboard()) /*WHILE FUNCTION TO MAKE PROGRAM IN CONDITIONAL LOOP*/
	{
		cin >> i;

		switch (i)/*SWITCH FUNCTION TO IMPLEMENT WHAT USER'S CHOSE*/
		{
		case 0:
			cout << "\n\n\t\tApp Closed :)\n\t\t-------------\n\t\t#JUNIOR\n\n";
			return 0;
			break;

		case 1:
			save_contact();
			break;

		case 2:
			show_all_contacts();
			break;
		case 3:
			int num;
			cout << "\n\n\tPhone: ";
			cin >> num;
			display_contact(num);
			break;
		case 4:
			edit_contact();
			break;

		case 5:
			delete_contact();
			break;
		default:
		cout<<"\nERROR : Wrong Choice! ,Try Again..\n";
			break;
		}
	}
	return 0;
}