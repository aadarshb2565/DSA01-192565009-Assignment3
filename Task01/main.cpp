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
    Book() : title(""), author(""), copies(0), price(0.0) {}

    // Parameterised constructor
    Book(string t, string a, int c, double p) 
        : title(t), author(a), copies(c), price(p) {
        if (copies < 0) copies = 0;
        if (price < 0) price = 0.0;
    }

    // Overloaded constructor for donated book (title only)
    Book(string t) : title(t), author("Unknown"), copies(1), price(0.0) {}

    // Display book details
    void display() const {
        cout << "Title: '" << title << "' | ";
        cout << "Author: '" << author << "' | ";
        cout << "Copies: " << copies << " | ";
        cout << "Price: $" << price << endl;
    }
};

// Demonstration of when compiler supplies default constructor
class NoDefaultConstructor {
private:
    int value;
public:
    NoDefaultConstructor(int v) : value(v) {}  // Only parameterised constructor
    // No default constructor - compiler will not supply one
    int getValue() const { return value; }
};

int main() {
    cout << "=== Constructor Demonstration ===" << endl;
    
    // Test 1: Default constructor behavior
    cout << "\n1. Default constructor:" << endl;
    Book defaultBook;
    defaultBook.display();
    
    // Test 2: Parameterised constructor
    cout << "\n2. Parameterised constructor:" << endl;
    Book paramBook("Effective C++", "Scott Meyers", 3, 39.99);
    paramBook.display();
    
    // Test 3: Overloaded constructor (donated book)
    cout << "\n3. Overloaded constructor (donated book):" << endl;
    Book donatedBook("Clean Code: A Handbook of Agile Software Craftsmanship");
    donatedBook.display();
    
    // Test 4: Show that compiler does NOT supply default constructor when we define our own
    cout << "\n4. Compiler-provided default constructor:" << endl;
    cout << "   When we define any constructor, compiler does NOT supply a default constructor." << endl;
    cout << "   Try uncommenting the following line to see the error:" << endl;
    cout << "   // NoDefaultConstructor ndc;  // Error: no default constructor" << endl;
    
    // Test 5: Array of objects requires default constructor
    cout << "\n5. Array of Books (requires default constructor):" << endl;
    Book books[2] = {
        Book("First Book", "Author A", 1, 15.99),
        Book("Second Book", "Author B", 2, 25.99)
    };
    
    for (int i = 0; i < 2; i++) {
        cout << "   Book " << (i+1) << ": ";
        books[i].display();
    }
    
    // Test 6: Member initialization order
    cout << "\n6. Member initialization order:" << endl;
    cout << "   Members are initialized in declaration order, not initializer list order." << endl;
    cout << "   Declaration order: title, author, copies, price" << endl;
    
    // Test 7: Negative copies validation
    cout << "\n7. Testing negative copies validation:" << endl;
    Book invalidCopies("Test Book", "Test Author", -5, 10.0);
    cout << "   Book with -5 copies (should be corrected to 0):" << endl;
    invalidCopies.display();
    
    cout << "\n=== Demonstration Complete ===" << endl;
    return 0;
}
