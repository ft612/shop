#include <iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstring>
#include<vector>
#include<time.h>
#include<random>
#include<stdlib.h>

using namespace std;


class Comment
{
    friend ostream& operator<<(ostream& out ,const Comment& c );
public:
    Comment(){};
    void print();


public:
    int _idKala;
    string _username;
    string _text;
    int _star;
    bool _show;
};

class Kala
{
    friend ostream& operator<<(ostream& out ,const Kala& k );
public:
    Kala(){};
    void print();
    void print2();
    void decreaseCount(int c);

public:
    int _id;
    string _name;
    int _price;
    string _description;
    int _amount;
    string _category;
    string _city;
    vector<Comment> comments;
    int countBuy;
};

class stFactor
{
public:
    stFactor()
    {
        for(int i=0 ; i<50 ; i++)
        {
            id[i]=-1;
            price[i]=-1;
            count[i]=-1;
        }
            
    }

    int id[50];
    int price[50];
    int count[50];
    string username;
};

class Factor
{
public:
    Factor() : _kala(){};
    void print();

public:
    Kala _kala;
    int _count;
};

//--------------------------------------------------------------------------------------------------------------------------

class Person
{
    friend ostream& operator<<(ostream& out ,const Person& p );
public:
    Person(){};
public:
    int _id;
    string _name;
    string _city;
    string _address;
    string _email;
    string _username;
    string _pass;
    string _type;
};

class Admin : public Person
{
public:
    Admin(){};
    void print();
    Admin operator=(const Person& p);

};

class User : public Person
{
public:
    User(){}
    void print();
    User operator=(const Person& p);
    void addFactor(vector<Factor>& cart);

public:
    vector<Factor> _factor;
};



void readPersonTextFileAndSetVector(vector<Person>&persons);
void readKalaTextFileAndSetVector( vector<Kala>&kalas);
void readCommentTextFileAndSetVector( vector<Comment>&comments);
void readFactorTextFileAndSetVector( vector<stFactor>&factors);

void setUserAndAdmin(vector<User>& userList,vector<Admin>& adminList , vector<Person>& personList);
void setFactorForUsers(vector<User>& userList , vector<stFactor>& stFactorList , vector<Kala>& KalaList);
void setCommentForKala(vector<Kala>& KalaList , vector<Comment>& commentList);

void firstMeno( vector<Person>& personList ,  vector<User>& userList
               , vector<Admin>& adminList ,vector<Kala>&kalaList
               ,vector<Comment>&comments , vector<stFactor>& factors);




int main()
{
    srand(time(0));

    vector<Person>persons;
    readPersonTextFileAndSetVector(persons);

    vector<Kala>kalas;
    readKalaTextFileAndSetVector(kalas);

    vector<Comment>comments;
    readCommentTextFileAndSetVector(comments);

    vector<stFactor>factors;
    readFactorTextFileAndSetVector(factors);

    vector<User>users;
    vector<Admin>admins;

    setUserAndAdmin(users,admins,persons);
    setCommentForKala(kalas,comments);
    setFactorForUsers(users,factors,kalas);

    firstMeno(persons,users,admins,kalas,comments,factors);



    return 0;
}






ostream& operator<<(ostream& out ,const Person& p )
{
    out<<"id = "<<p._id<<" , name = "<<p._name<<" , city = "<<p._city
            <<" , address = "<<p._address<<"\n"<<"email = "<<p._email
            <<" , username = "<<p._username<<" , pass = "<<p._pass
           <<" , type = "<<p._type;
    return  out;
}


void Admin::print()
{
    cout << setiosflags(ios::left) << setw(10) << "id" << setw(20) << "Name"
         << setw(20) << "City" << setw(30) << "Address"<< setw(30) << "Email"<< setw(20) << "Username"
         << setw(20) << "password"<< setw(20) << "type"<< setiosflags(ios::fixed | ios::showpoint)<<endl;


    cout << fixed<<left << setw(10) << _id << setw(20) << _name
         << setw(20) << _city << setw(30) << _address
         << setw(30) << _email<< setw(20) << _username
         << setw(20) << _pass<< setw(20) << _type<<endl;


    cout<<endl;
}
Admin Admin::operator=(const Person &p)
{
    _id = p._id;
    _name = p._name;
    _city = p._city;
    _address = p._address;
    _email = p._email;
    _username = p._username;
    _pass = p._pass;
    _type = p._type;

    return  *this;
}


void User::print()
{
    cout << fixed<<left << setw(10) << _id << setw(15) << _name
         << setw(15) << _city << setw(30) << _address
         << setw(30) << _email<< setw(15) << _username
         << setw(15) << _pass<< setw(10) << _type<<endl;
}
User User::operator=(const Person &p)
{
     _id = p._id;
     _name = p._name;
     _city = p._city;
     _address = p._address;
     _email = p._email;
     _username = p._username;
     _pass = p._pass;
     _type = p._type;

     return  *this;
}
void User::addFactor(vector<Factor> &cart)
{
    for(int i=0 ; i<(int)cart.size() ; i++)
    {
        _factor.push_back(cart[i]);
    }
}


void Kala::print()
{
    cout << "id = " << _id  <<"\nName = "<< _name
         << "\nPrice = " << _price<<"$" << "\nDescription = " << _description<< "\nAmount = " <<_amount
         << "\nCategory = " << _category << "\nCity = " << _city<< endl;

    cout<<"\ncomments of customers :\n\n";

    int j=1;
    for(int i=0 ; i<(int)comments.size() ; i++)
    {
        if(comments[i]._show)
        {
            cout<<j<<") ";
            if(comments[i]._show)
                comments[i].print();
            cout<<endl;
            j++;
        }

    }

}
void Kala::print2()
{
    cout << fixed<<left << setw(10) << _id << setw(20) << _name
         << setw(10) << _price << setw(50) << _description<< setw(10) << _amount
         << setw(20) << _category << setw(20) << _city<<endl;
}
void Kala::decreaseCount(int c)
{
    _amount -=c;
}
ostream& operator<<(ostream& out ,const Kala& k )
{
    out<<"id = " << k._id << " , name = " <<k._name
            << " , price = " << k._price << " , description = " << k._description<< endl
            <<"amount = "<<k._amount
            << " , category = " << k._category << " , city = " << k._city;

    return out;
}


