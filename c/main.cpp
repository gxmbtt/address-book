#include <iostream>
#include<cstring>
using namespace std;
#include<fstream>
typedef long long ll;

class phoneperson{
protected:
string name;
ll number;
public:
   phoneperson(string str,ll num);
   void setpp(string str,ll num);
   void modify();
   ll getn();
   string getname();
   friend istream&operator>>(istream & cin,phoneperson&p);
   friend ostream &operator<<(ostream&cout,phoneperson&p);

};
phoneperson::phoneperson(string str="0",ll num=0){
    number=num;
    name=str;
}
void phoneperson::setpp(string str,ll num)
{
    name=str;
    number=num;
}
void phoneperson::modify()
{
    string str;
    ll num;
    cout<<"请输入要修改联系人的名字"<<endl;
    cin>>str;
     cout<<"请输入要修改联系人的电话号码"<<endl;
     cin>>num;
    name=str;
    number=num;
}
istream&operator>>(istream&cin,phoneperson&p)
{
    cin>>p.name>>p.number;
    return cin;
}
ostream&operator<<(ostream&cout,phoneperson&p)
{
    cout<<p.name<<"  "<<p.number;
    return cout;
}
ll phoneperson::getn()
{
    return number;
}
string phoneperson::getname()
{
    return name;
}


class simperson:public phoneperson
{
    protected:
    string home;
    ll qq;
public:
    void setpp(string str,ll num,string ho,ll q);
    void modify();
    string gethome();
    ll getqq();
    friend istream&operator>>(istream&cin,simperson&s);
    friend ostream&operator<<(ostream&cout,simperson&s);

};
void simperson::setpp(string str,ll num,string ho,ll q)
{
    phoneperson::setpp(str,num);
    home=ho;
    qq=q;
}
void simperson::modify()
{
    string ho;
    ll q;
    phoneperson::modify();
    cout<<"请输入要修改的地址"<<endl;
    cin>>ho;
    cout<<"请输入要修改的qq"<<endl;
    cin>>q;
    home=ho;
    qq=q;
}
istream&operator>>(istream&cin,simperson&s)
{

    cin>>s.name>>s.number>>s.home>>s.qq;
    return cin;
}
ostream&operator<<(ostream&cout,simperson&s)
{
    cout<<s.name<<"  "<<s.number<<"  "<<s.home<<"  "<<s.qq<<endl;
}
string simperson::gethome()
{
    return home;
}
ll simperson::getqq()
{
    return qq;
}


class address_list{
public:
    virtual void add()=0;
    virtual void deleteperson()=0;
    virtual void findperson()=0;
    virtual void findchange()=0;
    virtual void display()=0;
};


