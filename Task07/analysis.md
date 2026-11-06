# Task 07 - Design a Complex-Number Class from First Principles

## Predict the Output
*(We will implement and test the given programs from the assignment, then compare prediction vs actual)*

## Implementation Tasks
Based on Assignment 3, Q7: AC Circuit Impedance Calculator

We need to design and implement a `Complex` class from first principles to represent complex numbers for AC circuit calculations. The class should support arithmetic operations needed for impedance calculations.

### Stage 1 - Interpret the Problem
- **Data**: Complex numbers with real and imaginary parts (both floating-point)
- **Operations Needed**: 
  - Addition (series impedances)
  - Subtraction 
  - Multiplication
  - Division (parallel impedances)
  - Equality comparison
  - Stream output
  - Magnitude calculation
- **Constructors Needed**:
  - Default: creates 0 + 0i
  - From real part: creates real + 0i (purely real)
  - From real and imaginary parts: creates real + imaginary*i

### Stage 2 - Design
**Complex Class Design**:
- Private members: `double real; double imag;`
- Constructors:
  - `Complex()` : default (0, 0)
  - `Complex(double r)` : from real part (r, 0)
  - `Complex(double r, double i)` : from real and imaginary parts (r, i)
- Arithmetic Operators (as member functions):
  - `operator+` : returns new Complex
  - `operator-` : returns new Complex  
  - `operator*` : returns new Complex
  - `operator/` : returns new Complex (handles division by zero)
- Comparison Operator:
  - `operator==` : exact equality (for testing)
- Stream Operator:
  - `operator<<` : friend function for output
- Utility Functions:
  - `magnitude()` : sqrt(real² + imag²)
  - `printPolar()` : optional polar form display

**Formulas for Operators**:
- Addition: (a+bi) + (c+di) = (a+c) + (b+d)i
- Subtraction: (a+bi) - (c+di) = (a-c) + (b-d)i
- Multiplication: (a+bi) × (c+di) = (ac-bd) + (ad+bc)i
- Division: (a+bi) ÷ (c+di) = [(ac+bd)/(c²+d²)] + [(bc-ad)/(c²+d²)]i
  - Special case: if c=0 and d=0, throw division by zero error

### Stage 3 - Implement and Verify
See `Task07/complex.cpp` for the complete implementation.

**AC Circuit Calculations Tested**:
1. **Series RLC Circuit**: 
   - Resistor: R + 0i
   - Inductor: 0 + ωLi  
   - Capacitor: 0 - (1/(ωC))i
   - Total: R + j(ωL - 1/(ωC))

2. **Parallel RLC Circuit**:
   - Individual impedances as above
   - Combined: Z_total = (Z₁ × Z₂) / (Z₁ + Z₂) for two components
   - Extended for three: pairwise combination

3. **Verification by Hand Calculation**:
   - Sample values: R=100Ω, L=0.1H, C=10μF, f=50Hz → ω=314 rad/s
   - Z_R = 100 + 0i
   - Z_L = 0 + 31.4i
   - Z_C = 0 - 31.83i
   - Z_series = 100 - 0.43i
   - Magnitude ≈ 100.0009Ω

4. **Division by Zero Safety**:
   - Detect zero denominator (0+0i)
   - Provide error handling (exception or special value)
   - Clear error messaging

### Stage 4 - Defend the Design
**Comparison with std::complex<double>**:
- **Similarities**:
  - Same memory layout: two doubles (real, imaginary)
  - Same asymptotic complexity: O(1) for all operations
  - Same mathematical correctness
- **Differences**:
  - Our version: Educational, explicit control, customizable behavior
  - std::complex: Optimized, extensive, standard library integration
  - std::complex: Built-in magnitude (`abs()`), conjugation, etc.
  - Our version: Division by zero handling explicit and customizable

**Why Each Constructor/Operator Is Needed**:
- **Default Constructor**: For declaring arrays, temporary objects
- **Real-part Constructor**: For purely resistive impedances (R + 0i)
- **Full Constructor**: For general complex impedances
- **Addition**: Series impedance combination
- **Subtraction**: Impedance differences, reactance calculations
- **Multiplication**: Used in parallel impedance formula
- **Division**: Critical for parallel impedance calculations
- **Equality**: Testing and validation
- **Stream Output**: Debugging and display of results
- **Magnitude**: Overall impedance magnitude (what meters measure)

**One Remaining Limitation**:
Our implementation uses exact equality for `operator==` which can be problematic with floating-point due to precision errors. A production version might use epsilon-based comparison or provide both exact and approximate equality options.

## Experimental Investigation
*(Conducted and documented in source code and output)*

### Tests Performed:
1. **Basic Constructor Testing**:
   - Default, real-part, and full constructors
   - Verification of correct initialization

2. **Arithmetic Operator Testing**:
   - Addition, subtraction, multiplication, division
   - Verification against known mathematical identities
   - Testing with real-only, imaginary-only, and complex numbers

