#include "../include/ej1.hpp"

/*creo varios pokemons y los agrego a la pokedex, luego 
los muestro, serializo la pokedex, deserializo y vuelvo a mostrar los pokemons*/

int main(){
    PokemonInfo info1("Fuego", "una lagartija con una llama en su cola", {0, 200, 300});
    info1.agregarAtaque("Llamarada", 50);
    info1.agregarAtaque("Bola de Fuego", 70);
    Pokemon charmander("Charmander", 50, info1);

    PokemonInfo info2("Agua", "una tortuga azul facherita", {0, 220, 320});
    info2.agregarAtaque("Hidrobomba", 60);
    info2.agregarAtaque("Surf", 80);
    Pokemon squirtle("Squirtle", 60, info2);

    PokemonInfo info3("Planta", "una rata rara con una planta en la espalda", {0, 150, 300});
    info2.agregarAtaque("Latigo Cepa", 70);
    info2.agregarAtaque("Rayo Solar", 100);
    Pokemon bulbasur("Bulbasur", 230, info3);

    Pokedex pokedex("pokedex.dat");
    pokedex.agregarPokemon(charmander);
    pokedex.agregarPokemon(bulbasur);

    cout << "ANTES DE SERIALIZAR" << endl;
    cout << "---------------------" << endl;

    // muestra todos los pokemons
    pokedex.mostrarTodos();
    // muestra un pokemon en particular
    pokedex.mostrar(squirtle);
    pokedex.mostrar(charmander);

    //serializar la pokedex
    pokedex.serializar();

    //deserializar la pokedex
    Pokedex pokedex2("pokedex.dat");
    pokedex2.deserializar();

    cout << "DESPUES DE DESERIALIZAR" << endl;
    cout << "------------------------" << endl;

    // muestra todos los pokemons deserializados
    pokedex2.mostrarTodos();
    // muestra un pokemon en particular deserializado
    pokedex2.mostrar(squirtle);
    pokedex2.mostrar(bulbasur);

    return 0;
}