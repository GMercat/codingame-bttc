#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int Largeur = 35;
int Hauteur = 35;

struct Coord {
   Coord(const int& aX, const int& aY) : mX(aX), mY(aY) {};
   string getCoordStr () {
      stringstream coordSStr;
      coordSStr << mX << " " << mY;
      return coordSStr.str ();
   }

   bool operator == (const Coord& aCoord) {
      return aCoord.mX == mX && aCoord.mY == mY;
   }

   bool operator != (const Coord& aCoord) {
         return aCoord.mX != mX || aCoord.mY != mY;
      }

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
      } else if (0 == string("0").compare(aValue)) {
         mOwner = 0;
      } else if (0 == string("3").compare(aValue)) {
         mOwner = 1;
      } else if (0 == string("2").compare(aValue)) {
         mOwner = 2;
      } else if (0 == string("2").compare(aValue)) {
         mOwner = 2;
      }
   }

   bool isMine () const {
      return mOwner == 0;
   }

   bool isEmpty () const {
      return mOwner == -1;
   }
};

class Board {
public:
   Board () {
      for (int y = 0; y < Hauteur; ++y) {
         vector<Case> line;
         for (int x = 0; x <= Largeur; ++x) {
            line.push_back(Case());
         }
      mPlateau.push_back(line);
      }
   }
   Case& getCase(const int& aX, const int& aY) {
      return mPlateau[aY][aX];
   }

   const Case& getCase(const int& aX, const int& aY) const{
      return mPlateau[aY][aX];
   }

   const Case& getCase (const Coord& aCoord) const{
      return mPlateau[aCoord.mY][aCoord.mX];
   }

   void setLine (const int& aIndLine, const string& aLine) {
      for (unsigned int col = 0; col < aLine.length(); ++col) {
         getCase(col, aIndLine).setValue(aLine.substr(col,1));
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

   bool isEmpty (const Coord& aCoord1, const Coord& aCoord2) const {
      bool bEmpty = true;
      int x = aCoord1.mX;
      int y = aCoord1.mY;
      while (bEmpty == true && y <= aCoord2.mY) {
         while (bEmpty == true && x <= aCoord2.mX) {
            bEmpty = getCase(x, y).isEmpty();
            ++x;
         }
         ++y;
      }
      return bEmpty;
   }

   bool isEmptyOrMine (const Coord& aCoord1, const Coord& aCoord2) const {
      bool bEmptyOrMine = true;
      int x = aCoord1.mX;
      int y = aCoord1.mY;
      while (bEmptyOrMine == true && y <= aCoord2.mY) {
         while (bEmptyOrMine == true && x <= aCoord2.mX) {
            bEmptyOrMine = getCase(x, y).isEmpty() || getCase(x, y).isMine();
            ++x;
         }
         ++y;
      }
      return bEmptyOrMine;
   }

private:
    vector <vector <Case> > mPlateau;
};

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

Coord getOpposedCorner (const Coord& aCoord) {
   Coord Result(0, 0);
   if (aCoord.mX > (Largeur/2 + 1)) {
      if (aCoord.mY > (Largeur/2 + 1))
      {
         Result = Coord (0, 0);
      } else {
         Result = Coord (0, Hauteur);
      }
   } else {
      if (aCoord.mY > (Largeur/2 + 1))
      {
         Result = Coord (Largeur, 0);
      } else {
         Result = Coord (Largeur, Hauteur);
      }
   }
   return Result;
}

int distance (const Coord& aCoord1, const Coord& aCoord2) {
   return abs(aCoord1.mX - aCoord2.mX) + abs(aCoord1.mY - aCoord2.mY);
}

Coord strategyFearful (Board& aBoard, const Opponent::Vect& aOpponents) {
   int maxDist = 10;
   string target;
   Coord myCoord = aOpponents[0].mCoord;
   int bestScore = 0;
   Coord bestCoord (0, 0);
   //int scoreBoard[Hauteur][Largeur];
   for (int y=0; y<Hauteur; y++) {
      for (int x=0; x<Largeur; x++) {
         int score = 0;
         const Case& currentCase    = aBoard.getCase (x, y);
         const Coord currentCoord   = Coord (x, y);
         const int   distToMe       = distance (myCoord, currentCoord);
         cerr << "CurrenCase(" << currentCase.mOwner << ")" << endl;
         if (currentCase.isEmpty ()) {
            if (aBoard.isEmpty (myCoord, currentCoord)) {
               if (distToMe <= maxDist) {
                  score = distToMe;
               } else if (distToMe < (2 * maxDist)) {
                  score = (2*maxDist) - distToMe;
               } else {
                  score = 1;
               }
            } else if (aBoard.isEmptyOrMine (myCoord, currentCoord)) {
               if (distToMe <= maxDist) {
                  score = distToMe - 0.5;
               } else if (distToMe < (2 * maxDist)) {
                  score = (2*maxDist) - distToMe - 0.5;
               } else {
                  score = 0.5;
               }
            } else {
               score = 1;
            }
         }
         //scoreBoard[y][x] = score;
         if (score > bestScore) {
            bestScore = score;
            bestCoord = Coord (x, y);
         }
      }
   }

   return bestCoord;
}

//
Coord originCoord (0, 0);
Coord targetCoord (0, 0);

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
   Opponent::Vect opponents;
   Board board;

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
         opponents.push_back(Opponent(i, opponentX, opponentY, opponentBackInTimeLeft));
      }
      for (int i = 0; i < 20; i++) {
         string line; // One line of the map ('.' = free, '0' = you, otherwise the id of the opponent)
         cin >> line; cin.ignore();
         board.setLine(i, line);
      }

      // Write an action using cout. DON'T FORGET THE "<< endl"
      // To debug: cerr << "Debug messages..." << endl;
      string targetStr;
      if (gameRound == 1) {
         targetCoord = strategyFearful (board, opponents);
      } else {
         if (targetCoord == opponents[0].mCoord && targetCoord != originCoord) {
            targetCoord = originCoord;
         } else if (targetCoord == opponents[0].mCoord) {
            targetCoord = strategyFearful (board, opponents);
         }
      }

      targetStr = targetCoord.getCoordStr ();
      cout << targetStr << endl; // action: "x y" to move or "BACK rounds" to go back in time
   }
}

