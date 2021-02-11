#include "game.h"
#include <sstream>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}


Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    game= initiateGame(0, h, points, states);
}


//TODO
string Game::writeGame()
{
    BTItrLevel<Circle> it (game);
    string sofi = "";
    while(!it.isAtEnd()){
        if(it.retrieve().getState()){
            sofi += to_string(it.retrieve().getPoints()) + "-" + "true" + "-" + to_string(it.retrieve().getNVisits()) + "\n" ;
            it.advance();
        }
        else
        {
            sofi += to_string(it.retrieve().getPoints()) + "-" + "false" + "-" + to_string(it.retrieve().getNVisits()) + "\n" ;
            it.advance();
        }
    }
    return sofi;
}

//TODO
int Game::move()
{
    int pos=1; int nPoints=-1;
    BTItrLevel<Circle> it(game);
    if (it.isAtEnd()) return nPoints;
    while (true) {
        Circle &c1=it.retrieve();
        bool state=c1.getState();
        int n;
        if (state==false) n=pos;
        else n=pos+1;
        c1.changeState();
        c1.addVisit();
        nPoints=c1.getPoints();
        int i=0;
        while(i<n && !it.isAtEnd()) {
            it.advance();        // advances to left or right child
            i++;
        }
        if (!it.isAtEnd()) pos+=n;
        else break;
    }
    return nPoints;
}


//TODO
int Game::mostVisited()
{
    int sum = 0;
    BTItrLevel<Circle> it(game);
    it.advance();
    while(!it.isAtEnd()){
        if(it.retrieve().getNVisits() > sum){
            sum = it.retrieve().getNVisits();
        }
        it.advance();
    }
    return sum;
}

BinaryTree<Circle> Game::initiateGame(int pos, int level, vector<int> &points, vector<bool> &states) {
    Circle c1(points[pos],states[pos]);
    if (level==0) return BinaryTree<Circle>(c1);
    BinaryTree<Circle> leftChild = initiateGame(2 * pos + 1, level - 1, points, states);
    BinaryTree<Circle> rightChild = initiateGame(2 * pos + 2, level - 1, points, states);
    return BinaryTree<Circle>(c1, leftChild, rightChild);
}
