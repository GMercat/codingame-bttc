#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Case {
   int mOwner;

   Case (): mOwner (-1) {}

   void setValue (const string& aValue) {
      if (0 == string(".").compare(aValue)) {
         mOwner = -1;
      } else {
         mOwner = std::stoi(aValue);
      }
   }

   bool isMine() {
      return mOwner == 0;
   }

   bool isEmpty() {
      return mOwner == -1;
   }
};

class Plateau {
public:
   Plateau () {}
   void setLine(const int& aIndLine, const string& aLine) {
      for (unsigned int col = 0; col < aLine.length(); ++col) {
         mPlateau[aIndLine][col].setValue(&aLine[col]);
      }
   }

private:
   Case mPlateau[20][35];
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
   Plateau plateau;

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
            plateau.setLine(i, line);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "17 10" << endl; // action: "x y" to move or "BACK rounds" to go back in time
    }
}
