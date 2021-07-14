#include "Usuario.h"
#include <iostream>


using namespace std;

bool posee;
int opc; 
char dest[100];
char buscado[100];
int prueba;


string tipoUsuario[4] = {"ADMINISTRATIVO","OBRERO","ESTUDIANTE","PROFESOR"};

string meses[13] = {"NULL","ENERO","FEBRERO","MARZO","ABRIL","MAYO","JUNIO","JULIO","AGOSTO","SEPTIEMBRE","OCTUBRE","NOVIEMBRE","DICIEMBRE"};

string pos[2] = {"NO","SI"};

struct listaUsuarios{

    struct nodo usuarios;
    struct listaUsuarios *prox;

};
typedef struct listaUsuarios *Tlista;

struct listaCarros{

     int su_propietario;
    struct carro carros;
    struct listaCarros *prox;

};
typedef struct listaCarros *Tcarro;

struct listaColas{

     int pedidordecola;
    struct cola colas;
    struct listaColas *prox;

};
typedef struct listaColas *Tcolas;

struct listaOfrece{

     int ofrecedordecola;
    struct ofrece colas;
    int numerodepuestos;
    struct listaOfrece *prox;

};
typedef struct listaOfrece *Tofrece;

struct listaDestinos{

    struct destino destinos;
    struct listaDestinos *prox;

};
typedef struct listaDestinos *Tdestino;

struct listaProcesa{

    int cedulaprestador;
    int cedulapedidor;
    struct listaProcesa *prox;

};
typedef struct listaProcesa *Tprocesa;

//PROTOTIPOS

//USUARIOS
void registrarPersona(Tlista &lista,Tcarro &listacarros, int cedula);
Tlista crearNodo(Tlista &lista, int cedula,bool posee);
bool esVaciaLista(Tlista &lista);
void modificar(Tlista &lista,Tcarro &listacarros, int cedula);
void mostrarModificacion(Tlista variable);
bool esVaciaLista(Tlista &lista);

//CARROS
void registrarCarro(Tcarro &listacarros, int cedula);
Tcarro crearCarro(Tcarro &listacarros, int cedula);
bool esVaciaCarros(Tcarro &listacarros);
void eliminarCarro(Tcarro &listacarros, int valor);

//PEDIR COLA
void pedirCola(Tlista &lista,Tcolas &listacolas,Tdestino &listadestinos,  int cedula);
void registrarCola(Tlista variable, Tcolas &listacolas,Tdestino &listadestinos);
void registrarColaModificada(Tcolas nodo , Tcolas &listacolas);
bool verificarDestinoRepetido(char destino[100],Tdestino &listadestinos);
Tcolas crearNodoCola(Tlista variable,Tcolas &listacolas,Tdestino &listadestinos);
void mostrarCola(Tlista variable);
void modificarCola(Tcolas &listacolas,Tdestino &listadestinos, int cedula,Tprocesa &listaprocesa);
void mostrarModificacionCola(Tcolas variable);
void eliminarCola(Tcolas &listacolas,  int valor);
void mostrarSolicitud(Tcolas variable);
void mostrarSolicitudProcesada(Tcolas variable,Tlista &lista, Tcarro &listacarros,int cedula);
void mostrarSolicitudCola(Tcolas &listacolas,  int cedula,Tprocesa &listaprocesa,Tcarro &listacarros,Tlista &lista);
void mostrarSolicitudDestino(Tcolas &listacolas, char destino[100]);
bool esVaciaColas(Tcolas &listacolas);

//OFRECER LA COLA
void ofrecerCola(Tlista &lista,Tofrece &listaofrece,Tofrece &listadestinos,  int cedula);
void registrarOfrece(Tlista variable, Tofrece &listaofrece,Tdestino &listadestinos);
Tofrece crearNodoOfrece(Tlista variable,Tofrece &listaofrece,Tdestino &listadestinos);
void mostrarOfrecimientosModificacion(Tofrece variable);
void modificarOfrece(Tofrece &listaofrece,  int cedula);
bool esVaciaOfrece(Tofrece &listaofrece);
void mostrarOfrecimientos(Tofrece variable);
void eliminarOfrece(Tofrece &listaofrece, int valor);

//DESTINOS 
void mostrarDestinos(Tdestino variable);
void registrarDestinos (char destino[100],Tdestino &listadetinos);
Tdestino crearDestino(Tdestino &listadestinos,char destino[100]);
bool buscarDireccionClave(Tdestino &listadestinos, int codigo);
void eliminarColaModificada(Tcolas &listacolas, int valor);
void registrarProcesa(Tprocesa &listaprocesa, int cedulaprestador,int cedulapedidor);

//ESCRITURA 
void escribirLista(Tlista variable);
void escribirListaCarros(Tcarro variable);
void escribirListaColas(Tcolas variable);
void escribirListaOfrece(Tofrece variable);
void escribirListaDestino(Tdestino variable);

//LECTURA 
void cargarPersona(Tlista nodo,Tlista &lista);
void cargarCarro(Tcarro nodocarro, Tcarro &listacarros);
void cargarCola(Tcolas nodo, Tcolas &listacolas);
void cargarDestino (Tdestino nodo,Tdestino &listadestinos);
void cargarOfrece(Tofrece nodo, Tofrece &listaofrece);

//LECTURA DE FICHEROS
void cargarLista(Tlista &lista, char dirLista[200]);
void cargarListaCarros(Tcarro &listacarros, char dirListaCarros[200]);
void cargarListaColas(Tcolas &listacolas, char dirListaCarros[200]);
void cargarListaDestinos(Tdestino &listadestinos, char dirListaDestinos[200]);
void cargarListaOfrecimientos(Tofrece &listaofrece, char dirListaOfrecimientos[200]);

//PROCESAR LAS COLAS
void procesarColas(Tcolas &listacolas, Tofrece &listaofrece,Tprocesa &listaprocesa);
Tprocesa crearNodoProcesa(int cedulaprestador,int cedulapedidor);
void registrarProcesa(Tprocesa &listaprocesa, int cedulaprestador,int cedulapedidor);
void limpiarListaProcesa(Tprocesa &listaprocesa);
bool Procesada(Tprocesa &listaprocesa, int cedula);
int cedulaDelPrestador(Tprocesa &listaprocesa, int cedula);

//FIN DE LOS PROTOTIPOS 


//PROCESAR LAS COLAS
void procesarColas(Tcolas &listacolas, Tofrece &listaofrece,Tprocesa &listaprocesa){

	Tofrece prestador = listaofrece;

	if (prestador!=NULL){
		while (prestador!=NULL){
            Tcolas pedidor = listacolas;
			int contador = prestador->numerodepuestos;
    				while (pedidor!=NULL && contador > 0){
    					if ((!strcmp(prestador->colas.destino,pedidor->colas.destino)) && (prestador->colas.hora == pedidor->colas.hora) && !Procesada(listaprocesa,pedidor->pedidordecola)){
                           registrarProcesa(listaprocesa,prestador->ofrecedordecola,pedidor->pedidordecola);
                            contador--;
    					}
    				pedidor=pedidor->prox;
    				}
		prestador = prestador->prox;
	   }
    }
}

Tprocesa crearNodoProcesa(int cedulaprestador,int cedulapedidor){

    fflush(stdin);

    Tprocesa nodo = new (struct listaProcesa);

    (nodo->cedulaprestador) = cedulaprestador;
    (nodo->cedulapedidor) = cedulapedidor; 

    fflush(stdin);
    nodo->prox = NULL;
    return(nodo);
}

void registrarProcesa(Tprocesa &listaprocesa, int cedulaprestador,int cedulapedidor){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION.
   
    Tprocesa q = listaprocesa;
    int i = 1, band = 0;

    if(band==0){ 
        Tprocesa nodo = crearNodoProcesa(cedulaprestador,cedulapedidor);
        Tprocesa t = new(struct listaProcesa);

        if(listaprocesa==NULL) {

                listaprocesa = nodo;
                
            }
            else
            {
            t = listaprocesa;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                
            }   
         }
}

void limpiarListaProcesa(Tprocesa &listaprocesa){
  
    Tprocesa p, ant;
    p = listaprocesa;
 
    if(listaprocesa!=NULL) {
        while(p!=NULL) {
            
            if(p==listaprocesa) {
                listaprocesa = listaprocesa->prox;
            }
            else {
                ant->prox = p->prox;
                delete(p);
                return;
            }
            ant = p;
            p = p->prox;    
        }
    }
}

