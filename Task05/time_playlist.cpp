#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// Time class for music track timer
class Time {
private:
    int hours;   // 0-23
    int minutes; // 0-59
    int seconds; // 0-59

public:
    // Constructors
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    // Prefix increment: ++time
    Time& operator++() {
        ++seconds;
        normalize();
        return *this;
    }

    // Postfix increment: time++
    Time operator++(int) {
        Time temp = *this;  // Copy current state
        ++seconds;          // Increment current object
        normalize();
        return temp;        // Return the copy
    }

    // Comparison operators
    bool operator==(const Time& other) const {
        return hours == other.hours && 
               minutes == other.minutes && 
               seconds == other.seconds;
    }

    bool operator<(const Time& other) const {
        if (hours != other.hours) return hours < other.hours;
        if (minutes != other.minutes) return minutes < other.minutes;
        return seconds < other.seconds;
    }

    // Normalize time to proper ranges
    void normalize() {
        // Handle seconds overflow
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        } else if (seconds < 0) {
            // Handle negative seconds (borrow from minutes)
            int borrow = (-seconds + 59) / 60;
            minutes -= borrow;
            seconds += borrow * 60;
        }
        
        // Handle minutes overflow
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        } else if (minutes < 0) {
            // Handle negative minutes (borrow from hours)
            int borrow = (-minutes + 59) / 60;
            hours -= borrow;
            minutes += borrow * 60;
        }
        
        // Handle hours overflow (wrap around 24-hour clock)
        if (hours >= 24) {
            hours %= 24;
        } else if (hours < 0) {
            // Handle negative hours (wrap backward)
            hours = ((hours % 24) + 24) % 24;
        }
    }

    // Display time in HH:MM:SS format
    void display() const {
        cout << setfill('0') << setw(2) << hours << ':'
             << setw(2) << minutes << ':'
             << setw(2) << seconds;
    }

    // Getters for testing
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }
};

// Playlist class for managing music tracks
class Playlist {
private:
    vector<string> tracks;

public:
    // Constructors
    Playlist() = default;
    Playlist(initializer_list<string> list) : tracks(list) {}

    // Non-const subscript operator (returns reference for modification)
    string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            cerr << "ERROR: Playlist index out of bounds! "
                 << "Requested index: " << index << ", "
                 << "Valid range: 0 to " << tracks.size()-1 << endl;
            // Return a dummy reference to prevent crash (not ideal but demonstrates concept)
            static string dummy;
            return dummy;
        }
        return tracks[index];
    }

    // Const subscript operator (returns const reference for read-only access)
    const string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks.size())) {
            cerr << "ERROR: Playlist index out of bounds! "
                 << "Requested index: " << index << ", "
                 << "Valid range: 0 to " << tracks.size()-1 << endl;
            // Return a dummy reference to prevent crash
            static string dummy;
            return dummy;
        }
        return tracks[index];
    }

    // Get number of tracks
    size_t size() const { return tracks.size(); }

    // Add a track to the playlist
    void addTrack(const string& track) {
        tracks.push_back(track);
    }

    // Display playlist
    void display() const {
        cout << "Playlist (" << tracks.size() << " tracks):" << endl;
        for (size_t i = 0; i < tracks.size(); i++) {
            cout << "  [" << i << "] " << tracks[i] << endl;
        }
    }
};

