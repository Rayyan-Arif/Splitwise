#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;

//Global Variables
char members[30] , group_name[30];
string GROUP , checkName;
int num_of_GroupMembers=0;
bool GroupAvailable = false;

//Function prototypes
int createAccount();
int createGroups();
int AddExpenses();
void DisplayDetails();
int Menu();
int choice();
int settleUp();
void clearScreen();
bool loggedIn();
bool checkGroup();
int stringLength(string);

int main()
{
    int selectOperation , checkSignUp;
    bool checkLogin;
    while(true)     //this loop runs for sign up and login
    {
        int select = choice();
        if(select == 1)
        {
            checkSignUp = createAccount();
            if(checkSignUp == 0)
                checkLogin = false;
            else
            {
                checkLogin = true;
                break;
            }
        }
        else if(select == 2)
        {
            checkLogin = loggedIn();
            if(checkLogin)
                break;
        }
        else
        {
            cout<<"\nInvalid choice!"<<endl<<endl;
        }
    }
    clearScreen();
    if(checkLogin)      //if login or signup is true then this loop works for operations for the user
    {
        while(true)
        {
            selectOperation = Menu();
            switch(selectOperation)
            {
                case 1:
                    createGroups();
                    break;

                case 2:
                    AddExpenses();
                    break;

                case 3:
                    settleUp();
                    break;
                
                case 4:
                    DisplayDetails();
                    break;
                
                case 5:
                    cout<<"\nThanks for using the application!"<<endl<<endl;
                    return 0;
                
                default:
                    cout<<"Invalid choice! Enter between (1-5)!"<<endl;
                    break;
            }
            clearScreen();
        }
    }
    return 0;
}

//This function is to check if the user has an account or not when user tries to log in
bool loggedIn()
{
    string check ,phone , checkPhone , name , password ,checkPass;
    cout<<"Enter Your name: "<<endl;
    cin.ignore();
    getline(cin , name);
    checkName = name;
    cout<<"Enter phone number: "<<endl;
    getline(cin , phone);
    cout<<"Enter password: "<<endl;
    cin>>password;
    cin.ignore();
    ifstream fin;
    fin.open("Accounts.txt" , ios::in);
    if(!fin)
    {
        cout<<"File not found!"<<endl;
        return 0;
    }
    while(!fin.eof())           //This loops runs till the end of file
    {
        getline(fin , checkName);
        if(stringLength(checkName) == 0)
            continue;
        getline(fin , checkPhone);
        getline(fin , checkPass);
        if(checkName == name && phone == checkPhone && password == checkPass)
        {
            cout<<"Welcome "<<name<<"!"<<endl;
            return true;
        }
    }
    cout<<"Account does not Exist! Please signup!"<<endl;
    return false;
}

//This function is for signup
int createAccount()
{
    string checkPhone, checkNamefromFile , checkPass;
    string phone , name , password;
    cout<<"Enter Your name: "<<endl;
    cin.ignore();
    getline(cin , name);
    checkName = name;
    cout<<"Enter phone number: "<<endl;
    getline(cin , phone);
    cout<<"Enter password: "<<endl;
    cin>>password;
    cin.ignore();
    ifstream fin;
    ofstream createFile;
    createFile.open("Accounts.txt" , ios::out);
    createFile.close();
    fin.open("Accounts.txt" , ios::in);
    while(!fin.eof())   //This loop checks if there is already an account with the same details as user sign up
    {
        getline(fin , checkNamefromFile);
        if(stringLength(checkNamefromFile) == 0) 
                continue;
        getline(fin , checkPhone);
        getline(fin , checkPass);
        if(name == checkNamefromFile)
        {
            cout<<"Name not Available!"<<endl;
            return 0;
        } 
        else if(checkPhone == phone)
        {
            cout<<"Phone number not Available!"<<endl;
            return 0;
        }  
        else if(checkPass == password)
        {
            cout<<"Password not Available!"<<endl;
            return 0;
        }
    }
    ofstream fout;
    fout.open("Accounts.txt" , ios::app);
    fout<<endl<<name<<endl<<phone<<endl<<password<<endl;
    cout<<"Your Account has been opened!"<<endl;
    cout<<"Welcome "<<name<<"!"<<endl;
    fout.close();
    return 1;
}

