#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>

class Ticket {
private:
    string name_ticket;
    string price_ticket;
    string date_ticket;
    string number_ticket;
    string flight_ticket;
    vector<int> seats;

public:
    Ticket(string date, string flight, string price, const vector<int>& list_of_seats)
           : date_ticket(date), flight_ticket(flight), price_ticket(price), seats(list_of_seats) {}

    string getDate() const { return date_ticket; }
    string getFlight() const { return flight_ticket; }
    vector<int> getSeats() const { return seats; }

    bool vaild() const { return true; }
};



class FileReader {
public:
    vector<Ticket> from_file(const string& filename) {

        vector<Ticket> tickets;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "error :(" << endl;
            return tickets;
        }

        string line;
        while (getline(file, line)) {
            string date, flight, price, seats_range;

            int index = 0;


            while (index < line.size() && line[index] != ' ') {
                date += line[index];
                index++;
            }
            index++;


            while (index < line.size() && line[index] != ' ') {
                flight += line[index];
                index++;
            }
            index++;



            while (index < line.size() && line[index] != ' ') {
                seats_range += line[index];
                index++;
            }

            vector<int> seats;
            int dash = seats_range.find('-');
            if (dash != string::npos) {
                int A = stoi(seats_range.substr(0, dash));
                int B = stoi(seats_range.substr(dash + 1));




                for (int i = A; i <= B; ++i) {
                    seats.push_back(i);
                }
            }






            tickets.push_back(Ticket(date, flight, price, seats));


        }

        file.close();
        return tickets;
    }

};


class Transport {

private:
    string flight;
    string seat;
    string status_ticket;




};

void status_ticket(const vector<Ticket> &tickets, const string &date, const string &flight);
void booking(const vector<Ticket> &tickets, const string &date, const string &flight);

int main() {
    int choice;

    cout << "--- choice ---\n";
    cout << "1. check\n";
    cout << "2. book\n";
    cout << "3. return\n";
    cout << "4. view\n";

    cout << "--- Choice ---\n";
    cin >> choice;

    FileReader fileReader;
    vector<Ticket> tickets = fileReader.from_file("/home/anastasiia/Documents/oop_01.txt");

    switch (choice) {

        case 1: {
            string date;
            string flight;

            cout << "enter date\n";
            cin >> date;
            cout << "enter flight\n";
            cin >> flight;

            status_ticket(tickets, date, flight);

            break;
        }

        case 2: {
            string date;
            string flight;
            int seats;
            string user_name ;



            cout << "enter date\n";
            cin >> date;

            cout << "enter flight\n";
            cin >> flight;

            cout << "enter seats\n";
            cin >> seats;

            cout << "enter user name\n";
            cin >> user_name;

            break;
        }

        case 3:
            break;

        case 4:
            break;

        default:
            cout << "Invalid Choice\n";
    }
}


void status_ticket(const vector<Ticket>& tickets, const string& date, const string& flight) {


     for (const auto& ticket : tickets) {
        if (ticket.getDate() == date && ticket.getFlight() == flight && ticket.vaild()) {

            vector<int> Valid_s = ticket.getSeats();

            if (!Valid_s.empty()) {
                cout << "List of valid seats : ";
                for (int seat : Valid_s) {
                    cout << seat << " , ";
                }
                cout << endl;

            }
        }
    }
}




void booking(const vector<Ticket> &tickets, const string &date, const string &flight) {




}