class address_phone:public address_list
{
    int n;
    phoneperson p[1000];
public:
    address_phone();
    void add();
    void deleteperson();
    void findperson();
    void findchange();
    void display();
    int getnn();
    string gname(int i);
    ll gnum(int i);
    void copy01(string name,ll num);
    void clearphone();
    ~address_phone();



};
void address_phone::clearphone()
{
    n=0;

}
ll address_phone::gnum(int i)
{
    return p[i].getn();
}
string address_phone::gname(int i)
{
    return p[i].getname();
}
address_phone::address_phone()
{
    ifstream ifs("phone.txt",ios::in);
    n=0;
    if(!ifs)
    {
        cout<<"文件打开失败"<<endl;
        abort();
    }
    string name;
    ll num;
   /* ifs>>name>>num;
    p[n].setpp(name,num);

    while(!ifs.eof())
    {
        n++;
        ifs>>name>>num;
        p[n].setpp(name,num);
    }*/
    while(ifs>>name>>num)
    {
        p[n].setpp(name,num);
        n++;
    }
    ifs.close();
}
void address_phone::add()
{
    cout<<"请输入要添加联系人的名字"<<endl;
    string name;
    cin>>name;
    cout<<"请输入要添加联系人的电话号码"<<endl;
   ll num;
   cin>>num;
   bool temp=0;

   for(int i=0;i<n;i++)
   {
      if(p[i].getn()==num)
      {
          temp=1;
      }
   }

   if(temp){
        cout<<"这个电话号码已经存在"<<endl;
   }
    else
    {
        p[n].setpp(name,num);
        n++;
        cout<<"添加成功"<<endl;
    }

}
void address_phone::deleteperson()
{
    cout<<"请输入你要删除的电话号码"<<endl;
    ll num;
    cin>>num;
    int flag=-1;
    for(int i=0;i<n;i++)
    {
        if(num==p[i].getn())
        {
            flag=i;
        }
    }
    if(flag==-1)
    {
        cout<<"不好意思，手机没有这个人"<<endl;
    }
    else
    {
        for(int j=flag;j<n;j++)
        {
            p[j]=p[j+1];
        }
        n--;
        cout<<"手机删除成功"<<endl;
    }
}
void address_phone::findperson()
{
    cout<<"请输入要查找的姓名"<<endl;
    string name;
    cin>>name;
    bool flag=0;
    for(int i=0;i<n;i++)
    {
        if(name==p[i].getname())
        {
            cout<<p[i]<<endl;
            flag=1;
        }
    }
    if(flag==0)
    {
        cout<<"不好意思，手机没有这个人"<<endl;
    }

}
void address_phone::findchange()
{
    cout<<"请输入要查找的电话号码"<<endl;
    ll num;
    cin>>num;
    int flag=0;
    for(int i=0;i<n;i++)
    {
        if(num==p[i].getn())
        {
           p[i].modify();
            flag=1;

        }
    }
    if(flag==0)
    {
        cout<<"不好意思，手机没有这个人"<<endl;
    }
}
void address_phone::display()
{
    for(int i=0;i<n;i++)
    {
        cout<<p[i]<<endl;
    }
    if(n==0)
    {
        cout<<"手机中还未添加联系人"<<endl;
    }
}
address_phone::~address_phone()
{
    ofstream ofs;
    ofs.open("phone.txt",ios::out);
    if(!ofs)
    {
        cout<<"文件打开失败"<<endl;
        abort();
    }
    for(int i=0;i<n;i++)
    {
        ofs<<p[i].getname()<<" "<<p[i].getn()<<endl;
    }
    ofs.close();


}
int address_phone::getnn()
{
    return n;
}
void address_phone::copy01(string name,ll num)
{
    p[n].setpp(name,num);
    n++;
}


class address_sim:public address_list
{
    int n;
    simperson s[1000];
public:
    address_sim();
    void add();
    void deleteperson();
    void findperson();
    void findchange();
    void display();
    int getnn();
    string gname(int i);
    ll gnum(int i);
    void copy02(string name,ll num);
    void clearsim();
    ~address_sim();
};
void address_sim::clearsim()
{
    n=0;
}
string address_sim::gname(int i)
{
    return s[i].getname();
}
ll address_sim::gnum(int i)
{
    return s[i].getn();
}
address_sim::address_sim()
{
    ifstream ifs("sim.txt",ios::in);
    n=0;
    if(!ifs)
    {
        cout<<"文件打开失败"<<endl;
        abort();
    }
    string name,home;
    ll number,qq;
    ifs>>name>>number>>home>>qq;
    s[n].setpp(name,number,home,qq);
 while(!ifs.eof())
 {
     n++;
     ifs>>name>>number>>home>>qq;
     s[n].setpp(name,number,home,qq);

 }
 ifs.close();
}
void address_sim::add()
{
     cout<<"请输入要添加联系人的名字"<<endl;
    string name;
    cin>>name;
    cout<<"请输入要添加联系人的电话号码"<<endl;
   ll num;
   cin>>num;
   cout<<"请输入要添加联系人的地址"<<endl;
   string home;
   cin>>home;
   cout<<"请输入要添加联系人的qq"<<endl;
   ll qq;
   cin>>qq;
   bool flag=0;
   for(int i=0;i<n;i++)
   {
       if(num==s[i].getn())
       {
           flag=1;
       }
   }

   if(!flag){
   s[n].setpp(name,num,home,qq);

   n++;
   cout<<"添加成功"<<endl;
   }
  else{

    cout<<"该电话号码已存在"<<endl;
   }

}
void address_sim::deleteperson()
{
    cout<<"请输入你要删除的电话号码"<<endl;
    ll num;
    cin>>num;
    int flag=-1;
    for(int i=0;i<n;i++)
    {
        if(num==s[i].getn())
        {
            flag=i;
        }
    }
    if(flag==-1)
    {
        cout<<"不好意思，手机卡中没有这个人"<<endl;
    }
    else
    {
        for(int j=flag;j<n;j++)
        {
            s[j]=s[j+1];
        }
        n--;
        cout<<"手机卡删除成功"<<endl;
    }
}
void address_sim::findperson()
{
     cout<<"请输入要查找的姓名"<<endl;
    string name;
    cin>>name;
    bool flag=0;
    for(int i=0;i<n;i++)
    {
        if(name==s[i].getname())
        {
            cout<<s[i]<<endl;
            flag=1;
        }
    }
    if(flag==0)
    {
        cout<<"不好意思，手机卡中没有这个人"<<endl;
    }

}
void address_sim::findchange()
{
    cout<<"请输入要查找的电话号码"<<endl;
    ll num;
    cin>>num;
    int flag=0;
    for(int i=0;i<n;i++)
    {
        if(num==s[i].getn())
        {
           s[i].modify();
            flag=1;

        }
    }
    if(flag==0)
    {
        cout<<"不好意思，手机卡中没有这个人"<<endl;
    }
}
void address_sim::display()
{
    for(int i=0;i<n;i++)
    {
        cout<<s[i];
    }
    if(n==0)
    {
        cout<<"手机卡中还未添加联系人"<<endl;
    }
}
address_sim::~address_sim()
{
    ofstream ofs;
    ofs.open("sim.txt",ios::out);
     if(!ofs)
    {
        cout<<"文件打开失败"<<endl;
       abort();
    }
    for(int i=0;i<n;i++)
    {
        ofs<<s[i].getname()<<" "<<s[i].getn()<<" "<<s[i].gethome()<<" "<<s[i].getqq()<<endl;
    }
    ofs.close();

}
int address_sim::getnn()
{
    return n;
}
void address_sim::copy02(string name,ll num)
{
    s[n].setpp(name,num,"0",0);
    n++;
}