bool Procesada(Tprocesa &listaprocesa, int cedula){

    bool ban = false; 

    Tprocesa q = listaprocesa;

    while (q!= NULL){
        if (q->cedulapedidor == cedula){
            ban = true;
        }
        q=q->prox;
    }
    return (ban);
}

int cedulaDelPrestador(Tprocesa &listaprocesa, int cedula){

    Tprocesa q = listaprocesa;

    int cedulaprestador = 0;

    while(q!=NULL){

        if(q->cedulapedidor == cedula){

            cedulaprestador = (q->cedulaprestador);
        }
        q=q->prox;
    }
    return (cedulaprestador);
}

//USUARIOS
void registrarPersona(Tlista &lista,Tcarro &listacarros,  int cedula){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION.
   
    Tlista q = lista;
    int i = 1, band = 0;


    while(q!=NULL) {
        if(q->usuarios.cedula==cedula) {

            cout<<endl<<"ERROR, ESTA PERSONA YA ESTA REGISTRADA."<<endl<<endl;  
            band = 1;
        }
        q = q->prox;
    }

    if(band==0){

        cout<<endl<<"POSEE CARRO? (1:SI ; 0:NO)";
        cin>>posee;

        Tlista nodo = crearNodo(lista,cedula,posee);
        Tlista t = new(struct listaUsuarios);

        if(lista==NULL) {

                lista = nodo;
                cout<<endl<<"*** ESTUDIANTE DE CEDULA: "<< nodo->usuarios.cedula<<" REGISTRADO CON EXITO ***"<<endl;

                if (posee)
                {
                registrarCarro(listacarros,cedula);
                }


                }
            else
            {
            t = lista;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                cout<<endl<<"*** ESTUDIANTE DE CEDULA: "<< nodo->usuarios.cedula<<" REGISTRADO CON EXITO ***"<<endl;


                if (posee)
                {
                registrarCarro(listacarros,cedula);
                }
            }   
         }
}

Tlista crearNodo(Tlista &lista, int cedula,bool posee){

    fflush(stdin);
    Tlista nodo = new (struct listaUsuarios);

    (nodo->usuarios.cedula) = cedula;

    cout<<endl<<"NOMBRE: "<< endl;
    scanf(" %[^\n]", nodo->usuarios.nombre);
    mayuscula(nodo->usuarios.nombre);
    cout<<endl<<"APELLIDO: "<<endl; 
    scanf(" %[^\n]", nodo->usuarios.apellido);
    mayuscula(nodo->usuarios.apellido);
    cout<<endl<<"DIRECCION DE HABITACION: "<<endl;
    scanf(" %[^\n]", nodo->usuarios.direccionhab);
    mayuscula(nodo->usuarios.direccionhab);
    cout<<endl<<"DIRECCION DE TRABAJO: "<<endl; 
    scanf(" %[^\n]", nodo->usuarios.direcciontrab);
    mayuscula(nodo->usuarios.direcciontrab);
    cout<<endl<<"DESTINO HABITUAL"<<endl;
    scanf(" %[^\n]", nodo->usuarios.destino_habitual);
    mayuscula(nodo->usuarios.destino_habitual);
    cout<<endl<<"TELEFONO DE HABITACION: "<<endl; 
    cin>> nodo->usuarios.telefonohab;
    cout<<endl<<"TELEFONO CELULAR: "<<endl;
    cin>> nodo->usuarios.celular;
    cout<<endl<<"TELEFONO DE TRABAJO: "<<endl;
    cin>> nodo->usuarios.teleftrab;
    cout<<endl<<"DIA DE NACIMIENTO: "<<endl; 
    cin>> nodo->usuarios.dia;
    cout<<endl<<"MES DE NACIMIENTO (EN NUMERO): "<<endl; 
    cin>> nodo->usuarios.mes;
    cout<<endl<<"AÑO DE NACIMIENTO: "<<endl; 
    cin>> nodo->usuarios.year;
    cout<<endl<<"TELEFONO DE ALGUN FAMILIAR: "<<endl; 
    cin>> nodo->usuarios.telefami;    
    cout<<endl<<"HORA HABITUAL DE SALIDA"<<endl;
    cin>> nodo->usuarios.hora_habitual;
    cout<<endl<<"TIPO DE USUARIO (ADMINISTRATIVO:0, OBRERO:1, ESTUDIANTE:2, PROFESOR:3)"<<endl;
    cin>> nodo->usuarios.tipoPersonal;
    (nodo->usuarios.posee) = posee; 

    fflush(stdin);
    nodo->prox = NULL;
    return(nodo);
}

bool esVaciaLista(Tlista &lista) {
    bool log = false;
    if (lista==NULL) log= true;
    return log;
} 

void modificar(Tlista &lista,Tcarro &listacarros,  int cedula) {
    Tlista q = lista;
    int i = 1, band = 0;
 
    while(q!=NULL) {
        if(q->usuarios.cedula==cedula) {
            do{
                system("tput clear");
                
                mostrarModificacion(q);

                cout<<endl<<"QUE DESEA MODIFICAR ?(1-16).....0 PARA SALIR. ";
                cin>>opc;
                cout<<endl<<"*MODIFICANDO*";

                switch (opc){

                    case 0: break ;

                    case 1: cout<<endl<<"NUEVA CEDULA: ";
                    cin>>q->usuarios.cedula;
                    break;

                    case 2: cout<<endl<<"NUEVO NOMBRE: ";
                    scanf(" %[^\n]", q->usuarios.nombre);
                    mayuscula(q->usuarios.nombre);
                    break;

                    case 3: cout<<endl<<"NUEVO APELLIDO: ";
                    scanf(" %[^\n]", q->usuarios.apellido);
                    mayuscula(q->usuarios.apellido);
                    break;

                    case 4: cout<<endl<<"NUEVO TELEFONO DE HABITACION: ";
                    cin>>q->usuarios.telefonohab;
                    break;

                    case 5: cout<<endl<<"NUEVO TELEFONO CELULAR: ";
                    cin>>q->usuarios.celular;
                    break;

                    case 6: cout<<endl<<"NUEVO TELEFONO DE TRABAJO: ";
                    cin>>q->usuarios.teleftrab;
                    break;

                    case 7: cout<<endl<<"NUEVO DIA DE NACIMIENTO: ";
                    cin>>q->usuarios.dia;
                    break;

                    case 8: cout<<endl<<"NUEVO MES DE NACIMIENTO: ";
                    cin>>q->usuarios.mes;
                    break;

                    case 9: cout<<endl<<"NUEVO AÑO DE NACIMIENTO: ";
                    cin>>q->usuarios.year;
                    break;

                    case 10: cout<<endl<<"NUEVA DIRECCION DE HABITACION: ";
                     scanf(" %[^\n]", q->usuarios.direccionhab);
                     mayuscula(q->usuarios.direccionhab);
                    break;

                    case 11: cout<<endl<<"NUEVA DIRECCION DE TRABAJO: ";
                    scanf(" %[^\n]", q->usuarios.direcciontrab);
                    mayuscula(q->usuarios.direcciontrab);
                    break;

                    case 12: cout<<endl<<"NUEVO TELEFONO DE ALGUN FAMILIAR: ";
                    cin>>q->usuarios.telefami;
                    break;

                    case 13: cout<<endl<<"NUEVO DESTINO HABITUAL (PARA PEDIR LA COLA): ";
                    scanf(" %[^\n]", q->usuarios.destino_habitual);
                    mayuscula(q->usuarios.destino_habitual);
                    break;

                    case 14: cout<<endl<<"NUEVA HORA HABITUAL (PARA PEDIR LA COLA): ";
                    cin>>q->usuarios.hora_habitual;
                    break;

                    case 15: cout<<endl<<"POSEE VEHICULO?: (1:SI ; 0:NO) ";
                    cin>>q->usuarios.posee; if (q->usuarios.posee) {registrarCarro(listacarros,cedula);} else {eliminarCarro(listacarros,cedula);}

                    break;

                    case 16: cout<<endl<<"TIPO DE USUARIO: (ADMINISTRATIVO:0, OBRERO:1, ESTUDIANTE:2, PROFESOR:3) ";
                    cin>>q->usuarios.tipoPersonal;
                    break;
                }
            }while (opc != 0 );
            band = 1;
        }
        q = q->prox;
    }
    if(band==0)
        cout<<"\n\n ERROR, EL USUARIO INTRODUCIDO NO EXISTE"<< endl;
}

