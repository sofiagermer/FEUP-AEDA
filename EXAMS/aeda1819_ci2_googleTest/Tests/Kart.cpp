#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{

	vector<CKart> vord;

	for(auto & p: pistasG){
	    for(auto k: p.getFrotaActual()){
	        vord.push_back(k);
	    }
	}
	auto comp = [](CKart ck1, CKart ck2){
	    return ck1.getNumero() < ck2.getNumero();
	};
	sort(vord.begin(), vord.end(), comp);
	return vord;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    /*
    int total = 0;
    for(auto  p: pistasG) {
        for( auto k: p.getKartsAvariados()){
            if(k.getCilindrada() == cilind){
                total++;
            }
        }
    }
    return total;*/
    int counter = 0;
    for(auto elem: pistasG){
        for(auto kart: elem.getKartsAvariados())
            if( ((int) kart.getCilindrada()) == cilind)
                counter++;
    }
    return counter;
}

//Exercicio 1 c)
/*
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    int aux = 0;
    for(auto p: frotaKartsPista){
        if(aux < numeroKarts){
            if((!p.getAvariado()) && p.getCilindrada() == cilind){
                aux++;
                kartsLinhaPartida.push(p);
            }
        }
    }
    if(aux == numeroKarts){
        return true;
    }
    else{
        for(auto p: frotaKartsPista){
            if(!p.getAvariado()){
                kartsEmProva.push_back(p);
            }
        }
        return false;
    }
}*/
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    for(auto& elem: frotaKartsPista){
        if(numeroKarts){
            if(!elem.getAvariado() && elem.getCilindrada() == cilind){
                kartsLinhaPartida.push(elem);
                numeroKarts--;
            }
        }
        if(!numeroKarts)
            return true;
    }
    return false;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    return 0;
}

