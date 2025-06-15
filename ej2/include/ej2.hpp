#ifndef EJ2_HPP
#define EJ2_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

constexpr int numDrones = 5;                       //Cantidad de drones y zonas de inerferencia 

class Garage{
    private:
        std::mutex zonasInterferencia[numDrones];  //Mutex para las zonas de interferencia
        std::mutex coutMutex;                      //Mutex para los cout
        std::vector<std::thread> drones;           // Vector de hilos para los drones

    public:
        Garage();
        void iniciarVuelo();
};

#endif