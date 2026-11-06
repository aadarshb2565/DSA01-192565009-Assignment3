#include <iostream>
#include <string>
using namespace std;

class Prescription {
    int n;
    string* medicines;            // dynamically allocated array

public:
    explicit Prescription(int count) : n(count), medicines(new string[count]) {
        // Initialize all strings to empty
        for (int i = 0; i < count; i++) {
            medicines[i] = "";
        }
    }

    // TODO 1: Copy constructor: allocate a NEW array of the same size and copy every
    //   medicine (deep copy)
    Prescription(const Prescription& other) 
        : n(other.n), medicines(new string[other.n]) {
        cout << "Copy constructor called" << endl;
        // Deep copy: allocate new array and copy each element
        for (int i = 0; i < other.n; i++) {
            medicines[i] = other.medicines[i];
        }
    }

    // TODO 2: Copy assignment: guard against self-assignment, build a new array, copy,
    //   release the old array and return *this
    Prescription& operator=(const Prescription& other) {
        cout << "Copy assignment operator called" << endl;
        // Guard against self-assignment
        if (this == &other) {
            return *this;
        }
        
        // Release old array
        delete[] medicines;
        
        // Build new array
        n = other.n;
        medicines = new string[n];
        
        // Copy elements
        for (int i = 0; i < n; i++) {
            medicines[i] = other.medicines[i];
        }
        
        return *this;
    }

    ~Prescription()
    {
        // TODO 3: Release the dynamically allocated array
        cout << "Destructor called" << endl;
        delete[] medicines;
    }

    void set(int i, const string& m) { 
        if (i >= 0 && i < n) {
            medicines[i] = m; 
        }
    }
    
    string get(int i) const { 
        if (i >= 0 && i < n) {
            return medicines[i]; 
        }
        return "";  // Return empty string for invalid index
    }
};

// Main function from the assignment
int main()
{
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");
    Prescription q = p;                // copy constructor
    q.set(1, "Cetirizine");
    Prescription r(1);
    r = p;                             // copy assignment
    p.set(0, "Ibuprofen");
    cout << p.get(0) << ' ' << p.get(1) << " | " << q.get(0) << ' ' << q.get(1)
         << " | " << r.get(0) << ' ' << r.get(1) << '\n';
}
