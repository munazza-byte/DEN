#include<string>
#include<vector>
using namespace std;
class Contact
{
private:
	string Name;
	long PhoneNumber;
public:
	Contact();
	Contact(string N,  long PNo);
	static void AddAContact(vector<Contact>&ContactsDiary);
	static void ShowAllList(vector<Contact>&ContactsDiary);
	static void RemoveAContact(vector<Contact>&ContactsDiary);
};