void Comment::print()
{
    cout <<_username <<" : "<<_text <<" ("<< _star<<" star)";
}
ostream& operator<<(ostream& out ,const Comment& c )
{
    out<<"id = "<<c._idKala  <<" , username = "<<c._username
            <<" , comment = "<<c._text<<" , star = "<<c._star <<" , show = "<<c._show;
    return  out;
}


void Factor::print()
{
    cout << fixed<<left << setw(10) << _kala._id << setw(20) << _kala._name
         << setw(10) << _kala._price << setw(50) << _kala._description
         << setw(20) << _kala._category << setw(20) << _kala._city<<setw(20) << _count<<endl;
}


//--------------------------------------------------------------------------------------------------------------------------


Person extractPerson(string& s1 , string& s2)
{

    int start = 0;
    int end = 0;
    Person p;

    end = s1.find(" , name = ");
    p._id = stoi(s1.substr(5,end-5));

    start = end + 10;
    end = s1.find(" , city = ");
    p._name = s1.substr(start,end-start);

    start = end + 10;
    end = s1.find(" , address = ");
    p._city = s1.substr(start,end-start);

    start = end + 13;
    p._address = s1.substr(start,s1.size()-start);

//----------------

    start = 8;
    end = s2.find(" , username = ");
    p._email = s2.substr(start,end-start);

    start = end + 14;
    end = s2.find(" , pass = ");
    p._username = s2.substr(start,end-start);

    start = end + 10;
    end = s2.find(" , type = ");
    p._pass = s2.substr(start,end-start);

    start = end + 10;
    p._type = s2.substr(start,s2.size()-start);

    return p;
}
void readPersonTextFileAndSetVector(vector<Person>&persons)
{
    ifstream inputTXT("E:\\university\\lessons\\pishrafte\\final Project\\user.txt"
                      , ios::in);
    if(!inputTXT)
        cout<<"cant open TXT file";

    string line1 , line2;
    Person p;

    while(!inputTXT.eof())
    {
        getline(inputTXT,line1,'\n');
        getline(inputTXT,line2,'\n');
        inputTXT.get();
        p=extractPerson(line1,line2);
        persons.push_back(p);
        //persons[p.id] = p;
    }


}

Kala extractKala(string& s1 , string& s2)
{
    int start = 0;
    int end = 0;
    Kala k;

    end = s1.find(" , name = ");
    k._id = stoi(s1.substr(5,end-5));

    start = end + 10;
    end = s1.find(" , price = ");
    k._name = s1.substr(start,end-start);

    start = end + 11;
    end = s1.find(" , description = ");
    k._price = stod(s1.substr(start,end-start));

    start = end + 17;
    end = s1.find(" , amount = ");
    k._description = s1.substr(start,s1.size()-start);

//-------------------

    start = 9;
    end = s2.find(" , category = ");
    k._amount = stoi(s2.substr(start,end-start));

    start = end + 14;
    end = s2.find(" , city = ");
    k._category = s2.substr(start,end-start);


    start = end + 10;
    k._city = s2.substr(start,s2.size()-start);

    return k;
}
void readKalaTextFileAndSetVector( vector<Kala>&kalas)
{
    ifstream inputTXT("E:\\university\\lessons\\pishrafte\\final Project\\product.txt"
                      , ios::in);
    if(!inputTXT)
        cout<<"cant open TXT file";

    string line1,line2;
    Kala k;
    //int i=0 ;

    while(!inputTXT.eof())
    {
        getline(inputTXT,line1,'\n');
        getline(inputTXT,line2,'\n');
        inputTXT.get();
        k=extractKala(line1,line2);
        kalas.push_back(k);
        //i++;
    }


}

Comment extractComment(string& s)
{
    int start = 0;
    int end = 0;
    Comment c;

    end = s.find(" , username = ");
    c._idKala = stoi(s.substr(5,end-5));

    start = end + 14;
    end = s.find(" , comment = ");
    c._username = s.substr(start,end-start);

    start = end + 13;
    end = s.find(" , star = ");
    c._text = s.substr(start,end-start);


    start = end + 10;
    end = s.find(" , show = ");
    c._star = stoi(s.substr(start,end-start));


    start = end + 10;
    c._show = stoi(s.substr(start,s.size()-start));

    return c;
}
void readCommentTextFileAndSetVector( vector<Comment>&comments)
{
    ifstream inputTXT("E:\\university\\lessons\\pishrafte\\final Project\\comment.txt"
                      , ios::in);
    if(!inputTXT)
        cout<<"cant open TXT file";

    string line;
    Comment c;
    //int i=0;

    while(!inputTXT.eof())
    {
        getline(inputTXT,line,'\n');
        inputTXT.get();
        c=extractComment(line);
        comments.push_back(c);
        //i++;

    }


}