class user{
address_phone ap;
address_sim as;
public:
    void add();
    void deleteperson();
    void display();
    void findchange();
    void findperson();
    void copy1();
    void copy2();
    void copy3();
    void copy4();




};
void user::add()
{
    cout<<"请选择："<<endl;
    cout<<"------1、添加到手机上------"<<endl;
    cout<<"------2、添加到手机卡上------"<<endl;
    address_list*a;
    int choose;
    cin>>choose;
    switch(choose)
    {
    case 1:
        a=&ap;
        a->add();
        break;
    case 2:
        a=&as;
        a->add();
        break;
    }

}
void user::deleteperson()
{

   address_list*a;
   cout<<"在手机中删除："<<endl;
   a=&ap;
   a->deleteperson();
   cout<<"在手机卡中删除："<<endl;
   a=&as;
   a->deleteperson();
}
void user::display()
{
    cout<<"请选择："<<endl;
    cout<<"------1、打印手机通讯录------"<<endl;
    cout<<"------2、打印手机卡通讯录------"<<endl;
    int choose;
    cin>>choose;
    address_list*a;
    switch(choose)
    {
    case 1:
        a=&ap;
        a->display();
        break;
    case 2:
        a=&as;
        a->display();
        break;
    }

}
void user::findperson()
{
    address_list*a;
    cout<<"在手机中查询："<<endl;
    a=&ap;
    a->findperson();
    cout<<"在手机卡中查询"<<endl;
    a=&as;
    a->findperson();
}
void user::findchange()
{
    address_list*a;
    a=&ap;
    cout<<"在手机中修改："<<endl;
    a->findchange();
    a=&as;
    cout<<"在手机卡中修改："<<endl;
    a->findchange();

}
void user::copy1()
{
    int a[1000]={0};
    int flag=0;
    string name;
    ll num;

    if(as.getnn()==0)
    {
        flag=1;
        for(int i=0;i<ap.getnn();i++)
        {
            name=ap.gname(i);
            num=ap.gnum(i);
            as.copy02(name,num);
        }
    }
    else
    {
        for(int i=0;i<ap.getnn();i++)
        {
            for(int j=0;j<as.getnn();j++)
            {
                if(ap.gnum(i)==as.gnum(j))
                {
                    a[i]=1;
                }
            }
        }
    }
    for(int i=0;i<ap.getnn();i++)
    {
        if(a[i]==0&&flag==0)
        {
            name=ap.gname(i);
            num=ap.gnum(i);
            as.copy02(name,num);
        }
    }
    ap.clearphone();

    cout<<"移动成功"<<endl;
}
void user::copy2()
{
     int a[1000]={0};
    int flag=0;
    string name;
    ll num;

    if(ap.getnn()==0)
    {
        flag=1;
        for(int i=0;i<as.getnn();i++)
        {
            name=as.gname(i);
            num=as.gnum(i);
            ap.copy01(name,num);
        }
    }
    else
    {
        for(int i=0;i<as.getnn();i++)
        {
            for(int j=0;j<ap.getnn();j++)
            {
                if(as.gnum(i)==ap.gnum(j))
                {
                    a[i]=1;
                }
            }
        }
    }
    for(int i=0;i<as.getnn();i++)
    {
        if(a[i]==0&&flag==0)
        {
             name=as.gname(i);
            num=as.gnum(i);
            ap.copy01(name,num);
        }
    }
   as.clearsim();
   cout<<"移动成功"<<endl;
}
void user::copy3()
{
   int a[1000]={0};
    int flag=0;
    string name;
    ll num;

    if(as.getnn()==0)
    {
        flag=1;
        for(int i=0;i<ap.getnn();i++)
        {
            name=ap.gname(i);
            num=ap.gnum(i);
            as.copy02(name,num);
        }
    }
    else
    {
        for(int i=0;i<ap.getnn();i++)
        {
            for(int j=0;j<as.getnn();j++)
            {
                if(ap.gnum(i)==as.gnum(j))
                {
                    a[i]=1;
                }
            }
        }
    }
    for(int i=0;i<ap.getnn();i++)
    {
        if(a[i]==0&&flag==0)
        {

            name=ap.gname(i);
            num=ap.gnum(i);
            as.copy02(name,num);
        }
    }
    cout<<"复制成功"<<endl;
}
void user::copy4()
{
  int a[1000]={0};
    int flag=0;
    string name;
    ll num;

    if(ap.getnn()==0)
    {
        flag=1;
        for(int i=0;i<as.getnn();i++)
        {
            name=as.gname(i);
            num=as.gnum(i);
            ap.copy01(name,num);
        }
    }
    else
    {
        for(int i=0;i<as.getnn();i++)
        {
            for(int j=0;j<ap.getnn();j++)
            {
                if(as.gnum(i)==ap.gnum(j))
                {
                    a[i]=1;
                }
            }
        }
    }
    for(int i=0;i<as.getnn();i++)
    {
        if(a[i]==0&&flag==0)
        {
            name=as.gname(i);
            num=as.gnum(i);
            ap.copy01(name,num);
        }
    }
   cout<<"复制成功"<<endl;
}


