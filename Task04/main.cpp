#include <iostream>
#include <iomanip>
using namespace std;

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        long long totalPaise = this->paise + other.paise;
        long long rupees = totalPaise / 100;
        int remainingPaise = static_cast<int>(totalPaise % 100);
        if (remainingPaise < 0) {
            remainingPaise += 100;
            rupees--;
        }
        return Money(rupees, remainingPaise);
    }

    bool operator==(const Money& other) const {
        return this->paise == other.paise;
    }

    friend ostream& operator<<(ostream& os, const Money& m);
};

ostream& operator<<(ostream& os, const Money& m) {
    long long rupees = m.paise / 100;
    int paise = static_cast<int>(m.paise % 100);
    if (paise < 0) {
        paise += 100;
        rupees--;
    }
    os << "Rs " << rupees << '.';
    os << setw(2) << setfill('0') << abs(paise);
    return os;
};

// Exact main function from the assignment
int main()
{
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\n' << boolalpha << (c == Money(200)) << '\n';
    
    return 0;
}

// Additional test: Add a test where paise carry into rupees (Rs 0.75 + Rs 0.50)
// We could add this after the main output, but let's keep it clean and just test the assignment requirement
