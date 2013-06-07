NetworkModels
=============

Some simulations to generate networks

******

#Classes: 

- Network class:
Every Algorithm that generates a network should inherit from the Network class.
Every network has vertexes and every vertexes has edges.
Network -> vertex -> edges 

- Vertex class:
The vertexes has some connections with other vertexes.
Those connections are stored inside the class edges.

- Edge class:
A class that holds information of which is the owner vector an with which other
vertex it has a connection.

Implemented Networks:

[Erdős–Rényi](http://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model)

To be implemented:

[Barabási–Albert](http://en.wikipedia.org/wiki/Barabasi-Albert_model)

