#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
using namespace std;
class user									
{                                             
    char name[20],phoneno[15],email[30];
    int userid;
    public:
        void getuserdetails()      //get user details
        {
        	cout<<"Enter the details of the card holder\n";
		    cout<<"Enter id: ";
		    cin>>userid;
		    cout<<"Enter name: ";
		    cin>>name;
		    cout<<"Enter phone number: ";
		    cin>>phoneno;
		    cout<<"Enter email: ";
		    cin>>email;
		}
        void display()				//display user details
        {
        	cout<<"\nUser Details:\n";
        	cout<<"\nUser Id: "<<userid<<"\nName: "<<name<<"\nPhone No: "<<phoneno<<"\nEmail: "<<email<<"\n";
		}
		int getuserid()				//get user id
		{
			return userid;
		}
		
		void deluser()				//delete user details
		{
			user u[3];
			int ui=0,uid;
			char found='f',confirm='n';
			cout<<"Enter user id of user to be deleted: ";
			cin>>uid;
			ifstream fin("user_details.txt",  ios::in | ios::binary | ios::app); 
			ofstream fout("temp.txt", ios::out | ios::binary | ios::app); 
			while(!fin.eof())
			{
				fin.read((char*)&u[ui], sizeof(u[ui]));
				if(u[ui].getuserid()==uid)
				{
					u[ui].display();
					found='t';
					cout<<"Are you sure to delete the user?(y/n) ";
					cin>>confirm;
					if(confirm=='n')
						fout.write((char*)&u[ui],sizeof(u[ui]));
					else
						break;
				}
				else
					fout.write((char*)&u[ui],sizeof(u[ui]));
				ui++;
			}
			if(found=='f')
				cout<<"\nUser not found!\n";
			else
				cout<<"\nUser Deleted!\n";
			fin.close();
			fout.close();
			remove("user_details.txt");
			rename("temp.txt","user_details.txt");
		}
};			//end of class user
void upduser()             //update user details
		{
			user u[3];
			char found;
			fstream f;	
    		f.open("user_details.txt", ios::out | ios::in); 
			long pos;
			int ui=0;
			int uid;
			cout<<"Enter user id: ";
			cin>>uid;
			while(f.read((char*)&u[ui],sizeof(u[ui])))
			{
				pos=f.tellg();
				if(u[ui].getuserid()==uid)
				{
					u[ui].getuserdetails();
					pos = pos - sizeof(u[ui]);
					f.seekg(pos);
					f.write((char*)&u[ui],sizeof(u[ui]));
					u[ui].display();
					found = 'f';
					cout<<"\nUser Details Modified!\n";
					break;
				}
				++ui;
			}
			f.close();
		}
