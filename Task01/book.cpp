#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int copies;
    double price;

public:
    // Default constructor
    Book() : Book("", "", 0, 0.0) {
        cout << "Default constructor called" << endl;
    }

    // Parameterised constructor
    Book(string t, string a, int c, double p) 
        : title(t), author(a), copies(c), price(p) {
        cout << "Parameterised constructor called" << endl;
        validateCopies();
        validatePrice();
    }

    // Overloaded constructor for donated book (title only)
    Book(string t) : Book(t, "Unknown", 1, 0.0) {
        cout << "Overloaded constructor (donated book) called" << endl;
    }

    // Copy constructor (demonstrates Rule of Three preparation)
    Book(const Book& other) 
        : title(other.title), author(other.author), 
          copies(other.copies), price(other.price) {
        cout << "Copy constructor called" << endl;
    }

    // Destructor
    ~Book() {
        cout << "Destructor called for: " << title << endl;
    }

    // Validate that copies is not negative
    void validateCopies() {
        if (copies < 0) {
            cout << "ERROR: Number of copies cannot be negative!" << endl;
            cout << "Setting copies to 0." << endl;
            copies = 0;
        }
    }

    // Validate that price is not negative
    void validatePrice() {
        if (price < 0) {
            cout << "ERROR: Price cannot be negative!" << endl;
            cout << "Setting price to 0.0." << endl;
            price = 0.0;
        }
    }

    // Display book details
    void display() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Copies: " << copies << endl;
        cout << "Price: $" << price << endl;
        cout << "--------------------------" << endl;
    }
};

// Main function to test all constructors
int main() {
    cout << "=== Testing Book Constructors ===" << endl;
    
    cout << "\n1. Testing default constructor:" << endl;
    Book book1;
    book1.display();
    
    cout << "\n2. Testing parameterised constructor:" << endl;
    Book book2("The C++ Programming Language", "Bjarne Stroustrup", 5, 49.99);
    book2.display();
    
    cout << "\n3. Testing overloaded constructor (donated book):" << endl;
    Book book3("Donated Book: Effective Modern C++");
    book3.display();
    
    cout << "\n4. Testing validation - negative copies:" << endl;
    Book book4("Invalid Copies Book", "Some Author", -3, 15.99);
    book4.display();
    
    cout << "\n5. Testing validation - negative price:" << endl;
    Book book5("Invalid Price Book", "Another Author", 2, -5.50);
    book5.display();
    
    cout << "\n6. Testing copy constructor:" << endl;
    Book book6 = book2;  // Copy constructor invocation
    book6.display();
    
    cout << "\n7. Testing explicit constructor requirement:" << endl;
    // This would fail if constructor was explicit:
    // Book book7 = "Just a Title";  // Requires explicit conversion
    
    Book book8(string("Explicit Title"));  // This works
    book8.display();
    
    cout << "\n8. Testing array of Books (requires default constructor):" << endl;
    Book library[3] = {
        Book("Book 1", "Author 1", 1, 10.0),
        Book("Book 2", "Author 2", 2, 20.0),
        Book("Book 3", "Author 3", 3, 30.0)
    };
    
    for (int i = 0; i < 3; i++) {
        cout << "Book " << i+1 << ":" << endl;
        library[i].display();
    }
    
    return 0;
}
