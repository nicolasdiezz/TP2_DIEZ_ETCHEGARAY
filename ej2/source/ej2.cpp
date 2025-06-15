#include "../include/ej2.hpp"

Garage ::Garage(){
    // No es necesario inicializar los mutex, ya que el constructor por defecto del mutex lo hace automáticamente.
    // El vector de hilos lo inicializo vacío y lo lleno despues en iniciarVuelo.
}

void Garage:: iniciarVuelo(){
    for(int i = 0; i < numDrones; i++){
        drones.emplace_back([this, i]() {
            int zonaIzq = i;
            int zonaDer = (i + 1) % numDrones;

            {
                std::lock_guard<std::mutex> lockCout(coutMutex);                 // Bloqueo el mutex de cout para que no se mezcle con otros cout
                std::cout << "Dron " << i << " esperando para despegar...\n";
            }

            std::lock(zonasInterferencia[zonaIzq], zonasInterferencia[zonaDer]); // Bloqueo ambas zonas al mismo tiempo

            // Desde acá los mutex ya están bloqueados manualmente
            {
                std::lock_guard<std::mutex> lockCout(coutMutex);
                std::cout << "Dron " << i << " despegando...\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulo el despegue

            {
                std::lock_guard<std::mutex> lockCout(coutMutex);
                std::cout << "Dron " << i << " alcanzó altura de 10m\n";
            }
            
            //Libero los mutex manualmente
            zonasInterferencia[zonaIzq].unlock();
            zonasInterferencia[zonaDer].unlock();
        });
    }
}
