#include <iostream>
#include <string>
using namespace std;

const int total_seats = 100;
int seats[total_seats] = {0};  // 0 = available, -1 = booked
int reservation_counter = 1000;
int cancelled_tickets = 0;

class Flight {
public:
    Flight() : start(nullptr) {}

    void book_ticket();
    void cancel_ticket();
    void change_reservation();
    void passenger_details();
    void get_booking_details();
    void get_seat_map();

private:
    struct Passenger {
        string fname;
        string lname;
        string ID;
        string phone_number;
        string food_menu;
        int seat_number;
        int reservation_number;
        Passenger* next;
    };

    Passenger* start;

    Passenger* find_by_reservation(int res_num);
    void show_available_seats();
};

Flight flight;

void Flight::show_available_seats() {
    cout << "\nAvailable seats:\n";
    for (int i = 0; i < total_seats; ++i) {
        if (seats[i] == 0)
            cout << "| " << i + 1 << " ";
        else
            cout << "| XX ";
        if ((i + 1) % 10 == 0)
            cout << "|\n";
    }
}

void Flight::book_ticket() {
    Passenger* p = new Passenger;

    cout << "\nEnter First Name: ";
    cin >> p->fname;
    cout << "Enter Last Name: ";
    cin >> p->lname;
    cout << "Enter ID: ";
    cin >> p->ID;
    cout << "Enter Phone Number: ";
    cin >> p->phone_number;

    int sn;
    while (true) {
        show_available_seats();
        cout << "\nEnter desired seat number (1 to " << total_seats << "): ";
        cin >> sn;
        if (sn < 1 || sn > total_seats || seats[sn - 1] == -1) {
            cout << "Invalid or already taken. Try again.\n";
        } else {
            seats[sn - 1] = -1;
            p->seat_number = sn;
            break;
        }
    }

    int choice;
    cout << "\nFood Preference:\n1. Veg\n2. Non-Veg\n3. No Food\nYour choice: ";
    cin >> choice;
    if (choice == 1) p->food_menu = "Veg";
    else if (choice == 2) p->food_menu = "Non-Veg";
    else p->food_menu = "No Food";

    p->reservation_number = ++reservation_counter;
    p->next = nullptr;

    cout << "\nBooking Successful! Your Reservation Number: " << p->reservation_number << "\n";

    if (!start)
        start = p;
    else {
        Passenger* temp = start;
        while (temp->next) temp = temp->next;
        temp->next = p;
    }
}

Flight::Passenger* Flight::find_by_reservation(int res_num) {
    Passenger* temp = start;
    while (temp) {
        if (temp->reservation_number == res_num) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void Flight::cancel_ticket() {
    int res;
    cout << "Enter Reservation Number to Cancel: ";
    cin >> res;

    Passenger* curr = start;
    Passenger* prev = nullptr;

    while (curr) {
        if (curr->reservation_number == res) {
            if (prev)
                prev->next = curr->next;
            else
                start = curr->next;

            seats[curr->seat_number - 1] = 0;
            delete curr;
            ++cancelled_tickets;
            cout << "Ticket Cancelled. Refund initiated.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Reservation not found.\n";
}

void Flight::change_reservation() {
    int res;
    cout << "Enter your Reservation Number: ";
    cin >> res;

    Passenger* p = find_by_reservation(res);
    if (!p) {
        cout << "No reservation found.\n";
        return;
    }

    show_available_seats();
    int new_seat;
    cout << "\nChoose new seat number: ";
    cin >> new_seat;

    if (new_seat < 1 || new_seat > total_seats || seats[new_seat - 1] == -1) {
        cout << "Invalid or already taken seat.\n";
        return;
    }

    seats[p->seat_number - 1] = 0; // Free old seat
    seats[new_seat - 1] = -1;
    p->seat_number = new_seat;

    cout << "Seat changed successfully.\n";
}

void Flight::passenger_details() {
    int res;
    cout << "Enter Reservation Number: ";
    cin >> res;

    Passenger* p = find_by_reservation(res);
    if (p) {
        cout << "\nPassenger Details:\n";
        cout << "Reservation #: " << p->reservation_number
             << "\nName: " << p->fname << " " << p->lname
             << "\nID: " << p->ID
             << "\nPhone: " << p->phone_number
             << "\nSeat #: " << p->seat_number
             << "\nFood: " << p->food_menu << "\n";
    } else {
        cout << "No reservation found.\n";
    }
}

void Flight::get_booking_details() {
    Passenger* temp = start;
    cout << "\nAll Bookings:\n";
    cout << "Res#\tName\t\tSeat\tFood\n";
    while (temp) {
        cout << temp->reservation_number << "\t"
             << temp->fname << " " << temp->lname << "\t"
             << temp->seat_number << "\t"
             << temp->food_menu << "\n";
        temp = temp->next;
    }
}

void Flight::get_seat_map() {
    show_available_seats();
}

void welcome() {
    int choice;
    do {
        cout << "\n================= Airline Reservation System =================\n";
        cout << "1. Book Ticket\n2. Cancel Ticket\n3. Change Reservation\n";
        cout << "4. View Passenger Details\n5. Show All Bookings\n6. View Seat Map\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: flight.book_ticket(); break;
            case 2: flight.cancel_ticket(); break;
            case 3: flight.change_reservation(); break;
            case 4: flight.passenger_details(); break;
            case 5: flight.get_booking_details(); break;
            case 6: flight.get_seat_map(); break;
            case 7: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);
}

int main() {
    welcome();
    return 0;
}
