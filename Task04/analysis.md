# Task 04 - Overloading Arithmetic and Stream Operators

## Predict the Output
*(We will implement and test the given program from the assignment, then compare prediction vs actual)*

## Implementation Tasks
Based on Assignment 3, Q4: Money Arithmetic for a Billing Counter

We need to implement a `Money` class that stores amounts in paise and overloads operators for arithmetic and stream operations.

### Required Implementation:
1. **Constructor**: Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}
2. **Operator +**: Overload as member function returning new Money object
3. **Operator ==**: Overload as member function 
4. **Operator <<**: Overload as friend function to print "Rs XXX.YY" format
5. **Bill calculation**: Use overloaded operators instead of functions like add(), print()

### Key Concepts:
- **Operator Overloading**: Making operators work with user-defined types
- **Member vs Friend Functions**: 
  - Member functions: implicit `this` parameter, can access private members
  - Friend functions: not members, but can access private parameters
- **Return Types**: 
  - `+` returns new object (doesn't modify operands)
  - `+=` would return reference to `*this` (modifies left operand)
- **Stream Operator**: `<<` must be non-member because first parameter is `ostream&` (not our class)

## Money Class Implementation

See `Task04/money.cpp` for the complete implementation.

### Features Implemented:
- Internal storage: `long long paise` (avoids floating-point precision issues)
- Constructor: Converts rupees and paise to total paise
- Operator+: Returns new Money object with summed paise
- Operator==: Compares paise values for equality
- Operator<<: Friend function that formats output as "Rs XX.YY"
- Additional operators tested: + with carry, == with different formats

## Experimental Investigation
*(Conducted and documented in source code and output)*

### Tests Performed:
1. **Basic arithmetic**: Addition of money objects
2. **Paise carry**: Testing when paise >= 100 (carries into rupees)
3. **Equality testing**: Various equal and unequal amounts
4. **Stream output**: Verification of "Rs XXX.YY" format
5. **Bill calculation**: Using operators in realistic scenario
6. **Comparison with double**: Precision comparison for large numbers
7. **Operator chaining**: Using multiple operators in expressions

### Key Findings:
- **Operator +**: Correctly returns new object, handles paise → rupee carry
- **Operator ==**: Accurate comparison without floating-point errors
- **Operator <<**: Proper formatting with leading zeros for paise < 10
- **Bill Calculation**: Much more readable with operators vs. function calls
- **Precision**: Integer paise avoids floating-point rounding errors
- **Readability**: `money1 + money2` vs `add(money1, money2)` - former is more intuitive

### Specific Test Results:
- **Rs 0.75 + Rs 0.50** = Rs 1.25 (paise: 75 + 50 = 125 → 1 rupee, 25 paise)
- **Rs 200.00** output format verified exactly
- **Boolean alpha**: `true`/`false` output for equality tests
- **Double comparison**: For 1,000,000 additions, integer version exact, double version showed drift

## Money Arithmetic Benefits

### Why + returns new object:
- Mathematical expectation: `a + b` doesn't modify `a` or `b`
- Consistency with built-in types: `int x = 3 + 4;` doesn't change 3 or 4
- Enables expression chaining: `(a + b) + c`

### Why << must be non-member:
- Stream insertion: `ostream& operator<<(ostream& os, const Money& m)`
- First parameter is `ostream&` (not Money), so can't be member function
- If attempted as member: `Money::operator<<(ostream& os)` - wrong parameter order

### Operator Translation:
- Expression `a + b` → `a.operator+(b)` (member function call)
- Expression `os << m` → `operator<<(os, m)` (friend function call)

## Complete the Code Programs

### Money Class (`money.cpp`)
Implements constructor, operator+, operator==, and operator<< as friends.

### Test Program (`main.cpp`)
Tests:
- Basic constructor and arithmetic
- Paise carry into rupees
- Stream output formatting
- Equality comparisons
- Bill calculation scenario
- Comparison with double-based implementation
- Additional test: Rs 0.75 + Rs 0.50

## Compilation & Execution:
```bash
cd Task04
g++ -std=c++17 -Wall -Wextra -o money_money money.cpp
g++ -std=c++17 -Wall -Wextra -o main main.cpp
./money_money    # Runs the money class demonstration
./main           # Runs the test program
```

## Expected Output Verification
For the "Complete the Code" section in the assignment:
```cpp
int main()
{
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\n' << boolalpha << (c == Money(200)) << '\n';
}
```

**Expected output:**
```
Rs 200.00
true
```

## Alternative Concept and Complexity Analysis

**Alternative**: Operators as non-member friend functions instead of members

**What would change**:
- `operator+` and `operator==` would be non-member friends
- Syntax: `Money operator+(const Money& a, const Money& b)`
- Would need friend declarations in class
- Could support `100 + m` (if we also overload for built-in types)

**Comparison**:

| Aspect                     | Member Operators (Ours) | Non-member Friends |
|----------------------------|-------------------------|-------------------|
| `a + b`                    | `a.operator+(b)`        | `operator+(a,b)`  |
| `100 + m`                  | ❌ Not possible         | ✅ Possible       |
| `m + 100`                  | ✅ Possible             | ✅ Possible       |
| Access to private members  | Yes (implicit this)     | Yes (friend)      |
| Symmetry                   | Left-biased             | Fully symmetric   |
| Encapsulation impact       | Moderate                | Similar           |
| Typical use case           | When left operand is class | When symmetry needed |

**Verdict**: 
- For `+` and `==`: Member functions are sufficient and conventional
- For `<<`: Must be non-member (first param is ostream)
- For mixed-type operations (e.g., `int + Money`): Non-member friends needed
- Our implementation follows standard practice: arithmetic/comparison as members, stream as friend

## Engineering Decision: Money Multiplication

**Should Money allow multiplication by another Money?**
- ❌ No meaningful interpretation: `$5 × $3 = $15`?? 
- Units don't work: money² has no financial meaning
- Better alternatives:
  - Money × scalar (e.g., `amount * quantity` for line items)
  - Scalar × Money (e.g., `quantity * amount`)
  - Percentage operations: `amount * rate / 100`

**Operators that make sense for money**:
- ✅ `+`, `-` (addition/subtraction of amounts)
- ✅ `+=`, `-=` (compound assignment)
- ✅ `==`, `!=`, `<`, `>` (comparison)
- ✅ `*`, `/` (scalar multiplication/division)
- ❌ `*` (money × money) - meaningless units
- ❌ `/` (money ÷ money) - usually percentage, better expressed explicitly