int createGroups()      //This function creates the group for a particular user
{   
    float individual_expense = 0;
    string name;
    cout<<"\nEnter name of the Group: "<<endl;
    cin.ignore();
    getline(cin , name);
    int create=1;
    ofstream fout;
    fout.open("groups.txt",ios::app);
    fout<<name<<endl;
    cout<<"Enter the number of group members: ";
    cin>>num_of_GroupMembers;
    fout<<num_of_GroupMembers<<endl;
    cout<<"Enter name of members of the group: ";
    cin.ignore();
    while(create<=num_of_GroupMembers)      //This loop add members to a group upto user's choice
    { 
        cin.getline(members , 30);
        fout<<members<<endl<<individual_expense<<endl;
        create++;
    }
    fout<<endl<<endl;
    fout.close();
    cout<<"Group has been succesfully created!"<<endl;
    return 1;
}


int AddExpenses()       //this function adds expenses to the group entered by the user
{
    GroupAvailable = false;
    bool check = false;
    int k , counter=0;
    string match, match1 , oneLine , Group_Name , person;
    float splitted,temp;
    ifstream fin;
    ofstream fout;
    ifstream fin2;
    char name[30];
    float expense , sum=0;
    int num_of_members , split , userID;
    int ID[] = {0,1,2,3,4,5,6,7,8,9};
    fin.open("groups.txt" , ios::in);
    if(!fin)
    {
        cout<<"File not found!"<<endl;
        return 0;
    }
    if(!checkGroup())           //This checks if the user is in the group entered or not / there is a group in the file or not
    {
        cout<<"Group not found! It may not be created by you!"<<endl;
        return 0;
    }
    cout<<"Enter the name of person who paid the bill: ";
    getline(cin , person);
    cout<<"Enter the total expense: ";
    cin>>expense;
    cout<<"Enter the split option: "<<endl;
    cout<<"1. Equal split"<<endl;
    cout<<"2. Unequal split"<<endl;
    cin>>split;
    cin.ignore();
    fout.open("tempfile.txt", ios::out);
    while(getline(fin , Group_Name))
    {
        if(stringLength(Group_Name) == 0) 
                continue;
        if(Group_Name == GROUP)         //If group entered by user matches with group in the file and user can perform further operations
        {
            fin>>num_of_GroupMembers;
            string Members[num_of_GroupMembers];
            int Expenses[num_of_GroupMembers];
            fin.ignore();
            if(split == 1)          //if split is equal
            {
                cout<<"Enter the total members who will pay the bill: ";
                cin>>num_of_members;
                if(num_of_members<=0 || num_of_members>num_of_GroupMembers)
                {
                    cout<<"Invalid input for number of members!"<<endl;
                    return 0;
                }
                cin.ignore();
                fout<<Group_Name<<endl;
                fout<<num_of_GroupMembers<<endl;
                for(int j=0 ; j<num_of_GroupMembers ; j++)
                {
                    getline(fin , Members[j]);
                    fin>>Expenses[j];
                    Expenses[j] = 0;
                    fin.ignore();
                }
                for(int l=0 ; l<num_of_GroupMembers ; l++)
                {
                    cout<<"Name: "<<Members[l]<<"  ID: "<<ID[l]<<endl;  //Shows name of members with their ID's
                }
                for(int j=0 ; j<num_of_members ; j++)
                {
                    check = false;
                    cout<<"Enter the ID of Member "<<Members[j]<<": ";
                    cin>>userID;
                    cin.ignore();
                    for(k=0 ; k<num_of_GroupMembers ; k++)
                    {
                        if(userID == ID[k])
                        {
                            splitted = expense/num_of_members;
                            Expenses[k] += splitted;
                            check = true;
                            break;
                        }
                    }
                    if(check == false)
                    {
                        cout<<"Member not found!"<<endl;
                        j--;
                    }
                }
                for(int k=0 ; k<num_of_GroupMembers ; k++)
                {
                    fout<<Members[k]<<endl;
                    fout<<Expenses[k]<<endl;
                }
                fout<<"The members have to pay money to "<<person<<endl;
                fout<<endl<<endl;
            }
            else if(split == 2)         //If split is unequal
            {
                cout<<"Enter the total members who will pay the bill: ";
                cin>>num_of_members;
                if(num_of_members<=0 || num_of_members>num_of_GroupMembers)
                {
                    cout<<"Invalid input for number of members!"<<endl;
                    return 0;
                }
                cin.ignore();
                fout<<Group_Name<<endl;
                fout<<num_of_GroupMembers<<endl;
                for(int j=0 ; j<num_of_GroupMembers ; j++)
                {
                    getline(fin , Members[j]);
                    fin>>Expenses[j];
                    Expenses[j] = 0;
                    fin.ignore();
                }
                for(int l=0 ; l<num_of_GroupMembers ; l++)
                {
                    cout<<"Name: "<<Members[l]<<"  ID: "<<ID[l]<<endl;
                }
                for(int j=0 ; j<num_of_members && sum<expense ; j++)
                {
                    check = false;
                    cout<<"Enter the ID of Member "<<Members[j]<<": ";
                    cin>>userID;
                    cin.ignore();
                    for(k=0 ; k<num_of_GroupMembers ; k++)
                    {
                        if(userID == ID[k])
                        {
                            cout<<"Enter the amount to be paid by Member "<<Members[k]<<": ";
                            cin>>splitted;
                            if((sum+splitted)>expense)
                            {
                                splitted = expense-sum;
                            }
                            sum += splitted;
                            cin.ignore();
                            Expenses[k] += splitted;
                            check = true;
                            break;
                        }
                    }
                    if(check == false)
                    {
                        cout<<"Member not found!"<<endl;
                        j--;
                    }
                }
                for(int k=0 ; k<num_of_GroupMembers ; k++)
                {
                    fout<<Members[k]<<endl;
                    fout<<Expenses[k]<<endl;
                }
                fout<<"The members have to pay money to "<<person<<endl;
                fout<<endl<<endl;
            }
            counter++;
        }
        else{           //All groups will remain as it is in the file
            fin>>num_of_GroupMembers;
            fin.ignore();
            int Expenses[num_of_GroupMembers];
            fout<<Group_Name<<endl;
            fout<<num_of_GroupMembers<<endl;
            for(int i=0 ; i<num_of_GroupMembers; i++)
            {
                fin.getline(members , 30);
                fin>>Expenses[i];
                fout<<members<<endl;
                fout<<Expenses[i]<<endl;
                fin.ignore();
            }
            getline(fin , oneLine);
            fout<<oneLine<<endl;
            fout<<endl<<endl;
        }
        getline(fin , oneLine);
    }
    if(counter == 0)
    {
        cout<<"\nGroup Not Found!"<<endl;
        return 0;
    }
    fin.close();
    fout.close();
    remove("groups.txt");       //This function deletes the file
    rename("tempfile.txt" , "groups.txt");      //This function renames the temp file to deleted file name
    cout<<"\nExpense has been added! Operation Successful!"<<endl;
    return 1;
}

