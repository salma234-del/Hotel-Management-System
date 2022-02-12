#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
using namespace std;
class Customer{
private:
    int id , numOfDays;
    char typeOfRoom;
    char name[15];
public:
void readCustomer(){
	ifstream file;
	file.open("customer.txt");
	ifstream ifs("customer.txt", ios::ate); 
    Customer c;
    if(file.is_open() && ifs.tellg() != 0){
    	cout << "Show All Hotel Booking: ";
    	cout << "\n______________________\n\n";
    	cout << "Name\tId\tType Of Room\tNumber Of Dayes Booked\n";
    	file.read((char*) &c , sizeof(c));
        while(!file.eof()){
            cout << c.name << "\t" << c.id << "\t";
			if(c.typeOfRoom == 's' || c.typeOfRoom == 'S') cout << "Single\t\t";
			else if(c.typeOfRoom == 'd' || c.typeOfRoom == 'D') cout << "Double\t\t";
			cout << c.numOfDays << "\n";
            file.read((char*) &c, sizeof(c));
		}
        file.close();
    }else cout << "File Not Found\n";
    cout << "\n\nPress any key to continue....!! ";
	getch();
}

void writeCustomer(){
	ofstream file;
	file.open("customer.txt" , ios::out | ios::app);
    char ch ;
    do{
    	Customer c;
        cout << "Add a New Booking: ";
		cout << "\n_________________\n\n";
        cout << "Enter Your Name: "; cin >> c.name;
        bool valid = true;
        for(int i = 0; i < strlen(c.name); i++){
        	if(isspace(c.name[i]) || !isalpha(c.name[i])){
        		valid = false;
        		break;
			}	 
		}
		if(strlen(c.name) < 3) valid = false;
		while(!valid){
			valid = true;
        	cout << "Enter a valid name: "; cin >> c.name;
			for(int i = 0; i < strlen(c.name); i++){
        	if(isspace(c.name[i]) || !isalpha(c.name[i])){
        		valid = false;
        		break;
			}	 
	     } 	
	     if(strlen(c.name) < 3) valid = false;
		}
        cout << "Enter your Id: "; cin >> c.id;
        cout << "Do you want single room or double ? (S/D): "; cin >> c.typeOfRoom;
		while(c.typeOfRoom != 'S' && c.typeOfRoom != 's' && c.typeOfRoom != 'D' && c.typeOfRoom != 'd'){
			cout << "Enter a valid character: ";
			cin >> c.typeOfRoom;
		} 
        cout << "Enter the number of days you will book: "; cin >> c.numOfDays;
        file.write((char*) &c, sizeof(c));
        cout << "**************************************************\nAdd Another Booking ? (y/press any character such (n)): "; cin >> ch;
		system("cls");
    }while(ch == 'y' || ch == 'Y');
    file.close();
}

void searchCustomer(){
    Customer c;
    fstream file("customer.txt");
    ifstream ifs("customer.txt", ios::ate); 
    cout << "Search about Booking by Id: ";
	cout << "\n__________________________\n\n";
    bool found = false;
    int x;
    cout << "Enter Id: ";
    cin >> x;
    if(file.is_open() && ifs.tellg() != 0){
        file.read((char*) &c, sizeof(c));
        while(!file.eof()){
        	if(x == c.id){
        	found = true;
        	cout << "Name\tId\tType Of Room\tNumber Of Dayes Booked\n";
            cout << c.name << "\t" << c.id << "\t";
			if(c.typeOfRoom == 's' || c.typeOfRoom == 'S') cout << "Single\t\t";
			else if(c.typeOfRoom == 'd' || c.typeOfRoom == 'D') cout << "Double\t\t";
			cout << c.numOfDays << "\n";
            break;
        }
        file.read((char*) &c, sizeof(c));
        }if(!found){
           cout << "Not found\n";
        }file.close();
    }else cout << "File Not Found\n";
    cout << "\n\nPress any key to continue....!! ";
	getch();
}
    
void updateCustomer(){
    Customer c;
    fstream file("customer.txt" , ios::in | ios::out);
    ifstream ifs("customer.txt", ios::ate); 
    cout << "Update Booking: ";
	cout << "\n______________\n\n";
    bool found = false;
    int x;
    cout << "Enter Id Of Customer to update number of days booked: "; cin >> x;
    if(file.is_open() && ifs.tellg() != 0){
        file.read((char*)&c,sizeof(c));
        while(!file.eof()){
        	if(x == c.id){
        	    cout << "Enter your new number of days: ";
            	cin >> c.numOfDays;
            	int n = file.tellg();
            	int m = sizeof(c);
            	file.seekp(n - m , ios::beg);
            	file.write((char*)&c, sizeof(c));
            	found = true;
        		cout << "\n\nName\tId\tType Of Room\tNumber Of Days Booked\n";
            	file.seekg(n - m , ios::beg);
				file.read((char*)&c , sizeof(c));
				cout << c.name << "\t" << c.id << "\t";
				if(c.typeOfRoom == 's' || c.typeOfRoom == 'S') cout << "Single\t\t";
				else if(c.typeOfRoom == 'd' || c.typeOfRoom == 'D') cout << "Double\t\t";
				cout << c.numOfDays << "\n";
            	break;
        	}
			file.read((char*)&c,sizeof(c));
       }file.close();
       if(!found) cout << "\nId Not Found\n";
    }else cout << "File Not Found\n";
    cout << "\n\nPress any key to continue....!! ";
	getch();
}
    
void deleteRecordCustomer(){
    Customer c;
    ifstream file("customer.txt");
    ofstream temp ("temp.txt");
    cout << "Delete Booking:- ";
	cout << "\n______________\n\n";
    int x;
    cout << "Enter Id Of Customer To Delete: ";   cin >> x;
    bool found = false;
    if(file.is_open()){
    	file.read((char*) &c, sizeof(c));
        while(!file.eof()){
            if(x != c.id){
                temp.write((char*)&c,sizeof(c));
            }else found = true;
        	file.read((char*) &c, sizeof(c));
       }
    file.close();
    temp.close();
    remove("customer.txt");
    rename("temp.txt", "customer.txt");
    }else cout << "No records are matched!\n";
    if(found) cout << "\nThe customer record was deleted successfully";
    else cout << "\n\nCustomer record not found\n";
   	cout << "\n\nPress any key to continue....!! ";
	getch();
}
};

