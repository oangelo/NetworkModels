#include "erdos-renyi.h"

ErdosRenyi::ErdosRenyi(unsigned nodes, unsigned edges)
:random_device(), random_gen(random_device()), Network(nodes)
{

}
