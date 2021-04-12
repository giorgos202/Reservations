#include <iostream>
#include <string>
#include <list>
using namespace std;
class Booking {
	friend class Room;
	friend class RoomB;
	friend class RoomC;
	public:
		Booking(string name,int arr, int st, int peo){		//dimiourgos klassis
			setName(name);
			setBookingCode();
			if (arr>0 && arr<31 && arr+st<32 ){		//elegxos parametrwn
				setArrival(arr);
				setStay(st);
				setPeople(peo);
				codecounter++;
				cout<<"H kratisi "<<code<<" egine apo ton pelati '"<<name<<"' kai afora "<<people<<" atoma pou ftanoun stis "<<arrival;
				cout<<" tou mina kai tha parameinoun gia "<<stay<<" meres diladi apo tis "<<arrival<<" mexri kai tis ";
				cout<<arrival+stay-1<<" tou mina"<<endl;
			}
			else {
				cout<<"I afiksi kai i diamoni prepei na einai metaksu tis 1is kai tis 30is tou minos"<<endl;
				arrival=0;
				stay=0;
				people=0;
			}
		}									
		void setName(string x){								//sunartiseis set kai get gia kathe metavliti tis klassis
			name=x;											//gia eukoloteri xrisi kai parousiasi tous
		}
		string const getName(){
			return name;
		}
		void setBookingCode(){
			code=codecounter;
		}
		int const getBookingCode(){
			return code;
		}
		void setArrival(int x){
			arrival=x;
		}
		int const getArrival(){
			return arrival;
		}
		void setStay(int x){
			stay=x;
		}
		int const getStay(){
			return stay;
		}
		void setPeople(int x){
			people=x;
		}
		int const getPeople(){
			return people;
		}
	private:
		int stay;									//metavlites tis klassis
		int arrival;
		static int codecounter;
		string name;
		int code;
		int people;
};
class Room{
	public:
		Room(int maxpeople,  double value){		//dimiourgos tis klassis
			setRoomCode();
			setMaxPeople(maxpeople);
			setValue(value);
			roomcodecounter ++;
		}															//sunartiseis set kai get gia kathe metavliti tis klassis
		void setRoomCode(){											//gia eukoloteri xrisi kai parousiasi tous
			roomcode=roomcodecounter;
		}
		int const getRoomCode(){
			return roomcode;
		}
		void setMaxPeople(int x){
			maxpeople=x;
		}
		int const getMaxPeople(){
			return maxpeople;
		}
		void setValue(double x){
			value=x;
		}
		double const getValue(){
			return value;
		}
		bool InsertBooking(Booking x){
			if (x.Booking::arrival && x.Booking::stay && x.Booking::people){				//elegxos parametrwn
				if (x.Booking::people<= maxpeople){ 																			//elegxos atomwn
					for (int i=x.Booking::arrival-1; i<=x.Booking::arrival+x.Booking::stay-2; i++){
						if (array[i]){
							cout<<"Den einai dunati i kratisi "<<x.Booking::code<< " , logw elleipsis diathesimotitas tou dwmatiou "<<roomcode<<endl; //elegxos diathesimotitas dwmatiou
							return false;																					  
							break;
						}
						else continue;
					}
					cout<<"To dwmatio "<<roomcode<<" einai diathesimo gia tin kratisi me arithmo "<<x.Booking::code<<endl;
					for (int i=x.Booking::arrival-1; i<=x.Booking::arrival+x.Booking::stay-2; i++){								//allagi twn timwn tou pinaka diathesimotitas
					array[i]=&x;																							//stin periptwsi pou to dwmatio einai diathesimo
					}
					return true;
				}
				else {
					cout<<"To dwmatio "<<roomcode<<" mporei na eksipuretisei mexri "<<maxpeople<<" atoma"<<endl;		//elegxos atomwn
					return false;
				}
			}
			else cout<<"I kratisi den uparxei"<<endl;
		}
		double Pricing(){
			double sum=0;
			for(int i=0; i<30; i++){
				if (array[i]){				//euresi atomwn ana mera* timi tou dwmatiou ana atomo ana mera
					sum+=(*array[i]).people*value ;
				}
				else continue;
				}
				return sum;
		}
		bool Canceling(int x){
			for(int i=0; i<30; i++){
				if(array[i]){
					if(array[i]->code==x){
					array[i]=NULL;
					}
				}
				else continue;
			}
			cout<<"I akurwsi tis kratisis "<<x<<" pragmatopoiithike"<<endl;
			return true;
		}
		float Completeness(){
			float counter=0;
			for (int i=0; i<30; i++){
				if(array[i])counter++;
				else continue;
			}
			cout<<"To pososto plirotitas tou dwmatiou "<<roomcode<<" einai "<<(counter*10)/3<<"% auton to mina"<<endl;
			return (counter*10)/3;
		}
	private:				//metavlites tis klassis
		static int roomcodecounter;
		double value;
	protected:
		Booking *array[30]={};
		int roomcode;
		int maxpeople;	
};
class RoomA : public Room{
	public:
		RoomA(int maxpeople,  double value, double valueperday) : Room(maxpeople,value){
			setValueperday(valueperday);
		}
		void setValueperday(double x){
			valueperday=x;
		}
		double Pricing(){
			double sum=0;
			for(int i=0; i<30; i++){
				if (array[i]){
					sum+=valueperday;
				}
			}
			return sum;
		}
	protected:
		double valueperday;
};
class RoomB : public RoomA{
	public:
		RoomB(int maxpeople, double value, double valueperday, double discountperday) : RoomA(maxpeople,value,valueperday){
			setDiscountperday(discountperday);
		}
		void setDiscountperday(double x){
			discountperday=x;
		}
		double Pricing(){
			int sum=0;
			for(int i=0; i<30; i++){
				if(array[i] && array[i]!=array[i+1]){		//euresi twn diaforetikwn kratisewn
					for(int z=0; z<(*array[i]).stay;z++){	//upologismos twn imerwn ekptwsis xrisimopoiontas tin metavliti stay
						if(z*discountperday<=valueperday/2)	sum+= valueperday - (z*discountperday);
						else sum+=valueperday/2;
					}
				}
				else continue;
			}
			return sum;
		}
		bool Canceling(int x){
			return false;
		}
	private:
		double discountperday;
};
class RoomC : public Room{
	public:
		RoomC(int maxpeople, double value, int minpeople, int mindays) : Room(maxpeople,value){
			setMinpeople(minpeople);
			setMindays(mindays);
	}
		void setMinpeople(int x){
			minpeople=x;
	}
		void setMindays(int x){
			mindays=x;
	}
	bool InsertBooking(Booking x){
			if (x.Booking::arrival && x.Booking::stay && x.Booking::people){				//elegxos parametrwn
				if (x.Booking::people<= maxpeople && x.Booking::people>= minpeople && x.Booking::stay>= mindays){ 																			//elegxos atomwn
					for (int i=x.Booking::arrival-1; i<=x.Booking::arrival+x.Booking::stay-2; i++){
						if (array[i]){
							cout<<"Den einai dunati i kratisi "<<x.Booking::code<< " sto dwmatio "<<roomcode<<endl; //elegxos diathesimotitas dwmatiou
							return false;																					  
							break;
						}
						else continue;
					}
					cout<<"To dwmatio "<<roomcode<<" einai diathesimo gia tin kratisi me arithmo "<<x.Booking::code<<endl;
					for (int i=x.Booking::arrival-1; i<=x.Booking::arrival+x.Booking::stay-2; i++){								//allagi twn timwn tou pinaka diathesimotitas
					array[i]=&x;																							//stin periptwsi pou to dwmatio einai diathesimo
					}
					return true;
				}
				else {
					cout<<"To dwmatio "<<roomcode<<" mporei na eksipuretisei apo "<<minpeople<<" ews "<<maxpeople<<" atoma"<<" gia to ligotero "<<mindays<<" meres.";		//elegxos atomwn kai diamonis
					return false;
				}
			}
			else cout<<"I kratisi den uparxei"<<endl;
		}
	private:
		int minpeople;
		int mindays;
};
class Hotel{
	public:
		Hotel(string name){
			setHotelname(name);
		}
		void setHotelname(string x){
			hotelname=x;
		}
		string getHotelname(){
			return hotelname;
		}
		void InsertRoom(Room x){
			rooms.insert(rooms.end(),x);
			cout<<"prostethike ena dwmatio\n";														
		}
		Room RecoverRoom(int x){
			list<Room>::iterator p=rooms.begin();
			while(p!=rooms.end()){
				if(p->Room::getRoomCode()==x) {
					cout<<"to dwmatio me kwdiko dwmatiou "<<p->Room::getRoomCode()<<" vrethike\n";
					return *p;
				}
				p++;
			}
		}
				
