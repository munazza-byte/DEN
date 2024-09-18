#include"Contact.h"
#include<iostream>
using namespace std;

Contact:: Contact()
{
	Name=" ";
	PhoneNumber=0;
}

Contact:: Contact( string N,long PNo)
{
	Name=N;
	PhoneNumber=PNo;
}

void Contact:: AddAContact(vector<Contact>&ContactsDiary)
{
	string Name;
	long PhoneNo;
	cout<< "Enter A Contact Name :"<<endl;
	getline(cin,Name);
	cout<<"Enter The Phone Number :"<<endl;
	cin>>PhoneNo;
	Contact newContact(Name,PhoneNo);
	ContactsDiary.push_back(newContact);
	cout<<"A NEW CONTACT ADDED SUCCESSFULLY!"<<endl;
}

void Contact:: ShowAllList(vector<Contact>&ContactsDiary)
{
	if(ContactsDiary.empty())
	{
		cout<<"THERE ARE NO CONTACTS TO SHOW "<<endl;
		return;
	}
	cout<<"CONTACTS: "<<endl;
	for(const auto&Number:ContactsDiary)
	{
		cout<<endl<<"Contact Name: "<<Number.Name<<endl;
		cout<<"PhoneNumber: "<<Number.PhoneNumber<<endl;
	}

}
void Contact:: RemoveAContact(vector<Contact>&ContactsDiary)
{
	if(ContactsDiary.empty())
	{
		cout<<endl<<" THERE ARE NO EXISTING CONTACTS!"<<endl;
		return;
	}
	string RemoveName;
	cout<<endl<<"ENTER THE NAME OF CONTACT YOU WANT TO REMOVE: "<<endl;
	getline(cin,RemoveName);
	
	bool found= false;
	for(size_t i=0; i<ContactsDiary.size(); i++)
	{
		if(ContactsDiary[i].Name==RemoveName)
		{
			ContactsDiary.erase(ContactsDiary.begin() + i);
			found=true;
			cout<<endl<<"CONTACT IS REMOVED SUCCESSFULLY"<<endl;
			break;
		}
	}
	if(!found)
	{
		cout<<endl<<" CONTACT NOT FOUND! "<<endl;
	}
}