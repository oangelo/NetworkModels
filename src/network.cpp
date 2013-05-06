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

Vertex* Network::NewVertex(){
    vertexes.push_back(Vertex());
    return &vertexes[vertexes.size() - 1];
}

void Network::CreateEdge(Vertex* v1, Vertex* v2) {
    v1->Add(Edge(v1, v2, true));
    v2->Add(Edge(v2, v1, true));
}

Network::~Network(){}


void NodesDistribution(Network& network){
    std::vector<unsigned> edge_amount; 
    for (size_t i = 0; i < network.size(); ++i) {
        edge_amount.push_back(network[i].size());
    }
    unsigned max(*std::max_element(edge_amount.begin(), edge_amount.end()));
    std::vector<unsigned> histogram(max, 0); 
    for (size_t i = 0; i < edge_amount.size(); ++i) {
        if(edge_amount[i] > 0)
            ++histogram[edge_amount[i] - 1];
    }
    for (size_t i = 0; i < histogram.size(); ++i) 
        std::cout << histogram[i] << std::endl;
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
