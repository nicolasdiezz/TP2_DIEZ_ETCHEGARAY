#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

struct Tarea { //creamos un struct para las tareas
    int idsensor;
    int idtarea;
    string descripcion_tarea;
};

queue<Tarea> cola;
mutex mtx;             // Mutex para proteger la cola de tareas
mutex cout_mtx;        // Mutex para proteger los cout
condition_variable cv; // Variable de condición para notificar a los robots

bool terminado = false; // Variable para indicar si todos los sensores terminaro
int sensores_terminados = 0; // Contador de sensores que han terminado, se pueden cambiar según lo pedido
const int NUM_SENSORES = 3; // Número de sensores, se pueden cambiar según lo pedido
const int NUM_ROBOTS = 3; // Número de robots, se pueden cambiar según lo pedido

//Funcion de los sensores: generan tareas y las ponen en la cola
void sensor(int id) {
    for (int i = 1; i <= NUM_SENSORES; ++i) {
        {
            lock_guard<mutex> lg(mtx);                       // Bloquea el mutex para acceder a la cola
            Tarea tarea{id, i, "Tarea generada por sensor " + to_string(id) + ", nro: " + to_string(i)}; // Crea una tarea
            cola.push(tarea);
        }
        {
            lock_guard<mutex> lg(cout_mtx); // Bloquea el mutex para los cout
            cout << "[Sensor " << id << "] Generó tarea " << i << endl;
        }

        cv.notify_one();   // Notifica a un robot que hay una nueva tarea disponible
        this_thread::sleep_for(chrono::milliseconds(175));
    }

    {
        lock_guard<mutex> lg(mtx); // Bloquea para actualizar el contador de sensores
        sensores_terminados++;
        if (sensores_terminados == NUM_SENSORES) {  // Me fijo si todos los sensores han terminado y notifico a todos los robots
            terminado = true;
            cv.notify_all();
        }
    }
}

//Funcion de los robots: procesan las tareas de la cola
void robot(int id) {
    while (true) {
        unique_lock<mutex> ul(mtx); // Bloquea  el mutex y despues el wait lo puede liberar temporalmente
        cv.wait(ul, [] { return !cola.empty() || terminado; }); // Espera hasta que haya tareas o se haya terminado

        if (!cola.empty()) { // Si hay tareas en la cola, las procesa, agarra la primera y la elimina de la cola
            Tarea tarea = cola.front();
            cola.pop();

            {
                lock_guard<mutex> lg(cout_mtx);  // Bloquea el mutex para los cout
                cout << "[Robot " << id << "] Procesando tarea del sensor "
                     << tarea.idsensor << ", idTarea: " << tarea.idtarea
                     << " - " << tarea.descripcion_tarea << endl;
            }

            ul.unlock();       // Libera el lock para que los sensores sigan
            this_thread::sleep_for(chrono::milliseconds(250));
        } else if (terminado) {
            break;
        }
    }

    {
        lock_guard<mutex> lg(cout_mtx);  // Bloquea el mutex para los cout
        cout << "[Robot " << id << "] Finalizó." << endl;
    }
}

int main() {
    vector<thread> sensores;
    for (int i = 0; i < NUM_SENSORES; ++i) { // Crea los sensores
        sensores.emplace_back(sensor, i + 1);
    }

    vector<thread> robots;
    for (int i = 0; i < NUM_ROBOTS; ++i) { // Crea los robots
        robots.emplace_back(robot, i + 1);
    }

    for (auto& s : sensores) { // Espera a que los sensores terminen
        s.join();
    }

    for (auto& r : robots) { // Espera a que los robots terminen
        r.join();
    }

    return 0;
}