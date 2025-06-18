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
mutex mtx;
mutex cout_mtx;
condition_variable cv;

bool terminado = false;
int sensores_terminados = 0;
const int NUM_SENSORES = 3;
const int NUM_ROBOTS = 3;

void sensor(int id) {
    for (int i = 1; i <= 3; ++i) {
        {
            lock_guard<mutex> lg(mtx);
            Tarea tarea{id, i, "Tarea generada por sensor " + to_string(id) + ", nro: " + to_string(i)};
            cola.push(tarea);
        }
        {
            lock_guard<mutex> lg(cout_mtx);
            cout << "[Sensor " << id << "] Generó tarea " << i << endl;
        }

        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(175));
    }

    {
        lock_guard<mutex> lg(mtx);
        sensores_terminados++;
        if (sensores_terminados == NUM_SENSORES) {
            terminado = true;
            cv.notify_all();
        }
    }
}

void robot(int id) {
    while (true) {
        unique_lock<mutex> ul(mtx);
        cv.wait(ul, [] { return !cola.empty() || terminado; });

        if (!cola.empty()) {
            Tarea tarea = cola.front();
            cola.pop();

            {
                lock_guard<mutex> lg(cout_mtx);
                cout << "[Robot " << id << "] Procesando tarea del sensor "
                     << tarea.idsensor << ", idTarea: " << tarea.idtarea
                     << " - " << tarea.descripcion_tarea << endl;
            }

            ul.unlock(); // liberar el lock para que los sensores sigan
            this_thread::sleep_for(chrono::milliseconds(250));
        } else if (terminado) {
            break;
        }
    }

    {
        lock_guard<mutex> lg(cout_mtx);
        cout << "[Robot " << id << "] Finalizó." << endl;
    }
}

int main() {
    vector<thread> sensores;
    for (int i = 0; i < NUM_SENSORES; ++i) { // crear los sensores
        sensores.emplace_back(sensor, i + 1);
    }

    vector<thread> robots;
    for (int i = 0; i < NUM_ROBOTS; ++i) { // crear los robots
        robots.emplace_back(robot, i + 1);
    }

    for (auto& s : sensores) { // esperar a que los sensores terminen
        s.join();
    }

    for (auto& r : robots) {
        r.join();
    }
    return 0;
}