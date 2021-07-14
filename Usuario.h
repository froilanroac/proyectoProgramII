#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>



using namespace std;


struct nodo{

    int cedula;
    char nombre[100];
    char apellido[100];

    char telefonohab[100];
    char celular[100]; 
    char teleftrab[100]; 
    char telefami[100];

    int dia;
    int mes;
    int year;

    char direccionhab[100] ;
    char direcciontrab[100];

    

    char destino_habitual[100]; 
    int  hora_habitual;

    int posee; // 1=SI ; 0=NO
 
    int tipoPersonal;


};

struct carro{

    char marca[100];
    char modelo[100];
    int year;
    char serialmotor[100]; 
    char colorcarro[100];
    char placa[100];
};

struct cola{

    int hora;
    char destino[100]; 
   

};

struct ofrece{

    int hora;
    char destino[100]; 

};

struct destino{

    char direccion[100]; 
    int codigo;

};

void mayuscula(char palabra[100]){
   int i;
   for(i = 0; palabra[i]; i++) 
      palabra[i] = toupper(palabra[i]); 
}
