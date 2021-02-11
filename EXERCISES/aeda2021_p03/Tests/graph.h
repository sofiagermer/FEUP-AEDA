#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges; // PARA CADA NÓ EXISTE UM VETOR DE ARESTAS
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes; //CADA ELEMENTO DA CLASSE DE GRAFOS APONTA PARA UM VETOR DE NÓS
public:
    Graph(){};
    ~Graph(){
        for(auto c : nodes){
            delete c;
        }
    };
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
//    Graph & removeEdge(const N &begin, const N &end);
//    E & edgeValue(const N &begin, const N &end);
   unsigned numEdges(void) const{
       int aux = 0;
       for(auto const c: nodes){
           aux += (c) ->edges.size();
       }
   }
    unsigned numNodes(void) const{
       int const aux = nodes.size();
       return aux;
    };
//    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template <class N, class E>
Graph<N, E> & Graph<N,E>::addNode(const N &inf) {
    /*for(auto c: nodes){ // VER SE O NÓ JÁ EXISTE
        if(c -> info == inf){
            throw NodeAlreadyExists<N>(inf);
        }
        //nodes é um vetor de pointes e inf é passado por referência
        Node<N,E> *new_node = new Node<N,E>(inf);
        nodes.push_back(new_node);
        return *this;
    }*/
    typename vector< Node<N,E> *>::const_iterator it;
    // see if node already exists and throws exception
    for (it = nodes.begin(); it != nodes.end(); it++) {
        if ((*it)->info == inf) throw NodeAlreadyExists<N>(inf);
    }
    Node<N,E> *no1 = new Node<N,E>(inf);
    nodes.push_back(no1);
    return *this;
}

template<class N, class E>
Graph<N, E> & Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
    // see the nodes vector for node where info= begin
    typename vector< Node<N,E> *>::iterator it;
    typename vector< Edge<N,E> >::iterator itedge;
    bool foundBegin = false;
    bool foundEnd = false;

    Node<N,E> *noBegin_apt=NULL;
    Node<N,E> *noEnd_apt=NULL;

    for (it = nodes.begin(); it != nodes.end(); it++)
    {
        // search vector nodes for node where info=begin
        if ( (*it)->info == begin )
        {
            // verifiy if vector edges already has an edge where destination=end
            foundBegin = true;
            noBegin_apt=*it;
            for (itedge = (*it)->edges.begin();  itedge != (*it)->edges.end(); itedge++)
            {
                // throw exception if edge already exists
                if ( itedge->destination->info == end) throw EdgeAlreadyExists<N> (begin, end);
            }
            if (foundEnd==true) break;
        }
        else if ( (*it)->info == end ) {
            foundEnd=true;
            noEnd_apt=*it;
            if (foundBegin==true) break;
        }
    }

    // if one of the nodes was not found, throws an exception
    if (!foundBegin) throw NodeDoesNotExist<N>(begin);
    if (!foundEnd) throw NodeDoesNotExist<N>(end);

    // creates a new Edge
    Edge<N,E> edge1(noEnd_apt, val);
    // add to edges vector
    noBegin_apt->edges.push_back(edge1);

    return *this;
}
