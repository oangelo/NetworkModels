NetworkModels
=============

Some simulations to generate networks

******

#Classes: 
Network -> vertex -> edges

- Network class:
Every Algorithm that generates a network should inherit from the Network class.
Every network has vertexes and every vertex has edges.
    - operator[i] -> list of vertex pointed by ith element

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

To be implemented:

[Barabási–Albert](http://en.wikipedia.org/wiki/Barabasi-Albert_model)