void mostrarModificacion(Tlista variable){  
    Tlista q = variable;
     
    cout<<endl;
    cout<<endl<<"1. CEDULA: "<<q->usuarios.cedula;
    cout<<endl<<"2. NOMBRE: "<<q->usuarios.nombre;
    cout<<endl<<"3. APELLIDO: "<<q->usuarios.apellido; 
    cout<<endl<<"4. TELEFONO DE HABITACION: "<<q->usuarios.telefonohab; 
    cout<<endl<<"5. TELEFONO CELULAR: "<<q->usuarios.celular;
    cout<<endl<<"6. TELEFONO DE TRABAJO: "<<q->usuarios.teleftrab;
    cout<<endl<<"7. DIA DE NACIMIENTO: "<<q->usuarios.dia; 
    cout<<endl<<"8. MES DE NACIMIENTO (EN NUMERO): "<<q->usuarios.mes; 
    cout<<endl<<"9. AÑO DE NACIMIENTO: "<<q->usuarios.year; 
    cout<<endl<<"10. DIRECCION DE HABITACION: "<<q->usuarios.direccionhab; 
    cout<<endl<<"11. DIRECCION DE TRABAJO: "<<q->usuarios.direcciontrab; 
    cout<<endl<<"12. TELEFONO DE ALGUN FAMILIAR: "<<q->usuarios.telefami; 
    cout<<endl<<"13. DESTINO HABITUAL: "<<q->usuarios.destino_habitual;
    cout<<endl<<"14. HORA HABITUAL"<<q->usuarios.hora_habitual;
    cout<<endl<<"15. POSEE VEHICULO: "<<pos[q->usuarios.posee];
    cout<<endl<<"16. TIPO DE USUARIO (ADMINISTRATIVO:0, OBRERO:1, ESTUDIANTE:2, PROFESOR:3): "<<tipoUsuario[q->usuarios.tipoPersonal]<<endl;
    
}


//CARROS
 void registrarCarro(Tcarro &listacarros, int cedula){ // INSERTANDO ELEMENTO EN PRIMERA POSICION.

        Tcarro nodocarro = crearCarro(listacarros,cedula);
        Tcarro t = new(struct listaCarros);
    
                if(listacarros==NULL) {
                listacarros = nodocarro;
                cout<<endl<<"*** CARRO: "<< nodocarro->carros.marca<<" REGISTRADO CON EXITO ***"<<endl;
                }
            else
            {
            t = listacarros;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodocarro;
                cout<<endl<<"*** CARRO: "<< t->carros.modelo<<" REGISTRADO CON EXITO ***"<<endl;
            } 
           

}

Tcarro crearCarro(Tcarro &listacarros, int cedula){

    Tcarro nodocarro = new (struct listaCarros);

    nodocarro->su_propietario = cedula;
    cout<<endl<<"REGISTRO DEL CARRO: "<< endl;
    cout<<endl<<"MARCA: "<< endl;
    scanf(" %[^\n]", nodocarro->carros.marca);
    mayuscula(nodocarro->carros.marca);
    cout<<endl<<"MODELO: "<<endl; 
    scanf(" %[^\n]", nodocarro->carros.modelo);
    mayuscula(nodocarro->carros.modelo);
    cout<<endl<<"COLOR DEL CARRO: "<<endl;
    scanf(" %[^\n]", nodocarro->carros.colorcarro);
    mayuscula(nodocarro->carros.colorcarro);
    cout<<endl<<"PLACA: "<<endl;
    scanf(" %[^\n]", nodocarro->carros.placa);
    mayuscula(nodocarro->carros.placa);
    cout<<endl<<"AÑO DEL CARRO: "<<endl;
    cin>> nodocarro->carros.year;
    cout<<endl<<"SERIAL DEL MOTOR: "<<endl;
    scanf(" %[^\n]", nodocarro->carros.serialmotor); 
    mayuscula(nodocarro->carros.serialmotor);

    
    nodocarro->prox = NULL; 
    return(nodocarro);

}

bool esVaciaCarros(Tcarro &listacarros) {
    bool log = false;
    if (listacarros==NULL) log= true;
    return log;
} 

void eliminarCarro(Tcarro &listacarros, int valor) {
    Tcarro p, ant;
    p = listacarros;
 
    if(listacarros!=NULL) {
        while(p!=NULL) {
            if(p->su_propietario==valor) {
                if(p==listacarros)
                {
                    listacarros = listacarros->prox;
                

                cout<<"***REGISTRO DE CARRO ELIMINADO CON EXITO***"<<endl<<endl;
                }
                else
                {
                    ant->prox = p->prox;
                
                delete(p);
                return;

                cout<<"***REGISTRO DE CARRO ELIMINADO CON EXITO***"<<endl<<endl;
            }
            }
            ant = p;
            p = p->prox;
            
        }

        
    }
    else
        cout<<" NO TENIA CARRO REGISTRADO..!"<<endl;
}

//COLAS
void pedirCola(Tlista &lista,Tcolas &listacolas,Tdestino &listadestinos, int cedula) {
    Tlista q = lista;
    int i = 1, band = 0;
 
    while(q!=NULL) {
        if(q->usuarios.cedula==cedula) {

                system("tput clear");
                
                mostrarCola(q);
  
                cout<<endl<<"*PIDIENDO COLA*"<<endl;

                registrarCola(q,listacolas,listadestinos);
                
                
            band = 1;
        }
        q = q->prox;
    }
    if(band==0)
        cout<<"\n\n ERROR, EL USUARIO INTRODUCIDO NO EXISTE"<< endl;
}

void registrarCola(Tlista variable, Tcolas &listacolas,Tdestino &listadestinos){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION
   
        Tlista q = variable;
        Tcolas p = listacolas;

        int band = 0;


        while(p!=NULL) {
        if(p->pedidordecola==q->usuarios.cedula) {

            cout<<endl<<"ERROR, ESTA PERSONA YA TIENE UNA SOLICITUD DE COLA."<<endl<<endl;  
            band = 1;
        }
        p = p->prox;
    }
    
    if(band==0){

        
        Tcolas nodo = crearNodoCola(q,listacolas,listadestinos);
        Tcolas t = new(struct listaColas);
    
                if(listacolas==NULL) {
                listacolas = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->pedidordecola<<" HA PEDIDO LA COLA CON EXITO***"<<endl;
                }
            else
            {
            t = listacolas;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->pedidordecola<<" HA PEDIDO LA COLA CON EXITO***"<<endl;
            }   
    }
}

void registrarColaModificada(Tcolas nodo , Tcolas &listacolas){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION
        
        Tcolas t = new(struct listaColas);
    
                if(listacolas==NULL) {
                listacolas = nodo;
                //cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->pedidordecola<<" HA PEDIDO LA COLA CON EXITO***"<<endl;
                }
            else
            {
            t = listacolas;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                //cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->pedidordecola<<" HA PEDIDO LA COLA CON EXITO***"<<endl;
            }   
    
}

bool verificarDestinoRepetido(char destino[100],Tdestino &listadestinos){
    Tdestino q = listadestinos;
    bool log = false;

    while (q != NULL){

        if (!strcmp(destino,q->destinos.direccion)){

            log = true;
        }

        q=q->prox;

    }
    return (log);
}