stFactor extractFactor(string& s)
{
    int start = 0;
    int end = 0;
    int start2,end2,i=0,k;
    stFactor f;

    end = s.find(" , price = ");
    start2=5;
    end2 = s.find(",");
    if(end2>end)
    {
        f.id[i] = stoi(s.substr(start2,end-start2));
        i++;
    }
    while(end2<=end)
    {
        k=end2-start2;
        f.id[i] = stoi(s.substr(start2,k));
        i++;
        start2 = end2+1;
        end2 = s.find(",",start2);
        if(end2>end)
        {
            f.id[i] = stoi(s.substr(start2,end-start2));
            i++;
        }
    }



    i=0;
    start = end + 11;
    end = s.find(" , count = ");
    start2 = start;
    end2 = s.find(",",start2);
    if(end2>end)
    {
        f.price[i] = stoi(s.substr(start2,end-start2));
        i++;
    }
    while(end2<=end)
    {
        k=end2-start2;
        f.price[i] = stoi(s.substr(start2,k));
        i++;
        start2 = end2+1;
        end2 = s.find(",",start2);
        if(end2>end)
        {
            f.price[i] = stoi(s.substr(start2,end-start2));
            i++;
        }
    }

    i=0;
    start = end + 11;
    end = s.find(" , username = ");
    start2 = start;
    end2 = s.find(",",start2);
    if(end2>end)
    {
        f.count[i] = stoi(s.substr(start2,end-start2));
        i++;
    }
    while(end2<=end)
    {
        k=end2-start2;
        f.count[i] = stoi(s.substr(start2,k));
        i++;
        start2 = end2+1;
        end2=s.find(",",start2);
        if(end2>end)
        {
            f.count[i] = stoi(s.substr(start2,end-start2));
            i++;
        }
    }



    start = end + 14;
    f.username = s.substr(start,s.size()-start);

    return f;
}
void readFactorTextFileAndSetVector( vector<stFactor>&factors)
{
    ifstream inputTXT("E:\\university\\lessons\\pishrafte\\final Project\\factors.txt"
                      , ios::in);
    if(!inputTXT)
        cout<<"cant open TXT file";

    string line;
    stFactor f;
    //int i=0;

    while(!inputTXT.eof())
    {
        getline(inputTXT,line,'\n');
        f =extractFactor(line);
        factors.push_back(f);
        //i++;
    }


}

void writePersonTXT(vector<Person>&persons)
{
    ofstream outputTXT("E:\\university\\lessons\\pishrafte\\final Project\\user.txt"
                       , ios::trunc | ios::out);
    if(!outputTXT)
        cout<<"cant open TXT file";


    for(int i=0 ; i<(int)persons.size() ; i++)
    {
        if(i!=0)
            outputTXT<<"\n";

        outputTXT<<persons[i];

        if(i!=(int)persons.size()-1)
            outputTXT<<"\n";
        /*outputTXT<<"id="<<persons[i]._id<<",name="<<persons[i]._name<<",city="<<persons[i]._city
                <<",address="<<persons[i]._address<<"\n"<<"email="<<persons[i]._email
                <<",username="<<persons[i]._username<<",pass="<<persons[i]._pass
               <<",type="<<persons[i]._type;*/
    }

}

void writeCommentTXT(vector<Comment>&comments)
{
    ofstream outputTXT("E:\\university\\lessons\\pishrafte\\final Project\\comment.txt"
                       , ios::trunc | ios::out);
    if(!outputTXT)
        cout<<"cant open TXT file";


    for(int i=0 ; i<(int)comments.size() ; i++)
    {
        if(i!=0)
            outputTXT<<"\n";

        outputTXT<<comments[i];

        if(i!=(int)comments.size()-1)
            outputTXT<<"\n";

        /*outputTXT<<"id="<<comments[i]._idKala  <<",username="<<comments[i]._username
                <<",comment="<<comments[i]._text<<",star="<<comments[i]._star <<",show="<<comments[i]._show;*/
    }

}

void writeFactorTXT(vector<stFactor>& factors)
{
    ofstream outputTXT("E:\\university\\lessons\\pishrafte\\final Project\\factors.txt"
                       , ios::trunc | ios::out);
    if(!outputTXT)
        cout<<"cant open TXT file";


    for(int i=0 ; i<(int)factors.size() ; i++)
    {
        if(i!=0)
            outputTXT<<"\n";
        int j=0;

        outputTXT<<"id = ";
        while(factors[i].id[j]!=-1)
        {
            outputTXT<<factors[i].id[j];
            j++;
            if(factors[i].id[j]!=-1)
                outputTXT<<",";
        }

        j=0;
        outputTXT<<" , price = ";
        while(factors[i].price[j]!=-1)
        {
            outputTXT<<factors[i].price[j];
            j++;
            if(factors[i].price[j]!=-1)
                outputTXT<<",";
        }

        j=0;
        outputTXT<<" , count = ";
        while(factors[i].count[j]!=-1)
        {
            outputTXT<<factors[i].count[j];
            j++;
            if(factors[i].count[j]!=-1)
                outputTXT<<",";
        }

        outputTXT<<" , username = "<<factors[i].username;

    }



}

void writeKalaTXT(vector<Kala>&kalas)
{
    ofstream outputTXT("E:\\university\\lessons\\pishrafte\\final Project\\product.txt"
                       , ios::trunc | ios::out);
    if(!outputTXT)
        cout<<"cant open TXT file";

    for(int i=0 ; i<(int)kalas.size() ; i++)
    {
        if(i!=0)
            outputTXT<<"\n";

        outputTXT<<kalas[i];

        if(i!=(int)kalas.size()-1)
            outputTXT<<"\n";
        /*outputTXT<<"id=" << kalas[i]._id << ",name=" << kalas[i]._name
                << ",price=" << kalas[i]._price << ",description=" << kalas[i]._description<< endl
                <<"amount="<< kalas[i]._amount
                << ",category=" << kalas[i]._category << ",city=" << kalas[i]._city;*/
    }

}


//--------------------------------------------------------------------------------------------------------------------------