//linked list for route----------- STRUCTURE
struct route			
{				                          
	char busstand[20];                   
	float dist;
    struct route *next;
}*start=NULL;                   //initializing to null
//QUEUE functions for BUS capacity/entering-----------
int first=-1;
int last=-1;
int buscap[40];
void enqueue(int a[],int *first, int *last, int val,int capacity)
{
    if((*first)==-1 && (*last)==-1)
    {
        (*first)=(*first)+1;
        (*last)=(*last)+1;
        a[(*first)]=val;
        cout<<endl;
        cout<<val<<" Added to bus queue";
    }
    else if((*last)==capacity)
        cout<<"\nQueue full";
    else
    {
        (*last)=(*last)+1;
        a[(*last)]=val;
        cout<<endl;
        cout<<val<<" Added to bus queue";
    }   
}
void dequeue(int a[],int *first, int *last)
{
    if((*first)==-1 || (*last)==-1)
        cout<<"\nQueue empty";
    else if((*first)==(*last))
    {
      cout<<"\nDeleted from queue of bus (reset queue): "<<a[(*first)];
      (*first)=(*last)=-1; 
    }
    else
    {
	    cout<<"\nDeleted from queue of bus: "<<a[(*first)];
	    (*first)=(*first)+1;
    }
}
void dispqueue(int a[], int first, int last)
{
   if(first==-1 || last==-1)
        cout<<"\nQueue empty";
    else
    { 
        cout<<"\n\nDisplaying Queue of Bus: \n";
        while(first<=last)
        {
            cout<<a[first]<<endl;
            first++;
        }   
    }   
}
class bus									//class with bus details and routes
{
	protected:
	    char busid[8]; 
	    int capacity;
	    float bp;               //base price of bus
    public:
	    bus()					//constructor for Bus class to initialize
	    {                           
		    capacity=0;
		    bp=0;
	    }
        void addbus()               //get bus details
        {
        	cout<<"Enter the details of the bus\n";
		    cout<<"Enter bus id: ";
		    cin>>busid;
		    cout<<"Enter capacity of the bus: ";
		    cin>>capacity;
		    cout<<"Enter base price of bus: ";
		    cin>>bp;
		    int no;
		    cout<<"Enter no. of bus stops: ";
		    cin>>no;
		    for(int i=0;i<no;i++)
		    {
		        char busstop[20];
		        float distance;
		        cout<<"Enter bus stop and distance: ";
		        cin>>busstop>>distance;
		        insert(&start,busstop,distance);
		    }
		    display(&start);
		    cout<<"\nBus and route added!\n";
		}
		void insert(struct route **start, char newstop[], float distance)		 //insert function for route 
		{                                                                                
			struct route* new_node=(struct route*)malloc(sizeof(struct route));
			strcpy(new_node->busstand,newstop);
			new_node->dist=distance;
			new_node->next=NULL;
			if((*start)==NULL)                      
			{
				(*start)=new_node;
			}
			else
			{
				struct route* temp=(struct route*)malloc(sizeof(struct route));
				temp=(*start);
				while(temp->next!=NULL)
				{
					temp=temp->next;
				}
				temp->next=new_node;
			}  
		}
		void display(struct route **head)		//testing linked list of route
		{
		    if((*head)==NULL)
		    	printf("\nRoute is empty\n");
		    else                             	//displaying all elements in sll
		    {
		        struct route* temp=(struct route*)malloc(sizeof(struct route));
		        temp=(*head);                           
		        while(temp!=NULL)
		        {
		            printf("\n%s\n%0.2f\n",temp->busstand,temp->dist);
		            temp=temp->next;
		        }
		    }
		}    
		void userenterbus()
        {
            int uid;
            cout<<"\nEnter UID of user entering Bus: ";
            cin>>uid;
            enqueue(buscap,&first,&last,uid,capacity);
            dispqueue(buscap, first,last);
        }
		void userleavebus()
        {
            dequeue(buscap,&first,&last);
            dispqueue(buscap, first,last);
        } 
};          //end of class bus
class ticket : private user, public bus		//class to get ticket details
{
	char tid[20];
	char start_loc[20];
	char end_loc[20];
	public:
		void start_location()
		{
		    cout<<endl;
			cout<<"Enter the starting location of the customer: ";
			cin>>start_loc;
		}
		void end_location()
		{
			cout<<"\nEnter the end destination of the customer: ";
			cin>>end_loc;
			cout<<"\n\n";
			totalfare(&start);
		}
		void totalfare(struct route **start)		//finaldest of the user who's on the bus
		{
			float totalprice=0,i=0;
		    if((*start)==NULL)
		    	printf("\nRoute is empty\n");
		    else                             	
		    {
		        struct route* temp=(struct route*)malloc(sizeof(struct route));
		        temp=(*start);                           
		        while(strcmp(temp->busstand,start_loc)!=0 && temp!=NULL)
		        {
		            temp=temp->next;
		        }
			    cout<<"This is starting busstand: "<<temp->busstand<<endl;
			    totalprice+=bp;
			    while(strcmp(temp->busstand,end_loc)!=0 && temp!=NULL)  
			    {
			        i++;                                             
			        totalprice+=(temp->dist)*10;
			        temp=temp->next;    
			    }
			    cout<<"Total no. of stops: "<<i<<endl;
			    cout<<"End stop: "<<end_loc<<endl;
			    cout<<"Price: "<<totalprice<<endl;
			}
		}
};			//end of class ticket
class bank
{
    char name[20];
    int acno;
    char actype[4];
    float balance;
    public:
    void init()
    {
		cout<<"New Account\n";
		cout<<"Enter the Name of the depositor: ";
		cin>>name;
		cout<<"Enter the Account Number: ";
		cin>>acno;
		cout<<"Enter the Account Type:(CURR/SAVG/FD/RD/DMAT) ";
		cin>>actype;
		cout<<"Enter the Amount to Deposit: ";
		cin>>balance;
	}
    void deposit()
    {
		float more;
		cout <<"Depositing\n";
		cout<<"Enter the amount to deposit: ";
		cin>>more;
		balance+=more;
	}
    void withdraw()
    {
		float amt;
		cout<<"Withdrwal\n";
		cout<<"Enter the amount to withdraw: ";
		cin>>amt;
		balance-=amt;
	}
    void disp_det()
    {
    	cout<<"Account Details\n";
		cout<<"Name of the depositor: "<<name<<endl;
		cout<<"Account Number       : "<<acno<<endl;
		cout<<"Account Type         : "<<actype<<endl;
		cout<<"Balance              : Rs."<<balance<<endl;
	}
};
class payment : private user, public bus		//class to get payment details
{
	char cno[16],cname[20],cvv[5],expiry[8];
	float price;
	public:
        void getpaydetails()               //get payment details for each user  
        {
        	cout<<"Enter the payment details\n";
		    cout<<"Enter card no: ";
		    cin>>cno;
		    cout<<"Enter name in card: ";
		    cin>>cname;
		    cout<<"Enter date of expiry: ";
		    cin>>expiry;
		    cout<<"Enter CVV: ";
		    cin>>cvv;
		    cout<<"\n\nPayment Details added!\n";
		}
};			//end of class payment
int main()
{
    user u[3];                      //class objects
    bus b[3];
    ticket t[3];
    payment p[3];
    bank a[3];
    fstream userdet;			//for storing user details into a file
    fstream busdet;				//for storing bus details into a file
    userdet.open("user_details.txt", ios::out | ios::in | ios::binary | ios::app); 
    busdet.open("bus_details.txt", ios::out | ios::in | ios::binary | ios::app);
    int ui=0,bi=0,ti=0,pi=0,ch,ai=0;
    char j;
    do
	{
        cout<<"1. Add user details\n";
        cout<<"2. Add bus and route details\n";
        cout<<"3. Add ticket details of user\n";   
        cout<<"4. Add payment details of user\n";
        cout<<"5. Modify user details\n";
        cout<<"6. Delete user details\n";
        cout<<"7. Get bank details\n";
        cout<<"Choose an option: ";
        cin>>ch;
        switch(ch)
		{
            case 1: u[ui].getuserdetails();          //to get user details
            		cout<<"\nUser added!\n";
                    userdet.write((char*)&u[ui], sizeof(u[ui]));	//writing user details into file
                    userdet.read((char*)&u[ui], sizeof(u[ui]));		//reading from file
                    u[ui].display();
            		ui++;
                    break;
            case 2: b[bi].addbus();                 //to get bus details
                    busdet.write((char*)&b[bi], sizeof(b[bi]));		//writing bus details into file 
                    bi++;
                    break;
            case 3: t[ti].start_location();			//to get ticket details - start location
					t[ti].end_location();
					b[bi--].userenterbus();
					ti++;
					break;
            case 4: p[pi].getpaydetails();          //to get payment details
            		pi++;
                    break;
            case 5: ui=0;							//to modify user details
					upduser();
					ui++;
					break;	
			case 6: ui=0;							//to delete user details
					u[ui].deluser();
					ui++;
					break;
			case 7: ai=0;
					a[ai].init();
					//a[ai].deposit();
					a[ai].withdraw();
					a[ai].disp_det();
					ai++;
					break;
            default: cout<<"Wrong option\n";     
			break;  
        }
        cout<<"\n\nDo you want to continue?(y/n) ";
        cin>>j;
        cout<<"\n\n";
    } while(j=='y');			//infinite loop until stopped
    userdet.close();		//close file for user details
    busdet.close();			//close file for bus details
    return 0;
}
