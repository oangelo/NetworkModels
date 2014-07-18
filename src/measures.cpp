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

} //namespace network_models 
