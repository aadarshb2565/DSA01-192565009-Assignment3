# Task 01 - Constructors and Constructor Overloading

## Predict the Output
*(No prediction required for this task as we are implementing from scratch)*

## Implementation Tasks
Based on Assignment 3, Q1: Library Book Records

We need to implement a `Book` class with:
- Default constructor (creates empty record)
- Parameterised constructor (full details: title, author, copies, price)
- Overloaded constructor for donated book (only title, others default)
- All constructors must use member initializer lists
- Use constructor delegation to avoid code repetition
- Prevent invalid number of copies (negative values)

## Book Class Implementation

See `Task01/book.cpp` for the complete implementation.

### Constructors Implemented:
1. **Default Constructor**: `Book()` - Creates empty record with default values
2. **Parameterised Constructor**: `Book(string title, string author, int copies, double price)` - Full details
3. **Overloaded Constructor**: `Book(string title)` - For donated books (title only)

All constructors use member initializer lists and delegate to the parameterised constructor where appropriate.

### Validation:
- Number of copies cannot be negative
- Price cannot be negative
- Default values provided for optional parameters

## Experimental Investigation
*(Conducted and documented in the source code comments and output)*

### Tests Performed:
1. Created Book objects with every constructor and printed them
2. Verified that default constructor is not supplied by compiler when we define our own
3. Attempted to create array of Books without default compiler-provided constructor
4. Demonstrated member initialization order vs. declaration order
5. Tested negative number of copies validation
6. Tested explicit constructor requirement

### Key Findings:
- Member initializer lists are preferred to assignment in constructor body for:
  - Better performance (direct initialization vs. default construction + assignment)
  - Ability to initialize const members and references
  - Ensuring all members are initialized before constructor body executes
- Members are initialized in declaration order, not initializer list order
- Constructor delegation reduces code duplication
- Validation logic centralized in parameterised constructor

## Complete the Code Programs

### Book Class Implementation (`book.cpp`)
Demonstrates all constructor types with proper validation and delegation.

### Test Program (`main.cpp`)
Tests all constructor variations and validation.

## Compilation & Execution:
```bash
cd Task01
g++ -std=c++17 -Wall -Wextra -o book_book book.cpp
g++ -std=c++17 -Wall -Wextra -o book_main main.cpp
./book_book    # Runs the Book class demonstration
./book_main    # Runs the test program
```

## Output Verification
The program demonstrates:
- Successful creation of books with all three constructor types
- Proper initialization of all member variables
- Prevention of invalid Book objects (negative copies)
- Constructor delegation working correctly
- Member initialization order correctness

## Alternative Concept and Complexity Analysis

**Alternative**: Using a single constructor with default arguments:
```cpp
Book(std::string t = "", std::string a = "", int c = 0, double p = 0.0)
```

**Analysis**:
- **Time Complexity**: Both designs O(1) for object creation
- **Space Complexity**: Both designs O(1) - same member variables
- **Validation Checks**: 
  - Multiple constructors: Validation in each constructor (more places)
  - Single constructor with defaults: Validation in one place (fewer places)
- **Code Duplication**: 
  - Multiple constructors: More code duplication without delegation
  - With delegation: Minimal duplication (validation in parameterised constructor)
  - Single constructor: Least duplication but less explicit about intended use cases

**Recommendation**: Multiple constructors with delegation is better because:
1. More explicit about different use cases (new book, donated book, empty record)
2. Clearer intent for each constructor
3. Easy to add validation specific to constructor type if needed
4. Delegation minimizes actual code duplication

