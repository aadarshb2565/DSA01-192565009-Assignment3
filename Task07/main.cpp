#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0.0), imag(0.0) {}
    Complex(double r) : real(r), imag(0.0) {}
    Complex(double r, double i) : real(r), imag(i) {}
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }
    Complex operator/(const Complex& other) const {
        double denom = other.real * other.real + other.imag * other.imag;
        if (denom == 0.0) {
            throw runtime_error("Division by zero");
        }
        return Complex(
            (real * other.real + imag * other.imag) / denom,
            (imag * other.real - real * other.imag) / denom
        );
    }
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }
    // Getter methods for testing
    double getReal() const { return real; }
    double getImag() const { return imag; }
    friend ostream& operator<<(ostream& os, const Complex& c);
};

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
};

// Main function focusing on AC circuit verification
int main()
{
    cout << "=== AC Circuit Impedance Verification ===" << endl;
    
    cout << "\n1. Testing Series RLC Circuit Calculation:" << endl;
    // Given: R = 50Ω, L = 0.2H, C = 15μF, f = 60Hz
    double R = 50.0;
    double L = 0.2;
    double C = 15e-6;
    double f = 60.0;
    
    double omega = 2.0 * M_PI * f;
    double XL = omega * L;           // ωL
    double XC = 1.0 / (omega * C);   // 1/(ωC)
    
    Complex Z_R(R, 0.0);
    Complex Z_L(0.0, XL);
    Complex Z_C(0.0, -XC);
    Complex Z_series = Z_R + Z_L + Z_C;
    
    cout << "Given: R = " << R << "Ω, L = " << L << "H, C = " << C*1e6 << "μF, f = " << f << "Hz" << endl;
    cout << "Calculated: ω = " << omega << " rad/s" << endl;
    cout << "          XL = ωL = " << XL << "Ω" << endl;
    cout << "          XC = 1/(ωC) = " << XC << "Ω" << endl;
    cout << "Impedances:" << endl;
    cout << "  Z_R = " << Z_R << endl;
    cout << "  Z_L = " << Z_L << endl;
    cout << "  Z_C = " << Z_C << endl;
    cout << "  Z_series = Z_R + Z_L + Z_C = " << Z_series << endl;
    cout << "  |Z_series| = " << Z_series.magnitude() << "Ω" << endl;
    cout << "  Phase angle = atan(" << Z_series.getImag() << "/" << Z_series.getReal() << ") = " 
              << atan2(Z_series.getImag(), Z_series.getReal()) * 180.0 / M_PI << "°" << endl;
    
    // Manual calculation for verification
    double manualReal = R;
    double manualImag = XL - XC;
    double manualMag = sqrt(manualReal*manualReal + manualImag*manualImag);
    cout << "\nManual verification:" << endl;
    cout << "  Z_manual = " << manualReal << " + j(" << manualImag << ") Ω" << endl;
    cout << "  |Z_manual| = " << manualMag << "Ω" << endl;
    cout << "  Match: " << boolalpha 
              << (abs(Z_series.getReal() - manualReal) < 0.001 && 
                  abs(Z_series.getImag() - manualImag) < 0.001) << endl;
    
    cout << "\n2. Testing Parallel RLC Circuit Calculation:" << endl;
    // Two branches: R-L series and C alone
    double R_branch = 30.0;
    double L_branch = 0.15;
    double C_branch = 20e-6;
    
    double XL_branch = omega * L_branch;
    double XC_branch = 1.0 / (omega * C_branch);
    
    Complex Z_R_L(R_branch, XL_branch);    // R-L series
    Complex Z_C_alone(0.0, -XC_branch);    // Capacitor alone
    Complex Z_parallel = (Z_R_L * Z_C_alone) / (Z_R_L + Z_C_alone);
    
    cout << "Branch 1 (R-L series): R = " << R_branch << "Ω, L = " << L_branch << "H" << endl;
    cout << "  XL = " << XL_branch << "Ω, Z_R_L = " << Z_R_L << endl;
    cout << "Branch 2 (C alone): C = " << C_branch*1e6 << "μF, XC = " << XC_branch << "Ω" << endl;
    cout << "  Z_C_alone = " << Z_C_alone << endl;
    cout << "Parallel combination:" << endl;
    cout << "  Z_parallel = (Z_R_L * Z_C_alone) / (Z_R_L + Z_C_alone)" << endl;
    cout << "  Z_parallel = " << Z_parallel << endl;
    cout << "  |Z_parallel| = " << Z_parallel.magnitude() << "Ω" << endl;
    
    cout << "\n3. Testing Component Impedances:" << endl;
    cout << "Resistor (100Ω): " << Complex(100.0, 0.0) << endl;
    cout << "Inductor (0.1H @ 50Hz): " << Complex(0.0, 2.0*M_PI*50*0.1) << endl;
    cout << "Capacitor (10μF @ 50Hz): " << Complex(0.0, -1.0/(2.0*M_PI*50*10e-6)) << endl;
    
    cout << "\n4. Testing Division by Zero:" << endl;
    try {
        Complex num(1.0, 2.0);
        Complex den(0.0, 0.0);
        Complex result = num / den;
        cout << "ERROR: Should have thrown exception!" << endl;
    } catch (const runtime_error& e) {
        cout << "Correctly caught exception: " << e.what() << endl;
    }
    
    cout << "\n5. Testing Polar Form Conversion:" << endl;
    Complex z(3.0, 4.0);
    double mag = z.magnitude();
    double angle = atan2(z.getImag(), z.getReal());  // radians
    cout << "z = " << z << endl;
    cout << "|z| = " << mag << endl;
    cout << "arg(z) = " << angle << " rad = " << angle * 180.0 / M_PI << "°" << endl;
    cout << "Reconstructed: " << mag * cos(angle) << " + j(" << mag * sin(angle) << ")" << endl;
    
    return 0;
}