void DisplayDetails()       //this function displays all the details of groups of user
{
    int counter=0;
    cout<<endl<<"All Groups Details!"<<endl<<endl;
    string oneLine , Group_Name;
    ifstream fin;
    fin.open("groups.txt" , ios::in);
    if(!fin)
    {
        cout<<"File not found!"<<endl;
        return;
    }
    while(!fin.eof())
    {
        bool checkAllGroups = false;
        getline(fin , Group_Name);
        if(stringLength(Group_Name) == 0) 
            continue;
        fin>>num_of_GroupMembers;
        int Expenses[num_of_GroupMembers];
        string Members[num_of_GroupMembers];
        fin.ignore();
        for(int i=0 ; i<num_of_GroupMembers ; i++)
        {
            getline(fin , Members[i]);
            fin>>Expenses[i];
            fin.ignore();
        }
        getline(fin , oneLine);
        for(int i=0 ; i<num_of_GroupMembers ; i++)  //This loop checks if user is in the group or not
        {
            if(checkName == Members[i])
            {
                checkAllGroups = true;
                break;
            }
        }
        if(checkAllGroups)      //If user is in the group then it's details will be displayed
        {
            cout<<"GROUP:  "<<Group_Name<<endl;
            cout<<"MEMBERS: "<<num_of_GroupMembers<<endl;
            for(int i=0 ; i<num_of_GroupMembers ; i++)
            {
                cout<<"Name: "<<Members[i]<<"       Expense: "<<Expenses[i]<<endl;
            }
            cout<<oneLine;
            counter++;
        }
        cout<<endl<<endl;
    }
    if(counter==0)
    {
        cout<<"No groups found!"<<endl;
    }
}

