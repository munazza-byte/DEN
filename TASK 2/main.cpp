#include"Contact.h"
#include<iostream>
using namespace std;
int main()
{
	vector<Contact>ContactsDiary= {
		Contact("Abdullah",30218574567),
		Contact("Faiza",30218574567),
		Contact("Aima",30218574567),
		Contact("Aleeza",30218574567)
	};
	int Choice;
	do
	{
		Contact C;
		cout<<endl<<"\t\t--- CONTACT HANDLING SYSTEM---"<<endl;
		cout<<endl<<"1. Add A Contact "<<endl;
		cout<<endl<<"2. Remove A Contact"<<endl;
		cout<<endl<<"3. Show All The Contacts"<<endl;
		cout<<endl<<"4. EXIT "<<endl;
		cout<<endl<<" Choose a Choice :"<<endl;
		cin>>Choice;
		cin.ignore();
		if (Choice==1)
		{
			C.AddAContact(ContactsDiary);
		}
		else if (Choice==2)
		{
			C.RemoveAContact(ContactsDiary);
		}
		else if (Choice==3)
		{
			C.ShowAllList(ContactsDiary);
		}
		else if (Choice==4)
		{
			cout<<endl<<" EXIT"<<endl;
		}
		else
		{
			cout<<" Invalid Choice. PLEASE TRY AGAIN!"<<endl;
		}

	}
	while(Choice!=4);
	return 0;
}