#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace std;

class Bike {
public:
    int position;
    char symbol;

    Bike(char s) : symbol(s), position(0) {}

    void move() {
        position += 1;
    }
};

void drawGame(const Bike& player1, const Bike& player2) {
    system("cls");  // Clear the console

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            if (i == 0 || i == 19) {
                cout << "-";
            } else if (j == 0 || j == 39) {
                cout << "|";
            } else if (j == player1.position && i == 18) {
                cout << player1.symbol;
            } else if (j == player2.position && i == 18) {
                cout << player2.symbol;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    Bike player1('A');
    Bike player2('B');

    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a') {
                player1.move();
            }
            if (key == 'l') {
                player2.move();
            }
        }

        drawGame(player1, player2);

        // Check for win condition
        if (player1.position == 38) {
            cout << "Player 1 wins!" << endl;
            break;
        }
        if (player2.position == 38) {
            cout << "Player 2 wins!" << endl;
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(100));  // Delay to control game speed
    }

    return 0;
}
