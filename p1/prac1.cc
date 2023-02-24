// Programación 2 - Práctica 1
// DNI:48679841L
// Nombre: Andrea Gómez Bobes
//Horas: 22 horas

#include <iostream>
#include <vector>
#include <cstring>
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
//Función que imprime un mapa por pantalla al cual hay que pasarle como parámetro el nivel que se desea imprimir
void showLevelOriginal(Level &level){
    int x,y; 
    for(x = 0;x < level.size;x++){
        for(y = 0;y<level.size;y++){ //Añadimos dos bucles para que imprima tanto filas como columnas
            int j;
            bool repetir = true;
            for(j=0;j<level.numObstacles;j++){
                //Se imprime X en la posición en la que haya obstáculos
                if(y==level.obstacles[j].column && x==level.obstacles[j].row){
                    cout << "X";
                    repetir = false;
                }
            }
            //Se imprime R en la posición inicial y más adelante en las posiciones a las que se mueva en Play
            if(x == level.start.row && y== level.start.column){
                cout << "R";
                repetir = false;
            }
            //Se imprime F en la posición final excepto que R se encunetre en esa posición
            else if(x == level.finish.row && y== level.finish.column){
                cout << "F";
                repetir = false;
            }
            //Se imprime O para el resto de posiciones en el mapa
            if(repetir==true){
                cout << "O";
            }
            
        }
        cout << '\n';
    }
    
}
//Función que se encarga de comprobar que una coordenada de un obstáculo pasada sea válida
void comprobar(Level &level,bool &rep){
    bool valid = true;
    for(int i=0;i<level.numObstacles; i++){
        if(i!=0){
            for(int j=0;j<level.numObstacles-1;j++){
                if(i!=j){
                    //Comprobamos que no haya ya una obstáculo en esa misma posición
                    if(level.obstacles[i].row == level.obstacles[j].row && level.obstacles[i].column == level.obstacles[j].column){
                        rep = true;
                        valid = false;

                    }
                    //Comprobamos que no haya ningun obstáculo adyacente a esa posición
                    if(abs(level.obstacles[i].column - level.obstacles[j].column)<=1 && abs(level.obstacles[i].row - level.obstacles[j].row)<=1){
                        rep = true;
                        valid = false;


                    }
                }
            }
        }
        //Comprobamos que el obstáculo está dentro del mapa
        if(level.obstacles[i].row >= level.size || level.obstacles[i].column >= level.size || level.obstacles[i].column < 0 || level.obstacles[i].row < 0){
            rep = true;
            valid = false;

        }
        //Comprobamos que la coordenada del obstáculo no sea la posición de inicio
        if(level.obstacles[i].column == level.start.column && level.obstacles[i].row==level.start.row ){
            rep =true;
            valid = false;

        }
        //Comprobamos que la coordenada del obstáculo no sea la posición de final
        if(level.obstacles[i].column == level.finish.column && level.obstacles[i].row==level.finish.row){
            rep = true;
            valid = false;
           
        }
    }
    //Si se cumple alguna de las comprobaciones anteriores mostramos un error
    if(valid == false){
         error(ERR_COORDINATE);
    }

}
//Función que pide los obstáculos y manjea las comprobaciones de estos
void Obstacles(Level &level,bool &rep){
    string obstacles;
    string srow,scolumn;
    unsigned int i;
    int j,row,column;
    do{
        cout << "Obstacles: "; //Pedimos los obstáculos al usuario
        getline(cin,obstacles);
        rep=false;
        level.numObstacles = 0;
        j=0;
        i=0;
        //Si no se introducen obstáculos creamos un mapa sin ellos
        if(obstacles.empty()){
            level.numObstacles = 0;
            rep = false;
        }else{
            do{
                Coordinate coord;
                srow="";
                scolumn="";
                row=0;
                column=0;
                //Recorremos el string y vamos guardando los valores como fila y columna por parejas saltando comas y barras divisorias
                if(obstacles[i]=='|'){
                        i++;
                    }
                while(i < obstacles.length() && obstacles[i] != ','){
                    srow += obstacles[i];
                    i++;
                }
                row = stoi(srow); //Transformamos el string a entero
                i++;
                while(i< obstacles.length() && obstacles[i] != '|'){
                    scolumn += obstacles[i];
                    i++;
                }
                level.numObstacles ++;
                column = stoi(scolumn); //Transformamos el string a entero
                coord.column = column;
                coord.row = row;
                //Guardamos los obstáculos en el nivel
                level.obstacles[j].column = coord.column;
                level.obstacles[j].row = coord.row;
                j++;
                 
            }while(i != obstacles.length()); //Repetimos este proceso hasta que se recorra el array entero
            //Comprobamos que la cantidad de obstáculos no es mayor al máximo de obstáculos permitidos en cada dificultad
            comprobar(level,rep);//Llamamos a la función que comprueba que sean coordenadas válidas
            if(level.size == 5){
                if(level.numObstacles > 5){
                    error(ERR_OBSTACLES);
                    rep = true;
                }
            }
            else if(level.size == 7){
                if(level.numObstacles > 10){
                    error(ERR_OBSTACLES);
                    rep = true;
                }
            }
            else if(level.size == 10){
                if(level.numObstacles > 20){
                    error(ERR_OBSTACLES);
                    rep = true;
                }
            }
        }
        

    }while(rep == true); //Repetimos el proceso mientras las coordenadas no sean válidas
}
//Función que crea cada nivel
void createLevel(vector<Level> &levels, int &id, Player &player,bool &rep){
    Level level;
    string obstacles;
    //Si ya hay 10 niveles imprimimos un error
    if(levels.size() > 9){
        error(ERR_LEVEL);
    }else{
        level.id = id;
        id++;
        level.numObstacles = 0;
        //inicializamos los valores del nivel según el nivel de dificultad que elegimos
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
        
        Obstacles(level,rep); //Pedimos los obstáculos
        levels.push_back(level); //Guardamos el nivel en el vector que almacena todos los niveles creados
        //Imprimimos el nivel creado
        cout << "Level " << level.id<< endl;
        showLevelOriginal(level);
    }
}
//Función que imprime todos los niveles
void showLevels(vector<Level>&levels){
    unsigned int i;
    for(i = 0;i<levels.size();i++){
        cout << "Level " << levels[i].id<< endl;
        showLevelOriginal(levels[i]);
    }
    
}
//Función que elimina un nivel concreto seleccionado por el usuario
void deleteLevel(vector<Level> &levels){
    int id;
    unsigned int i;
    char option;
    bool notId = false;
    //Pedimos el nivel a eliminar
    cout << "Id: ";
    cin >> id;
    //Recorremos el vector hasta encontrar el nivel deseado
    for(i=0;i<levels.size();i++){
        if(id == levels[i].id){
            notId = true;
            do{
                //Nos aseguramos de que se desea borrar
                cout << "Are you sure? [y/n]" << endl;
                cin >> option;
                option = tolower(option);
                if(option == 'y'){
                    levels.erase(levels.begin()+i); //Borramos el nivel
                }
            }while(option != 'y' && option != 'n');
            
        }
    }
    //Si se da un id que no existe se muestra un error
    if(notId == false){
        error(ERR_ID);
    }
}
//Función que permite al usuario jugar el nivel
void Play (vector<Level> &levels,Player &player){
    int position;
    unsigned int i,id;
    string instructions;
    //Se pide el ID del nivel al que se quiere jugar
    cout << "Id: ";
    cin >> id;
    //Si el id no existe da error
    if(id > (levels.size())){
        error(ERR_ID);
        return;
    }
    //Se imprime el nivel
    cout << "Level " << levels[id-1].id<< endl;
    showLevelOriginal(levels[id-1]);
    //Se solicitan las instrucciones que se quieren ejecutar con el personaje en el mapa
    cout << "Instructions: ";
    cin >> instructions;
    //Creamos un bucle para recorrer la serie de instrucciones
    for(i = 0;i<instructions.length();i++){
        int j = 0;
        //Definimos la posición de nuestro jugador (R) según la instrucción que se ejecute
        if(instructions[i] == 'R'){
            position = levels[id-1].start.column + 1; //Para la nueva posición sumamos 1 al valor de la columna
            for(j = 0; j<levels[id-1].numObstacles;j++){ //Recorremos el nivel para comprobar que no hayan obstáculos, si hay obstáculo se pierde la partida y aumento el número de derrotas
                if(position > levels[id-1].size || (position == levels[id-1].obstacles[j].column &&  levels[id-1].start.row== levels[id-1].obstacles[j].row)){ 
                    error(ERR_INSTRUCTION);
                    cout << "You lose" << endl;
                    player.losses++;
                    return;
                }
                levels[id-1].start.column = position; //Si no hay obstáculo se mueve a esa posición
            }
            cout << "Instruction R" << endl;
            showLevelOriginal(levels[id-1]);   // Imprimimos de nuevo el nivel reflejando el movimiento realizado
        }else if(instructions[i] == 'L'){
            position = levels[id-1].start.column - 1; //Para la nueva posición restamos 1 al valor de la columna
            for(j = 0; j<levels[id-1].numObstacles;j++){
                if(position > levels[id-1].size || (position == levels[id-1].obstacles[j].column &&  levels[id-1].start.row== levels[id-1].obstacles[j].row)){
                    error(ERR_INSTRUCTION);
                    cout << "You lose" << endl;
                    player.losses++;
                    return;
                }else{
                    levels[id-1].start.column = position;
                }
            }
            cout << "Instruction L" << endl;
            showLevelOriginal(levels[id-1]); 

        }else if(instructions[i] == 'U'){
            position = levels[id-1].start.row - 1; //Para la nueva posición restamos 1 al valor de la fila
            for(j = 0; j<levels[id-1].numObstacles;j++){
                if(position > levels[id-1].size || (position == levels[id-1].obstacles[j].row &&  levels[id-1].start.column== levels[id-1].obstacles[j].column)){
                    error(ERR_INSTRUCTION);
                    cout << "You lose" << endl;
                    player.losses++;
                    return;
                }else{
                    levels[id-1].start.row = position;
                }
            }
            cout << "Instruction U" << endl;
            showLevelOriginal(levels[id-1]);
        }else if(instructions[i] == 'D'){
            position = levels[id-1].start.row + 1; //Para la nueva posición sumamos 1 al valor de la fila
            for(j = 0; j<levels[id-1].numObstacles;j++){
                if(position > levels[id-1].size || (position == levels[id-1].obstacles[j].row &&  levels[id-1].start.column== levels[id-1].obstacles[j].column)){
                    error(ERR_INSTRUCTION);
                    cout << "You lose" << endl;
                    player.losses++;
                    return;
                }else{
                    levels[id-1].start.row = position;
                }
            }
            cout << "Instruction D" << endl;
            showLevelOriginal(levels[id-1]);
        }else{
            error(ERR_INSTRUCTION);
            cout << "You lose" << endl;
            player.losses++;
            return;
        }

    }
    // Si se consigue llegar al final se gana el nivel y se añade una victoria al jugador
    if(levels[id-1].start.row == levels[id-1].finish.row && levels[id-1].start.column == levels[id-1].finish.column){
        int points = 0;
        points = 3*(levels[id-1].size - 1) - instructions.length(); //Los puntos se calculan de esta forma
        if(points < 0){
            points = 0;
        }
        cout << "You win " << points << " points" <<endl;
        player.score += points;
        player.wins++;

    }

    
}
//Función que imprime las características del jugador
void report(Player &player){
    string difficulty;

    cout << "[Report]" << endl;
    cout << "Name: "<< player.name << endl;
    if(player.difficulty == 1){
        difficulty = "Easy";
    }else if(player.difficulty == 2){
        difficulty = "Medium";
    }else{
        difficulty = "Hard";
    }
    cout << "Difficulty: " << difficulty << endl;
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
    bool rep;
    int id = 1;
    string name;
    Player player;
    vector<Level> levels;
    //Se pide le nombre para el jugador
    cout<< "Name: ";
    getline(cin,name);
    strcpy(player.name,name.c_str());
    //Pedimos la dificultad y comprobamos que sea correcta
    do{
        cout<< "Difficulty: ";
        cin >> dif;
        if(dif < 1 || dif > 3){
            error(ERR_DIFFICULTY);
         }
    }while(dif > 3 || dif < 1);
    //Inicializamos los valores del jugador
    player.difficulty = dif;
    player.losses = 0;
    player.score = 0;
    player.wins = 0;
    //Mostramos el menú siempre que la opción elegida sea distinta de q
    do{
        showMenu();
        cin >> option;
        cin.get();
        //Si se introduce una opción no válida sale mensaje de error y se vuelve a mostrar el menú y pedir otra opción
        if(option != '1' && option != '2' &&option != '3' &&option != '4' && option != '5' && option != 'q'){
            error(ERR_OPTION);
        }else{
            switch(option){
            case '1': 
                createLevel(levels,id,player,rep); // Llamar a la función para crear un nuevo nivel
                break;
            case '2': 
                deleteLevel(levels);// Llamar a la función para borrar un nivel existente
                break;
            case '3': showLevels(levels);// Llamar a la función para mostrar los niveles creados
                break;
            case '4': Play(levels,player);// Llamar a la función para jugar
                break;
            case '5':
                report(player); // Llamar a la función para mostrar información del jugador
                break;
            case 'q': break;
            default: error(ERR_OPTION); // Muestra "ERROR: wrong option"
            }
        }
         // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
    
        
    }while(option!='q');
}


