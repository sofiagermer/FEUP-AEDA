#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game()
{
}

// TODO
Game::Game(list<Kid>& l2)
{
    //o this pointer usamos quando local variable's name é o emsmo que o member's name
    l2 = kids;
}

// TODO
void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const
{
 return kids;
}

// TODO
string Game::write() const
{
    string final = "";
    list<Kid>::const_iterator it;
    if(kids.empty()) return "";
    for(it = kids.begin(); it != kids.end(); it++){
        final += it->getName() + " : " + to_string(it -> getAge()) + "\n";
    }
    return final;
}

// TODO
Kid& Game::loseGame(string phrase) {
    int nr_words = numberOfWords(phrase);
    list<Kid>::const_iterator it;
    int test = 0;
    int index = -1;
    while (kids.size() > 1) {
        //descobrir index da criança a ser removida
        for (int i = 1; i <= nr_words; i++) {
            index++;
            if (index == kids.size()) {
                index = 0;
            }
        }
        //remover criança
        for (it = kids.begin(); it != kids.end(); it++) {
            if (test == index) {
                kids.remove(*it);
                break;
            }
            test++;
        }
        index--;
        test = 0;
    }
    return *kids.begin();
}

// TODO
list<Kid>& Game::reverse()
{
    kids.reverse();
    return kids;
}

//Esta função remove do jogo as crianças de idade superior ao valor aespecificado como parâmetro, eretorna umanovalista com as crianças que foram removidas
list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;
    list<Kid> l1;
    list<Kid>::iterator it = kids.begin();
    list<Kid>::iterator ite = kids.end();
    while ( it != ite )
    {
        if ( it->getAge() > id )
        {
            l1.push_back(*it);
            it=kids.erase(it);
        }
        else
            it++;
    }
    return l1;
    /*list <Kid> :: iterator it;
    for(it = kids.begin(); it != kids.end(); it++){
        if((it -> getAge()) > id){
            res.push_back(*it);
            kids.remove(*it);
            it--;
        }
    }
    return res;*/
}

// TODO
void Game::setKids(const list<Kid>& l1)
{
    list<Kid>::const_iterator i;
    for(i = l1.begin(); i != l1.end(); i++){
        kids.push_back(*i);
    }
}

bool Game::operator==(Game& g2)
{
    if(kids.size() != g2.kids.size()){
        return false;
    }
    list <Kid> :: iterator it;
    list <Kid> :: iterator itg2 = g2.kids.begin();
    for(it = kids.begin(); it != kids.end(); it++){
        if(it -> getName() != itg2 ->getName()){
            return false;
        }
        if(it -> getAge() != itg2 -> getAge()){
            return false;
        }
        itg2++;
    }
    return true;
}

//Esta  função  cria  uma  nova  lista  onde  as  crianças  do  jogosão  colocadas  em  uma  posição  determinada aleatoriamente (use a função rand()para gerar números aleatórios)
list<Kid> Game::shuffle() const
{
    list<Kid> res;
    list <Kid> :: iterator it;
    int child = kids.size();
    while(child != 0){
        int rand = rand() % kids.size();

    }
    return res;
}
