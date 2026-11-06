#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Constructors
    Complex() : real(0.0), imag(0.0) {}                                    // Default
    Complex(double r) : real(r), imag(0.0) {}                              // From real part
    Complex(double r, double i) : real(r), imag(i) {}                      // From real and imaginary parts

    // Copy constructor
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    // Copy assignment
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    // Arithmetic operators
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    Complex operator/(const Complex& other) const {
        // (a+bi)/(c+di) = [(ac+bd)/(c²+d²)] + [(bc-ad)/(c²+d²)]i
        double denom = other.real * other.real + other.imag * other.imag;
        if (denom == 0.0) {
            throw invalid_argument("Division by zero complex number");
        }
        return Complex(
            (real * other.real + imag * other.imag) / denom,
            (imag * other.real - real * other.imag) / denom
        );
    }

    // Equality operator
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // Magnitude (modulus)
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    // Stream output
    friend ostream& operator<<(ostream& os, const Complex& c);
};

// Stream output formatting
ostream& operator<<(ostream& os, const Complex& c) {
    os << fixed << setprecision(3);
    if (c.imag == 0.0) {
        os << c.real;
    } else if (c.real == 0.0) {
        os << c.imag << "i";
    } else {
        os << c.real;
        if (c.imag >= 0) {
            os << " + " << c.imag << "i";
        } else {
            os << " - " << -c.imag << "i";
        }
    }
    return os;
}

// AC Circuit Functions
double calculateInductiveReactance(double frequency, double inductance) {
    return 2.0 * M_PI * frequency * inductance;  // XL = 2πfL
}

double calculateCapacitiveReactance(double frequency, double capacitance) {
    return 1.0 / (2.0 * M_PI * frequency * capacitance);  // XC = 1/(2πfC)
}

// Main function to test the Complex class
int main()
{
    cout << "=== Testing Complex Class (Assignment 3, Q7) ===" << endl;
    
    cout << "\n1. Testing constructors:" << endl;
    Complex c1;                    // Default
    Complex c2(5.0);               // From real part
    Complex c3(3.0, 4.0);          // From real and imaginary
    Complex c4 = c3;               // Copy constructor
    
    cout << "c1 (default): " << c1 << endl;
    cout << "c2 (real 5): " << c2 << endl;
    cout << "c3 (3+4i): " << c3 << endl;
    cout << "c4 (copy of c3): " << c4 << endl;
    
    cout << "\n2. Testing arithmetic operators:" << endl;
    Complex a(2.0, 3.0);   // 2+3i
    Complex b(1.0, -1.0);  // 1-i
    
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "a + b: " << (a + b) << endl;
    cout << "a - b: " << (a - b) << endl;
    cout << "a * b: " << (a * b) << endl;
    cout << "a / b: " << (a / b) << endl;
    
    cout << "\n3. Testing equality:" << endl;
    Complex c5(2.0, 3.0);
    Complex c6(2.0, 3.0);
    cout << "c5: " << c5 << endl;
    cout << "c6: " << c6 << endl;
    cout << "c5 == c6: " << boolalpha << (c5 == c6) << endl;
    
    cout << "\n4. Testing magnitude:" << endl;
    Complex c7(3.0, 4.0);  // Should have magnitude 5.0
    cout << "c7: " << c7 << endl;
    cout << "|c7|: " << c7.magnitude() << endl;
    
    cout << "\n5. Testing Series RLC Circuit:" << endl;
    // Example: R=100Ω, L=0.1H, C=10μF, f=50Hz
    double R = 100.0;
    double L = 0.1;          // Henry
    double C = 10e-6;        // Farads
    double f = 50.0;         // Hz
    double omega = 2.0 * M_PI * f;
    
    double XL = calculateInductiveReactance(f, L);  // ωL
    double XC = calculateCapacitiveReactance(f, C); // 1/(ωC)
    
    Complex Z_R(R, 0.0);                    // Pure resistance
    Complex Z_L(0.0, XL);                   // Pure inductance
    Complex Z_C(0.0, -XC);                  // Pure capacitance (negative imaginary)
    Complex Z_series = Z_R + Z_L + Z_C;     // Series combination
    
    cout << "Frequency: " << f << " Hz" << endl;
    cout << "Angular frequency (ω): " << omega << " rad/s" << endl;
    cout << "Inductive reactance (XL): " << XL << " Ω" << endl;
    cout << "Capacitive reactance (XC): " << XC << " Ω" << endl;
    cout << "Z_R: " << Z_R << endl;
    cout << "Z_L: " << Z_L << endl;
    cout << "Z_C: " << Z_C << endl;
    cout << "Z_series = Z_R + Z_L + Z_C: " << Z_series << endl;
    cout << "|Z_series|: " << Z_series.magnitude() << " Ω" << endl;
    
    cout << "\n6. Testing Parallel Impedance:" << endl;
    // Two impedances in parallel: Z_total = (Z1 * Z2) / (Z1 + Z2)
    Complex Z1(4.0, 3.0);   // 4+3i Ω
    Complex Z2(2.0, -1.0);  // 2-1i Ω
    
    Complex Z_parallel = (Z1 * Z2) / (Z1 + Z2);
    
    cout << "Z1: " << Z1 << endl;
    cout << "Z2: " << Z2 << endl;
    cout << "Z1 * Z2: " << (Z1 * Z2) << endl;
    cout << "Z1 + Z2: " << (Z1 + Z2) << endl;
    cout << "Z_parallel = (Z1*Z2)/(Z1+Z2): " << Z_parallel << endl;
    cout << "|Z_parallel|: " << Z_parallel.magnitude() << " Ω" << endl;
    
    cout << "\n7. Testing Division by Zero Handling:" << endl;
    try {
        Complex numerator(1.0, 2.0);
        Complex zero(0.0, 0.0);
        Complex result = numerator / zero;
        cout << "This should not be printed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    
    cout << "\n8. Testing Special Cases:" << endl;
    Complex zero(0.0, 0.0);
    Complex pureReal(5.0, 0.0);
    Complex pureImag(0.0, -3.0);
    
    cout << "Zero: " << zero << endl;
    cout << "Pure real: " << pureReal << endl;
    cout << "Pure imag: " << pureImag << endl;
    cout << "Zero magnitude: " << zero.magnitude() << endl;
    cout << "Pure real magnitude: " << pureReal.magnitude() << endl;
    cout << "Pure imag magnitude: " << pureImag.magnitude() << endl;
    
    return 0;
}
