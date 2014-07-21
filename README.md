NetworkModels
=============

Some simulations to generate networks

******

#Classes: 
Network -> vertex -> edges

- Network class:
Every Algorithm that generates a network should inherit from the Network class.
Every network has vertexes and every vertex has edges.
    - operator[i] -> Return the ith Vertex 

- Vertex class:
The vertexes have connections with other vertexes,
those connections are stored inside the class edges.
    - operator[i] -> ith connected vertex
    - operator(i) -> ith edge
    - vertexes do not accept repeated edges 

- Edge class:
A class that holds information of which is the owner vector an with which other
vertex it has a connection.
This object is need for adding properties to the connection between vertex.

Implemented Networks:

[Erdős–Rényi](http://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model)

[Barabási–Albert](http://en.wikipedia.org/wiki/Barabasi-Albert_model)

[Square-Lattice](http://en.wikipedia.org/wiki/Lattice_graph)

#Network Measures

[k-shell](http://arxiv.org/abs/cs/0310049)
[Betweenness](http://en.wikipedia.org/wiki/Centrality#Betweenness_centrality)

#How to use:

- Link the lib with: -lnetmodels
- The headers are under the folder network_models/
