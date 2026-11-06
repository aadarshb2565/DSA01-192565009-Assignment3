#include <iostream>
#include <iomanip>
using namespace std;

class Money {
    long long paise;

public:
    // Constructor
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // Overload + as a member function that returns a new Money object
    Money operator+(const Money& other) const {
        long long totalPaise = this->paise + other.paise;
        long long rupees = totalPaise / 100;
        int remainingPaise = static_cast<int>(totalPaise % 100);
        // Handle negative modulo correctly
        if (remainingPaise < 0) {
            remainingPaise += 100;
            rupees--;
        }
        return Money(rupees, remainingPaise);
    }

    // Overload == as a member function
    bool operator==(const Money& other) const {
        return this->paise == other.paise;
    }

    // Friend declaration for stream operator
    friend ostream& operator<<(ostream& os, const Money& m);
};

// Overload << as friend that prints "Rs XXX.YY"
ostream& operator<<(ostream& os, const Money& m) {
    long long rupees = m.paise / 100;
    int paise = static_cast<int>(m.paise % 100);
    // Handle negative values
    if (paise < 0) {
        paise += 100;
        rupees--;
    }
    os << "Rs " << rupees << '.';
    os << setw(2) << setfill('0') << abs(paise);  // Always show 2 digits
    return os;
}

// Main function to test the Money class
int main()
{
    cout << "=== Testing Money Class (Assignment 3, Q4) ===" << endl;
    
    cout << "\n1. Testing basic constructor and output:" << endl;
    Money m1(10, 50);    // Rs 10.50
    Money m2(5, 75);     // Rs 5.75
    cout << "m1: " << m1 << endl;
    cout << "m2: " << m2 << endl;
    
    cout << "\n2. Testing addition operator:" << endl;
    Money sum = m1 + m2;
    cout << "m1 + m2 = " << sum << endl;
    
    cout << "\n3. Testing equality operator:" << endl;
    Money m3(200, 0);    // Rs 200.00
    Money m4(199, 100);  // Also Rs 200.00 (199 + 100/100 = 200)
    cout << "m3: " << m3 << endl;
    cout << "m4: " << m4 << endl;
    cout << "m3 == m4: " << boolalpha << (m3 == m4) << noboolalpha << endl;
    
    cout << "\n4. Testing the exact assignment example:" << endl;
    Money a(120, 75), b(79, 25);  // Rs 120.75 + Rs 79.25
    Money c = a + b;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c = a + b: " << c << endl;
    cout << boolalpha << "(c == Money(200)): " << (c == Money(200)) << noboolalpha << endl;
    
    cout << "\n5. Testing paise carry into rupees:" << endl;
    Money m5(0, 75);   // Rs 0.75
    Money m6(0, 50);   // Rs 0.50
    Money m7 = m5 + m6; // Should be Rs 1.25
    cout << m5 << " + " << m6 << " = " << m7 << endl;
    
    cout << "\n6. Testing edge cases:" << endl;
    Money zero;        // Default constructor
    Money neg1(-5, 0); // Rs -5.00
    Money neg2(0, -25);// Rs -0.25
    Money sumNeg = neg1 + neg2;
    cout << "Zero: " << zero << endl;
    cout << "neg1: " << neg1 << endl;
    cout << "neg2: " << neg2 << endl;
    cout << "neg1 + neg2 = " << sumNeg << endl;
    
    cout << "\n7. Testing bill calculation scenario:" << endl;
    // Simulate a simple bill: 2 coffees + 1 sandwich
    Money coffee(1, 50);   // Rs 1.50 each
    Money sandwich(3, 25); // Rs 3.25
    Money total = (coffee + coffee) + sandwich;
    cout << "2 coffees: " << (coffee + coffee) << endl;
    cout << "1 sandwich: " << sandwich << endl;
    cout << "Total bill: " << total << endl;
    
    return 0;
}
