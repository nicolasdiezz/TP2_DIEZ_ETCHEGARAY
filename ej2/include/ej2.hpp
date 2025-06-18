#ifndef EJ2_HPP
#define EJ2_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
using namespace std;

constexpr int numDrones = 5;  //Cantidad de drones y zonas de inerferencia, se puede cambair segun lo pedido

class Garage{
    private:
        mutex zonasInterferencia[numDrones];  //Mutex para las zonas de interferencia
        mutex coutMutex;                      //Mutex para los cout
        vector<std::thread> drones;           // Vector de hilos para los drones

    public:
        Garage();                            
        void iniciarVuelo();
};

#endif