// Main function to test all required scenarios
int main() {
    cout << "=== Testing Time and Playlist Classes (Assignment 3, Q5) ===" << endl;
    
    cout << "\n1. Testing Time class basic functionality:" << endl;
    Time t1(10, 30, 45);
    cout << "Initial time: ";
    t1.display();
    cout << endl;
    
    cout << "\n2. Testing prefix increment (++time):" << endl;
    Time t2(10, 30, 45);
    Time& ref = ++t2;  // Prefix increment
    cout << "After ++t2: ";
    t2.display();
    cout << " (Reference to same object)" << endl;
    
    cout << "\n3. Testing postfix increment (time++):" << endl;
    Time t3(10, 30, 45);
    Time copy = t3++;  // Postfix increment
    cout << "Original t3 after t3++: ";
    t3.display();
    cout << endl;
    cout << "Copy returned from t3++: ";
    copy.display();
    cout << " (Copy of original value)" << endl;
    
    cout << "\n4. Testing comparison operators:" << endl;
    Time t4(10, 30, 45);
    Time t5(10, 30, 46);
    Time t6(10, 31, 44);
    cout << "t4: ";
    t4.display();
    cout << ", t5: ";
    t5.display();
    cout << ", t6: ";
    t6.display();
    cout << endl;
    cout << "t4 == t5: " << boolalpha << (t4 == t5) << endl;
    cout << "t4 < t5:  " << (t4 < t5) << endl;
    cout << "t4 < t6:  " << (t4 < t6) << endl;
    cout << "t5 < t6:  " << (t5 < t6) << endl;
    
    cout << "\n5. Testing roll-over behavior:" << endl;
    Time t7(23, 59, 58);  // One second before midnight
    cout << "Starting at: ";
    t7.display();
    cout << endl;
    
    for (int i = 0; i < 5; i++) {
        ++t7;
        cout << "After ++: ";
        t7.display();
        cout << endl;
    }
    
    cout << "\n6. Testing Playlist class:" << endl;
    Playlist myPlaylist;
    myPlaylist.addTrack("Track 1: Song Alpha");
    myPlaylist.addTrack("Track 2: Song Beta");
    myPlaylist.addTrack("Track 3: Song Gamma");
    
    cout << "Initial playlist:" << endl;
    myPlaylist.display();
    
    cout << "\n7. Testing Playlist subscript operators:" << endl;
    cout << "Non-const access (read): " << myPlaylist[0] << endl;
    cout << "Non-const access (modify): ";
    myPlaylist[1] = "Modified Track 2";
    cout << myPlaylist[1] << endl;
    
    const Playlist constPlaylist = myPlaylist;
    cout << "Const access: " << constPlaylist[2] << endl;
    
    cout << "\n8. Testing Playlist out-of-bounds access:" << endl;
    cout << "Attempting to access index -1: ";
    string negResult = myPlaylist[-1];  // Should show error
    cout << "Result: '" << negResult << "'" << endl;
    
    cout << "Attempting to access index 5 (too large): ";
    string largeResult = myPlaylist[5];  // Should show error
    cout << "Result: '" << largeResult << "'" << endl;
    
    cout << "\n9. Testing the exact Counter example from assignment:" << endl;
    struct Counter {
        int v;
        Counter& operator++() { ++v; return *this; }                     // prefix
        Counter operator++(int) { Counter old = *this; ++v; return old; } // postfix
    };
    
    Counter c{5};
    Counter a = c++;   // a gets 5, c becomes 6
    Counter b = ++c;   // c becomes 7, b gets 7
    cout << a.v << ' ' << b.v << ' ' << c.v << ' ' << endl;
    
    cout << "\n10. Testing practical music scenario:" << endl;
    Time currentTime(0, 0, 0);  // Start at beginning
    Playlist album;
    album.addTrack("Introduction");
    album.addTrack("Main Theme");
    album.addTrack("Development");
    album.addTrack("Recapitulation");
    album.addTrack("Finale");
    
    cout << "Now playing: " << album[0] << " at ";
    currentTime.display();
    cout << endl;
    
    // Simulate playing tracks
    for (size_t i = 0; i < album.size(); i++) {
        // Play track (simulated by advancing time)
        ++currentTime; ++currentTime; ++currentTime;  // 3 seconds per track
        cout << "Finished: " << album[i] << " at ";
        currentTime.display();
        cout << endl;
        
        // Prepare for next track
        if (i + 1 < album.size()) {
            cout << "Next up: " << album[i+1] << endl;
        }
    }
    
    return 0;
}
