#ifndef KSHELL_H
#define KSHELL_H 

#include "interface.h"

namespace network_models {
  //k-shell algorithm (ref arXiv:cs/0310049v1)
  class Kshell: public Measures{
    public:
      template<typename Node>
      Kshell(Network<Node>& network);
    private:
      template<typename Node>
      void BuildKshell(Network<Node>& network);
  };

  template<typename Node>
  struct Comp 
  {
    Comp(Node* v) : v(v) { }

    bool operator () (std::pair<Node*, unsigned>& p)
    {
      return (p.first == v);
    }
    Node* v;
  };

  template<typename Node>
  void Decrement(Node* vertex, std::vector<std::pair<Node*, unsigned>> &core){
    typename std::vector<std::pair<Node*, unsigned>>::iterator it;
    Node& v(*vertex);
    for(size_t k(0); k < v.size(); ++k){
      it = std::find_if(core.begin(), core.end(), Comp<Node>(&(v[k])));
      if(it != core.end()){
        --(it->second);
      }
    }
  }

  template<typename Node>
  Kshell::Kshell(Network<Node>& network){
    BuildKshell(network);
  }

  template<typename Node>
  void Kshell::BuildKshell(Network<Node>& network){
    typedef std::pair<Node*, unsigned> bin;
    std::vector<bin> core;
    //building the core
    for(typename std::deque<Node>::iterator it(network.begin());
        it != network.end(); ++it){
      core.push_back(bin(&(*it), it->size()));
    }
    std::sort(core.begin(), core.end(), [] (bin a, bin b)
        {return a.second < b.second;});

    //get the vertex within the shell
    unsigned shell(core.begin()->second);
    std::vector<Node*> on_the_shell;
    typedef typename std::vector<bin>::iterator core_it;  
    while(core.size() > 0){
      core_it it(core.begin());
      while(it->second <= shell && it != core.end()){
        map[it->first] = shell;
        Decrement<Node>(it->first, core);
        core.erase(it);
        std::sort(core.begin(), core.end(), [] (bin a, bin b)
            {return a.second < b.second;});
        it = core.begin();
      }
      ++shell;
    }
  }


}

#endif /* KSHELL_H */
