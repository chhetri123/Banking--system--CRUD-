#include<iostream>
#include<fstream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<iomanip>

using namespace std;
class Bank{
    private:
        int bankid;
         long accountNumber;
        char lastname[20], firstname[20];
        float totalBalance;
    protected:
        int getBankId();
        void showHeader();

    public:
        void getDetail();
        void showDetail();
        void addAccount();
        void showAccounts();
        void searchAccount();
        void deleteAccount();
        void updateAccount();
};

int Bank::getBankId(){

    ifstream fin;
    Bank temp;
    int id = 0;
    fin.open("account.txt", ios::in);
    if(!fin){
        return (id++);
    }
    else
    {
        fin.read((char *)&temp, sizeof(temp));
        while(!fin.eof()){
            id = temp.bankid;
            
        fin.read((char *)&temp, sizeof(temp));

        }
        id++;
        return id;
    }
}

void Bank::showHeader(){
    cout << left;
    cout << endl
         << setw(10) << "ID" << setw(10) << "firstname" << setw(10) << "accountNumber" << setw(10) << "Balance" << endl;
    cout << "----------------------------------------------------------------" << endl;
}



void Bank::getDetail(){
   try{
   
    cout << "Enter firstName";
    cin>> firstname;
    cout << "Enter lastName";
   cin>>lastname;
    cout << "Enter AccountNumber";
    cin >> accountNumber;
    cout << "Enter Balance";
    cin >> totalBalance;
    if (totalBalance < 10)
    {
        throw "Balance must be greater than 10";
         }
if(!bankid){
bankid = getBankId();
}
         
   }
   catch (string err)
   {
       cout << err << endl;
       
   }
}
void Bank::showDetail(){
        cout << left;
    cout << endl
         << setw(10) << bankid << setw(10) << firstname << setw(10) << accountNumber << setw(10) << totalBalance << endl;

}
void Bank::addAccount(){
    ofstream fout;
    fout.open("account.txt", ios::out | ios::binary | ios::app);
    if(!fout){
        cout << "File cannot open";
    }
    else
    {

        fout.write((char *)this, sizeof(this));
        fout.close();
    }
}
void Bank::showAccounts(){
    ifstream fin;
    fin.open("account.txt", ios::in | ios::binary);
    if(!fin){
        cout<<"File not found";
    }
    else{
        showHeader();
        fin.read((char*)this,sizeof(this));
        while(!fin.eof()){
            showDetail();
            fin.read((char *)this, sizeof(this));
        }

    }
    fin.close();
}
void Bank::searchAccount(){
    ifstream fin;
    char str[20];
    fin.open("account.txt", ios::in | ios::binary);
    cout << "Enter the name of account" << endl;
    cin >> str;
    if(!fin){
        cout << "File  not found";

    }else{
        fin.read((char *)this, sizeof(this));
        while(!fin.eof()){
            if(strcmp(this->firstname,str)){
                showHeader();
                showDetail();
                break;
            }
            fin.read((char *)this, sizeof(this));
        }

        if(fin.eof()){
            cout << "Record not found" << endl;
        }
    }
    fin.close();
}

void Bank::updateAccount(){
    int id, r = 0;
    fstream file;
    file.open("account.txt",ios::app |ios::in|ios::out |ios::ate|ios::binary);
    cin >> id;
    file.seekg(0);
    if(!file){
        cout << "File not found";

    }
    else{
        file.read((char *)this, sizeof(this));
        while(!file.eof()){
            r++;
            if(this->bankid== id){
                showHeader();
                showDetail();
                cout << endl << "Re enter the details" << endl;
                this->getDetail();
                file.seekp((r - 1) * sizeof(Bank), ios::beg);
                file.write((char *)this, sizeof(this));
                break;
            }
            file.read((char *)this, sizeof(this));

        }
        if(file.eof()){
            cout << "Record not found" << endl;
        }
    }
    file.close();

}

void Bank::deleteAccount(){
    ifstream fin;
    ofstream fout;
    int id;
    char x[1];
    fin.open("account.txt", ios::in | ios::binary);
    fout.open("deletedAccount.txt", ios::out | ios::app | ios::binary);
    cout << "Enter the bank id you want to delete" << endl;
    cin >> id;
    if(!fin){
        cout << "File not found";

    }
    else{
        fin.read((char *)this, sizeof(this));
        while(!fin.eof()){
            if(this->bankid==id){
                cout << "Record you want to delete is:" << endl;
                showHeader();
                showDetail();
                cout << "Are you sure you want to delete?[Y/N] :";
                fflush(stdin);
                cin >> x;
                if(x=="n"){
                    fout.write((char *)this, sizeof(this));



                }else{
                    cout << endl
                         << "Record deleted" << endl;
                }
            }else{
                fout.write((char *)this, sizeof(this));
                fin.read((char *)this, sizeof(this));
            }
        }
        fin.close();
        fout.close();
        system("erase account.txt");
        system("rename deletedAccount.txt account.txt");
    }
}
int menu(){
    
    system("clear");
    int ch;
    cout << "1.Create BankAccount" << endl;
    cout << "2. View all Accounts" << endl;
    cout << "3.Search Accounts" << endl;
    cout << "4.Update BankAccount" << endl;
    cout << "5.Delete BankAccount" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice= ";
    cin >> ch;
    return ch;
}

int main(){
    Bank b;
    int ch;

        ch = menu();
        system("clear");
        switch (ch)
        {
        case 1:
            b.getDetail();
            b.addAccount();
            break;
        case 2:
            b.showAccounts();
            break;

        case 3:
        b.searchAccount();
        break;
        case 4:
        b.updateAccount();
        break;

        case 5:
        b.deleteAccount();
        break;

        case 6:
            exit(0);

         default:
             cout << "Enter valid choice";
         }

    return 0;
}