void setCommentForKala(vector<Kala>& KalaList , vector<Comment>& commentList)
{
    Comment c;

    for(int i=0 ; i<(int)KalaList.size() ; i++)
    {
        for(int j=0 ; j<(int)commentList.size() ; j++)
        {
            if(commentList[j]._idKala == KalaList[i]._id)
            {
                c=commentList[j];
                KalaList[i].comments.push_back(c);
            }
        }
    }
}

void seeProduct(vector<Kala>&kalaList)
{
    cout << setiosflags(ios::left) << setw(10) << "id" << setw(20) << "Name"
         << setw(10) << "Price" << setw(50) << "Description"<< setw(10) << "Amount"<< setw(20) << "Category"
         << setw(20) << "City"<< setiosflags(ios::fixed | ios::showpoint)<<endl;
    for(int i=0 ; i<(int)kalaList.size() ; i++)
        kalaList[i].print2();
}

int searchIdKala(vector<Kala>&kalaList, int id)
{
    for(int i=0 ; i<(int)kalaList.size() ; i++)
    {
        if(kalaList[i]._id == id)
        {
            return i;
        }
    }
    return -1;
}

void seeFactor(vector<Factor>& cart)
{
    cout << setiosflags(ios::left) << setw(10) << "id" << setw(20) << "Name"
         << setw(10) << "Price" << setw(50) << "Description"<< setw(20) << "Category"
         << setw(20) << "City"<<setw(20) << "Number"<< setiosflags(ios::fixed | ios::showpoint)<<endl;
    for(int i=0 ; i<(int)cart.size() ; i++)
        cart[i].print();
}

void updateStfactor(string& username,vector<stFactor>& factors,vector<Factor>& cart)
{
    stFactor factor;
    int addIndex = 0;

    factor.username = username;

    for(int i=0 ; i<(int)cart.size() ; i++)
    {
        factor.id[addIndex] = cart[i]._kala._id;

        factor.price[addIndex] = cart[i]._kala._price;

        factor.count[addIndex] = cart[i]._count;

        addIndex++;
    }

    factors.push_back(factor);

}

void seeCommentAndConfirm(vector<Kala>&kalaList)
{

    for (int i = 0; i < (int)kalaList.size(); i++)
    {
        for (int j = 0; j < (int)kalaList[i].comments.size(); j++)
        {
            if(!kalaList[i].comments[j]._show)
            {
                cout << kalaList[i].comments[j] <<endl;
            }
        }

    }
}

int searchProductId(int id, vector<Kala>&kalaList)
{
    for (int i = 0; i < (int)kalaList.size(); i++)
    {
        if(kalaList[i]._id==id)
            return i;
    }

    return -1;
}

void setCountBuyingOfEachProduct(vector<User>& userList , vector<Kala>&kalaList)
{
    int count=0;

    for (int i = 0; i < (int)kalaList.size(); i++)
    {
        for (int j = 0; j < (int)userList.size(); j++)
        {
            for (int k = 0; k < (int)userList[j]._factor.size(); k++)
            {
                if(userList[j]._factor[k]._kala._id == kalaList[i]._id)
                    count += userList[j]._factor[k]._count;
            }

        }


        kalaList[i].countBuy = count;
        count = 0;
    }


}


//--------------------------------------------------------------------------------------------------------------------------


void setUserAndAdmin(vector<User>& userList,vector<Admin>& adminList , vector<Person>& personList)
{
    User u;
    Admin a;

    for(int i=0 ; i<(int)personList.size() ; i++)
    {
        if(personList[i]._type == "user")
        {
            u=personList[i];
            userList.push_back(u);
        }
        else if(personList[i]._type == "admin")
        {
            a=personList[i];
            adminList.push_back(a);
        }
    }
}

Kala searchKala(vector<Kala>& KalaLis , int id)
{
    for(int i=0 ; i<(int)KalaLis.size() ; i++)
    {
        if(KalaLis[i]._id==id)
            return KalaLis[i];
    }

    Kala k;
    k._name="deleted";
    k._id = -1;
    k._price=0;
    
    return  k;
}
void convert_stFactor_to_Factor(User& user , stFactor& stFactor , vector<Kala>& KalaList)
{
    int i=0;
    Factor f;

    while (stFactor.id[i] > -1)
    {
        f._kala = searchKala(KalaList,stFactor.id[i]);
        f._count = stFactor.count[i];
        user._factor.push_back(f);
        i++;
    }

}
void setFactorForUsers(vector<User>& userList , vector<stFactor>& stFactorList , vector<Kala>& KalaList)
{
    for(int i=0 ; i<(int)userList.size() ; i++)
    {
        for(int j=0 ; j<(int)stFactorList.size() ; j++)
        {
            if(userList[i]._username == stFactorList[j].username)
            {
                convert_stFactor_to_Factor(userList[i],stFactorList[j],KalaList);
            }
        }
    }
}

bool searchUsername(string& u,vector<Person>& personList)
{
    bool f=false;
    for(int i=0 ; i<(int)personList.size() ; i++)
    {
        if(personList[i]._username == u)
            f=true;
    }
    return  f;
}
bool searchPass(string& p,vector<Person>& personList)
{
    bool f=false;
    for(int i=0 ; i<(int)personList.size() ; i++)
    {
        if(personList[i]._pass == p)
            f=true;
    }
    return  f;
}
bool searchId(int id,vector<Person>& personList)
{
    bool f=false;
    for(int i=0 ; i<(int)personList.size() ; i++)
    {
        if(personList[i]._id == id)
            f=true;
    }
    return  f;
}
bool chekPasswordCharacter(string& p)
{
    bool num=0,w=0,ch=0;
    for(int i=0 ; i<(int)p.size() ; i++)
    {
        int x;
        x=p[i];
        if((x>=97 && x<=122) || (x>=65&&x<=90))
            w=true;
        if(x>=48&&x<=57)
            num=true;
        if((x>=33&&x<=47)||(x>=58&&x<=64) || (x>=91&&x<=96) || (x>=123&&x<=126))
            ch=true;
    }

    if(num && w && ch)
        return true;
    else
        return false;
}
int productId(vector<Person>& personList)
{
    int id=4;
    while (searchId(id,personList))
    {
        id = (rand()%100)+1;
    }

    return  id;
}

