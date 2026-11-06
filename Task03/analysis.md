# Task 03 - Dynamic Constructors and Destructors

## Predict the Output
*(We will implement and test the given program from the assignment, then compare prediction vs actual)*

## Implementation Tasks
Based on Assignment 3, Q3: Auditorium Seat Booking

We need to implement an `Event` class that manages a two-dimensional seat map using dynamic memory allocation.

### Required Implementation:
1. **Dynamic constructor**: Allocates a two-dimensional seat map with `new`
2. **Destructor**: Releases every allocation and prints a summary
3. **Seat booking/cancelling**: Methods to book and cancel seats
4. **Testing**: Create events on stack, heap (new/delete), and inside blocks

### Key Concepts:
- **Dynamic Constructor**: Constructor that allocates memory with `new`
- **RAII (Resource Acquisition Is Initialization)**: Tie resource lifetime to object lifetime
- **Rule of Three/Five**: Since we manage resources, we need proper copying semantics
- **Memory Layout**: Understanding how 2D arrays are allocated as array of pointers

## Event Class Implementation

See `Task03/event.cpp` for the complete implementation.

### Features Implemented:
- Dynamic 2D seat map allocation: `char** seats = new char*[rows];` then `seats[i] = new char[cols];`
- Proper initialization of all seats to available state (e.g., 'A' for available)
- Seat booking: Change seat state from 'A' to 'B' (booked)
- Seat cancelling: Change seat state from 'B' to 'A' (available)
- Destructor: Properly deletes each row then the row pointers array
- Constructor/destructor messages for tracing object lifecycle
- Summary print in destructor showing final statistics

## Experimental Investigation
*(Conducted and documented in source code and output)*

### Tests Performed:
1. **Object lifecycle tracing**: Created events on stack, heap, and in blocks
2. **Constructor/destructor order**: Verified correct sequence for different storage types
3. **Memory leak detection**: Used address sanitizer to verify proper cleanup
4. **Boundary conditions**: Tested event with zero rows
5. **Seat operations**: Verified booking and cancelling work correctly
6. **Heap vs stack**: Compared behavior of dynamically vs statically allocated objects

### Key Findings:
- **Construction order**: For local objects: constructor → ... → destructor
- **Block scope**: Objects destroyed in reverse order of construction when leaving block
- **Dynamic objects**: Constructor called at `new`, destructor at `delete`
- **Memory layout**: Seat map as `char**` where each `seats[i]` points to a row array
- **Zero-sized events**: Handled gracefully (no allocation when rows=0 or cols=0)
- **Delete vs delete[]**: Using `delete` instead of `delete[]` causes undefined behavior
- **Forgotten delete**: Causes memory leak (detected by address sanitizer)

### Sanitizer Results:
- **With correct code**: No memory leaks, no errors
- **With missing delete**: AddressSanitizer detects memory leak
- **With delete instead of delete[]**: AddressSanitizer detects incorrect deallocation

### Memory Measurements:
*(Approximate memory usage for different seat map sizes)*

| Rows × Seats | Elements | Memory Allocated | # of Allocations |
|--------------|----------|------------------|------------------|
| 10 × 20      | 200      | ~200 bytes       | 11 (1 row ptr array + 10 row arrays) |
| 100 × 200    | 20,000   | ~20KB            | 101 (1 row ptr array + 100 row arrays) |
| 1,000 × 2,000| 2M       | ~2MB             | 1,001 (1 row ptr array + 1,000 row arrays) |

*Note: Actual memory includes overhead for allocation metadata.*

## Performance Characteristics

### Access Time:
- **O(1)** for accessing any seat: `seats[row][col]`
- Two memory dereferences: first to get row pointer, second to get element

### Number of Allocations:
- **Rows + 1** total allocations:
  - 1 allocation for array of row pointers (`char**`)
  - Rows allocations for each row (`char*` each)

### Extra Space for Row Pointers:
- **Pointer array overhead**: `(rows × sizeof(char*))` bytes
- For typical systems: 8 bytes per pointer on 64-bit systems
- Percentage overhead: `(rows × 8) / (rows × cols × sizeof(char)) × 100%`
- Decreases as cols increases (becomes negligible for large seat maps)

## Complete the Code Programs

### Event Class (`event.cpp`)
Implements dynamic seat map allocation/deallocation with booking/cancelling.

### Test Program (`main.cpp`)
Tests:
- Stack, heap, and block-scoped object creation
- Constructor/destructor order verification
- Seat booking and cancelling operations
- Zero-sized event handling
- Memory leak scenarios (for demonstration)
- Expected output from assignment's "Predict the Output" section

## Compilation & Execution:
```bash
cd Task03
g++ -std=c++17 -Wall -Wextra -o event_event event.cpp
g++ -std=c++17 -Wall -Wextra -o main main.cpp
./event_event    # Runs the event class demonstration
./main           # Runs the test program
```

## Expected Output Verification
For the "Predict the Output" section in the assignment:
```cpp
struct Logger { /* ... */ };
void use(Logger) { /* ... */ };
int main() {
    Logger a("A");
    {
        Logger b("B");
    }
    use(a);
    Logger* p = new Logger("P");
    delete p;
    cout << "end ";
}
```

**Expected output:**
```
+A +B -Bc use A +Pc -Pc -A end 
```

*(Explanation: Logger objects constructed/destroyed in order, copy made when passed by value to use())*

## Alternative Concept and Complexity Analysis

**Alternative 1**: Single block allocation (`rows × seats` elements)
```cpp
char* seats = new char[rows * cols];
// Access: seats[row * cols + col]
```

**Alternative 2**: `std::vector<std::vector<char>>`
```cpp
vector<vector<char>> seats(rows, vector<char>(cols, 'A'));
```

**Comparison**:

| Aspect                   | Array of Pointers (Ours) | Single Block       | Vector of Vectors  |
|--------------------------|--------------------------|--------------------|--------------------|
| Access Time              | O(1)                     | O(1)               | O(1)               |
| # of Allocations         | rows + 1                 | 1                  | 1 (vector overhead)|
| Extra Space              | rows × pointer_size      | 0                  | Small (vector obj) |
| Row Length Flexibility   | Yes (jagged arrays)      | No (fixed)         | Yes                |
| Memory Contiguity        | No (rows scattered)      | Yes (contiguous)   | No (per row)       |
| Allocation Failure Risk  | Higher (multiple allocs) | Lower (single)     | Lower              |
| Deallocation Complexity  | Moderate (loop)          | Simple             | Simple (automatic) |
| Cache Efficiency         | Lower                    | Higher             | Lower              |

**Trade-offs**:
- **Array of Pointers**: Flexible row lengths, but more allocations and poorer cache performance
- **Single Block**: Best cache performance, simplest allocation/deallocation, but fixed row length
- **Vector of Vectors**: Automatic memory management, exception safe, but some overhead

**Recommendation**: For fixed-size seat maps where all rows have same length, single block allocation is optimal. For truly jagged arrays or when learning manual memory management, array of pointers approach is educational.