class room{
private:
	int room_no , room_price;
	char room_type;
	char room_view;
public:
void writeRoom(){
	ofstream out;
	out.open("rooms.txt" , ios::out | ios::app);
	char ch;
	do{
		room r;
		cout << "Add a New Room: ";
		cout << "\n______________\n";
		cout << "\nRoom Number: "; cin >> r.room_no;
		cout << "Room Type 'S' for Single 'D' for Double (S/D): ";  cin >> r.room_type;
		while(r.room_type != 'S' && r.room_type != 's' && r.room_type != 'D' && r.room_type != 'd'){
			cout << "Enter a valid character: ";
			cin >> r.room_type;
		} 
		cout << "Room View 'S' for Sea and 'P' for Pool and 'G' Garden: "; cin >> r.room_view;
			while(r.room_view != 'S' && r.room_view != 's' && r.room_view != 'P' && r.room_view != 'p' && r.room_view != 'G' && r.room_view != 'g'){
			cout << "Enter a valid character: ";
			cin >> r.room_view;
		} 	
		cout << "Room Price in one day: "; cin >> r.room_price;
		out.write((char*) &r, sizeof(r));
		cout << "**********************************************\nDo you want add more rooms (y/press any character such (n))? ";
		cin >> ch;
		system("cls");
	}while(ch == 'y' || ch == 'Y'); 
	out.close();
}

void readRoom(){	
	ifstream in;
	in.open("rooms.txt");
	ifstream ifs("rooms.txt", ios::ate); 
	room r;
	cout << "Show all Rooms: ";
	cout << "\n______________\n\n";
	if(in.is_open() && ifs.tellg() != 0){
		cout << "NUMBER\tTYPE\tVIEW\tPRICE\n";
		in.read((char*) &r, sizeof(r));
		while(!in.eof()){	
		cout << r.room_no << "\t";
		if(r.room_type == 's' || r.room_type == 'S') cout << "Single\t";
		else if(r.room_type == 'd' || r.room_type == 'D') cout << "Double\t";
		if(r.room_view == 'S' || r.room_view == 's') cout << "Sea\t";
		else if(r.room_view == 'P' || r.room_view == 'p') cout << "Pool\t";
		else if(r.room_view == 'G' || r.room_view == 'g') cout << "Garden\t";
		cout << r.room_price << "\n";
		in.read((char*) &r, sizeof(r));
	}
	in.close();
    }else cout << "FILE NOT FOUND\n\n";
	cout << "\n\nPress any key to continue....!! ";
	getch();
}

void searchRoom(){
	room r;
	fstream in("rooms.txt");
	ifstream ifs("rooms.txt", ios::ate); 
	cout << "Search Room: ";
	cout << "\n___________\n\n";
	int n;
	bool found = false;
	cout << "Enter Room Number You Search For: ";
	cin >> n;
	if(in.is_open() && ifs.tellg() != 0){
		in.read((char*) &r, sizeof(r));
		while(!in.eof()){		
			if(n == r.room_no){
			found = true;
			cout << "NUMBER\tTYPE\tVIEW\tPRICE\n";
			cout << r.room_no << "\t";
			if(r.room_type == 's' || r.room_type == 'S') cout << "Single\t";
			else if(r.room_type == 'd' || r.room_type == 'D') cout << "Double\t";
			if(r.room_view == 'S' || r.room_view == 's') cout << "Sea\t";
			else if(r.room_view == 'P' || r.room_view == 'p') cout << "Pool\t";
			else if(r.room_view == 'G' || r.room_view == 'g') cout << "Garden\t";
			cout << r.room_price << "\n";
		    break;
	}
		in.read((char*) &r, sizeof(r));	
	}if(!found){
		cout << "NOT FOUND!\n\n";
	}in.close();
    }else cout << "FILE NOT FOUND\n\n";
  		cout << "\n\nPress any key to continue....!! ";
		getch();
}

void updateRoom(){
	room r;
	fstream in("rooms.txt");
	ifstream ifs("rooms.txt", ios::ate); 
	cout << "Update Room: ";
	cout << "\n___________\n\n";
	int n;
	bool found = false;
	cout << "Enter room number to update its price: ";
	cin >> n;
	if(in.is_open() && ifs.tellg() != 0){
		in.read((char*) &r, sizeof(r));
		while(!in.eof()){
			if(n == r.room_no){
				cout << "Enter the New Price For Room Number " << r.room_no << ": ";
				cin >> r.room_price;
				int curpos = in.tellg();
				int roomSize = sizeof(r);
				in.seekp(curpos - roomSize , ios::beg);
				in.write((char*) &r, sizeof(r));
				found = true;
				cout << "NUMBER\tTYPE\tVIEW\tPRICE\n";
				in.seekg(curpos - roomSize , ios::beg);
				in.read((char*) &r, sizeof(r));
	            cout << r.room_no << "\t";
				if(r.room_type == 's' || r.room_type == 'S') cout << "Single\t";
				else if(r.room_type == 'd' || r.room_type == 'D') cout << "Double\t";
				if(r.room_view == 'S' || r.room_view == 's') cout << "Sea\t";
				else if(r.room_view == 'P' || r.room_view == 'p') cout << "Pool\t";
				else if(r.room_view == 'G' || r.room_view == 'g') cout << "Garden\t";
				cout << r.room_price << "\n";
		        break;
	}in.read((char*) &r, sizeof(r));	
	}if(!found){
		cout << "\n\nNOT FOUND!\n\n";
	}in.close();
    }else cout << "FILE NOT FOUND\n\n";
	cout << "\n\nPress any key to continue....!! ";
	getch();
}

void deleteRoom(){
	ifstream input("rooms.txt");
	ofstream output("temp.txt");
	cout << "Delete Room:- ";
	cout << "\n___________\n\n";
	room r;
	int n;
	cout << "\nEnter Room Number you want to delete: "; cin >> n;
	bool found = false;
	if(input.is_open()){
		input.read((char*) &r, sizeof(r));
		while(!input.eof()){
			if(n != r.room_no){
				output.write((char*) &r, sizeof(r));
			}else found = true;
			input.read((char*) &r, sizeof(r));
		}
		input.close();
		output.close();
		remove("rooms.txt");
		rename("temp.txt" , "rooms.txt");	
	}else{
		cout << "No records are matched!\n\n";
	}
	if(found) cout << "\nThe room was deleted successfully\n";
	else cout << "\n\nRoom Not Found\n";
   	cout << "\n\nPress any key to continue....!! ";
	getch();
}
};

