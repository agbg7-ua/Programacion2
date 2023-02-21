// Programación 2 - Práctica 1
// DNI:48679841L
// Nombre: Andrea Gómez Bobes

#include <iostream>
#include <vector>

using namespace std;

const int KNAME=40;
const int KMAXOBSTACLES=20;

enum Error{
    ERR_OPTION,
    ERR_DIFFICULTY,
    ERR_LEVEL,
    ERR_COORDINATE,
    ERR_OBSTACLES,
    ERR_ID,
    ERR_INSTRUCTION
};

// Registro para las coordenadas
struct Coordinate{
    int row;
    int column;
};

// Registro para el jugador
struct Player{
    char name[KNAME];
    int difficulty;
    int score;
    int wins;
    int losses;
};

// Registro para el nivel
struct Level{
    int id;
    int size;
    int numObstacles;
    Coordinate obstacles[KMAXOBSTACLES];
    Coordinate start;
    Coordinate finish;
};

// Función que muestra los mensajes de error
void error(Error e){
    switch(e){
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
            break;
        case ERR_DIFFICULTY: cout << "ERROR: wrong difficulty" << endl;
            break;
        case ERR_LEVEL: cout << "ERROR: cannot create level" << endl;
            break;
        case ERR_COORDINATE: cout << "ERROR: wrong coordinate" << endl;
            break;
        case ERR_OBSTACLES: cout << "ERROR: wrong number of obstacles" << endl;
            break;
        case ERR_ID: cout << "ERROR: wrong id" << endl;
            break;
        case ERR_INSTRUCTION: cout << "ERROR: wrong instruction" << endl;
            break;
    }
}


void createLevel(vector<Level> &levels, int &id, Player &player){
    Level level;
    string obstacles;
    string srow,scolumn;
    int row,column,i;
    if(levels.size() > 9){
        error(ERR_LEVEL);
    }else{
        level.id = id;
        id++;
        if(player.difficulty == 1){
            level.size = 5;
            level.start.row =4;
            level.start.column =0;
            level.finish.row= 0;
            level.finish.column= 4;
        }else if(player.difficulty == 2){
            level.size = 7;
            level.start.row =6;
            level.start.column =0;
            level.finish.row= 0;
            level.finish.column= 6;
        }else if(player.difficulty == 3){
            level.size = 10;
            level.start.row =9;
            level.start.column =0;
            level.finish.row= 0;
            level.finish.column= 9;
        }
    levels.push_back(level);
    cout << "Obstacles: ";
    cin >> obstacles;
    do{
        while(i < obstacles.length() && obstacles[i] != ','){

        }
    }while(i);
    }
}
void deleteLevel(vector<Level> &levels){
    int id,i;
    char option;
    bool idc = false;
    cout << "Id: ";
    cin >> id;
    for(i=0;i<levels.size();i++){
        if(id == levels[i].id){
            idc = true;
            do{
                cout << "Are you sure? [y/n]" << endl;
                cin >> option;
                option = tolower(option);
                if(option == 'y'){
                    levels.erase(levels.begin()+i);
                }
            }while(option != 'y' && option != 'n');
            
        }
    }
    if(idc == false){
        error(ERR_ID);
    }
}
void showLevels(vector<Level>levels){
    
}
void report(Player &player){
    cout << "[Report]" << endl;
    cout << "Name: "<< player.name << endl;
    cout << "Difficulty: " << player.difficulty << endl;
    cout << "Score: " << player.score << endl;
    cout << "Wins: " << player.wins << endl;
    cout << "Losses: " << player.losses << endl;
    cout << "Total: " << player.wins + player.losses << endl;

}

// Función que muestra el menú de opciones
void showMenu(){
    cout << "[Options]" << endl
        << "1- Create level" << endl
        << "2- Delete level" << endl
        << "3- Show levels" << endl
        << "4- Play" << endl
        << "5- Report" << endl
        << "q- Quit" << endl
        << "Option: ";
}

// Función principal (tendrás que añadirle más código tuyo)
int main(){
    char option;
    int dif;
    int id = 0;
    Player player;
    vector<Level> levels;
    cout<< "Name: ";
    cin >> player.name;
    do{
        cout<< "Difficulty: ";
        cin >> dif;
        if(dif < 1 || dif > 3){
            error(ERR_DIFFICULTY);
         }
    }while(dif > 3 || dif < 1);
    player.difficulty = dif;
    player.losses = 0;
    player.score = 0;
    player.wins = 0;
    do{
        showMenu();
        cin >> option;
        cin.get();
        
         // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
    
        switch(option){
            case '1': 
                createLevel(levels,id,player); // Llamar a la función para crear un nuevo nivel
                break;
            case '2': 
                deleteLevel(levels);// Llamar a la función para borrar un nivel existente
                break;
            case '3': // Llamar a la función para mostrar los niveles creados
                break;
            case '4': // Llamar a la función para jugar
                break;
            case '5':
                report(player); // Llamar a la función para mostrar información del jugador
                break;
            case 'q': break;
            default: error(ERR_OPTION); // Muestra "ERROR: wrong option"
        }
    }while(option!='q');
}


