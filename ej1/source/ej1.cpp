#include "../include/ej1.hpp"

//implementacion de Pokemon
string Pokemon::getNombre() const {
    return nombre;
}

//devuelve la experiencia del pokemon
int Pokemon::getExperiencia() const {
    return experiencia;
}

//devuelve la informacion del pokemon
PokemonInfo Pokemon::getInformacion() const {
    return informacion;
}

//devuelve el nivel del pokemon segun su experiencia
int Pokemon::getNivel() const {
    if(experiencia >= informacion.getExperienciaProxNivel()[2]) {
        return 3;
    }
    else if(experiencia >= informacion.getExperienciaProxNivel()[1]) {
        return 2;
    }
    return 1; // Si la experiencia es menor que el primer nivel, se considera nivel 1.
}

// serializa el pokemon
void Pokemon::serializar(ofstream& out) const {
    size_t nombreSize = nombre.size();
    out.write(reinterpret_cast<const char*>(&nombreSize), sizeof(nombreSize)); // escribir el tamaño del nombre
    out.write(nombre.c_str(), nombreSize); // escribir el nombre

    out.write(reinterpret_cast<const char*>(&experiencia), sizeof(experiencia));
    informacion.serializar(out);    
}

// deserializa el pokemon
void Pokemon::deserializar(ifstream& in) {
    size_t nombreSize;
    in.read(reinterpret_cast<char*>(&nombreSize), sizeof(nombreSize)); // leer el tamaño del nombre
    nombre.resize(nombreSize); // redimensionar el string para que tenga el tamaño correcto
    in.read(&nombre[0], nombreSize); // leer el nombre
    
    in.read(reinterpret_cast<char*>(&experiencia), sizeof(experiencia));
    
    informacion.deserializar(in);
}


//implementacion de PokemonInfo
void PokemonInfo::agregarAtaque(string ataque, int danio) {
    ataques.push_back(make_pair(ataque, danio));
}

// devuelve el tipo del pokemon
string PokemonInfo::getTipo() const {
    return tipo;
}

// devuelve la descripcion del pokemon
string PokemonInfo::getDescripcion() const {
    return descripcion;
}

// devuelve los ataques del pokemon, como vector de pares (nombre del ataque, daño)
vector<pair<string, int>> PokemonInfo::getAtaques() const {
    return ataques;
}

// devuelve la experiencia necesaria para el proximo nivel del pokemon
vector<int> PokemonInfo::getExperienciaProxNivel() const {
    return experienciaProxNivel;
}

// serializa la informacion del pokemon
void PokemonInfo::serializar(ofstream& out) const {
    size_t tipoSize = tipo.size();
    size_t descripcionSize = descripcion.size();
    out.write(reinterpret_cast<const char*>(&tipoSize), sizeof(tipoSize)); // escribir el tamaño del tipo
    out.write(reinterpret_cast<const char*>(&descripcionSize), sizeof(descripcionSize)); // escribir el tamaño de la descripcion
    out.write(tipo.c_str(), tipoSize);
    out.write(descripcion.c_str(), descripcionSize);
    
    int numAtaques = ataques.size();
    out.write(reinterpret_cast<const char*>(&numAtaques), sizeof(numAtaques));
    
    for (const auto& ataque : ataques) {
        size_t ataqueSize = ataque.first.size();
        out.write(reinterpret_cast<const char*>(&ataqueSize), sizeof(ataqueSize)); // escribir el tamaño del ataque
        out.write(ataque.first.c_str(), ataqueSize); // escribir el ataque
        out.write(reinterpret_cast<const char*>(&ataque.second), sizeof(ataque.second));
    }
    
    int numExp = experienciaProxNivel.size();
    out.write(reinterpret_cast<const char*>(&numExp), sizeof(numExp));
    for (int exp : experienciaProxNivel) {
        out.write(reinterpret_cast<const char*>(&exp), sizeof(exp));
    }
}

// deserializa la informacion del pokemon
void PokemonInfo::deserializar(ifstream& in) {
    size_t tipoSize;
    size_t descripcionSize;
    in.read(reinterpret_cast<char*>(&tipoSize), sizeof(tipoSize)); // leer el tamaño del tipo
    in.read(reinterpret_cast<char*>(&descripcionSize), sizeof(descripcionSize)); // leer el tamaño de la descripcion
    tipo.resize(tipoSize); // redimensionar el string para que tenga el tamaño correcto
    descripcion.resize(descripcionSize); // redimensionar el string para que tenga el tamaño correcto
    in.read(&tipo[0], tipoSize); // leer el tipo
    in.read(&descripcion[0], descripcionSize); // leer la descripcion
    
    int numAtaques;
    in.read(reinterpret_cast<char*>(&numAtaques), sizeof(numAtaques));

    ataques.clear();
    for (int i = 0; i < numAtaques; ++i) {
        string ataque;
        size_t ataqueSize;
        in.read(reinterpret_cast<char*>(&ataqueSize), sizeof(ataqueSize)); // leer el tamaño del ataque
        ataque.resize(ataqueSize); // redimensionar el string para que tenga el tamaño correcto
        in.read(&ataque[0], ataqueSize); // leer el ataque
    
        int danio;
        in.read(reinterpret_cast<char*>(&danio), sizeof(danio));
        ataques.push_back(make_pair(ataque, danio));
    }

    int numExp;
    in.read(reinterpret_cast<char*>(&numExp), sizeof(numExp));
    experienciaProxNivel.clear();
    for (int i = 0; i < numExp; ++i) {
        int exp;
        in.read(reinterpret_cast<char*>(&exp), sizeof(exp));
        experienciaProxNivel.push_back(exp);
    }
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

// muestra todos los pokemons de la pokedex y sus informaciones
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
// muestra un pokemon en particular y su informacion
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
            cout << ataque.first << " (Daño = " << ataque.second << "), ";
        }
        cout << endl;
        cout << endl;
    }
    else {
        cout << "El pokemon " << pokemon.getNombre() << " no se encuentra en la pokedex." << endl;
    }
    cout << endl;
}
// serializa la pokedex a un archivo binario
void Pokedex::serializar() const {
    ofstream out(archivo, ios::binary);
    if (!out) {
        throw runtime_error("No se pudo abrir el archivo");
    }
    
    int numPokemon = pokedex.size();
    out.write(reinterpret_cast<const char*>(&numPokemon), sizeof(numPokemon));
    
    for (const auto& entry : pokedex) { // serializar cada Pokemon y su informacion
        entry.first.serializar(out);
        entry.second.serializar(out);
    }
    
    out.close();
}

// deserializa la pokedex desde un archivo binario
void Pokedex::deserializar() {
    ifstream in(archivo, ios::binary);
    if (!in) {
        throw runtime_error("No se pudo abrir el archivo");
    }
    
    int numPokemon;
    in.read(reinterpret_cast<char*>(&numPokemon), sizeof(numPokemon));
    
    pokedex.clear();
    for (int i = 0; i < numPokemon; ++i) {
        Pokemon pokemon("", 0, PokemonInfo("", "", {}));
        pokemon.deserializar(in); // deserializar el pokemon
        PokemonInfo info("", "", {});
        info.deserializar(in); // deserializar la informacion del pokemon
        pokedex.insert({pokemon, info});
    }
    
    in.close();
}