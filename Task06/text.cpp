#include <iostream>
#include <cstring>
using namespace std;

class Text {
private:
    char* text;      // Dynamically allocated character array
    size_t length;   // Length of the string (excluding null terminator)

public:
    // Constructor
    Text(const char* s = "") {
        length = strlen(s);
        text = new char[length + 1];  // +1 for null terminator
        strcpy(text, s);
    }

    // Copy constructor: Deep copy
    Text(const Text& other) {
        length = other.length;
        text = new char[length + 1];
        strcpy(text, other.text);
    }

    // Copy assignment: Guard against self-assignment
    Text& operator=(const Text& other) {
        if (this == &other) {
            return *this;  // Self-assignment check
        }
        
        // Release old memory
        delete[] text;
        
        // Copy data from other
        length = other.length;
        text = new char[length + 1];
        strcpy(text, other.text);
        
        return *this;
    }

    // Destructor
    ~Text() {
        delete[] text;
    }

    // Operator+: Concatenation
    Text operator+(const Text& other) const {
        size_t newLength = length + other.length;
        char* newText = new char[newLength + 1];
        
        // Copy first string
        strcpy(newText, text);
        // Append second string
        strcpy(newText + length, other.text);
        
        Text result;
        result.length = newLength;
        result.text = newText;
        return result;
    }

    // Operator==: Equality comparison
    bool operator==(const Text& other) const {
        return (length == other.length) && (strcmp(text, other.text) == 0);
    }

    // Operator!=: Inequality comparison
    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    // Operator<<: Stream output
    friend ostream& operator<<(ostream& os, const Text& t);

    // Utility: Get length
    size_t getLength() const { return length; }

    // Utility: Get C-style string
    const char* c_str() const { return text; }
};

// Operator<< implementation
ostream& operator<<(ostream& os, const Text& t) {
    os << '"' << t.text << '"';  // Output in quotes for clarity
    return os;
}

// Main function to test the Text class
int main()
{
    cout << "=== Testing Text Class (Assignment 3, Q6) ===" << endl;
    
    cout << "\n1. Testing basic construction and destruction:" << endl;
    Text t1("Hello");
    Text t2("World");
    cout << "t1: " << t1 << ", length: " << t1.getLength() << endl;
    cout << "t2: " << t2 << ", length: " << t2.getLength() << endl;
    
    cout << "\n2. Testing copy constructor:" << endl;
    Text t3 = t1;  // Copy constructor
    cout << "t3 (copy of t1): " << t3 << endl;
    
    cout << "\n3. Testing copy assignment:" << endl;
    Text t4;
    t4 = t2;  // Copy assignment
    cout << "t4 (assigned from t2): " << t4 << endl;
    
    cout << "\n4. Testing operator+ (concatenation):" << endl;
    Text t5 = t1 + t2;
    cout << "t1 + t2 = " << t5 << endl;
    
    cout << "\n5. Testing operator== and !=" << endl;
    Text t6("Hello");
    Text t7("hello");
    cout << "t1: " << t1 << endl;
    cout << "t6: " << t6 << endl;
    cout << "t7: " << t7 << endl;
    cout << "t1 == t6: " << boolalpha << (t1 == t6) << endl;  // true (case-sensitive)
    cout << "t1 == t7: " << (t1 == t7) << endl;              // false
    cout << "t1 != t7: " << boolalpha << (t1 != t7) << endl; // true
    
    cout << "\n6. Testing operator<< (stream output):" << endl;
    cout << "Three texts: " << t1 << ", " << t2 << ", " << t5 << endl;
    
    cout << "\n7. Testing empty string handling:" << endl;
    Text empty1;                    // Default constructor
    Text empty2("");               // Explicit empty string
    Text empty3 = empty1 + empty2; // Empty + Empty
    cout << "empty1: " << empty1 << ", length: " << empty1.getLength() << endl;
    cout << "empty2: " << empty2 << ", length: " << empty2.getLength() << endl;
    cout << "empty3: " << empty3 << ", length: " << empty3.getLength() << endl;
    
    cout << "\n8. Testing self-assignment:" << endl;
    Text selfTest("Self-assignment test");
    cout << "Before self-assignment: " << selfTest << endl;
    selfTest = selfTest;  // Self-assignment
    cout << "After self-assignment:  " << selfTest << endl;
    
    cout << "\n9. Testing longer strings:" << endl;
    string longStr(100, 'A');  // 100 'A' characters
    Text long1(longStr.c_str());
    Text long2("End");
    Text longResult = long1 + long2;
    cout << "long1 length: " << long1.getLength() << endl;
    cout << "long2 length: " << long2.getLength() << endl;
    cout << "longResult length: " << longResult.getLength() << endl;
    cout << "longResult ends with: \""
         << longResult.c_str()[longResult.getLength()-2] 
         << longResult.c_str()[longResult.getLength()-1] 
         << "\" (should be 'nd')" << endl;
    
    return 0;
}
