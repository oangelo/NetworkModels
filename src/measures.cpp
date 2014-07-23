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

  std::deque<Path> ShortestPaths_Hunger(Vertex& source){
    std::deque<Path> old_paths;
    std::deque<Path> new_paths;
    std::deque<Path> short_paths;
    VertexesSet visited;

    old_paths.push_back(Path({&source}));
    visited.insert(&source);
    while(old_paths.size() != 0){
      while(old_paths.size() != 0){
        Path path(old_paths.back());
        old_paths.pop_back();
        for(Edge& edge: *(path.back())){
          Vertex* vertex(edge.To()); 
          if(visited.find(vertex) == visited.end()){
            Path new_path(NewPath(path, vertex));
            new_paths.push_front(new_path);
            short_paths.push_back(new_path);
          }
        }
      }
      for(Path& v: new_paths){
        visited.insert(v.back());
      }
      old_paths = new_paths;
      new_paths.clear();
    }
    return short_paths;
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

  VertexesSet  PathVertexSet(Path& path, Vertex& n, Vertex& m){
    VertexesSet result;
    for(auto& i: path)
      if(i != &n and i != &m)
        result.insert(i);
    return result;
  }

  PathsMap ShortPaths(Vertex& source, VertexesSet& visited){
    PathsMap map;
    std::deque<Path> paths(network_models::ShortestPaths_Hunger(source));
    for(Path& i: paths){
        if(visited.find(i.back()) == visited.end())
          map[i.back()].push_back(PathVertexSet(i, *i.front(), *i.back()));
    }
    return map;
  }

  void BetweennessCentrality::HungerBetweenness(Network& network){
    VertexesSet visited;
    for(Vertex& i: network){
      betweenness[&i] = 0;
    }
    Network::iterator i;
    for(i = network.begin(); i != network.end(); ++i){
      PathsMap map(ShortPaths((*i), visited));
      for(auto& j: map){
        Paths& paths(j.second);
        for(auto& path_vertex_set: paths)
          for(auto& v: path_vertex_set){
            unsigned count_paths(0);
            for(auto& path: j.second){
              auto v_it(path.find(v));
              if(v_it != path.end()){
                ++count_paths;
              }
            }
            if(count_paths > 0){
              betweenness[v] += static_cast<double>(count_paths) / j.second.size();
            }
          }
      }
      visited.insert(&(*i));
    }
  }

  BetweennessCentrality::BetweennessCentrality(Network& network):betweenness(){
    HungerBetweenness(network);
  }

  double BetweennessCentrality::GetBetweenness(Vertex* v){
    unsigned net_size(betweenness.size());
    double  value(betweenness[v]);
    double norm((net_size - 1.0) * (net_size - 2.0)/ 2.0);
    return value/norm;
  }

} //namespace network_models 
