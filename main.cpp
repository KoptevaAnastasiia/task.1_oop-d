#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Seat {
    int seat_number;
    string status;
    string user_name;

    Seat(int number) : seat_number(number), status("available"), user_name("") {}
};

class Ticket {
private:
    string date_ticket;
    string flight_ticket;
    string price_ticket;
    vector<Seat> seats;
    int id_id;
    string user_name;

public:
    Ticket(string date, string flight, string price, const vector<int>& list_of_seats)
     : date_ticket(date), flight_ticket(flight), price_ticket(price), id_id(0), user_name("") {
        for (int seat_number : list_of_seats) {
            seats.emplace_back(seat_number);
        }
    }


    string getDate() const { return date_ticket; }
    string getFlight() const { return flight_ticket; }

 //   string getPrice() const { return price_ticket; }

    string getUserName() const { return user_name; }
    void setUserName(const string& name) { user_name = name; }

    int getId() const { return id_id; }
    void setId(int ticket_id) { id_id = ticket_id; }

    vector<Seat>& getSeats() { return seats; }
    const vector<Seat>& getSeats() const { return seats; }


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
            index++;


            while (index < line.size()) {
                price += line[index];
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


void status_ticket(const vector<Ticket>& tickets, const string& date, const string& flight) {
    for (const auto& ticket : tickets) {
        if (ticket.getDate() == date && ticket.getFlight() == flight) {

            const vector<Seat>& seats = ticket.getSeats();
             for (const Seat& seat : seats) {
                if (seat.status == "available") {
                    cout << seat.seat_number << " ";
                }

            }

        }
    }
}

void return_tickets(vector<Ticket>& tickets, int ticket_id, const string& user_name) {
    for (auto& ticket : tickets) {
        if (ticket.getId() == ticket_id) {
            vector<Seat>& seats = ticket.getSeats();
            for (auto& seat : seats) {
                if (seat.user_name == user_name && seat.status == "booked") {
                    seat.status = "available";
                    seat.user_name = "";
                    cout <<  " successfully)))\n";
                    return;
                }
            }
            cout << "No.\n";
            return;
        }
    }
    cout <<  " not found.\n";
}




void booking(vector<Ticket>& tickets, const string& date, const string& flight, int seat_number, const string& user_name, int& book_id) {
    for (auto& ticket : tickets) {
        if (ticket.getDate() == date && ticket.getFlight() == flight) {
            vector<Seat>& seats = ticket.getSeats();

            for (Seat& seat : seats) {
                if (seat.seat_number == seat_number) {
                    if (seat.status == "available") {
                        seat.status = "booked";
                        seat.user_name = user_name;
                        ticket.setId(book_id);
                        ticket.setUserName(user_name);

                        book_id++;

                        cout << "Seat " << seat.seat_number << " is booked by " << seat.user_name
                             << "; ID: " << ticket.getId() << endl;
                    } else {
                        cout << "Seat " << seat_number << " is not available.\n";
                    }
                    return;
                }
            }
            return;
        }
    }
}


void view_ticket_by_id(const vector<Ticket>& tickets, int ticket_id) {
    for (const auto& ticket : tickets) {
        if (ticket.getId() == ticket_id) {
            cout << "ID: " << ticket.getId() << endl;
        //    cout << "Price: " << ticket.getPrice() << endl;
            cout << "Booked : " << ticket.getUserName() << endl;
            return;
        }

    }
}
int main() {
    int choice;
    int book_id = 1;

    FileReader fileReader;
    vector<Ticket> tickets = fileReader.from_file("/home/anastasiia/Documents/oop_01.txt");

    while (true) {
        cout << "--- choice ---\n";
        cout << "1. check\n";
        cout << "2. book\n";

        cout << "3. view by ID\n";
        cout << "4. return\n";

        cout << "0. exit\n";
        cout << "--- Choice ---\n";
        cin >> choice;
        if (choice == 0) { break; }

        switch (choice) {
            case 1: {
                string date, flight;
                cout << "enter date\n";
                cin >> date;
                cout << "enter flight\n";
                cin >> flight;
                status_ticket(tickets, date, flight);
                break;
            }
            case 2: {
                string date, flight, user_name;
                int seat;

                cout << "enter date\n";
                cin >> date;
                cout << "enter flight\n";
                cin >> flight;
                cout << "enter seat\n";
                cin >> seat;
                cout << "enter user name\n";
                cin >> user_name;

                booking(tickets, date, flight, seat, user_name, book_id);
                break;
            }
            case 3: {
                int ticket_id;
                cout << "Enter ticket ID: ";
                cin >> ticket_id;
                view_ticket_by_id(tickets, ticket_id);
                break;
            }
            case 4: {
                int ticket_id;
                string user_name;
                cout << "Enter ticket ID: ";
                cin >> ticket_id;
                cout << "Enter your user name: ";
                cin >> user_name;

                return_tickets(tickets, ticket_id, user_name);
                break;
            }




            default:
                cout << "Invalid Choice\n";
        }
    }

    return 0;
}