int choice()
{
    int choice;
    cout<<"\nWelcome to the Expense-sharing APP!"<<endl;
    cout<<"1. Sign Up"<<endl;
    cout<<"2. Login"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    return choice;
}

int Menu()      //Menu function
{
    int choice;
    cout<<"\nYou can perform the following operations!"<<endl;
    cout<<"1. Create Groups"<<endl;
    cout<<"2. Add Expenses"<<endl;
    cout<<"3. Settle up"<<endl;
    cout<<"4. Display Expense Details"<<endl;
    cout<<"5. Log out"<<endl;
    cout<<"NOTE: You need to create a group first for other operations!"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    return choice;
}

int settleUp()      //this function displays the details of particular group entered by the user
{
    GroupAvailable = false;
    string oneLine , Group_Name , searchGroup , MEMBERS;
    float expense;
    if(!checkGroup())
    {
        cout<<"Group not found! It may not be created by you!"<<endl;
        return 0;
    }
    ifstream fin;
    fin.open("groups.txt" , ios::in);
    if(!fin)
    {
        cout<<"File not found!"<<endl;
        return 0;
    }
    while(getline(fin , searchGroup))
    {
        if(stringLength(searchGroup) == 0) 
            continue;
        if(searchGroup == GROUP)
        {
            fin>>num_of_GroupMembers;
            float Expenses[num_of_GroupMembers];
            string Members[num_of_GroupMembers];
            fin.ignore();
            cout<<"\nGroup: "<<GROUP<<endl;
            cout<<"MEMBERS: "<<num_of_GroupMembers<<endl;
            for(int i=1 ; i<=num_of_GroupMembers ; i++)
            {
                getline(fin , MEMBERS);
                fin>>expense;
                fin.ignore();
                cout<<"Name: "<<MEMBERS<<"     Expense: "<<expense<<endl;
            }
            getline(fin , oneLine);
            cout<<oneLine<<endl;
        }
    }
    fin.close();
    return 0;
}

void clearScreen()
{
	cout<<"\nPress Any Key to Continue.....\n";
	getch();
	system("CLS");
}

bool checkGroup()       //this function checks if the group entered by the user is accessible to the user or not
{
    ifstream fin;
    string oneLine , Group_Name , searchGroup;
    cout<<"Enter the name of the Group: ";
    cin.ignore();
    getline(cin , Group_Name);
    GROUP = Group_Name;
    fin.open("groups.txt" , ios::in);
    if(!fin)
    {
        cout<<"File not found!"<<endl;
        return 0;
    }
    while(getline(fin , searchGroup))
    {
        if(stringLength(searchGroup) == 0) 
                continue;
        if(Group_Name == searchGroup)
        {
            fin>>num_of_GroupMembers;
            float Expenses[num_of_GroupMembers];
            string Members[num_of_GroupMembers];
            fin.ignore();
            for(int j=0 ; j<num_of_GroupMembers ; j++)
            {
                getline(fin , Members[j]);
                fin>>Expenses[j];
                fin.ignore();
            }
            for(int j=0 ; j<num_of_GroupMembers ; j++)      //This loops verifies if group is accessible by the user or not
            {
                if(Members[j] == checkName)
                {
                    cout<<"Group found!"<<endl;     
                    return true;
                }
            }
        }
    }
    fin.close();
    return false;
}

int stringLength(string STRING)     //This function finds the string length
{
    int length;
    for(length=0 ; STRING[length]!='\0' ; length++);
    return length;
}