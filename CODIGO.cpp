//Busqueda binaria para Vocabulario de palabras
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

struct Concepto{
    string termino;
    string definicion;
};

const int MAX=100;

void ingresar(Concepto*,int&);
void ordenar(Concepto*, int);
int buscar(Concepto*, int, string);//busqueda binaria
void mostrar(Concepto*, int);
//void navegar(Concepto*, int);
void gotoxy(int , int );
void cambio_color(int );
void interfaz(string[],string[],const int,int);
void ocultarCursor();

int main(){
    SetConsoleOutputCP(CP_UTF8);
    
    Concepto Palabra[MAX];
    int contador=0; //contador de palabras ingresadas
    const int total=4;
    string opcionesMayus[total] = {"INGRESAR", "BUSCAR", "MOSTRAR","SALIR"};
    string opcionesMin[total] = {"Ingresar", "Buscar", "Mostrar","Salir"};

    int opcionActual = 0;
    string palabrita;

    // Dibujar el menú por primera vez
    interfaz(opcionesMayus, opcionesMin, total, opcionActual);
    
    while (true) {
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            
            if (tecla == 80) {//abajo
                opcionActual++;
                if (opcionActual >= total) {
                    opcionActual = 0;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
            else if (tecla == 72) {//arriba
                opcionActual--;
                if (opcionActual < 0) {
                    opcionActual = total - 1;
                }
                interfaz(opcionesMayus, opcionesMin, total, opcionActual);
            }
        }
        else if (tecla == 13) {
            system("cls");
            switch(opcionActual){
                case 0:
                ingresar(Palabra,contador);
                break;

                case 1:
                // = buscar()
                break;

                case 2:
                mostrar(Palabra, contador);
                break;

                case 3:
                cout<<"\n\n\n    Saliendo...";
                break;

                default:
                break;
            }

            if(opcionActual==3)break;

            _getch();
            system("cls");
            interfaz(opcionesMayus, opcionesMin, total, opcionActual);


        }
    }

    return 0;
}

//Diseño del menú
void interfaz(string opcionesMayus[], string opcionesMin[], const int total, int seleccionada) {
    gotoxy(0,0);//mover el cursor
    string texto;
    int x=9,y=6;
    int espacio_vertical=5;
    
    cout << "\n\n\n";
    //cambio_color(11);
    //cout << "               " << encabezado << "\n\n\n\n    ";
    //cambio_color(7);
    
    for(int i=0;i<total;i++){

        if(i==seleccionada){
            cambio_color(5);
            texto= *(opcionesMayus+i);
            gotoxy(x,y);cout<<  "╔═════════════════╗";
            gotoxy(x,y+1);cout<<"║  "<< texto<<"  ║";
            gotoxy(x,y+2);cout<<"╚═════════════════╝";
            cambio_color(7);
        }else{
            texto= *(opcionesMin+i);
            gotoxy(x,y);cout<<  "╔═════════════════╗";
            gotoxy(x,y+1);cout<<"║  "<< texto<<"  ║";
            gotoxy(x,y+2);cout<<"╚═════════════════╝";

        }
        y+=espacio_vertical;
        
    }
    
   
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cambio_color(int x){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

void ocultarCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void ingresar(Concepto* p, int &contador){
    cout<<"\n\n\n    ¡Hola!, soy tu vocabulario personal.\n";
    cout<<"    Que palabra deseas agregar?: ";
    cin>>p[contador].termino;
    cin.ignore();
    cout<<"\n\n    Cual es su definición?: ";
    getline(cin, p[contador].definicion);

    contador++;
    cout<<"\n    Palabra agregada exitosamente.\n";
}

//ordenamiento por insercion
void ordenar(Concepto* p, int contador){
    for(int i=0;i<contador;i++){
        Concepto temp=p[i];//crea una variable de tipo concepto temporal la cual guarda el valor de P[i]
        int pos=i;

        while(pos>0 && p[pos-1].termino>temp.termino){
            p[pos]=p[pos-1];
            pos--;
        }
        
        p[pos]=temp;
    }
}

int buscar(Concepto* p, int contador, string palabrita){
    int inicio=0, fin=contador, medio;

    while(inicio<=fin){
        medio=(inicio+fin)/2;

        if(p[medio].termino==palabrita){
            return medio;//encontrado
        }
        else if(p[medio].termino<palabrita){
            inicio=medio+1;//buscar en la mitad superior a la actual
        }
        else{
            fin=medio-1;//buscar en la mitad inferior a la actual
        }
    }
    
    return -1;
}

void mostrar(Concepto* p, int contador){
    cout<<"\n\n\n    Tus palabras son:\n\n";
    for(int i=0;i<contador;i++){
        cout<<"    "<<i+1<<". "<<p[i].termino<<": "<<p[i].definicion<<"\n";
    }
}
