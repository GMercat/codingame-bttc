#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int opponentCount; // Opponent count
    cin >> opponentCount; cin.ignore();

    // game loop
    while (1) {
        int gameRound;
        cin >> gameRound; cin.ignore();
        int x; // Your x position
        int y; // Your y position
        int backInTimeLeft; // Remaining back in time
        cin >> x >> y >> backInTimeLeft; cin.ignore();
        for (int i = 0; i < opponentCount; i++) {
            int opponentX; // X position of the opponent
            int opponentY; // Y position of the opponent
            int opponentBackInTimeLeft; // Remaining back in time of the opponent
            cin >> opponentX >> opponentY >> opponentBackInTimeLeft; cin.ignore();
        }
        for (int i = 0; i < 20; i++) {
            string line; // One line of the map ('.' = free, '0' = you, otherwise the id of the opponent)
            cin >> line; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "17 10" << endl; // action: "x y" to move or "BACK rounds" to go back in time
    }
}
