#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node{
    int bookingID;
    string customerName;
    string vehicleType;
    string source;
    string destination;
    node *link;
};

class list{
    node *start,*temp,*curr;

public:
    list(){
        start=NULL;
    }

    void append(int id,string cname,string vtype,string src,string dest){

        if(start==NULL){
            start=new node;
            start->bookingID=id;
            start->customerName=cname;
            start->vehicleType=vtype;
            start->source=src;
            start->destination=dest;
            start->link=NULL;
        }
        else{
            curr=start;
            while(curr->link!=NULL)
                curr=curr->link;

            temp=new node;
            temp->bookingID=id;
            temp->customerName=cname;
            temp->vehicleType=vtype;
            temp->source=src;
            temp->destination=dest;
            temp->link=NULL;

            curr->link=temp;
        }
    }

    void display(){
        if(start==NULL){
            cout<<"No Confirmed Transport Bookings\n";
            return;
        }

        curr=start;
        while(curr!=NULL){
            cout<<"\nBooking ID: "<<curr->bookingID;
            cout<<"\nCustomer: "<<curr->customerName;
            cout<<"\nVehicle Type: "<<curr->vehicleType;
            cout<<"\nFrom: "<<curr->source;
            cout<<"\nTo: "<<curr->destination;
            cout<<"\n----------------------\n";
            curr=curr->link;
        }
    }
};


class queue{
    int bookingID[10];
    string customerName[10];
    string vehicleType[10];
    string source[10];
    string destination[10];
    int front,rear;

public:
    queue(){
        front=-1;
        rear=-1;
    }

    void enqueue(int id,string cname,string vtype,string src,string dest){

        if((front==0 && rear==9) || (rear+1==front)){
            cout<<"Queue is full"<<endl;
            return;
        }

        if(front==-1){
            front=rear=0;
        }
        else if(rear==9){
            rear=0;
        }
        else{
            rear++;
        }

        bookingID[rear]=id;
        customerName[rear]=cname;
        vehicleType[rear]=vtype;
        source[rear]=src;
        destination[rear]=dest;
    }

    void dequeue(int &id,string &cname,string &vtype,string &src,string &dest){

        if(front==-1){
            cout<<"Queue is empty"<<endl;
            id=-1;
            return;
        }

        id=bookingID[front];
        cname=customerName[front];
        vtype=vehicleType[front];
        src=source[front];
        dest=destination[front];

        if(front==rear){
            front=rear=-1;
        }
        else if(front==9){
            front=0;
        }
        else{
            front++;
        }
    }

    void print(){
        if(front==-1){
            cout<<"Queue is empty"<<endl;
            return;
        }

        int i=front;
        while(true){
            cout<<"Booking ID: "<<bookingID[i]<<endl;
            if(i==rear)
                break;
            i=(i+1)%10;
        }
    }
};


int vehicleID[5];
string vehicleName[5];
int vehicleCapacity[5];
int vehicleCount=0;


int main(){

    list confirmed;
    queue requests;

    int choice;

    while(true){

        cout<<"\n===== TRANSPORT BOOKING SYSTEM =====\n";
        cout<<"1. Add Vehicle\n";
        cout<<"2. View Vehicles\n";
        cout<<"3. Request Transport Booking\n";
        cout<<"4. Process Next Booking\n";
        cout<<"5. View Confirmed Bookings\n";
        cout<<"6. View Pending Requests\n";
        cout<<"7. Exit\n";
        cout<<"Enter Choice: ";
        cin>>choice;

        switch(choice){

        case 1:
            if(vehicleCount<5){
                cout<<"Enter Vehicle ID: ";
                cin>>vehicleID[vehicleCount];
                cout<<"Enter Vehicle Name: ";
                cin>>vehicleName[vehicleCount];
                cout<<"Enter Capacity: ";
                cin>>vehicleCapacity[vehicleCount];
                vehicleCount++;
                cout<<"Vehicle Added Successfully\n";
            }else{
                cout<<"Vehicle List Full\n";
            }
            break;

        case 2:
            if(vehicleCount==0){
                cout<<"No Vehicles Available\n";
            }
            for(int i=0;i<vehicleCount;i++){
                cout<<"\nID: "<<vehicleID[i];
                cout<<"\nName: "<<vehicleName[i];
                cout<<"\nCapacity: "<<vehicleCapacity[i];
                cout<<"\n-----------------\n";
            }
            break;

        case 3:{
            int id;
            string cname,vtype,src,dest;

            cout<<"Enter Booking ID: ";
            cin>>id;
            cout<<"Enter Customer Name: ";
            cin>>cname;
            cout<<"Enter Vehicle Type: ";
            cin>>vtype;
            cout<<"Enter Source: ";
            cin>>src;
            cout<<"Enter Destination: ";
            cin>>dest;

            requests.enqueue(id,cname,vtype,src,dest);
            cout<<"Transport Request Added to Queue\n";
            break;
        }

        case 4:{
            int id;
            string cname,vtype,src,dest;

            requests.dequeue(id,cname,vtype,src,dest);

            if(id!=-1){
                confirmed.append(id,cname,vtype,src,dest);
                cout<<"Transport Booking Confirmed\n";
            }
            break;
        }

        case 5:
            confirmed.display();
            break;

        case 6:
            requests.print();
            break;

        case 7:
            return 0;

        default:
            cout<<"Invalid Choice\n";
        }
    }
}