int searchIdU(int id,vector<User>& userList)
{
    for(int i=0 ; i<(int)userList.size() ; i++)
    {
        if(userList[i]._id == id)
            return i;
    }
    return -1;
}
int searchIdP(int id,vector<Person>& personList)
{
    for(int i=0 ; i<(int)personList.size() ; i++)
    {
        if(personList[i]._id == id)
            return i;
    }
    return -1;
}

void updateCommentAndFactorUsername(string s1 , string s2
                                    ,vector<Comment>&comments , vector<stFactor>& factors )
{
    for(int i=0 ; i<(int)comments.size() ; i++)
    {
        if(comments[i]._username==s1)
            comments[i]._username = s2;
    }

    for(int i=0 ; i<(int)factors.size() ; i++)
    {
        if(factors[i].username==s1)
            factors[i].username = s2;
    }
}


//--------------------------------------------------------------------------------------------------------------------------


void chooseKala(string& username,vector<Kala>&kalaList , vector<Factor>& cart
                ,vector<Comment>&comments)
{
    int idKala, index;
    cout<<"\nwhat you want ?\nEnter id : ";
    cin>>idKala;
    cin.get();

    index = searchIdKala(kalaList,idKala);
    while (index==-1)
    {
        cout<<"\n       !! invalid id !!\n";
        cout<<"\nwhat you want ?\nEnter id : ";
        cin>>idKala;
        cin.get();
        index = searchIdKala(kalaList,idKala);
    }

    cout<<endl<<endl;
    kalaList[index].print();

    int choice=0;
    cout<<"\nare you want leave a comment ?\n";
    cout<<"1-yes , 2-no\nenter choice : ";
    cin>>choice;
    cin.get();

    if(choice==1)
    {
        Comment c;
        c._idKala = idKala;
        c._username = username;
        c._show=false;
        cout<<"\nwrite your comment : ";
        getline(cin,c._text,'\n');
        cout<<"\nenter star 1-5 : ";
        cin>>c._star;
        cin.get();

        kalaList[index].comments.push_back(c);
        comments.push_back(c);

        writeCommentTXT(comments);

    }


    cout<<"\n\nare you want add this ware in your cart ?\n";
    cout<<"1-yes , 2-no\nenter choice : ";
    cin>>choice;
    cin.get();

    if(choice==1)
    {
        int num;
        cout<<"\nenter number of this ware who you want : ";
        cin>>num;
        cin.get();

        while (num > kalaList[index]._amount)
        {
            cout<<"\n       !! invalid number !!\n";
            cout<<"enter number of this ware who you want : ";
            cin>>num;
            cin.get();
        }

        Factor c;
        bool flag=true;
        c._kala=kalaList[index];
        c._count = num;

        for(int i=0 ; i<(int)cart.size() ; i++)
        {
            if(c._kala._id==cart[i]._kala._id)
            {
                cart[i]._count+=num;
                flag=false;
            }
        }

        if(flag)
            cart.push_back(c);

        cout<<"\nadded successfully";
        cin.get();

    }



}

void filters(string& username,vector<Kala>&kalaList , vector<Factor>& cart
             ,vector<Comment>&comments )
{
    int choice=0;
    vector<Kala> AfterFilter;
    AfterFilter = kalaList;

    string city,category;
    int beginPrice=-1,endPrice=-1;

    while (choice!=5)
    {
        system("cls");
        cout<<"1)Limitations city\n2)Limitations price\n3)Limitations category\n4)See product\n5)Back\n\n";
        cout<<"enter choice :";
        cin>>choice;
        cin.get();

        if(choice==1)
        {
            cout<<"enter city :";
            cin>>city;
            cin.get();

            for (int i = 0; i < (int)AfterFilter.size(); i++)
            {
                if(AfterFilter[i]._city != city)
                {
                    vector<Kala>::iterator it = AfterFilter.begin() + i;
                    AfterFilter.erase(it);
                    i=-1;
                }
            }
            cout<<"\n\nFilter applied successfully";
            cin.get();
        }
        else if(choice==2)
        {
            cout<<"enter beginPrice :";
            cin>>beginPrice;
            cin.get();
            cout<<"enter endPrice :";
            cin>>endPrice;
            cin.get();

            for (int i = 0; i < (int)AfterFilter.size(); i++)
            {
                if(AfterFilter[i]._price < beginPrice || AfterFilter[i]._price > endPrice)
                {
                    vector<Kala>::iterator it = AfterFilter.begin() + i;
                    AfterFilter.erase(it);
                    i=-1;
                }
            }
            cout<<"\n\nFilter applied successfully";
            cin.get();
        }
        else if(choice==3)
        {
            cout<<"enter category :";
            cin>>category;
            cin.get();

            for (int i = 0; i < (int)AfterFilter.size(); i++)
            {
                if(AfterFilter[i]._category != category)
                {
                    vector<Kala>::iterator it = AfterFilter.begin() + i;
                    AfterFilter.erase(it);
                    i=-1;
                }
            }
            cout<<"\n\nFilter applied successfully";
            cin.get();
        }
        else if(choice==4)
        {
            if(AfterFilter.size()==0)
                cout<<"\n\n     !According to the applied filters there is no product to display!\n";
            else
            {
                seeProduct(AfterFilter);
                int c;
                cout<<"\nare you want choose ware ?\n1-yes , 2-no\nenter choice :";
                cin>>c;
                cin.get();
                if(c==1)
                    chooseKala(username,kalaList,cart,comments);
                cin.get();
            }
        }
        else if(choice==5)
        {
            choice=5;
        }
    }

}