class menu{

public:
    void display();


};
void menu::display()
{
    cout<<"------欢迎来到通讯录管理系统------"<<endl;
    cout<<"------0、退出系统------"<<endl;
    cout<<"------1、添加联系人------"<<endl;
    cout<<"------2、删除联系人------"<<endl;
    cout<<"------3、查询联系人------"<<endl;
    cout<<"------4、修改联系人------"<<endl;
    cout<<"------5、打印联系人------"<<endl;
    cout<<"------6、把手机联系人移动到手机卡------"<<endl;
    cout<<"------7、把手机卡联系人移动到手机------"<<endl;
    cout<<"------8、把手机联系人复制到手机卡------"<<endl;
    cout<<"------9、把手机卡联系人复制到手机------"<<endl;
}
int main() {
      int choose;
      menu m;
      user u;
      while(1)
      {
          m.display();
          cout<<"请选择："<<endl;
          cin>>choose;
          switch(choose)
          {
              case 0:return 0;

              case 1:
                u.add();
                break;
              case 2:
                u.deleteperson();
                break;
              case 3:
                u.findperson();
                break;
              case 4:
                u.findchange();
                break;
              case 5:
                u.display();
                break;
              case 6:
               u.copy1();
                break;
              case 7:
                u.copy2();
                break;
              case 8:
                u.copy3();
                break;
              case 9:
                u.copy4();
                break;
          }
           system("pause");
         system("cls");

      }




    return 0;
}
