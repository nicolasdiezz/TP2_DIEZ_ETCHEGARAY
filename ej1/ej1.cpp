#include "ej1.hpp"

//implementacion de Pokemon
string Pokemon::getNombre() const {
    return nombre;
}
int Pokemon::getExperiencia() const {
    return experiencia;
}
PokemonInfo Pokemon::getInformacion() const {
    return informacion;
}
int Pokemon::getNivel() const {
    if(experiencia >= informacion.getExperienciaProxNivel()[2]) {
        return 3;
    }
    else if(experiencia >= informacion.getExperienciaProxNivel()[1]) {
        return 2;
    }
    else if(experiencia >= informacion.getExperienciaProxNivel()[0]) {
        return 1;
    }
    return 1; // Si la experiencia es menor que el primer nivel, se considera nivel 1.
}




//implementacion de PokemonInfo
void PokemonInfo::agregarAtaque(string ataque, int daño) {
    ataques.push_back(make_pair(ataque, daño));
}
string PokemonInfo::getTipo() const {
    return tipo;
}
string PokemonInfo::getDescripcion() const {
    return descripcion;
}
vector<pair<string, int>> PokemonInfo::getAtaques() const {
    return ataques;
}
vector<int> PokemonInfo::getExperienciaProxNivel() const {
    return experienciaProxNivel;
}




//implementacion de Pokedex
void Pokedex::agregarPokemon(const Pokemon& pokemon) {
    pokedex.insert({pokemon, pokemon.getInformacion()});
}
PokemonInfo Pokedex::obtenerInformacion(const Pokemon& pokemon) const {
    auto it = pokedex.find(pokemon);
        if (it != pokedex.end()) {
            return it->second;
        } else {
            throw runtime_error("Pokemon desconocido!!");
    }
}

void Pokedex::mostrarTodos() const {
    for (const auto& entry : pokedex) {
        const Pokemon& pokemon = entry.first;
        const PokemonInfo& info = entry.second;
        cout << "Nombre: " << pokemon.getNombre() << endl;
        cout << "Experiencia: " << pokemon.getExperiencia() << endl;
        cout << "Nivel: " << pokemon.getNivel() << endl;
        cout << "Tipo: " << info.getTipo() << endl;
        cout << "Descripcion: " << info.getDescripcion() << endl;
        cout << "Ataques: ";
        for (const auto& ataque : info.getAtaques()) {
            cout << ataque.first << " (Daño: " << ataque.second << "), ";
        }
        cout << endl;
        cout << endl;
    }
}

void Pokedex::mostrar(const Pokemon& pokemon) const {
    auto it = pokedex.find(pokemon);
    if (it != pokedex.end()) {
        cout << "Nombre: " << pokemon.getNombre() << endl;
        cout << "Experiencia: " << pokemon.getExperiencia() << endl;
        cout << "Nivel: " << pokemon.getNivel() << endl;
        cout << "Tipo: " << pokemon.getInformacion().getTipo() << endl;
        cout << "Descripcion: " << pokemon.getInformacion().getDescripcion() << endl;
        cout << "Ataques: ";
        for (const auto& ataque : pokemon.getInformacion().getAtaques()) {
            cout << ataque.first << " (Daño: " << ataque.second << "), ";
        }
        cout << endl;
        cout << endl;
    }
    else {
        cout << "El pokemon " << pokemon.getNombre() << " no se encuentra en la pokedex." << endl;
    }
}