#include "ej1.hpp"

int main(){
    PokemonInfo info1("Fuego", "Un pokemon de tipo fuego", {100, 200, 300});
    info1.agregarAtaque("Llamarada", 50);
    info1.agregarAtaque("Bola de Fuego", 70);
    Pokemon charmander("Charmander", 50, info1);

    PokemonInfo info2("Agua", "Un pokemon de tipo agua", {120, 220, 320});
    info2.agregarAtaque("Hidrobomba", 60);
    info2.agregarAtaque("Surf", 80);
    Pokemon squirtle("Squirtle", 60, info2);

    Pokedex pokedex;
    pokedex.agregarPokemon(charmander);
    pokedex.agregarPokemon(squirtle);
}