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
    cout<<"������Ҫ�޸���ϵ�˵�����"<<endl;
    cin>>str;
     cout<<"������Ҫ�޸���ϵ�˵ĵ绰����"<<endl;
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
    cout<<"������Ҫ�޸ĵĵ�ַ"<<endl;
    cin>>ho;
    cout<<"������Ҫ�޸ĵ�qq"<<endl;
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
        cout<<"�ļ���ʧ��"<<endl;
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
    cout<<"������Ҫ�����ϵ�˵�����"<<endl;
    string name;
    cin>>name;
    cout<<"������Ҫ�����ϵ�˵ĵ绰����"<<endl;
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
        cout<<"����绰�����Ѿ�����"<<endl;
   }
    else
    {
        p[n].setpp(name,num);
        n++;
        cout<<"��ӳɹ�"<<endl;
    }

}
void address_phone::deleteperson()
{
    cout<<"��������Ҫɾ���ĵ绰����"<<endl;
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
        cout<<"������˼���ֻ�û�������"<<endl;
    }
    else
    {
        for(int j=flag;j<n;j++)
        {
            p[j]=p[j+1];
        }
        n--;
        cout<<"�ֻ�ɾ���ɹ�"<<endl;
    }
}
void address_phone::findperson()
{
    cout<<"������Ҫ���ҵ�����"<<endl;
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
        cout<<"������˼���ֻ�û�������"<<endl;
    }

}
void address_phone::findchange()
{
    cout<<"������Ҫ���ҵĵ绰����"<<endl;
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
        cout<<"������˼���ֻ�û�������"<<endl;
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
        cout<<"�ֻ��л�δ�����ϵ��"<<endl;
    }
}
address_phone::~address_phone()
{
    ofstream ofs;
    ofs.open("phone.txt",ios::out);
    if(!ofs)
    {
        cout<<"�ļ���ʧ��"<<endl;
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
        cout<<"�ļ���ʧ��"<<endl;
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
     cout<<"������Ҫ�����ϵ�˵�����"<<endl;
    string name;
    cin>>name;
    cout<<"������Ҫ�����ϵ�˵ĵ绰����"<<endl;
   ll num;
   cin>>num;
   cout<<"������Ҫ�����ϵ�˵ĵ�ַ"<<endl;
   string home;
   cin>>home;
   cout<<"������Ҫ�����ϵ�˵�qq"<<endl;
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
   cout<<"��ӳɹ�"<<endl;
   }
  else{

    cout<<"�õ绰�����Ѵ���"<<endl;
   }

}
void address_sim::deleteperson()
{
    cout<<"��������Ҫɾ���ĵ绰����"<<endl;
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
        cout<<"������˼���ֻ�����û�������"<<endl;
    }
    else
    {
        for(int j=flag;j<n;j++)
        {
            s[j]=s[j+1];
        }
        n--;
        cout<<"�ֻ���ɾ���ɹ�"<<endl;
    }
}
void address_sim::findperson()
{
     cout<<"������Ҫ���ҵ�����"<<endl;
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
        cout<<"������˼���ֻ�����û�������"<<endl;
    }

}
void address_sim::findchange()
{
    cout<<"������Ҫ���ҵĵ绰����"<<endl;
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
        cout<<"������˼���ֻ�����û�������"<<endl;
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
        cout<<"�ֻ����л�δ�����ϵ��"<<endl;
    }
}
address_sim::~address_sim()
{
    ofstream ofs;
    ofs.open("sim.txt",ios::out);
     if(!ofs)
    {
        cout<<"�ļ���ʧ��"<<endl;
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
    cout<<"��ѡ��"<<endl;
    cout<<"------1����ӵ��ֻ���------"<<endl;
    cout<<"------2����ӵ��ֻ�����------"<<endl;
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
   cout<<"���ֻ���ɾ����"<<endl;
   a=&ap;
   a->deleteperson();
   cout<<"���ֻ�����ɾ����"<<endl;
   a=&as;
   a->deleteperson();
}
void user::display()
{
    cout<<"��ѡ��"<<endl;
    cout<<"------1����ӡ�ֻ�ͨѶ¼------"<<endl;
    cout<<"------2����ӡ�ֻ���ͨѶ¼------"<<endl;
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
    cout<<"���ֻ��в�ѯ��"<<endl;
    a=&ap;
    a->findperson();
    cout<<"���ֻ����в�ѯ"<<endl;
    a=&as;
    a->findperson();
}
void user::findchange()
{
    address_list*a;
    a=&ap;
    cout<<"���ֻ����޸ģ�"<<endl;
    a->findchange();
    a=&as;
    cout<<"���ֻ������޸ģ�"<<endl;
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

    cout<<"�ƶ��ɹ�"<<endl;
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
   cout<<"�ƶ��ɹ�"<<endl;
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
    cout<<"���Ƴɹ�"<<endl;
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
   cout<<"���Ƴɹ�"<<endl;
}


class menu{

public:
    void display();


};
void menu::display()
{
    cout<<"------��ӭ����ͨѶ¼����ϵͳ------"<<endl;
    cout<<"------0���˳�ϵͳ------"<<endl;
    cout<<"------1�������ϵ��------"<<endl;
    cout<<"------2��ɾ����ϵ��------"<<endl;
    cout<<"------3����ѯ��ϵ��------"<<endl;
    cout<<"------4���޸���ϵ��------"<<endl;
    cout<<"------5����ӡ��ϵ��------"<<endl;
    cout<<"------6�����ֻ���ϵ���ƶ����ֻ���------"<<endl;
    cout<<"------7�����ֻ�����ϵ���ƶ����ֻ�------"<<endl;
    cout<<"------8�����ֻ���ϵ�˸��Ƶ��ֻ���------"<<endl;
    cout<<"------9�����ֻ�����ϵ�˸��Ƶ��ֻ�------"<<endl;
}
int main() {
      int choose;
      menu m;
      user u;
      while(1)
      {
          m.display();
          cout<<"��ѡ��"<<endl;
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