Tcolas crearNodoCola(Tlista variable,Tcolas &listacolas, Tdestino &listadestinos){

    bool op;
    int hora;

    Tcolas nodo = new (struct listaColas);
    Tlista q = variable;

    (nodo->pedidordecola) = (q->usuarios.cedula);
  
 


    cout<<endl<<"DESEA PEDIR LA COLA PARA EL DESTINO HABITUAL? (1:SI ; 0:NO)"<<endl;
    cin>>op;

 
    if (op){ 
    strcpy(nodo->colas.destino,q->usuarios.destino_habitual);
    strcpy(dest,q->usuarios.destino_habitual);
    if (!verificarDestinoRepetido(dest,listadestinos)){
    registrarDestinos(dest,listadestinos);};

    }
    else
    {
        cout<<endl<<"INTRODUZCA EL DESTINO DE LA COLA: ";
        scanf(" %[^\n]", nodo->colas.destino);
        mayuscula(nodo->colas.destino); 
 
        strcpy(dest,nodo->colas.destino);
        if (!verificarDestinoRepetido(dest,listadestinos)){
        registrarDestinos(dest,listadestinos);};
       
    }

    cout<<endl<<"DESEA PEDIR LA COLA PARA CON LA HORA HABITUAL? (1:SI ; 0:NO)"<<endl;
    cin>>op;

    if (op){ 
    (nodo->colas.hora) = (q->usuarios.hora_habitual);
    }
    else
    {
        cout<<endl<<"INTRODUZCA LA HORA DE LA COLA: ";
        cin>>hora;
        (nodo->colas.hora) = hora;
    }
        nodo->prox = NULL;
       return (nodo);
}



void registrarDestinos (char destino[100],Tdestino &listadestinos){

        Tdestino nodo = crearDestino(listadestinos,destino);
        Tdestino t = new(struct listaDestinos);
        int codigo = 1; int cod = 2;
                if(listadestinos==NULL) {

                (nodo->destinos.codigo) = codigo;
                listadestinos = nodo;

                }
            else
            {
            t = listadestinos;
            while(t->prox!=NULL) {

                t = t->prox;
                cod++;

                }
                (nodo->destinos.codigo) = cod;
                t->prox = nodo;
            } 

}

Tdestino crearDestino(Tdestino &listadestinos,char destino[100]){

    Tdestino nodo = new (struct listaDestinos);

    strcpy(nodo->destinos.direccion,destino);
    nodo->prox = NULL;
    return(nodo);
}

bool buscarDireccionClave(Tdestino &listadestinos, int codigo) {
    Tdestino q = listadestinos;
    bool log;
    int i = 1, band = 0;
 
    while(q!=NULL) {
        if(q->destinos.codigo==codigo) {

            band = 1;
            log = true;
        }
        q = q->prox;
        i++;
    }
    if(band==0){

        log = false;

     }

    return(log);
    

}

void eliminarColaModificada(Tcolas &listacolas, int valor) {
    Tcolas p, ant;
    p = listacolas;



    if(listacolas!=NULL) {
        
        while(p!=NULL) {
            
            if(p->pedidordecola==valor) {
                if(p==listacolas)
                {
                    listacolas = listacolas->prox;
               
                cout<<"***PETICION DE COLA ELIMINADA CON EXITO***"<<endl<<endl;
                
                }
                else
                {
                    
                    ant->prox = p->prox;
                
                delete(p);
                return;

                cout<<"***PETICION DE COLA ELIMINADA CON EXITO***"<<endl<<endl;
                
                }

            }


            ant = p;
            p = p->prox;    
        }

        
    }

}

void mostrarCola(Tlista variable){  
    Tlista q = variable;
     
    cout<<endl;
    cout<<endl<<"1. CEDULA: "<<q->usuarios.cedula;
    cout<<endl<<"2. NOMBRE: "<<q->usuarios.nombre;
    cout<<endl<<"3. APELLIDO: "<<q->usuarios.apellido; 
    cout<<endl<<"4. TELEFONO CELULAR: "<<q->usuarios.celular;
    cout<<endl<<"5. DESTINO HABITUAL: "<<q->usuarios.destino_habitual;
    cout<<endl<<"6. HORA HABITUAL: "<<q->usuarios.hora_habitual;
    cout<<endl<<"7. TIPO DE USUARIO: "<<tipoUsuario[q->usuarios.tipoPersonal];
    //cout<<endl<<"8. POSEE CARRO: "<<q->usuarios.mostrarposee<<endl<<endl;   
}

void modificarCola(Tcolas &listacolas,Tdestino &listadestinos, int cedula, Tprocesa &listaprocesa) {
    Tcolas q = listacolas;
    int i = 1, band = 0;
    int pc;
    while(q!=NULL) {
        if(q->pedidordecola==cedula) {
            if (!Procesada(listaprocesa,cedula)){
            do{
                system("tput clear");
                
                mostrarModificacionCola(q);

                cout<<endl<<"QUE DESEA MODIFICAR ?(1-2).....0 PARA SALIR. ";
                cin>>pc;
                cout<<endl<<"*MODIFICANDO*";

                switch (pc){

                    case 0: break ;

                    case 1: cout<<endl<<"NUEVA DESTINO: ";
                    scanf(" %[^\n]", q->colas.destino); 
                    mayuscula(q->colas.destino);

                    strcpy(dest,q->colas.destino);
                    if (!verificarDestinoRepetido(dest,listadestinos)){
                    registrarDestinos(dest,listadestinos);};
               
                    break;

                    case 2: cout<<endl<<"NUEVA HORA DE PETICION: ";
                    cin>>q->colas.hora;
                    break;     
                }
            }while (pc != 0 );
        }else
        {

            Tcolas n = new (struct listaColas);
                (n->pedidordecola) = (q->pedidordecola);
                strcpy(n->colas.destino,q->colas.destino); 
                (n->colas.hora) = (q->colas.hora);
                n->prox=NULL;
                eliminarColaModificada(listacolas,q->pedidordecola);
            do{
                system("tput clear");
        
                mostrarModificacionCola(n);

                cout<<endl<<"QUE DESEA MODIFICAR ?(1-2).....0 PARA SALIR. ";
                cin>>pc;
                cout<<endl<<"*MODIFICANDO*";

                switch (pc){

                    case 0: break ;

                    case 1: cout<<endl<<"NUEVO DESTINO: ";
                        scanf(" %[^\n]", n->colas.destino ); 
                        mayuscula(n->colas.destino);

                        strcpy(dest,n->colas.destino);
                        if (!verificarDestinoRepetido(dest,listadestinos)){
                            registrarDestinos(dest,listadestinos);
                        };
               
                    break;

                    case 2: cout<<endl<<"NUEVA HORA DE PETICION: ";
                        cin>>n->colas.hora;
                    break;     
                }    
            }while (pc != 0 );

            registrarColaModificada(n,listacolas);
            return ;
        }
         band = 1;
        }
        q = q->prox;
    }
    if(band==0)
        cout<<"\n\n ERROR, LA PETICION INTRODUCIDA NO EXISTE"<< endl;
}

void mostrarModificacionCola(Tcolas variable){  
    Tcolas q = variable;
     
    cout<<endl<<"NUMERO DE CEDULA DEL PEDIDOR DE COLA: "<<q->pedidordecola;
    cout<<endl<<"1. DESTINO DE LA COLA: "<<q->colas.destino;
    cout<<endl<<"2. HORA DE PETICION DE COLA: "<<q->colas.hora<<endl<<endl;
    
    
}

void eliminarCola(Tcolas &listacolas, int valor) {
    Tcolas p, ant;
    p = listacolas;
    bool bandera = false ;


    if(listacolas!=NULL) {
        bandera = true ;
        while(p!=NULL) {
            
            if(p->pedidordecola==valor) {
                if(p==listacolas)
                {
                    listacolas = listacolas->prox;
                bandera = false;
                cout<<"***PETICION DE COLA ELIMINADA CON EXITO***"<<endl<<endl;
                
                }
                else
                {
                    bandera = false; 
                    ant->prox = p->prox;
                
                delete(p);
                return;

                cout<<"***PETICION DE COLA ELIMINADA CON EXITO***"<<endl<<endl;
                
                }

            }


            ant = p;
            p = p->prox;    
        }

        
    }
  
    else
    {
        cout<<"AUN NADIE HA SOLICITADO EL SERVICIO DE COLAS "<<endl;
        
     bandera = false;
    }
  
    if (bandera) {cout<<"ESTA INTRODUCIENDO UN NUMERO DE CEDULA INVALIDO..."<<endl;}

}

