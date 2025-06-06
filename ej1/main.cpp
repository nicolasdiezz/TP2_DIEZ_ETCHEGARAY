#include "ej1.hpp"

int main(){
    PokemonInfo info1("Fuego", "una lagartija con una llama en su cola", {0, 200, 300});
    info1.agregarAtaque("Llamarada", 50);
    info1.agregarAtaque("Bola de Fuego", 70);
    Pokemon charmander("Charmander", 50, info1);

    PokemonInfo info2("Agua", "una tortuga azul facherita", {0, 220, 320});
    info2.agregarAtaque("Hidrobomba", 60);
    info2.agregarAtaque("Surf", 80);
    Pokemon squirtle("Squirtle", 60, info2);

    PokemonInfo info3("Planta", "una rata rara con una planta en la espalda", {0, 220, 320});
    info2.agregarAtaque("Latigo Cepa", 60);
    info2.agregarAtaque("Rayo Solar", 80);
    Pokemon bulbasur("Bulbasur", 60, info2);

    Pokedex pokedex;
    pokedex.agregarPokemon(charmander);
    pokedex.agregarPokemon(bulbasur);

    pokedex.mostrarTodos();
    pokedex.mostrar(squirtle);
    pokedex.mostrar(charmander);
}