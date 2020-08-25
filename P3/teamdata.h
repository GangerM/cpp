#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include <string>

class TeamData {
 public:
 	TeamData();

	double PutInTree(int i, int j) {
		makefairfactor = winPercentages_[i][j] - 50;
		if(makefairfactor < 0) makefairfactor *= -1;
		return makefairfactor;
 	}
 	void insertWinPercentage(int player1, int player2, double win) {
	    winPercentages_[player1][player2] = win;
	}

 private:
	double** winPercentages_;
 	double makefairfactor;
 	// how far from 50
};

#endif  // _TEAMDATA_H_