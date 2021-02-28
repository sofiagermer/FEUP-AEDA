#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.word;
}

ostream &operator<<(ostream &os, const WordMeaning &dt) {
    os << dt.getWord() << endl;
    os << dt.getMeaning() << endl;
    return os;
}

bool WordMeaning::operator==(const WordMeaning &wm1) const {
    return word == wm1.word;
}



//TODO

void Dictionary::readDictionary(ifstream &f)
{
     string name, meaning;
     while(!f.eof()){
         getline(f,name);
         getline(f, meaning);
         WordMeaning wm (name,meaning);
         words.insert(wm);
     }
}

//TODO

string Dictionary::searchFor(string word) const
{
    const WordMeaning wordMeaning("","");
    auto val =  words.find(WordMeaning(word,""));
    if (val == wordMeaning) {
        throw WordInexistent(words,word);
    } else {
        return val.getMeaning();
    }
}
//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    const WordMeaning temp("","");
    auto val = words.find(WordMeaning(word, ""));
    if(val == temp){
        WordMeaning wii(word, newMeaning);
        words.insert(wii);
        return false;
    }
    else
    {
        words.remove(val);
        words.insert(WordMeaning(word, newMeaning));
        cout << val.getMeaning();
        return true;
    }
}


//TODO
void Dictionary::print() const
{
    words.printTree();
}


//MANEIRA DA STORA
/*
void Dictionary::print() const
{
    BSTItrIn<WordMeaning> it(words);
    while (!it.isAtEnd())
    {
        cout << it.retrieve().getWord() << endl << it.retrieve().getMeaning() << endl;
        it.advance();
    }

    cout << "novo iterador"<< endl;
    iteratorBST<WordMeaning> it2 = words.begin();
    while (it2!=words.end()) {
        cout << (*it2).getWord() << endl << (*it2).getMeaning() << endl;
        it2++;
    }
*/
