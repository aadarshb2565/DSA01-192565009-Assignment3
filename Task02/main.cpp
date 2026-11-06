#include <iostream>
#include <string>
using namespace std;

// Include the Prescription class
class Prescription {
    int n;
    string* medicines;

public:
    explicit Prescription(int count) : n(count), medicines(new string[count]) {
        for (int i = 0; i < count; i++) {
            medicines[i] = "";
        }
    }

    Prescription(const Prescription& other) 
        : n(other.n), medicines(new string[other.n]) {
        for (int i = 0; i < other.n; i++) {
            medicines[i] = other.medicines[i];
        }
    }

    Prescription& operator=(const Prescription& other) {
        if (this == &other) {
            return *this;
        }
        
        delete[] medicines;
        
        n = other.n;
        medicines = new string[n];
        
        for (int i = 0; i < n; i++) {
            medicines[i] = other.medicines[i];
        }
        
        return *this;
    }

    ~Prescription() {
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
        return ""; 
    }
};

int main()
{
    cout << "=== Testing Prescription Class (Assignment 3, Q2) ===" << endl;
    
    cout << "\n1. Testing basic functionality from assignment:" << endl;
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
    
    cout << "\nExpected output: Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS" << endl;
    
    cout << "\n2. Testing self-assignment (p = p):" << endl;
    Prescription s(3);
    s.set(0, "DrugA");
    s.set(1, "DrugB"); 
    s.set(2, "DrugC");
    cout << "Before self-assignment: ";
    for (int i = 0; i < 3; i++) {
        cout << s.get(i) << " ";
    }
    cout << endl;
    
    s = s;  // Self-assignment
    cout << "After self-assignment:  ";
    for (int i = 0; i < 3; i++) {
        cout << s.get(i) << " ";
    }
    cout << endl;
    
    cout << "\n3. Testing independence of copies:" << endl;
    Prescription original(2);
    original.set(0, "Medicine1");
    original.set(1, "Medicine2");
    
    Prescription copy1 = original;  // Copy constructor
    Prescription copy2(0);
    copy2 = original;               // Copy assignment
    
    // Modify the original
    original.set(0, "ChangedMedicine");
    
    cout << "Original:  ";
    for (int i = 0; i < 2; i++) {
        cout << original.get(i) << " ";
    }
    cout << endl;
    
    cout << "Copy1 (ctor): ";
    for (int i = 0; i < 2; i++) {
        cout << copy1.get(i) << " ";
    }
    cout << endl;
    
    cout << "Copy2 (assign): ";
    for (int i = 0; i < 2; i++) {
        cout << copy2.get(i) << " ";
    }
    cout << endl;
    
    cout << "\n4. Demonstrating what happens WITHOUT proper deep copy:" << endl;
    cout << "   (Commented out to avoid crash, but would show shallow copy problems)" << endl;
    cout << "   Without deep copy:" << endl;
    cout << "   - Copy constructor would just copy the pointer" << endl;
    cout << "   - Both objects would point to same memory" << endl;
    cout << "   - Modifying one would affect the other" << endl;
    cout << "   - Destructors would both delete[] the same array -> double free" << endl;
    
    cout << "\n=== All Tests Completed Successfully ===" << endl;
    return 0;
}
