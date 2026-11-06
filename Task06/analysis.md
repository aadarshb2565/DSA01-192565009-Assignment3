# Task 06 - The Rules of Operator Overloading

## Predict the Output
*(We will implement and test the given programs from the assignment, then compare prediction vs actual)*

## Implementation Tasks
Based on Assignment 3, Q6: A Simple Text Class for an SMS Gateway

We need to implement a `Text` class that holds a dynamically allocated character array and overloads various operators for text manipulation in an SMS gateway context.

### Required Implementation:
1. **Text Class with Rule of Three**:
   - Constructor:Allocates and initializes character array
   - Copy Constructor:Deep copy of character array
   - Copy Assignment Operator:With self-assignment check
   - Destructor:Releases dynamically allocated array

2. **Operator Overloading**:
   - Operator +:Concatenation of two Text objects
   - Operator == and !=:Comparison of Text objects
   - Operator <<:Stream output for Text objects
   - Prevent self-assignment problems in operator=

### Key Concepts:
- **Operators That Cannot Be Overloaded**:
  - `::` (scope resolution) - tied to compile-time name lookup
  - `.` (member access) - requires object as left operand
  - `.*` (pointer-to-member access) - complex semantics
  - `?:` (ternary conditional) - three operands, special parsing
  - `sizeof` - compile-time type information operator

- **Operator Overloading Rules**:
  - Precedence and arity cannot be changed
  - At least one operand must be user-defined type
  - Some operators must be members (especially assignment)

- **When to Use Friend Functions**:
  - When left operand is not your class (e.g., `ostream&` for `<<`)
  - When you need symmetric operations (e.g., `int + Text`)
  - When the operator conceptually doesn't modify the object

## Text Class Implementation

See `Task06/text.cpp` for the complete implementation.

### Features Implemented:
- Dynamic character array storage with proper memory management
- Constructor that allocates space and initializes to empty string
- Copy constructor that performs deep copy
- Copy assignment operator with self-assignment protection
- Destructor that releases memory with `delete[]`
- Operator+ for concatenation (creates new Text object)
- Operator== and != for lexicographical comparison
- Operator<< for stream output in quoted format
- Length utility methods
- Proper null-termination of character arrays

## Experimental Investigation
*(Conducted and documented in source code and output)*

### Tests Performed:
1. **Basic Functionality**:
   - Constructor, copy construction, assignment, destruction
   - Character array allocation and deallocation
   - String storage and retrieval

2. **Operator+ Concatenation**:
   - Counting copies made during evaluation (a + b + c)
   - Verifying correct concatenation results
   - Testing with empty strings
   - Testing with long messages

3. **Operator== and != Comparison**:
   - Lexicographical comparison (like strcmp)
   - Testing equal, less-than, greater-than cases
   - Empty string comparisons

4. **Operator<< Stream Output**:
   - Proper formatting of Text objects
   - Integration with standard output streams

5. **Memory Safety**:
   - Running under address sanitizer to detect leaks/errors
   - Verifying no memory leaks in normal operation
   - Checking for buffer overflows
   - Validating proper cleanup in destructors

6. **Self-Assignment Testing**:
   - Explicit test of `text = text` scenario
   - Verifying no corruption or crashes
   - Confirming self-check works correctly

7. **Performance Comparison**:
   - Comparing Text class with std::string for concatenations
   - Measuring time for 100,000 concatenations
   - Analyzing memory allocation patterns

### Key Findings:
- **Copy Counting**: 
  - Expression `a + b + c` creates 2 temporary objects:
    - First: `temp1 = a + b` (one copy constructor call)
    - Second: `result = temp1 + c` (another copy constructor call)
    - Plus potential return value copies depending on compiler

- **Memory Safety**:
  - AddressSanitizer: No leaks, no errors with proper implementation
  - Common errors without proper implementation:
    - Memory leaks (missing destructor)
    - Double free (missing copy constructor/assignment)
    - Buffer overflows (missing bounds checks)

- **Self-Assignment**:
  - Handled correctly by early return in operator=
  - Prevents unnecessary work and potential self-destruction

- **Performance vs std::string**:
  - Text class: Manual memory management, O(n) concatenation
  - std::string: Optimized, often uses small-string optimization
  - For 100,000 concatenations: std::string typically faster due to better algorithms
  - Text class provides learning value for understanding memory management

