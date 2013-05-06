#include "network.h"

Network::Network(unsigned size)
:vertexes(size){}

unsigned Network::size() const{
    return vertexes.size();
}

Vertex& Network::operator[](unsigned index){
    return vertexes[index];
}

const std::vector<Vertex> Network::get_vertexes() {
    return vertexes;
}

void Network::CreateEdge(Vertex* v1, Vertex* v2) {
    v1->Add(Edge(v1, v2, true));
    v2->Add(Edge(v2, v1, true));
}

Network::~Network(){}


void NodesDistribuition(Network& network){
    
}

void Graphviz(Network& network, std::string file_name){
    typedef std::pair<Vertex*,Vertex*> key;
    std::set<key> set;
    std::ofstream file;
    file.open(file_name);

    file << "graph G {" << std::endl;
    for (size_t i = 0; i < network.size(); ++i) {
        for (size_t j = 0; j < network[i].size(); ++j) {
            if(set.find(key(network[i][j].From(), network[i][j].To())) == set.end()){
                file << "\"" << network[i][j].From() << "\"" << " -- " << "\"" << network[i][j].To() << "\""<< std::endl; 
                set.insert(key(network[i][j].From(), network[i][j].To()));
                set.insert(key(network[i][j].To(), network[i][j].From()));
            }
        }
    }

    file << "}" << std::endl;

    file.close();
}
