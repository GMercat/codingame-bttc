#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int Largeur = 35;
int Hauteur = 35;

struct Coord {
   Coord(const int& aX, const int& aY) : mX(aX), mY(aY) {};
   int mX;
   int mY;
};

struct Opponent {
   typedef vector<Opponent> Vect;
   Opponent(const int& aId, const int& aX, const int& aY, const int& abBackInTimeLeft) :
      mId (aId), mCoord (Coord(aX, aY)), mbBackInTimeLeft (abBackInTimeLeft==1) {}
   int   mId;
   Coord mCoord;
   bool  mbBackInTimeLeft;
};

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

   bool isMine () const {
      return mOwner == 0;
   }

   bool isEmpty () const {
      return mOwner == -1;
   }
};

class Plateau {
public:
   Plateau () {}

   const Case& getCase(const int& aX, const int& aY) const{
      return mPlateau[aY][aX];
   }

   const Case& getCase (const Coord& aCoord) const{
      return mPlateau[aCoord.mY][aCoord.mX];
   }

   void setLine (const int& aIndLine, const string& aLine) {
      for (unsigned int col = 0; col < aLine.length(); ++col) {
         mPlateau[aIndLine][col].setValue(&aLine[col]);
      }
   }

   int getNbEmptyCase (const Coord& aCoord1, const Coord& aCoord2) const {
      int counter = 0;
      for (int y = aCoord1.mY; y <= aCoord2.mY; ++y) {
         for (int x = aCoord1.mX; x <= aCoord2.mX; ++x) {
            if (getCase(x, y).isEmpty()) {
               ++counter;
            }
         }
      }
      return counter;
   }

   Coord getNearCorner (const Coord& aCoord) {
      Coord Result(0, 0);
      if (aCoord.mX > (Largeur/2 + 1)) {
         if (aCoord.mY > (Largeur/2 + 1))
         {
            Result = Coord (Largeur, Hauteur);
         } else {
            Result = Coord (Largeur, 0);
         }
      } else {
         if (aCoord.mY > (Largeur/2 + 1))
         {
            Result = Coord (0, Hauteur);
         } else {
            Result = Coord (0, 0);
         }
      }
      return Result;
   }

   int distance (const Coord& aCoord1, const Coord& aCoord2) {
      // TODO
      return 1;
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
   Opponent::Vect opponents;
   Plateau plateau;

   int opponentCount; // Opponent count
   cin >> opponentCount; cin.ignore();
   opponents.reserve(opponentCount);

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
         opponents[i] = Opponent(i, opponentX, opponentY, opponentBackInTimeLeft);
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
