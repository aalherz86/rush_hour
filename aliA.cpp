// Ali Alherz
/* the debugging steps:
 * 1. recognize that a bug exists.
 * 2. isolate the bad code.
 * 3. fix bad codes.
 * 4. test the source code.
 */

#include "fonts.h"
#include <fstream>
#include <vector>
#include <algorithm> 

using namespace std;

// getting current highscores
vector<int> getHighscore ()
{
	ifstream myfile("highscores.txt");
	vector<int> scores (5);

	for (int i = 0; i < 5; i++)
	{
		myfile >> scores[i];
	}
	return scores;
}

// finding the minimum score
int findMin(vector<int> myVector) 
{     
	int min = myVector[0]; 
	for (size_t i = 1; i < myVector.size(); i++) 
		if (myVector[i] < min) 
			min = myVector[i]; 
	return min; 
} 

// save scores to txt file
void writeScores(int score, vector<int> scores)
{
	int last = findMin(scores); 

	if (score > last)
		scores.push_back (score);

	// sorting in descending order
	sort(scores.begin(), scores.end(), greater<int>());

	// open txt file 
	ofstream myfile ("highscores.txt");

	if (myfile.is_open()) {
		for (auto x : scores) {
			myfile << x <<"\n";
		}
		myfile.close();
	}
}

void showCredit() 
{
	Rect n;

	n.bot = 400;
	n.left = 280;
	n.center = 0;
	ggprint8b(&n, 16, 0x00ffffff, "Ali Alherz");
}

void phpInfo ()
{
	char hostname[255] = "odin.cs.csub.edu";
	char pagename[255] = "/~aalherz/3350/lab3/lab3.php";
}
