#include <iostream>
#include <cstring>
using namespace std;

// Simple Text class for testing memory management
class Text {
private:
    char* text;
    size_t length;

public:
    Text(const char* s = "") {
        length = strlen(s);
        text = new char[length + 1];
        strcpy(text, s);
    }

    Text(const Text& other) {
        length = other.length;
        text = new char[length + 1];
        strcpy(text, other.text);
    }

    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        delete[] text;
        length = other.length;
        text = new char[length + 1];
        strcpy(text, other.text);
        return *this;
    }

    ~Text() {
        delete[] text;
    }

    Text operator+(const Text& other) const {
        size_t newLength = length + other.length;
        char* newText = new char[newLength + 1];
        strcpy(newText, text);
        strcpy(newText + length, other.text);
        Text result;
        result.length = newLength;
        result.text = newText;
        return result;
    }

    bool operator==(const Text& other) const {
        return (length == other.length) && (strcmp(text, other.text) == 0);
    }

    friend ostream& operator<<(ostream& os, const Text& t);
};

// Forward declarations for test functions
Text createText(const char* s);
void useText(Text t);

ostream& operator<<(ostream& os, const Text& t) {
    os << '"' << t.text << '"';
    return os;
}

// Test function that returns Text by value (tests copy constructor)
Text createText(const char* s) {
    return Text(s);  // Return by value invokes copy constructor
}

// Test function that takes Text by value (tests copy constructor for parameter)
void useText(Text t) {
    cout << "Received: " << t << endl;
}  // Parameter destroyed here (tests destructor)

int main()
{
    cout << "=== Testing Text Class Memory Management ===" << endl;
    
    cout << "\n1. Testing construction and destruction:" << endl;
    Text t1("Hello, World!");
    cout << "Created: " << t1 << endl;
    // t1 will be destroyed at end of scope
    
    cout << "\n2. Testing copy constructor (return by value):" << endl;
    Text t2 = createText("Return by value test");
    cout << "Received: " << t2 << endl;
    
    cout << "\n3. Testing copy constructor (pass by value):" << endl;
    useText(t2);  // t2 copied for parameter
    
    cout << "\n4. Testing copy assignment:" << endl;
    Text t3;
    t3 = t2;  // Assignment
    cout << "Assigned: " << t3 << endl;
    
    cout << "\n5. Testing concatenation:" << endl;
    Text part1("Hello, ");
    Text part2("beautiful ");
    Text part3("world!");
    Text greeting = part1 + part2 + part3;
    cout << "Greeting: " << greeting << endl;
    
    cout << "\n6. Testing comparison operators:" << endl;
    Text a("apple");
    Text b("banana");
    Text c("apple");
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
    cout << "a == b: " << boolalpha << (a == b) << endl;
    cout << "a == c: " << (a == c) << endl;
    
    cout << "\n7. Testing empty strings:" << endl;
    Text empty;
    Text empty2("");
    Text combined = empty + empty2;
    cout << "empty: '" << empty << "'" << endl;
    cout << "empty2: '" << empty2 << "'" << endl;
    cout << "combined: '" << combined << "'" << endl;
    
    cout << "\n8. Testing self-assignment:" << endl;
    Text self("self-assignment test");
    cout << "Before: " << self << endl;
    self = self;
    cout << "After:  " << self << endl;
    
    cout << "\n9. Testing chained operations:" << endl;
    Text x("A"), y("B"), z("C"), w("D");
    Text result = x + y + z + w;
    cout << "x + y + z + w = " << result << endl;
    
    cout << "\n=== All memory management tests completed ===" << endl;
    return 0;
}
