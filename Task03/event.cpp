#include <iostream>
#include <iomanip>
using namespace std;

class Event {
private:
    char** seats;      // 2D seat map: array of pointers to rows
    int rows;
    int cols;
    int bookedCount;

public:
    // Dynamic constructor
    Event(int r, int c) : rows(r), cols(c), bookedCount(0) {
        cout << "Dynamic constructor: Creating " << rows << "x" << cols << " seat map" << endl;
        
        if (rows <= 0 || cols <= 0) {
            seats = nullptr;
            cout << "Warning: Zero or negative dimensions. No seat map created." << endl;
            return;
        }
        
        // Allocate array of row pointers
        seats = new char*[rows];
        
        // Allocate each row and initialize to 'A' (Available)
        for (int i = 0; i < rows; i++) {
            seats[i] = new char[cols];
            for (int j = 0; j < cols; j++) {
                seats[i][j] = 'A';  // 'A' = Available
            }
        }
        
        cout << "Seat map initialized. All seats available." << endl;
    }

    // Copy constructor (prevent shallow copy issues)
    Event(const Event& other) 
        : rows(other.rows), cols(other.cols), bookedCount(other.bookedCount) {
        cout << "Copy constructor called" << endl;
        if (other.seats == nullptr) {
            seats = nullptr;
            return;
        }
        
        // Deep copy of seat map
        seats = new char*[rows];
        for (int i = 0; i < rows; i++) {
            seats[i] = new char[cols];
            for (int j = 0; j < cols; j++) {
                seats[i][j] = other.seats[i][j];
            }
        }
        bookedCount = other.bookedCount;
    }

    // Copy assignment operator
    Event& operator=(const Event& other) {
        cout << "Copy assignment operator called" << endl;
        if (this == &other) {
            return *this;
        }
        
        // Clean up existing resources
        if (seats != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] seats[i];
            }
            delete[] seats;
        }
        
        // Copy data from other
        rows = other.rows;
        cols = other.cols;
        bookedCount = other.bookedCount;
        
        if (other.seats == nullptr) {
            seats = nullptr;
            return *this;
        }
        
        // Deep copy
        seats = new char*[rows];
        for (int i = 0; i < rows; i++) {
            seats[i] = new char[cols];
            for (int j = 0; j < cols; j++) {
                seats[i][j] = other.seats[i][j];
            }
        }
        
        return *this;
    }

    // Destructor
    ~Event() {
        cout << "Destructor: Releasing seat map memory" << endl;
        if (seats != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] seats[i];
            }
            delete[] seats;
            seats = nullptr;
        }
        cout << "Event destroyed. Final stats: " << bookedCount << " seats booked out of " 
             << (rows * cols) << " total seats." << endl;
    }

    // Book a seat (returns success)
    bool bookSeat(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "Error: Invalid seat coordinates (" << row << "," << col << ")" << endl;
            return false;
        }
        
        if (seats[row][col] == 'B') {
            cout << "Error: Seat (" << row << "," << col << ") already booked." << endl;
            return false;
        }
        
        seats[row][col] = 'B';  // 'B' = Booked
        bookedCount++;
        cout << "Seat (" << row << "," << col << ") booked successfully." << endl;
        return true;
    }

    // Cancel a seat booking (returns success)
    bool cancelSeat(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            cout << "Error: Invalid seat coordinates (" << row << "," << col << ")" << endl;
            return false;
        }
        
        if (seats[row][col] == 'A') {
            cout << "Error: Seat (" << row << "," << col << ") is not booked." << endl;
            return false;
        }
        
        seats[row][col] = 'A';  // 'A' = Available
        bookedCount--;
        cout << "Seat (" << row << "," << col << ") booking cancelled." << endl;
        return true;
    }

    // Display seat map (for debugging)
    void displaySeatMap() const {
        if (seats == nullptr || rows == 0 || cols == 0) {
            cout << "No seat map to display." << endl;
            return;
        }
        
        cout << "Current seat map (" << rows << "x" << cols << "):" << endl;
        cout << "  Legend: A = Available, B = Booked" << endl;
        for (int i = 0; i < rows; i++) {
            cout << "Row " << setw(2) << i << ": ";
            for (int j = 0; j < cols; j++) {
                cout << seats[i][j] << ' ';
            }
            cout << endl;
        }
    }

    // Getters
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getBookedCount() const { return bookedCount; }
    int getTotalSeats() const { return rows * cols; }
};

// Main function to test all required scenarios
int main() {
    cout << "=== Testing Event Class (Assignment 3, Q3) ===" << endl;
    
    cout << "\n1. Testing event on stack:" << endl;
    {
        Event conference(3, 4);  // 3 rows, 4 columns
        conference.bookSeat(0, 1);
        conference.bookSeat(2, 3);
        conference.displaySeatMap();
    }  // conference destroyed here
    
    cout << "\n2. Testing event on heap (new/delete):" << endl;
    Event* concert = new Event(2, 3);
    concert->bookSeat(0, 0);
    concert->bookSeat(1, 2);
    concert->displaySeatMap();
    delete concert;  // Important: must call delete to avoid leak
    
    cout << "\n3. Testing event inside a block:" << endl;
    {
        Event workshop(2, 2);
        workshop.bookSeat(0, 0);
        workshop.displaySeatMap();
    }  // workshop destroyed when leaving block
    
    cout << "\n4. Testing zero-sized event:" << endl;
    Event emptyEvent(0, 5);  // Zero rows
    Event emptyEvent2(3, 0); // Zero columns
    // These should handle gracefully
    
    cout << "\n5. Testing seat booking/cancelling boundaries:" << endl;
    Event testEvent(2, 2);
    testEvent.bookSeat(0, 0);      // Valid
    testEvent.bookSeat(0, 1);      // Valid
    testEvent.bookSeat(1, 0);      // Valid
    testEvent.bookSeat(1, 1);      // Valid - all seats booked
    testEvent.bookSeat(0, 0);      // Should fail - already booked
    testEvent.cancelSeat(0, 0);    // Valid - cancel booking
    testEvent.cancelSeat(0, 0);    // Should fail - not booked
    testEvent.bookSeat(0, 5);      // Should fail - invalid column
    testEvent.bookSeat(5, 0);      // Should fail - invalid row
    
    cout << "\n6. Testing copy operations:" << endl;
    Event original(2, 3);
    original.bookSeat(0, 1);
    original.bookSeat(1, 2);
    
    Event copy1 = original;        // Copy constructor
    Event copy2(1, 1);             // Constructor
    copy2 = original;              // Copy assignment
    
    cout << "Original booked: " << original.getBookedCount() << endl;
    cout << "Copy1 booked:  " << copy1.getBookedCount() << endl;
    cout << "Copy2 booked:  " << copy2.getBookedCount() << endl;
    
    // Modify original to verify independence
    original.bookSeat(0, 0);
    cout << "After modifying original:" << endl;
    cout << "Original booked: " << original.getBookedCount() << endl;
    cout << "Copy1 booked:  " << copy1.getBookedCount() << endl;
    cout << "Copy2 booked:  " << copy2.getBookedCount() << endl;
    
    return 0;
}