3. **AC Circuit Calculations**:
   - Series RLC impedance calculation and verification
   - Parallel RLC impedance calculation and verification
   - Comparison with hand-calculated results
   - Frequency sweep testing

4. **Division by Zero Handling**:
   - Behavior when dividing by zero complex (0+0i)
   - Error reporting and program stability
   - Comparison with std::complex behavior

5. **Stream Output Formatting**:
   - Readable format for complex numbers
   - Handling of negative imaginary parts
   - Special cases (purely real, purely imaginary)

6. **Performance Characteristics**:
   - Operation timing (all O(1))
   - Memory usage verification
   - Comparison with std::complex performance

### Key Findings:
- **Constructor Correctness**: All three constructor types work as designed
- **Arithmetic Accuracy**: All operations produce mathematically correct results
- **Series Impedance**: 
  - Formula: Z = R + j(XL - XC) verified
  - Phase angle calculation correct
- **Parallel Impedance**:
  - Two-component formula: Z = (Z₁Z₂)/(Z₁+Z₂) verified
  - Three-component: sequential application works
  - Special cases (purely reactive) handled correctly
- **Division by Zero**:
  - Our implementation: Detects zero denominator, provides error message
  - Alternative: Could throw exception or return special NaN-like value
  - std::complex: Produces complex infinity or NaN (platform dependent)
- **Output Format**: 
  - Clear readable format: (a + bi) or (a - bi) 
  - Special handling for zero parts: "5" or "3i"
- **Performance**: 
  - All operations O(1) as expected
  - Memory footprint: exactly 16 bytes (2 × double)
  - No hidden allocations or memory leaks

## Complete the Code Programs

### Complex Class (`complex.cpp`)
Implements the Complex class with all required constructors, operators, and AC circuit calculation capabilities.

### Test Program (`main.cpp`)
Tests:
- All constructors and basic operations
- Arithmetic operator correctness
- Series and parallel RLC circuit calculations
- Division by zero handling
- Stream output formatting
- Comparison with manual calculations
- Performance characteristics setup

## Compilation & Execution:
```bash
cd Task07
g++ -std=c++17 -Wall -Wextra -o complex_complex complex.cpp
g++ -std=c++17 -Wall -Wextra -o main main.cpp
./complex_complex    # Runs the complex class demonstration
./main               # Runs the test program
```

## Expected Output Verification
While Assignment 3, Q7 doesn't specify a single "expected output" program to predict,
we verify correct behavior through:
- Proper constructor initialization
- Mathematically accurate arithmetic operations
- Correct AC circuit impedance calculations
- Safe handling of division by zero
- Clear, readable complex number output
- Agreement with hand-calculated results for test cases

## Alternative Concept and Complexity Analysis

**Alternative**: Using `std::complex<double>` instead of custom Complex class

**What would change**:
- Replace custom class with `#include <complex>` and `std::complex<double>`
- Use std::complex's built-in operators and functions
- Leverage standard library optimizations and extensions

**Comparison**:

| Aspect                    | Custom Complex Class | std::complex<double> |
|---------------------------|----------------------|----------------------|
| Memory Layout             | 2 doubles (16 bytes) | 2 doubles (16 bytes) |
| Time per Operation        | O(1)                 | O(1)                 |
| Space Complexity          | O(1)                 | O(1)                 |
| Constructor Options       | 3 (as designed)      | Similar flexibility  |
| Arithmetic Operators      | +, -, *, /, ==       | Full set incl. +=, etc. |
| Utility Functions         | magnitude()          | abs(), arg(), conj() |
| Stream Output             | Custom format        | Via operator<<       |
| Division by Zero          | Custom handling      | Platform-dependent   |
| Exception Safety          | Depends on impl.     | Generally good       |
| Standard Compliance       | Custom               | ISO C++ standard     |
| Learning Value            | High (understanding) | Low (black box)      |
| Production Readiness      | Good for learning    | Excellent            |

**Accuracy Comparison**:
- Both use IEEE 754 double precision
- Both subject to same floating-point precision limits
- Rounding behavior identical for equivalent operations
- No inherent accuracy advantage to either approach

**Work Needed to Handle Division by Zero**:
- **Custom Class**: Explicit check for (0+0i) denominator
  ```cpp
  if (other.real == 0.0 && other.imag == 0.0) {
      throw std::invalid_argument("Division by zero complex");
      // or return special error value
  }
  ```
- **std::complex**: Division by zero yields platform-specific result:
  - Often produces complex infinity or NaN
  - No exception thrown by default
  - Requires manual checking with `std::isinf()` or `std::isnan()`

**Verdict**: 
- **For Learning**: Custom class invaluable for understanding complex number internals
- **For Production**: std::complex preferred due to:
  - Battle-tested implementation
  - Extensive functionality (trigonometric, exponential, etc.)
  - Standard compatibility
  - Performance optimizations
  - Reduced development time
- **Hybrid Approach**: Learn with custom class, then migrate to std::complex for real projects