void cartMeno(int id ,vector<User>& userList
              ,vector<Factor>& cart,vector<Kala>& kalaList,vector<stFactor>& factors)
{
    int userIndex = searchIdU(id,userList);
    /*for(int i=0 ; i<(int)userList.size() ; i++)
    {
        if(userList[i]._id==id)
            userIndex = i;
    }*/


    if(cart.size()!=0)
    {
        int choice=0;
        while (choice!=3)
        {
            system("cls");
            seeFactor(cart);
            cout<<"\n\n1)Delete a product from cart\n2)Buying\n3)Back\n\n";
            cout<<"enter choice :";
            cin>>choice;
            cin.get();

            if(choice==1)
            {
                cout<<"\n\nenter id kala for delete : ";
                int c;
                cin>>c;
                cin.get();

                for(int i=0 ; i<(int)cart.size() ; i++)
                {
                    if(c==cart[i]._kala._id)
                    {
                        vector<Factor>::iterator it = cart.begin() + i;
                        cart.erase(it);
                    }
                }

                cout<<"\n\ndeleted successfully";
                cin.get();
            }
            else if(choice==2)
            {

                userList[userIndex].addFactor(cart);

                updateStfactor(userList[userIndex]._username,factors,cart);

                for(int i=0 ; i<(int)cart.size() ; i++)
                {
                    bool f=true;
                    for(int j=0 ; j<(int)kalaList.size() && f ; j++)
                    {
                        if(cart[i]._kala._id==kalaList[j]._id)
                        {
                            kalaList[j].decreaseCount(cart[i]._count);
                            f=false;
                        }
                    }
                }

                writeKalaTXT(kalaList);
                writeFactorTXT(factors);

                system("cls");
                cout<<"this buying factor : \n\n\n";
                seeFactor(cart);
                cin.get();

                cart.clear();

                cout<<"\nbuying successfully";
                cin.get();
            }
            else if(choice==3)
            {
                choice=3;
            }
        }
    }
    else
    {
        cout<<"\n\n       !! your cart is empty !!\n\n";
        cin.get();
    }





}

void changeInformation(int Id,vector<Person>& personList,vector<User>& userList)
{
    bool f=true;

    int u = searchIdU(Id,userList);
    int p = searchIdP(Id,personList);

    int choice=0;
    enum {id=1,username,pass,name,city,address,email,back};
    while (choice!=8)
    {
        system("cls");
        cout<<"1)Change id\n2)Change username\n3)Change password\n4)Change name"
              "\n5)Change city\n6)Change address\n7)Change email\n8)Back\n\n";
        cout<<"enter choice :";
        cin>>choice;
        cin.get();

        if(choice== id)
        {
            cout<<"id :";
            int iidd=0;
            cin>>iidd;
            cin.get();

            while (f)
            {
                if(searchId(iidd,personList) || iidd>99)
                {
                    cout<<"this id is repetitive";
                    cout<<"\nid :";
                    cin>>iidd;
                    cin.get();
                }
                else
                    f=false;
            }
            personList[p]._id = iidd;

            f=true;
        }
        else if(choice== username)
        {
            string s;
            cout<<"username :";
            getline(cin,s,'\n');
            while (f)
            {
                if(searchUsername(s,personList))
                {
                    cout<<"this username is repetitive";
                    cout<<"\nusername :";
                    getline(cin,s,'\n');
                }
                else
                    f=false;
            }
            personList[p]._username = s;

            f=true;
        }
        else if(choice== pass)
        {
            string s;
            cout<<"password :";
            getline(cin,s,'\n');
            f=true;
            while (f)
            {
                f=false;
                if(!chekPasswordCharacter(s))
                {
                    cout<<"! use number and letter and character in your password !";
                    cout<<"\npassword :";
                    getline(cin,s,'\n');
                    f=true;
                }
                if(searchPass(s,personList))
                {
                    cout<<"this password is repetitive";
                    cout<<"\npassword :";
                    getline(cin,s,'\n');
                    f=true;
                }
            }
            personList[p]._pass = s;

            f=true;
        }
        else if(choice== name)
        {
            cout<<"name :";
            getline(cin,personList[p]._name,'\n');
        }
        else if(choice== city)
        {
            cout<<"city :";
            getline(cin,personList[p]._city,'\n');
        }
        else if(choice== address)
        {
            cout<<"address :";
            getline(cin,personList[p]._address,'\n');

        }
        else if(choice== email)
        {
            cout<<"email :";
            getline(cin,personList[p]._email,'\n');

        }
        else if(choice== back)
        {
            userList[u]=personList[p];
            choice=8;
        }
    }
}

void userMeno(User& user,vector<User>& userList
              ,vector<Person>& personList,vector<Kala>&kalaList
              ,vector<Comment>&comments , vector<stFactor>& factors)
{
    int choice=0;
    vector<Factor> cart;
    while (choice!=5)
    {
        system("cls");
        cout<<"1)See product\n2)Cart\n3)Change information\n4)View all purchase history\n5)Back\n\n";
        cout<<"enter choice :";
        cin>>choice;
        cin.get();

        if(choice==1)
        {
            filters(user._username,kalaList , cart,comments);
        }
        else if(choice==2)
        {
            cartMeno(user._id , userList,cart,kalaList,factors);
        }
        else if(choice==3)
        {
            int userIndexU = searchIdU(user._id,userList);

            changeInformation(user._id,personList,userList);


            updateCommentAndFactorUsername(user._username ,userList[userIndexU]._username
                                           ,comments,factors);

            user = userList[userIndexU];

            writePersonTXT(personList);
            writeFactorTXT(factors);
            writeCommentTXT(comments);
        }
        else if(choice==4)
        {
            int userIndex = searchIdU(user._id,userList);

            seeFactor(userList[userIndex]._factor);

            cin.get();
        }
        else if(choice==5)
        {
            choice=5;
        }
    }
}

