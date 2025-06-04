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
    pokedex[pokemon] = pokemon.getInformacion();
}
PokemonInfo Pokedex::obtenerInformacion(const Pokemon& pokemon) const {
            auto it = pokedex.find(pokemon);
            if (it != pokedex.end()) {
                return it->second;
            } else {
                throw runtime_error("Pokemon desconocido!!");
            }
        }

