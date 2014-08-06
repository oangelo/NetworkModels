#include "kshell.h"

namespace network_models {

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

  Kshell::Kshell(Network& network){
    BuildKshell(network);
  }

  void Kshell::BuildKshell(Network& network){
    typedef std::pair<Vertex*, unsigned> bin;
    std::vector<bin> core;
    //building the core
    for(std::deque<Vertex>::iterator it(network.begin());
        it != network.end(); ++it){
      core.push_back(bin(&(*it), it->size()));
    }
    std::sort(core.begin(), core.end(), [] (bin a, bin b)
        {return a.second < b.second;});

    //get the vertex within the shell
    unsigned shell(core.begin()->second);
    std::vector<Vertex*> on_the_shell;
    typedef std::vector<bin>::iterator core_it;  
    while(core.size() > 0){
      core_it it(core.begin());
      while(it->second <= shell && it != core.end()){
        map[it->first] = shell;
        Decrement(it->first, core);
        core.erase(it);
        std::sort(core.begin(), core.end(), [] (bin a, bin b)
            {return a.second < b.second;});
        it = core.begin();
      }
      ++shell;
    }
  }

}