void mostrarSolicitudProcesada(Tcolas variable,Tlista &lista, Tcarro &listacarros,int cedula){ 

    Tcolas q = variable;
    Tlista a = lista;
    Tcarro c  = listacarros;
     
    cout<<"SOLICITUD PROCESADA...."<<endl;
    cout<<endl<<"NUMERO DE CEDULA DEL PEDIDOR DE COLA: "<<q->pedidordecola<<endl;
    cout<<"DESTINO DE LA COLA: "<<q->colas.destino<<endl;
    cout<<"HORA DE PETICION DE COLA: "<<q->colas.hora<<endl<<endl;

    while (a!=NULL){

        if (cedula == a->usuarios.cedula) {

            //datos del prestador 
            cout<<"MOSTRANDO DATOS DEL PRESTADOR DE SERVICIO: ";
            cout<<endl<<"CEDULA: "<<a->usuarios.cedula;
            cout<<endl<<"NOMBRE: "<<a->usuarios.nombre;
            cout<<endl<<"APELLIDO: "<<a->usuarios.apellido; 
            cout<<endl<<"TELEFONO CELULAR: "<<a->usuarios.celular<<endl;

        }

      a = a->prox;  
    }

    while (c != NULL){
    
    if (cedula == c->su_propietario){
    
    //mostrar datos del carro.
    cout<<endl<<"DATOS DEL CARRO: "<<endl;
    cout<<endl<<"MARCA: "<<c->carros.marca;
    cout<<endl<<"MODELO: "<<c->carros.modelo;
    cout<<endl<<"COLOR: "<<c->carros.colorcarro;
    cout<<endl<<"PLACA: "<<c->carros.placa;
    cout<<endl<<"ANIO: "<<c->carros.year;
    cout<<endl<<"SERIAL DEL MOTOR: "<<c->carros.serialmotor<<endl;  

    }

    c = c->prox;
    }    
}

void mostrarSolicitudCola(Tcolas &listacolas,  int cedula,Tprocesa &listaprocesa,Tcarro &listacarros,Tlista &lista){
    Tcolas q = listacolas;
    int  band = 0;
    int mostrar;
 
    while(q!=NULL) {

        if(q->pedidordecola==cedula) {
                mostrar = q->pedidordecola ;
                if (Procesada(listaprocesa,mostrar)){
                    
                   mostrar = cedulaDelPrestador(listaprocesa,q->pedidordecola);
                  
                   mostrarSolicitudProcesada(q,lista,listacarros,mostrar);
              }else
              {
                  
                   cout<<endl<<endl<<"SU PETICION AUN ESTA EN COLA..."<<endl;
                    mostrarSolicitud(q);
                }
            band = 1;
            
        }
       q = q->prox;
    }
    if(band==0)
        cout<<"\n\n ERROR, LA PETICION INTRODUCIDA NO EXISTE"<< endl;

}

void mostrarSolicitud(Tcolas variable){ 

    Tcolas q = variable;
     
   
    cout<<endl<<"NUMERO DE CEDULA DEL PEDIDOR DE COLA: "<<q->pedidordecola<<endl;
    cout<<"DESTINO DE LA COLA: "<<q->colas.destino<<endl;
    cout<<"HORA DE PETICION DE COLA: "<<q->colas.hora<<endl;
        
    
}

bool esVaciaColas(Tcolas &listacolas) {
    bool log = false;
    if (listacolas==NULL) log= true;
    return log;
} 

void mostrarSolicitudDestino(Tcolas &listacolas,Tdestino &listadestinos){
    Tcolas q = listacolas;
    Tdestino p = listadestinos;
    int  band = 0;
    int codig;
    char busc[100];
    bool error = true ;

    if (p==NULL)
    {cout<<endl<<"AUN NADIE HA SOLICITADO EL SERVICIO DE COLAS.."<<endl;}
    else
    {

             while (error == true) { //ciclo para ver si no hay error ,n 
        	
        		    cout<<endl<<"INTRODUZCA UN DESTINO A VERIFICAR DE LA SIGUIENTE LISTA (USE EL CODIGO)"<<endl;
        	
        		    cout<<endl<<endl<<"*LISTA DE DESTINOS*"<<endl;
        	
        		    mostrarDestinos(listadestinos); 
        	
        		    cout<<endl<<endl<<"*FIN DE LA LISTA*"<<endl;
        		    cout<<endl<<endl<<"INTRODUZA EL CODIGO: ";
        		   
        		    cin>>codig;

        		    if (!buscarDireccionClave(listadestinos,codig)){cout<<"***ERROR EL CODIGO INTRODUCIDO NO ESTA EN LA LISTA, INTENTE NUEVAMENTE"<<endl; error = true;}
        		    else
        		    {

        			cout<<"EL DESTINO SI ESTA."<<endl; 
        				

        				    	while(p!=NULL) {
        				        if(p->destinos.codigo==codig) {

        				        	strcpy(busc,p->destinos.direccion);
        				      
        				        }
        				       		p = p->prox;
        				        }

        				
        				error = false;
        	}

            }
         
            while(q!=NULL) {

                if(!strcmp(busc,q->colas.destino)) {
                    
                        //system("tput clear");
                        
                        mostrarSolicitud(q);

                    band = 1;
                }
               q = q->prox;
            }

    if(band==0)
        {cout<<"\n\n ERROR, NO EXISTEN PETICIONES DE COLA A ESTE DISTINO.."<< endl;}
    }
    
}

void ofrecerCola(Tlista &lista,Tofrece &listaofrece,Tdestino &listadestinos,  int cedula) {
    Tlista q = lista;
    int  band = 0;
    if (listadestinos != NULL){
    while(q!=NULL) {
        if(q->usuarios.cedula==cedula) {


                system("tput clear");
                
                mostrarCola(q);
  
                cout<<endl<<endl<<"OFRECIENDO LA COLA..";

                registrarOfrece(q,listaofrece,listadestinos);
                
                
            band = 1;
        }
        q = q->prox;
    }
    if(band==0)
        cout<<"\n\n ERROR, EL USUARIO INTRODUCIDO NO EXISTE"<< endl;
    }
    else 
    {cout<<endl<<"ERROR, NO PUEDE OFRECER COLA, AUN NADIE HA SOLICITADO EL SERVICIO"<<endl;};
}

void registrarOfrece(Tlista variable, Tofrece &listaofrece,Tdestino &listadestinos){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION
   
        Tlista q = variable;
        Tofrece p = listaofrece;

        int band = 0,  band2 = 0;

    

        if(!q->usuarios.posee){
 
          band = 2;
      }


        while(p!=NULL) {
            if(p->ofrecedordecola==q->usuarios.cedula) {

                cout<<endl<<"ERROR, ESTA PERSONA YA TIENE UN OFRECIMIENTO DE COLA."<<endl<<endl;  
                band = 1;
           

            }
            p = p->prox;
        }


       

    if(band==2){cout<<endl<<endl<<"ERROR, ESTA PERSONA NO POSEE VEHICULO PARA PODER PRESTAR EL SERVICIO."<<endl<<endl; }

   
    
    if(band==0){

        
        Tofrece nodo = crearNodoOfrece(q,listaofrece,listadestinos);
        Tofrece t = new(struct listaOfrece);
    
                if(listaofrece==NULL) {
                listaofrece = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->ofrecedordecola<<" HA OFRECIDO LA COLA CON EXITO***"<<endl;
                }
            else
            {
            t = listaofrece;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->ofrecedordecola<<" HA OFRECIDO LA COLA CON EXITO***"<<endl;
            }   
    }
}

void mostrarDestinos(Tdestino variable){

    Tdestino q = variable; 


    if (q==NULL)
        {cout<<endl<<"NO HAY DESTINOS..."<<endl;}

    else

    {


    while (q != NULL ) {

    cout<<endl<<"DESTINO: "<< q->destinos.direccion<<", CODIGO: "<<q->destinos.codigo<<"."<<endl;
    q = q->prox; 

    }

    }
}

