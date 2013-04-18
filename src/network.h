#ifndef NETWORK_H
#define NETWORK_H 
class Host{
    public:
        Host();
        Host& operator++();
        operator unsigned();
    private:
        unsigned connections;
};
#endif /* NETWORK_H */
