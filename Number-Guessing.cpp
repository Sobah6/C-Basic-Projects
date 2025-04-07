#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed RNG
    int secret = rand() % 100 + 1; // Random number between 1 and 100
    int guess;
    int tries = 0;

    cout << "🎲 Welcome to the Number Guessing Game!\n";
    cout << "I'm thinking of a number between 1 and 100.\n";

    do {
        cout << "Enter your guess: ";
        cin >> guess;
        ++tries;

        if (guess < secret) {
            cout << "Too low! Try again.\n";
        } else if (guess > secret) {
            cout << "Too high! Try again.\n";
        } else {
            cout << "🎉 Congrats! You guessed it in " << tries << " tries.\n";
        }

    } while (guess != secret);

    return 0;
}