- **Long and Empty Messages**:
  - Empty strings handled correctly (allocates space for null terminator)
  - Long messages work within memory limits
  - No arbitrary length restrictions

## Rule of Three Application

### Why the Three Functions Go Together:
- **Destructor**: Needed because we manage raw memory with `new[]`
- **Copy Constructor**: Needed because default would do shallow copy (pointer copy)
- **Copy Assignment**: Needed because default would do shallow copy + cause leaks

### Consequences of Missing Any One:
- **Missing Destructor**: Memory leak - allocated arrays never freed
- **Missing Copy Constructor**: Shallow copy - multiple objects point to same buffer
  - Leads to: modified copies affecting others, double-free on destruction
- **Missing Copy Assignment**: Same issues as copy constructor, plus leak on reassignment

### Three Situations Where Copy Constructor Is Called:
1. **Explicit copy initialization**: `Text b = a;` or `Text b(a);`
2. **Pass-by-value function parameters**: `void func(Text t);` when called as `func(a);`
3. **Return-by-value from functions**: `Text func() { return localText; }`

## Complete the Code Programs

### Text Class (`text.cpp`)
Implements Rule of Three with proper dynamic character array management.
Includes operator+ for concatenation, operator==/!= for comparison, and operator<< for output.

### Test Program (`main.cpp`)
Tests:
- All required operators (+, ==, !=, <<)
- Copy constructor and copy assignment behavior
- Self-assignment safety
- Empty and long message handling
- Memory leak detection readiness
- Character array fundamentals

## Compilation & Execution:
```bash
cd Task06
g++ -std=c++17 -Wall -Wextra -o text_text text.cpp
g++ -std=c++17 -Wall -Wextra -o main main.cpp
./text_text    # Runs the text class demonstration
./main         # Runs the test program
```

## Expected Output Verification
While Assignment 3, Q6 doesn't specify a single "expected output" program to predict,
we verify correct behavior through:
- Proper concatenation: `"Hello" + " World" = "Hello World"`
- Correct comparison: `"Text" == "Text"` → true
- Safe self-assignment: `text = text` works without corruption
- Proper streaming: `cout << text` shows quoted content
- No memory leaks or errors under address sanitizer

## Alternative Concept and Complexity Analysis

**Alternative 1**: If Text class were replaced by std::string

**What would change**:
- Eliminate need for Rule of Three implementations
- Automatic memory management
- Built-in operator overloads (+, ==, <<, etc.)
- Richer string functionality (substr, find, etc.)

**Comparison** (for n-character strings):

| Operation               | Text Class (Ours)     | std::string         |
|-------------------------|-----------------------|---------------------|
| Construction            | O(n) time, O(n) space | O(n) time, O(n) space|
| Copy Construction       | O(n) time, O(n) space | O(n) time, O(n) space|
| Copy Assignment         | O(n) time, O(n) space | O(n) time, O(n) space|
| Concatenation (a+b)     | O(n) time, O(n) space | O(n) time, O(n) space|
| Comparison (a==b)       | O(n) time             | O(n) time           |
| Memory Management       | Manual                | Automatic           |
| Exception Safety        | Requires care         | Built-in            |
| Small String Opt.       | ❌ Not implemented    | ✅ Often available  |
| Code Complexity         | Higher                | Lower               |

**Alternative 2**: If + were implemented with += on a copy
```cpp
Text operator+(Text a, const Text& b) { 
    a += b; 
    return a; 
}
```

**What would change**:
- One less temporary object in expression evaluation
- `a + b + c` would create only 1 temporary instead of 2
- More efficient but requires `operator+=` implementation
- Still follows same asymptotic complexity

**Complexity Comparison** for `a + b + c` (lengths la, lb, lc):

| Implementation          | Temporary Objects | Characters Copied | Total Work |
|-------------------------|-------------------|-------------------|------------|
| Our version (a+b)+c     | 2 temporaries     | la+lb + (la+lb)+lc | 2la+2lb+lc |
| Alternative (a+=b)+c    | 1 temporary       | lb + (la+lb)+lc   | la+2lb+lc  |
| std::string approach    | Varies            | Optimized         | Typically less |

**Work Needed to Handle Division by Zero**: 
- Not applicable to Text class (no division operators)
- For classes that would support division: check denominator zero, handle error