Tofrece crearNodoOfrece(Tlista variable,Tofrece &listaofrece,Tdestino &listadestinos){

    int codigo,hora,puestos;
    bool error = true; 
    int cod;
    char busc[100];
    Tdestino p = listadestinos;
    bool log,log2;
    int i = 1, band = 0;
    int ofrece;
    
    Tofrece nodo = new (struct listaOfrece);
    Tlista q = variable;

    (nodo->ofrecedordecola) = (q->usuarios.cedula);

    cout<<"DESEA OFRECER LA COLA A LA HORA HABITUAL?(1:SI, 0:NO): "<<endl;
    cin>>log2;
    if (log2){
    (nodo->colas.hora) = (q->usuarios.hora_habitual);
	}else
	{cout<<"INTRODUZCA LA HORA A OFRECER LA COLA: "<<endl;
	
	cin>>ofrece; 

	(nodo->colas.hora) = ofrece;
	}

    cout<<endl<<"INTRODUZCA EL NUMERO DE PUESTOS A OFRECER: "<<endl;
    cin>>puestos;

    (nodo->numerodepuestos) = puestos;
   
    while (error == true) { //ciclo para ver si no hay error ,n 
	
		    cout<<endl<<"INTRODUZCA UN DESTINO A OFRECER DE LA SIGUIENTE LISTA (USE EL CODIGO)"<<endl;
	
		    cout<<endl<<endl<<"*LISTA DE DESTINOS*"<<endl;
	
		    mostrarDestinos(listadestinos); 
	
		    cout<<endl<<endl<<"*FIN DE LA LISTA*"<<endl;
		    cout<<endl<<endl<<"INTRODUZA EL CODIGO: ";
		   
		    cin>>cod;

		    if (!buscarDireccionClave(listadestinos,cod)){cout<<"ERROR EL CODIGO INTRODUCIDO NO ESTA EN LA LISTA, INTENTE NUEVAMENTE"<<endl; error = true;}
		    else
		    {

			cout<<"EL DESTINO SI ESTA."<<endl; 
				

				    	while(p!=NULL) {
				        if(p->destinos.codigo==cod) {

				        	strcpy(busc,p->destinos.direccion);
				        	strcpy(nodo->colas.destino,busc);
				      
				        }
				       		p = p->prox;
				        }

				
				error = false;
			}

    }
 
    nodo->prox = NULL;
    return (nodo);
}
//


void mostrarOfrecimientosModificacion(Tofrece variable){

    Tofrece q = variable; 


    cout<<endl<<"NUMERO DE CEDULA DEL OFRECEDOR DE COLA : "<<q->ofrecedordecola;
    cout<<endl<<"1. DESTINO DE LA COLA: "<<q->colas.destino;
    cout<<endl<<"2. NUMERO DE PUESTOS: "<<q->numerodepuestos;
    cout<<endl<<"3. HORA: "<<q->colas.hora<<endl<<endl;


}


void modificarOfrece(Tofrece &listaofrece,  int cedula) {
    Tofrece q = listaofrece;
    int i = 1, band = 0;
 
    while(q!=NULL) {
        if(q->ofrecedordecola==cedula) {
            do{
                system("tput clear");
                
                mostrarOfrecimientosModificacion(q);

                cout<<endl<<"QUE DESEA MODIFICAR ?(1-3).....0 PARA SALIR. ";
                cin>>opc;
                cout<<endl<<"*MODIFICANDO*";

                switch (opc){

                    case 0: break ;

                    case 1: cout<<endl<<"NUEVO DESTINO: ";
                    scanf(" %[^\n]", q->colas.destino);
                    mayuscula(q->colas.destino);
               
                    break;

                    case 2: cout<<endl<<"NUMERO DE PUESTOS: ";
                    cin>>q->numerodepuestos;
                    break;

                    case 3: cout<<endl<<"NUEVA HORA: ";
                    cin>>q->colas.hora;
                    break;

                   
                }
            }while (opc != 0 );
            band = 1;
        }
        q = q->prox;
    }
    if(band==0)
        cout<<"\n\n ERROR, EL OFRECIMIENTO INTRODUCIDO NO EXISTE"<< endl;
}

void mostrarOfrecimientos(Tofrece variable){

    Tofrece q = variable; 


    if (esVaciaOfrece(variable))
        {cout<<endl<<"NO HAY OFRECIMIENTOS DE COLAS..."<<endl;}

    else

    {


    while (q != NULL ) {

    cout<<endl<<"NUMERO DE CEDULA DEL OFRECEDOR DE COLA : "<<q->ofrecedordecola;
    cout<<endl<<"1. DESTINO DE LA COLA: "<<q->colas.destino;
    cout<<endl<<"2. NUMERO DE PUESTOS: "<<q->numerodepuestos;
    cout<<endl<<"3. HORA: "<<q->colas.hora<<endl<<endl;

    q = q->prox; 

    }

    }
}

void eliminarOfrece(Tofrece &listaofrece, int valor) {
    Tofrece p, ant;
    p = listaofrece;
    bool ba = false;
 
    if(listaofrece!=NULL) {
         
        while(p!=NULL) {
            ba = true;
            if(p->ofrecedordecola==valor) {
                if(p==listaofrece)
                {
                    listaofrece = listaofrece->prox;
                    ba = false;

                cout<<"***OFRECIMIENTO DE COLA ELIMINADO CON EXITO***"<<endl<<endl;
                }
                else
                {
                    ant->prox = p->prox;
                    ba = false;
                delete(p);
                return;

                cout<<"***OFRECIMIENTO DE COLA ELIMINADO CON EXITO***"<<endl<<endl;
            }
            }
            ant = p;
            p = p->prox;
            
            
        }

        
    }
    else{
        cout<<"NO HAY OFRECIMIENTOS.."<<endl;
        ba = false;
    }
    if (ba) {cout<<"ESTA INTRODUCIENDO UN NUMERO DE CEDULA INVALIDO..."<<endl;}

}
    

bool esVaciaOfrece(Tofrece &listaofrece) {
    bool log = false;
    if (listaofrece==NULL) log= true;
    return log;
} 

//LECTURA Y ESCRITURA..

//LECTURA.
void escribirLista(Tlista variable) {

    Tlista q = variable;

    ofstream fs("lista.txt"); 
   if (q!=NULL){
   // Crea un fichero de salida
   
   fs<<"----------"<<endl;
   while (q != NULL ) {


    if (q->prox == NULL){
    
    fs<<q->usuarios.nombre<<endl;
    fs<<q->usuarios.apellido<<endl;
    fs<<q->usuarios.direccionhab<<endl; 
    fs<<q->usuarios.direcciontrab<<endl;  
    fs<<q->usuarios.destino_habitual<<endl; 
    fs<<q->usuarios.telefonohab<<endl; 
    fs<<q->usuarios.celular<<endl;
    fs<<q->usuarios.teleftrab<<endl;
    fs<<q->usuarios.telefami<<endl; 
    fs<<q->usuarios.dia<<endl;
    fs<<q->usuarios.mes<<endl;
    fs<<q->usuarios.year<<endl;  
    fs<<q->usuarios.hora_habitual<<endl;
    fs<<q->usuarios.posee<<endl;
    fs<<q->usuarios.tipoPersonal<<endl;
    fs<<q->usuarios.cedula;
    }else
    {
    fs<<q->usuarios.nombre<<endl;
    fs<<q->usuarios.apellido<<endl;
    fs<<q->usuarios.direccionhab<<endl; 
    fs<<q->usuarios.direcciontrab<<endl;  
    fs<<q->usuarios.destino_habitual<<endl; 
    fs<<q->usuarios.telefonohab<<endl; 
    fs<<q->usuarios.celular<<endl;
    fs<<q->usuarios.teleftrab<<endl;
    fs<<q->usuarios.telefami<<endl;
    fs<<q->usuarios.dia<<endl;
    fs<<q->usuarios.mes<<endl;
    fs<<q->usuarios.year<<endl;  
    fs<<q->usuarios.hora_habitual<<endl;
    fs<<q->usuarios.posee<<endl;
    fs<<q->usuarios.tipoPersonal<<endl;
    fs<<q->usuarios.cedula<<endl;
    }

    q = q->prox;
   } 

   fs.close();
}
}

void escribirListaCarros(Tcarro variable) {

    Tcarro q = variable;
   
   // Crea un fichero de salida
   ofstream fs("listacarros.txt"); 

   if (q!=NULL){
   fs<<"-----------------------"<<endl;
   while (q != NULL ) {

    if (q->prox == NULL){

    fs<<q->carros.marca<<endl;
    fs<<q->carros.modelo<<endl;
    fs<<q->carros.colorcarro<<endl;
    fs<<q->carros.serialmotor<<endl;
    fs<<q->carros.placa<<endl;  	
    fs<<q->carros.year<<endl;
    fs<<q->su_propietario;
    
    }
    else
    {

    fs<<q->carros.marca<<endl;
    fs<<q->carros.modelo<<endl;
    fs<<q->carros.colorcarro<<endl;
    fs<<q->carros.serialmotor<<endl;
    fs<<q->carros.placa<<endl;  	
    fs<<q->carros.year<<endl;
    fs<<q->su_propietario<<endl;
    }
    q = q->prox;
   } 

   fs.close();
}
}