		void RoomsPresentation(){
			list<Room>::iterator p = rooms.begin();
  			while(p != rooms.end()) {
    			cout << p->Room::getRoomCode() << " ";
    			p++;
  			}
		}
	private:
		string hotelname;
		list<Room> rooms;
		*n =NULL;
	
};
int Room::roomcodecounter=1;		//arxikopoisi static metavlitwn kai twn 2 klassewn
int Booking::codecounter=1;
int main(){
	Booking b1("kwstas", 16, 10, 3);
	Booking b2("kwsta", 1, 15, 4);
	cout<<b1.getName()<<b1.getBookingCode()<<" "<<b1.getArrival()<<" "<<b1.getStay()<<"	"<<b1.getPeople()<<endl;
	RoomC r1(4,10,3,10);
	Room r2(6,10);
	Room r3(5,11);
	Room r4(5,14);
	r1.InsertBooking(b1);
	r1.InsertBooking(b2);
	//r1.Canceling(1);
	r1.InsertBooking(b1);
	//cout<<r1.RoomB::Pricing()<<endl;
	r1.Completeness();
	Hotel h1("Pantheon");
	h1.InsertRoom(r2);
	h1.InsertRoom(r3);
	h1.InsertRoom(r4);
	cout<<r4.getRoomCode();
	h1.RoomsPresentation();
	h1.RecoverRoom(4);
	cout<<r4.getRoomCode();
	}

