#include <iostream>
#include <string>
using namespace std;

// This is the exact struct and function from the assignment's "Predict the Output" section
struct Logger {
    string n;
    Logger(const string& s) : n(s) { cout << '+' << n << ' '; }
    Logger(const Logger& o) : n(o.n + "c") { cout << "copy" << n << ' '; }
    ~Logger() { cout << '-' << n << ' '; }
};

void use(Logger l) { cout << "use "; }

// Main function from the assignment
int main()
{
    Logger a("A");
    {
        Logger b("B");
    }
    use(a);
    Logger* p = new Logger("P");
    delete p;
    cout << "end ";
    
    return 0;
}