void escribirListaColas(Tcolas variable) {

    Tcolas q = variable;
   
   // Crea un fichero de salida
   ofstream fs("listacolas.txt");
   if (q!=NULL){ 
   fs<<"-----------------------"<<endl;
   while (q != NULL ) {

    if (q->prox == NULL){
    
        fs<<q->colas.destino<<endl;
        fs<<q->pedidordecola<<endl;
        fs<<q->colas.hora;
    }
    else
    {
    
        fs<<q->colas.destino<<endl;
        fs<<q->pedidordecola<<endl;
        fs<<q->colas.hora<<endl;

    }
    q = q->prox;
   }

   fs.close();
}
}

void escribirListaOfrece(Tofrece variable) {

    Tofrece q = variable;
   
   // Crea un fichero de salida
   ofstream fs("listaofrece.txt"); 
   if (q!=NULL){ 
    fs<<"-----------------------"<<endl;
   while (q != NULL ) {

    if (q->prox == NULL){
    fs<<q->colas.destino<<endl;
    fs<<q->numerodepuestos<<endl;
    fs<<q->colas.hora<<endl;
    fs<<q->ofrecedordecola;

    }
    else
    {

    fs<<q->colas.destino<<endl; 
    fs<<q->numerodepuestos<<endl;
    fs<<q->colas.hora<<endl;
    fs<<q->ofrecedordecola<<endl;
    }
    
    q = q->prox;
   } 

   fs.close();
}
}

void escribirListaDestino(Tdestino variable) {

    Tdestino q = variable;
   
   // Crea un fichero de salida
   ofstream fs("listadestinos.txt");
   if (q!=NULL){ 
   fs<<"-----------------------"<<endl; 
   while (q != NULL ) {

    if (q->prox == NULL){
    fs<<q->destinos.direccion<<endl;
    fs<<q->destinos.codigo;
    }
    else
    {
    fs<<q->destinos.direccion<<endl;
    fs<<q->destinos.codigo<<endl;
    }
    q = q->prox;
   } 

   fs.close();
}
}

//CARGAR DE FICHEROS. 
void cargarPersona(Tlista nodo,Tlista &lista){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION.
   
    Tlista q = lista;
    int i = 1, band = 0;

        
        Tlista t = new(struct listaUsuarios);

        if(lista==NULL) {

                lista = nodo;
                cout<<endl<<"*** USURAIO DE CEDULA: "<< nodo->usuarios.cedula<<" REGISTRADO CON EXITO ***"<<endl;

                }
            else
            {
            t = lista;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                cout<<endl<<"*** USUARIO DE CEDULA: "<< nodo->usuarios.cedula<<" REGISTRADO CON EXITO ***"<<endl;

            }   
}

void cargarCarro(Tcarro nodocarro, Tcarro &listacarros){ // INSERTANDO ELEMENTO EN PRIMERA POSICION.

        //Tcarro nodocarro = crearCarro(listacarros,cedula);
        Tcarro t = new(struct listaCarros);
    
                if(listacarros==NULL) {
                listacarros = nodocarro;
                cout<<"*** CARRO: "<< nodocarro->carros.marca<<" REGISTRADO CON EXITO ***"<<endl;
                }
            else
            {
            t = listacarros;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodocarro;
                cout<<"*** CARRO: "<< t->carros.modelo<<" REGISTRADO CON EXITO ***"<<endl;
            } 
           

}

void cargarCola(Tcolas nodo, Tcolas &listacolas){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION
   
        

    int band = 0;
    
    if(band==0){

        
        Tcolas t = new(struct listaColas);
    
                if(listacolas==NULL) {
                listacolas = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->pedidordecola<<" HA PEDIDO LA COLA CON EXITO***"<<endl;
                }
            else
            {
            t = listacolas;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->pedidordecola<<" HA PEDIDO LA COLA CON EXITO***"<<endl;
            }   
    }
}


void cargarDestino (Tdestino nodo,Tdestino &listadestinos){

        //Tdestino nodo = crearDestino(listadestinos,destino);
        Tdestino t = new(struct listaDestinos);
        int codigo = 1; int cod = 2;
                if(listadestinos==NULL) {

                (nodo->destinos.codigo) = codigo;
                listadestinos = nodo;
                cout<<endl<<"DESTINO CARGADO"<<endl;
                }
            else
            {
            t = listadestinos;
            while(t->prox!=NULL) {

                t = t->prox;
                cod++;

                }
                (nodo->destinos.codigo) = cod;
                t->prox = nodo;
                cout<<endl<<"DESTINO CARGADO"<<endl;
            } 

}

void cargarOfrece(Tofrece nodo, Tofrece &listaofrece){ // INSERTANDO ELEMENTO EN LA ULTIMA POSICION
   
        //Tlista q = variable;
        //Tofrece p = listaofrece;

        int band = 0,  band2 = 0;

    
    if(band==0){

        
        //Tofrece nodo = crearNodoOfrece(q,listaofrece,listadestinos);
        Tofrece t = new(struct listaOfrece);
    
                if(listaofrece==NULL) {
                listaofrece = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->ofrecedordecola<<" HA OFRECIDO LA COLA CON EXITO***"<<endl;
                }
            else
            {
            t = listaofrece;
            while(t->prox!=NULL) {
                t = t->prox;
                }
                t->prox = nodo;
                cout<<endl<<"*** EL USUARIO DE CEDULA: "<< nodo->ofrecedordecola<<" HA OFRECIDO LA COLA CON EXITO***"<<endl;
            }   
    }
}


void cargarLista(Tlista &lista, char dirLista[200]) {
   
   char nombre[100]="0";
   char apellido[100]="0";
   char direccionhab[100]="0";
   char direcciontrabajo[100]="0";
   char destino_habitual[100]="0";
   
   
   char telefonohab[100]="0";
   char celular[100]="0"; 
   char telefonotrabajo[100]="0";
   char telefami[100]="0";

   int dia=0;
   int mes=0;
   int year=0;
   int horahab=0;
   int posee=0;
   int tipopersonal=0;
   int cedula=0;

   FILE *archivo;

   archivo = fopen(dirLista, "rt");
   if (archivo == NULL) {
      printf("\n\n\n No existe el archivo \"%s\" \n\n\n", dirLista);
      system("pause");
      exit(1) ;
   }

   //verifica si el archivo esta vacio y pone el cursor en el la primera prosicion
   long int file_start = ftell(archivo);
   fseek(archivo, 0, SEEK_END);
   long int file_end = ftell(archivo);
   if (file_end == file_start) return;

   fseek(archivo, 0, SEEK_SET);
 
   while (!(feof(archivo))) {
    
   Tlista nodo = new (struct listaUsuarios); 
   fgets(nombre, 100, archivo);
   fgets(nombre, 100, archivo);
   strtok(nombre, "\n");
   fgets(apellido, 100, archivo);
   strtok(apellido, "\n");
   fgets(direccionhab, 100, archivo);
   strtok(direccionhab, "\n");
   fgets(direcciontrabajo, 100, archivo);
   strtok(direcciontrabajo, "\n");
   fgets(destino_habitual, 100, archivo);
   strtok(destino_habitual, "\n");
   
   fgets(telefonohab, 100, archivo);
   strtok(telefonohab, "\n");
   fgets(celular, 100, archivo);
   strtok(celular, "\n");
   fgets(telefonotrabajo, 100, archivo);
   strtok(telefonotrabajo, "\n");
   fgets(telefami, 100, archivo);
   strtok(telefami, "\n");
   
   fscanf(archivo, "%i", &dia);
   fscanf(archivo, "%i", &mes);
   fscanf(archivo, "%i", &year);
   fscanf(archivo, "%i", &horahab);
   fscanf(archivo, "%i", &posee);
   fscanf(archivo, "%i", &tipopersonal);
   fscanf(archivo, "%i", &cedula);
   
   
    cout<<nombre<<endl;
    strcpy(nodo->usuarios.nombre,nombre);
    cout<<apellido<<endl;
    strcpy(nodo->usuarios.apellido,apellido);
    cout<<direccionhab<<endl;
    strcpy(nodo->usuarios.direccionhab,direccionhab);
    cout<<direcciontrabajo<<endl;
    strcpy(nodo->usuarios.direcciontrab,direcciontrabajo);
    cout<<destino_habitual<<endl;
    strcpy(nodo->usuarios.destino_habitual,destino_habitual);

    cout<<telefonohab<<endl;
    strcpy(nodo->usuarios.telefonohab,telefonohab);
    cout<<celular<<endl;
    strcpy(nodo->usuarios.celular,celular);
    cout<<telefonotrabajo<<endl;
    strcpy(nodo->usuarios.teleftrab,telefonotrabajo);
    cout<<telefami<<endl;
    strcpy(nodo->usuarios.telefami,telefami);

    cout<<dia<<endl;
    (nodo->usuarios.dia) = dia;
    cout<<mes<<endl;
    (nodo->usuarios.mes) = mes;
    cout<<year<<endl;
    (nodo->usuarios.year) = year;
    
    cout<<horahab<<endl;
    (nodo->usuarios.hora_habitual) = horahab;
    cout<<posee<<endl;
    (nodo->usuarios.posee) = posee;
    cout<<tipopersonal<<endl;
    (nodo->usuarios.tipoPersonal) = tipopersonal;
    cout<<cedula;
    (nodo->usuarios.cedula) = cedula;
    nodo->prox = NULL;
    cargarPersona(nodo,lista);
    }

    fclose(archivo);
}

