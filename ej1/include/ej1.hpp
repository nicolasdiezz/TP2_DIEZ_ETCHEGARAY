#ifndef EJ1_HPP
#define EJ1_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

class PokemonInfo{
    private:
        string tipo;
        string descripcion;
        vector<pair<string, int>> ataques;
        vector<int> experienciaProxNivel;
    public:
        PokemonInfo(string t, string desc, vector<int> expNiv) : tipo(t), descripcion(desc), experienciaProxNivel(expNiv) {}
        void agregarAtaque(string ataque, int danio);
        string getTipo() const;
        string getDescripcion() const;
        vector<pair<string, int>> getAtaques() const;
        vector<int> getExperienciaProxNivel() const;
        void serializar(ofstream& out) const;
        void deserializar(ifstream& in);
};

class Pokemon{
    private:
        string nombre;
        int experiencia;
        PokemonInfo informacion;
        int nivel;
    public:
        Pokemon(string n, int exp, PokemonInfo info) : nombre(n), experiencia(exp), informacion(info) {}
        string getNombre() const;
        int getExperiencia() const;
        PokemonInfo getInformacion() const;
        int getNivel() const;
        bool operator==(const Pokemon& other) const {
            return nombre == other.nombre;;
        }
        void serializar(ofstream& out) const;
        void deserializar(ifstream& in);
};

//hacer el hash
class PokedexHash {
    public:
        size_t operator()(const Pokemon& pokemon) const {
            return hash<string>()(pokemon.getNombre());
        }
};

class Pokedex{
    private:
        unordered_map<Pokemon, PokemonInfo, PokedexHash> pokedex;
        string archivo;
    public:
        Pokedex() = default;
        Pokedex(const string& archivo) : archivo(archivo) {}
        void agregarPokemon(const Pokemon& pokemon);
        PokemonInfo obtenerInformacion(const Pokemon& pokemon) const;
        void mostrarTodos() const;
        void mostrar(const Pokemon& pokemon) const;
        //serializar y deserializar
        void serializar() const;
        void deserializar();
};

#endif

