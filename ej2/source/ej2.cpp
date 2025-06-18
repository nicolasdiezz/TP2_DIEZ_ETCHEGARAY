#include "../include/ej2.hpp"


Garage ::Garage(){
    // No inicializo los mutex, porque el constructor por defecto del mutex lo hace automáticamente.
    // El vector de hilos lo inicializo vacío y lo lleno despues en iniciarVuelo.
}

// El método iniciarVuelo crea un hilo por cada dron, y cada hilo simula el vuelo de un dron.
void Garage:: iniciarVuelo(){
    for(int i = 0; i < numDrones; i++){
        drones.emplace_back([this, i]() {
            int zonaIzq = i;
            int zonaDer = (i + 1) % numDrones;

            {
                lock_guard<std::mutex> lockCout(coutMutex);                 // Bloqueo el mutex de cout para que no se mezcle con otros cout
                cout << "Dron " << i << " esperando para despegar..." << endl;
            }

            lock(zonasInterferencia[zonaIzq], zonasInterferencia[zonaDer]); // Bloqueo ambas zonas al mismo tiempo

            // Desde acá los mutex ya están bloqueados manualmente
            {
                lock_guard<std::mutex> lockCout(coutMutex);
                cout << "Dron " << i << " despegando..." << endl;
            }

            this_thread::sleep_for(std::chrono::seconds(5));  // Simulo el despegue

            {
                lock_guard<std::mutex> lockCout(coutMutex);
                cout << "Dron " << i << " alcanzó altura de 10m"<< endl;
            }

            //Libero los mutex manualmente
            zonasInterferencia[zonaIzq].unlock();
            zonasInterferencia[zonaDer].unlock();
        });
    }
    for(auto& dron : drones) {
        dron.join();          // Espero a que todos los drones terminen su vuelo
    }

    {
        lock_guard<std::mutex> lockCout(coutMutex);
        cout << "===============================" << endl;
        cout << "SE TERMINO TODA LA SIMULACIÓN" << endl;

    }
}
