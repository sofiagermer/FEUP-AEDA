#include "player.h"

//TODO

void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

//TODO
unsigned Player::betsInNumber(unsigned num) const
{
    unsigned sum = 0;
	for(auto x: bets){
	    for(auto y: x.getNumbers()){
	        if(y == num){
	            sum++;
	        }
	    }
	}
	return sum;
}

//TODO
tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
	for(auto y :bets){
	    if(y.countRights(draw) > 3){
	        res.insert(y);
	    }
	}
	return res;
}