void changeProductInformation(int Id,vector<Kala>&kalaList)
{
    bool f=true;

    int choice=0;
    enum {id=1,name,price,category,description,city,amount,back};
    while (choice!=8)
    {
        system("cls");
        cout<<"1)Change id\n2)Change name\n3)Change price\n4)Change category"
              "\n5)Change description\n6)Change city\n7)Change amount\n8)Back\n\n";
        cout<<"enter choice :";
        cin>>choice;
        cin.get();

        if(choice== id)
        {
            cout<<"id :";
            int iidd;
            cin>>iidd;
            cin.get();

            while (f)
            {
                if(searchProductId(iidd,kalaList)>-1)
                {
                    cout<<"this id is repetitive";
                    cout<<"\nid :";
                    cin>>iidd;
                    cin.get();
                }
                else
                    f=false;
            }
        }
        else if(choice== name)
        {
            cout<<"name :";
            getline(cin,kalaList[Id]._name,'\n');

        }
        else if(choice== price)
        {
            cout<<"price :";
            cin>>kalaList[Id]._price;
            cin.get();
        }
        else if(choice== category)
        {
            cout<<"category :";
            getline(cin,kalaList[Id]._category,'\n');
        }
        else if(choice== description)
        {
            cout<<"description :";
            getline(cin,kalaList[Id]._description,'\n');
        }
        else if(choice== city)
        {
            cout<<"city :";
            getline(cin,kalaList[Id]._city,'\n');

        }
        else if(choice== amount)
        {
            cout<<"amount :";
            cin>>kalaList[Id]._amount;
            cin.get();

        }
        else if(choice== back)
        {
            choice=8;
        }
    }
}

void takhfif(vector<User>& userList ,vector<Kala>&kalaList , int darsad)
{
    setCountBuyingOfEachProduct(userList,kalaList);

    int max=0;

    for (int i = 0; i < (int)kalaList.size(); i++)
    {
        if(kalaList[i].countBuy > max)
            max = kalaList[i].countBuy;
    }

    max *= 0.6 ;
    darsad = 100 - darsad;

    for (int i = 0; i < (int)kalaList.size(); i++)
    {
        if(kalaList[i].countBuy < max)
        {
            kalaList[i]._price = ((kalaList[i]._price*darsad)/100);
        }

    }
}

void adminMeno(vector<User>& userList ,vector<Kala>&kalaList
               ,vector<Comment>&comments )
{
    int choice=0;
    while (choice!=7)
    {
        system("cls");
        cout<<"1)Confirm comments\n2)Add product\n3)Edit product\n4)Delete product"
              "\n5)View all purchase history\n6)Discount\n7)Back\n\n";
        cout<<"enter choice :";
        cin>>choice;
        cin.get();

        if(choice==1)
        {
            system("cls");
            for (int i = 0; i < (int)comments.size(); i++)
            {
                if(!comments[i]._show)
                {
                    cout <<i<<") ";
                    comments[i].print();
                    cout <<endl;
                }
            }

            cout<<"enter comment id for confirm : ";
            int c;
            cin>>c;
            cin.get();

            if(c<(int)comments.size())
            {
                comments[c]._show = true;
                writeCommentTXT(comments);

                for (int i = 0; i < (int)kalaList.size(); i++)
                {
                    for (int j = 0; j < (int)kalaList[i].comments.size(); j++)
                    {
                        if(kalaList[i].comments[j]._username == comments[c]._username &&
                                kalaList[i].comments[j]._text == comments[c]._text)
                        {
                            kalaList[i].comments[j]._show = true;
                        }
                    }

                }
            }

            cout<<"\n\n      Done";
            cin.get();
        }
        else if(choice==2)
        {
            system("cls");
            seeProduct(kalaList);
            cout<<"\n\n";

            cout<<"are you want to add product ?";
            cout<<"\n1)yes  2)no";
            cout<<"\nenter your choice : ";
            int c;
            cin>>c;
            cin.get();

            if(c==1)
            {
                Kala k;
                bool f=true;

                cout<<"id :";
                cin>>k._id;
                cin.get();

                while (f)
                {
                    if(searchProductId(k._id,kalaList)>-1)
                    {
                        cout<<"this id is repetitive";
                        cout<<"\nid :";
                        cin>>k._id;
                        cin.get();
                    }
                    else
                        f=false;
                }

                cout<<"name :";
                getline(cin,k._name,'\n');

                cout<<"price :";
                cin>>k._price;
                cin.get();

                cout<<"category :";
                getline(cin,k._category,'\n');

                cout<<"description :";
                getline(cin,k._description,'\n');

                cout<<"city :";
                getline(cin,k._city,'\n');

                cout<<"amount :";
                cin>>k._amount;
                cin.get();

                kalaList.push_back(k);
                writeKalaTXT(kalaList);

                cout<<"\n\n        Done";
                cin.get();

            }

        }
        else if(choice==3)
        {
            system("cls");
            seeProduct(kalaList);
            cout<<"\n\n";

            cout<<"\nenter product id : ";
            int c;
            cin>>c;
            cin.get();

            int cc = searchProductId(c,kalaList);

            if(cc>-1)
            {
                changeProductInformation(cc,kalaList);

                writeKalaTXT(kalaList);

                cout<<"\n\n          Done";
                cin.get();
            }
            else
            {
                cout<<"\n\n          !! invalid id !!";
                cin.get();
            }
        }
        else if(choice==4)
        {
            system("cls");
            seeProduct(kalaList);
            cout<<"\n\n";

            cout<<"\nenter product id for delete : ";
            int c;
            cin>>c;
            cin.get();

            int cc = searchProductId(c,kalaList);

            if(cc>-1)
            {
                for(int i=0 ; i<(int)kalaList.size() ; i++)
                {
                    if(i==cc)
                    {
                        vector<Kala>::iterator it = kalaList.begin() + i;
                        kalaList.erase(it);
                    }
                }

                writeKalaTXT(kalaList);

                cout<<"\n\n          Done";
                cin.get();
            }
            else
            {
                cout<<"\n\n          !! invalid id !!";
                cin.get();
            }
        }
        else if(choice==5)
        {
            system("cls");
            cout << setiosflags(ios::left) << setw(10) << "id" << setw(15) << "Name"
                     << setw(15) << "City" << setw(30) << "Address"<< setw(30) << "Email"<< setw(15) << "Username"
                     << setw(15) << "password"<< setw(10) << "type"<< setiosflags(ios::fixed | ios::showpoint)<<endl;
            for (int i = 0; i < (int)userList.size(); i++)
            {
                userList[i].print();
            }

            cout<<"\n\n";

            cout<<"\nenter user id : ";
            int c;
            cin>>c;
            cin.get();

            int cc = searchIdU(c,userList);

            if(cc>-1)
            {
                system("cls");
                seeFactor(userList[cc]._factor);
                cin.get();
            }
            else
            {
                cout<<"\n\n          !! invalid id !!";
                cin.get();
            }
        }
        else if(choice==6)
        {
            cout<<"\n\n";
            cout<<"\nenter a number for discount : ";
            int c;
            cin>>c;
            cin.get();

            if(c>0 && c<100)
            {
                takhfif(userList,kalaList,c);
                writeKalaTXT(kalaList);

                cout<<"\n\n          The discount was successfully applied";
                cin.get();
            }
            else
            {
                cout<<"\n\n          !! invalid discount number !!";
                cin.get();
            }
        }
        else if(choice==7)
        {
            choice=7;
        }
    }
}