void manageHotel(){
	room r;
	Customer c;
	cout << "\n\t\t\t\t\tHotel Management System\n";
	cout << "\t\t\t\t\t_______________________\n\n";
	cout << "************\nManage Hotel\n************\n";
	cout << "1. Customer Class\n2. Room Class\n3. Exit\n";
	char ch;
	cout << "*****************\nYour Choice: ";
	cin >> ch;
	if(ch == '1'){
		while(true){
			int x;
			system("cls");
    		cout << "**************\nManage Booking\n**************";
			cout << "\n1. Add a New Booking \n2. Search about Booking by Id \n3. Update Booking \n4. Delete Booking \n5. Show all Hotel Booking \n6. Back to Main Menu\n";
    		cout << "*****************************";
    		cout << "\nYour choise: "; cin >> x;
    		system("cls");
   			if(x == 1) c.writeCustomer();
    		else if(x == 2) c.searchCustomer();
    		else if(x == 3) c.updateCustomer();
    		else if(x == 4) c.deleteRecordCustomer();
    		else if(x == 5) c.readCustomer();
    		else if(x == 6) manageHotel();
			else{
				cout << "Please, Enter a Correct Number.";
				cout << "\n\nPress any key to continue....!! ";
				getch();
			}
    	}
	}else if(ch == '2'){
		while(true){
			system("cls");
			cout << "***********\nManage Rooms\n***********\n1. Write Room\n2. Search Room\n3. Update Room\n4. Delete Room\n5. Show all Rooms\n6. Back to Main Menu\n********************\n";
			char x;
			cout << "Your Choice: "; cin >> x;
			cout << "*************\n";
			system("cls");
			if(x == '1') r.writeRoom();
			else if(x == '2') r.searchRoom();
			else if(x == '3') r.updateRoom();
			else if(x == '4') r.deleteRoom();
			else if(x == '5') r.readRoom();
			else if(x == '6') manageHotel();
			else{
				cout << "Please, Enter a Correct Number.";
				cout << "\n\nPress any key to continue....!! ";
				getch();
			}
		}			
	}else if(ch == '3'){
		system("cls");
		cout << "\n\n\t\t\t***************Thank you for visiting our hotel***************\n\n";
		exit(0);
	}else{
		system("cls");
		cout << "Please, Enter a Correct Number.";
		cout << "\n\nPress any key to continue....!! ";
		getch();
		system("cls");
		manageHotel();
	}
}
int main(){
	manageHotel();
	
	return 0;
}

