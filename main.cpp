#include <iostream>
#include <iostream>
using namespace std;

#include <string>

class Ticket {
private:
    string name_ticket;
    int price_ticket;
    string date_ticket;
    int number_ticket;
    int flight_ticket;
    int seat_number_ticket;
    string status_ticket;

};

class FileReader {



};


class Transport {



};


int main() {
    int choice;

    cout << "--- choice ---\n";
    cout << "1. check\n";
    cout << "2. book\n";
    cout << "3. return\n";
    cout << "4. view\n";

    cout << "--- Choice ---\n";
    cin >> choice;




    switch (choice) {

        case 1: {

            string date; int flight;
            cout << "enter date\n";
            cin >> date;
            cout << "enter flight\n";
            cin >> flight;



            break;


        }



        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        default:
            cout << "Invalid Choice\n";

    }


}