void cargarListaCarros(Tcarro &listacarros, char dirListaCarros[200]) {
   
   char marca[100]="0";
   char modelo[100]="0";
   char colorcarro[100]="0";
   char serialmotor[100]="0";
   char placa[100]="0";
   

   int year=0;
   int su_propietario=0;
 


   FILE *archivo;

   archivo = fopen(dirListaCarros, "rt");
   if (archivo == NULL) {
      printf("\n\n\n No existe el archivo \"%s\" \n\n\n", dirListaCarros);
      system("pause");
      exit(1) ;
   }

   //verifica si el archivo esta vacio y pone el cursor en el la primera prosicion
   long int file_start = ftell(archivo);
   fseek(archivo, 0, SEEK_END);
   long int file_end = ftell(archivo);
   if (file_end == file_start) return;

   fseek(archivo, 0, SEEK_SET);
 
   while (!(feof(archivo))) {
    
   Tcarro nodo = new (struct listaCarros); 
   fgets(marca, 100, archivo);
   fgets(marca, 100, archivo);
   strtok(marca, "\n");
   fgets(modelo, 100, archivo);
   strtok(modelo, "\n");
   fgets(colorcarro, 100, archivo);
   strtok(colorcarro, "\n");
   fgets(serialmotor, 100, archivo);
   strtok(serialmotor, "\n");
   fgets(placa, 100, archivo);
   strtok(placa, "\n");
   
   
   fscanf(archivo, "%i", &year);
   fscanf(archivo, "%i", &su_propietario);
 
   
   
    cout<<marca<<endl;
    strcpy(nodo->carros.marca,marca);
    cout<<modelo<<endl;
    strcpy(nodo->carros.modelo,modelo);
    cout<<colorcarro<<endl;
    strcpy(nodo->carros.colorcarro,colorcarro);
    cout<<serialmotor<<endl;
    strcpy(nodo->carros.serialmotor,serialmotor);
    cout<<placa<<endl;
    strcpy(nodo->carros.placa,placa);

   

    cout<<year<<endl;
    (nodo->carros.year) = year;
    cout<<su_propietario<<endl;
    (nodo->su_propietario) = su_propietario;
    
    nodo->prox = 	NULL;
    cargarCarro(nodo,listacarros);
    }

    fclose(archivo);
}
 

void cargarListaColas(Tcolas &listacolas, char dirListaCarros[200]) {
   
   char destino[100]="0";
   int pedidordecola=0;
   int hora=0;
   
   FILE *archivo;

   archivo = fopen(dirListaCarros, "r");
   if (archivo == NULL) {
      printf("\n\n\n No existe el archivo \"%s\" \n\n\n", dirListaCarros);
      system("pause");
      exit(1) ;
   }

   //verifica si el archivo esta vacio y pone el cursor en el la primera prosicion
   long int file_start = ftell(archivo);
   fseek(archivo, 0, SEEK_END);
   long int file_end = ftell(archivo);
   if (file_end == file_start) return;

   fseek(archivo, 0, SEEK_SET);
 
   while (!(feof(archivo))) {
    
   Tcolas nodo = new (struct listaColas);
   if (nodo == NULL) {
    fprintf(stderr, "%s\n", "Error de memoria");
    exit(1);
   }
   fgets(destino, 100, archivo);
   fgets(destino, 100, archivo);
   strtok(destino, "\n");
   
   
   
   fscanf(archivo, "%i", &pedidordecola);
   fscanf(archivo, "%i", &hora);
 
   
   
    cout<<destino<<endl;
    strcpy(nodo->colas.destino,destino);
     
    cout<<pedidordecola<<endl;
    (nodo->pedidordecola) = pedidordecola;
    cout<<hora<<endl;
    (nodo->colas.hora) = hora;
    
    nodo->prox = NULL;
    cargarCola(nodo,listacolas);
    }

    fclose(archivo);
}
 

 void cargarListaDestinos(Tdestino &listadestinos, char dirListaDestinos[200]) {
   
   char destino[100]="0";
   
   int codigo=0;
   
   FILE *archivo;

   archivo = fopen(dirListaDestinos, "rt");
   if (archivo == NULL) {
      printf("\n\n\n No existe el archivo \"%s\" \n\n\n", dirListaDestinos);
      system("pause");
      exit(1) ;
   }

   //verifica si el archivo esta vacio y pone el cursor en el la primera prosicion
   long int file_start = ftell(archivo);
   fseek(archivo, 0, SEEK_END);
   long int file_end = ftell(archivo);
   if (file_end == file_start) return;

   fseek(archivo, 0, SEEK_SET);
 
   while (!(feof(archivo))) {
    
        Tdestino nodo = new (struct listaDestinos); 
        fgets(destino, 100, archivo);
        fgets(destino, 100, archivo);
        strtok(destino, "\n");
     
        fscanf(archivo, "%i", &codigo);

        cout<<destino<<endl;
        strcpy(nodo->destinos.direccion,destino);
     
        cout<<codigo<<endl;
        (nodo->destinos.codigo) = codigo;
 
    
        nodo->prox = NULL;
        cargarDestino(nodo,listadestinos);
    }

    fclose(archivo);
}

void cargarListaOfrecimientos(Tofrece &listaofrece, char dirListaOfrecimientos[200]) {
   
   char destino[100]="0";
   
   int hora=0;
   int numerodepuestos=0;
   int ofrece=0;
   
   FILE *archivo;

   archivo = fopen(dirListaOfrecimientos, "rt");
   if (archivo == NULL) {
      printf("\n\n\n No existe el archivo \"%s\" \n\n\n", dirListaOfrecimientos);
      system("pause");
      exit(1) ;
   }

   //verifica si el archivo esta vacio y pone el cursor en el la primera prosicion
   long int file_start = ftell(archivo);
   fseek(archivo, 0, SEEK_END);
   long int file_end = ftell(archivo);
   if (file_end == file_start) return;

   fseek(archivo, 0, SEEK_SET);
 
   while (!(feof(archivo))) {
    
   Tofrece nodo = new (struct listaOfrece); 
   fgets(destino, 100, archivo);
   fgets(destino, 100, archivo);
   strtok(destino, "\n");
    
   fscanf(archivo, "%i", &numerodepuestos);
   fscanf(archivo, "%i", &hora);
   fscanf(archivo, "%i", &ofrece);

    cout<<destino<<endl;
    strcpy(nodo->colas.destino,destino);
     
    cout<<numerodepuestos<<endl;
    (nodo->numerodepuestos) = numerodepuestos;
    cout<<hora<<endl;
    (nodo->colas.hora) = hora;
    cout<<ofrece<<endl;
    (nodo->ofrecedordecola) = ofrece;
 
    
    nodo->prox = NULL; 
    cargarOfrece(nodo,listaofrece);
    }

    fclose(archivo);
}
