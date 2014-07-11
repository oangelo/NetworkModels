#include "network.h"

Network::Network(unsigned size, std::string model_name)
:vertexes(size), model_name(model_name), kshell(){}

unsigned Network::size() const{
    return vertexes.size();
}

Vertex& Network::operator[](unsigned index){
    return vertexes[index];
}

const std::deque<Vertex> Network::get_vertexes() {
    return vertexes;
}

Vertex* Network::NewVertex(){
    vertexes.push_back(Vertex());
    return (&vertexes.back());
}

void Network::CreateEdge(Vertex* v1, Vertex* v2) {
    v1->Add(Edge(v1, v2, true));
    v2->Add(Edge(v2, v1, true));
}

std::string Network::GetModelName(){
    return model_name;
}


double Network::GetMeanConnectivity(){
    unsigned sum(0);
    for(Vertex& v: vertexes)
        sum += v.size();
    return static_cast<double>(sum) / vertexes.size();
}

Network::~Network(){}


std::vector<bin> NodesDistribution(Network& network){
    std::vector<unsigned> edge_amount; 
    std::vector<bin> result;
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
        result.push_back(bin(i+1, histogram[i]));
    return(result);
}

void Graphviz(Network& network, std::string file_name){
    typedef std::pair<const Vertex*, const Vertex*> key;
    std::set<key> set;
    std::ofstream file;
    file.open(file_name);

    file << "graph G {" << std::endl;
    for (size_t i = 0; i < network.size(); ++i) {
        for (size_t j = 0; j < network[i].size(); ++j) {
            if(set.find(key(&network[i][j], &network[i][j])) == set.end()){
                file << "\"" << network[i](j).From() << "\"" << " -- " << "\"" << network[i](j).To() << "\""<< std::endl; 
                set.insert(key(network[i](j).From(), network[i](j).To()));
                set.insert(key(network[i](j).To(), network[i](j).From()));
            }
        }
    }

    file << "}" << std::endl;

    file.close();
}

std::set<Vertex*> Burn(Vertex* vertex){
    bool has_neighbors = true;
    std::set<Vertex*> cluster;
    std::vector<Vertex*> to_search;
    to_search.push_back(vertex);
    int mark = vertex->GetMark();
    while(has_neighbors){
        cluster.insert(to_search[to_search.size() - 1]);
        Vertex& fire(*to_search[to_search.size() - 1]);
        to_search.pop_back();
        for(size_t i(0); i < fire.size(); ++i){
            if(fire[i].GetMark() == mark && (cluster.find(&fire[i]) == cluster.end())){
                to_search.push_back(&fire[i]);
            }
        }
        if(to_search.size() == 0)
            has_neighbors = false;
    }
    return cluster;
}


std::map<int,std::vector<unsigned>> Clusters(Network& network){
    std::map<int, std::vector<unsigned>> size; 
    std::set<Vertex*> burnt; 

    std::set<int> mark_set;
    for(size_t i(0); i < network.size(); ++i){ 
        mark_set.insert(network[i].GetMark());
    }
    for(int i: mark_set){
        std::vector<unsigned> aux;
        size.insert(std::pair<int, std::vector<unsigned>>(i, aux));
    }

    for(size_t i(0); i < network.size(); ++i){ 
        if(burnt.find(&network[i]) == burnt.end()){
            std::set<Vertex*> cluster(Burn(&network[i])); 
            size[network[i].GetMark()].push_back(cluster.size());
            burnt.insert(cluster.begin(), cluster.end());
        }
    }
    return(size);

}

struct Comp 
{
    Comp(Vertex* v) : v(v) { }

    bool operator () (std::pair<Vertex*, unsigned>& p)
    {
        return (p.first == v);
    }
    Vertex* v;
};

void Decrement(Vertex* vertex, std::vector<std::pair<Vertex*, unsigned>> &core){
  std::vector<std::pair<Vertex*, unsigned>>::iterator it;
  Vertex& v(*vertex);
  for(size_t k(0); k < v.size(); ++k){
    it = std::find_if(core.begin(), core.end(), Comp(&(v[k])));
    if(it != core.end()){
      --(it->second);
    }
  }
}

void Network::BuildKshell(){
//  for(auto& i: vertexes){
//      std::cout <<  &i;
//      for(size_t j(0); j < i.size(); ++j)
//        std::cout << " " << &i[j];
//      std::cout << std::endl;
//  }
  typedef std::pair<Vertex*, unsigned> bin;
  std::vector<bin> core;
  //building the core
  for(std::deque<Vertex>::iterator it(vertexes.begin());
      it != vertexes.end(); ++it){
    core.push_back(bin(&(*it), it->size()));
  }
  std::sort(core.begin(), core.end(), [] (bin a, bin b)
      {return a.second < b.second;});

//  for(std::vector<bin>::iterator it(core.begin());
//      it != core.end(); ++it){
//    std::cout << it->first << " " << it->second << std::endl;
//  }

  //get the vertex within the shell
  unsigned shell(core.begin()->second);
  std::vector<Vertex*> on_the_shell;
  typedef std::vector<bin>::iterator core_it;  
  while(core.size() > 0){
    core_it it(core.begin());
    while(it->second <= shell && it != core.end()){
      kshell[it->first] = shell;
      Decrement(it->first, core);
      core.erase(it);
      std::sort(core.begin(), core.end(), [] (bin a, bin b)
          {return a.second < b.second;});
      it = core.begin();
//      std::cout << std::endl;
//          for(std::vector<bin>::iterator it(core.begin());
//              it != core.end(); ++it){
//            std::cout << it->first << " " << it->second << std::endl;
//          }
    }
    ++shell;
  }
}

unsigned Network::GetKshellVertexes(Vertex* target){
  if(kshell.size() == 0){
    BuildKshell();
  } 
  return kshell[target];
}
