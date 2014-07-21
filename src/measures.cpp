#include "measures.h"

namespace network_models{

  inline Path NewPath(Path path, Vertex*& new_vertex){
    path.push_back(new_vertex);
    return path;
  }

  inline VertexesSet ToSet(Path& path){ 
    VertexesSet aux;
    for(Vertex*& i: path){
      aux.insert(i);
    }
    return aux;
  }

  Paths ShortestPaths(Vertex& begin, Vertex& end, size_t max_iterations){
    std::deque<Path> old_paths;
    std::deque<Path> new_paths;
    
    Paths short_paths;
    VertexesSet visited;
    Path path;
    bool found(false);

    path.push_back(&begin);
    old_paths.push_back(path);
    size_t counter(0);
    while(!found and old_paths.size() > 0){
      while(old_paths.size() > 0){
        path = old_paths.back();
        old_paths.pop_back();
        for(Edge& edge: *(path.back())){
          Vertex* vertex(edge.To()); 
          if(visited.find(vertex) == visited.end()){
            Path new_path(NewPath(path, vertex));
            new_paths.push_front(new_path);
            if(vertex == &end){
              found = true;   
              short_paths.push_back(ToSet(new_path));
            }else{
              visited.insert(vertex);
            }
          }
        }
      }
      old_paths = new_paths;
      new_paths.clear();

      ++counter;
      if(max_iterations == counter){
        std::cerr << "Can't find minimum path" << std::endl;
        break;
      }
    }
    return short_paths;
  }

  AllShortestPaths::AllShortestPaths(Network& network){
    Network::iterator i,j;
    for(i = network.begin(); i < network.end(); ++i)
      for(j = (i+1); j < network.end(); ++j){
        all_spaths[&(*i)][&(*j)] = network_models::ShortestPaths(*i, *j, network.size()); 
      }
  }

  Paths AllShortestPaths::GetPaths(Vertex& a, Vertex& b){
    if(all_spaths.find(&a) != all_spaths.end()){
      return all_spaths[&a][&b];
    }else{
      return all_spaths[&b][&a];
    }
  }

std::unordered_set<Vertex*> PathVertexSet(Paths& paths, Vertex& n, Vertex& m){
  std::unordered_set<Vertex*> result;
  for(auto& i: paths)
    for(auto& j: i)
      if(j != &n and j != &m)
        result.insert(j);
  return result;
}

void BetweennessCentrality::HungerBetweenness(Network& network, AllShortestPaths& paths){
    unsigned aux(0);
    for(Vertex& i: network){
      betweenness[&i] = std::make_pair(aux, aux);
    }
    Network::iterator i, j;
    for(i = network.begin(); i != network.end(); ++i){
      for(j = (i + 1); j != network.end(); ++j){
        Paths shortest(paths.GetPaths(*i, *j));
        std::unordered_set<Vertex*> path_vertex_set(PathVertexSet(shortest, *i, *j));
        for(auto& v: path_vertex_set){
          unsigned count_paths(0);
          for(auto& path: shortest){
            auto v_it(path.find(v));
            if(v_it != path.end()){
              ++count_paths;
            }
          }
          if(count_paths > 0){
            betweenness[v].first += count_paths;
            betweenness[v].second += shortest.size();
          }
        }
      }
    }
  }

  BetweennessCentrality::BetweennessCentrality(Network& network, AllShortestPaths& paths){
    HungerBetweenness(network, paths);
  }

  double BetweennessCentrality::GetBetweenness(Vertex* v){
    unsigned net_size(betweenness.size());
    double value(0);
    if(betweenness[v].second > 0)
      value = (static_cast<double>(betweenness[v].first) / betweenness[v].second);
    double norm((net_size - 1.0) * (net_size - 2.0)/ 2.0);
    return value/norm;
  }

} //namespace network_models 
