#ifndef BETWEENNES_H
#define BETWEENNES_H 

#include <unordered_set>

#include "../network.h"
#include "interface.h"

namespace network_models{
  typedef std::unordered_set<Vertex*> VertexesSet;
  typedef std::vector<Vertex*> Path;
  typedef std::vector<VertexesSet> Paths;
  typedef std::unordered_map<Vertex*, Paths> PathsMap;

  Paths ShortestPaths(Vertex& begin, Vertex& end, size_t max_iterations);
  std::deque<Path> ShortestPaths_Hunger(Vertex& begin);

  class BetweennessCentrality: public Measures{
    public:
      template<typename Node>
      BetweennessCentrality(Network<Node>& network);
    private:
      template<typename Node>
      void HungerBetweenness(Network<Node>& network);
  };

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

  template<typename Node>
  void BetweennessCentrality::HungerBetweenness(Network<Node>& network){
    VertexesSet visited;
    for(Vertex& i: network){
      map[&i] = 0;
    }
    typename Network<Node>::iterator i;
    for(i = network.begin(); i != network.end(); ++i){
      PathsMap paths_map(ShortPaths((*i), visited));
      for(auto& j: paths_map){
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
              map[v] += static_cast<double>(count_paths) / j.second.size();
            }
          }
      }
      visited.insert(&(*i));
    }
  }


  template<typename Node>
  BetweennessCentrality::BetweennessCentrality(Network<Node>& network):Measures(){
    HungerBetweenness(network);
    //normalizing 
    unsigned net_size(network.size());
    double norm((net_size - 1.0) * (net_size - 2.0)/ 2.0);
    for(Vertex& v: network)
      map[&v] = map[&v] / norm;
  }



} //namespace network_model

#endif /* BETWEENNES_H */