void login(vector<Person>& personList,vector<User>& userList
           ,vector<Kala>&kalaList
           ,vector<Comment>&comments , vector<stFactor>& factors)
{
    system("cls");
    string userName,pass;
    cout<<"enter username :";
    cin>>userName;
    cin.get();

    cout<<"enter password :";
    cin>>pass;
    cin.get();

    User u;
    //Admin a;

    bool dontFind=false;
    bool f2=true;
    for(int i=0 ; i<(int)personList.size()&&f2 ; i++)
    {
        if(personList[i]._username==userName && personList[i]._pass==pass)
        {
            dontFind=true;
            f2=false;
            if(personList[i]._type == "user")
            {
                u=personList[i];
                userMeno(u,userList,personList,kalaList,comments,factors);
            }
            else
            {
                //a = personList[i];
                adminMeno(userList,kalaList,comments);
            }
        }
    }

    if(!dontFind)
        cout<<"\n"<<"         !! invalid information !!"<<"\n"
           <<"        please try againe or regirter"<<endl;
    cin.get();

}

void registerPerson(vector<Person>& personList)
{
    system("cls");
    Person p;
    bool f=true;

    cout<<"name :";
    getline(cin,p._name,'\n');
    //cin.get();

    cout<<"city :";
    getline(cin,p._city,'\n');
    //cin>>p._city;
    //cin.get();

    cout<<"address :";
    getline(cin,p._address,'\n');
    /*cin>>p._address;
    cin.get();*/

    cout<<"email :";
    getline(cin,p._email,'\n');
    //cin>>p._email;
    //cin.get();

    cout<<"username :";
    getline(cin,p._username,'\n');
    //cin>>p._username;
    //cin.get();
    while (f)
    {
        if(searchUsername(p._username,personList))
        {
            cout<<"this username is repetitive";
            cout<<"\nusername :";
            getline(cin,p._username,'\n');
            //cin>>p._username;
            //cin.get();
        }
        else
            f=false;
    }


    cout<<"password :";
    getline(cin,p._pass,'\n');
    //cin>>p._pass;
    //cin.get();
    f=true;
    while (f)
    {
        f=false;
        if(!chekPasswordCharacter(p._pass))
        {
            cout<<"! use number and letter and character in your password !";
            cout<<"\npassword :";
            getline(cin,p._pass,'\n');
            f=true;
        }

        if(searchPass(p._pass,personList))
        {
            cout<<"this password is repetitive";
            cout<<"\npassword :";
            getline(cin,p._pass,'\n');
            f=true;
        }

    }


    cout<<"choose your type :\n1)user\n2)admin\n?";
    int ch;
    cin>>ch;
    cin.get();

    if(ch==1)
        p._type="user";
    else if(ch==2)
        p._type="admin";


    p._id = productId(personList);
    cout<<"producted id is :"<<p._id;

    personList.push_back(p);

    cout<<"\n\n           Done";
    cin.get();


}

void firstMeno( vector<Person>& personList ,  vector<User>& userList
               , vector<Admin>& adminList ,vector<Kala>&kalaList
               ,vector<Comment>&comments , vector<stFactor>& factors)
{
    int choice=0;
    while (choice!=3)
    {
        system("cls");
        cout<<"1)Login\n2)Register\n3)Exit";

        cout<<"\n\nenter your choice : ";
        cin>>choice;
        cin.get();

        if(choice==1)
        {
            login(personList,userList,kalaList,comments,factors);
        }
        else if(choice==2)
        {
            registerPerson(personList);
            userList.clear();
            adminList.clear();
            setUserAndAdmin(userList,adminList,personList);
            writePersonTXT(personList);
        }
        else if(choice==3)
        {
            choice=3;
        }
    }

}9+




























































