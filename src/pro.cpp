/*
Alumno. Froilan Roa.
Prof. Joselito de Sousa. 
*/
#include "../libraries/Tda.h"

using namespace std;


int cedula; bool tener;
int op,year;
int dia;

char destino[100];


void mostrar(Tlista variable){

	 
	Tlista q = variable;

	if (!q)
		{cout<<endl<<"NO HAY USUARIOS REGISTRADOS..."<<endl;}

	else

	{

	 
	while (q != NULL ) {

	cout<<endl;
	cout<<endl<<"CEDULA: "<<q->usuarios.cedula;
	cout<<endl<<"NOMBRE: "<<q->usuarios.nombre;
	cout<<endl<<"APELLIDO: "<<q->usuarios.apellido; 
	cout<<endl<<"TELEFONO DE HABITACION: "<<q->usuarios.telefonohab; 
	cout<<endl<<"TELEFONO CELULAR: "<<q->usuarios.celular;
	cout<<endl<<"TELEFONO DE TRABAJO: "<<q->usuarios.teleftrab;
	cout<<endl<<"FECHA DE NACIMIENTO: "<<q->usuarios.dia<<"/"<<meses[q->usuarios.mes]<<"/"<<q->usuarios.year; 
	cout<<endl<<"DIRECCION DE HABITACION: "<<q->usuarios.direccionhab; 
	cout<<endl<<"DIRECCION DE TRABAJO: "<<q->usuarios.direcciontrab; 
	cout<<endl<<"TELEFONO DE ALGUN FAMILIAR: "<<q->usuarios.telefami; 
	cout<<endl<<"DESTINO HABITUAL: "<<q->usuarios.destino_habitual;
	cout<<endl<<"HORA HABITUAL: "<<q->usuarios.hora_habitual;
	cout<<endl<<"POSEE CARROS: "<<pos[q->usuarios.posee];
	cout<<endl<<"TIPO DE USUARIO: "<<tipoUsuario[q->usuarios.tipoPersonal]<<endl;
	
	q = q->prox; 

	}
	}
}

void mostrarCarros(Tcarro variable){

	Tcarro q = variable; 

	if (esVaciaCarros(variable))
		{cout<<endl<<"NO HAY CARROS REGISTRADOS..."<<endl;}

	else

	{

	while (q != NULL ) {

	cout<<endl<<"NUMERO DE CEDULA DEL PROPIETARIO: "<<q->su_propietario;
	cout<<endl<<"MARCA: "<<q->carros.marca;
	cout<<endl<<"MODELO: "<<q->carros.modelo;
	cout<<endl<<"COLOR: "<<q->carros.colorcarro;
	cout<<endl<<"PLACA: "<<q->carros.placa;
	cout<<endl<<"ANIO: "<<q->carros.year;
	cout<<endl<<"SERIAL DEL MOTOR: "<<q->carros.serialmotor<<endl;	
	q = q->prox; 

	}

	}
}

void mostrarColas(Tcolas variable){

	Tcolas q = variable; 


	if (esVaciaColas(variable))
		{cout<<endl<<"NO HAY PETICIONES DE COLAS..."<<endl;}

	else

	{


	while (q != NULL ) {

	cout<<endl<<"NUMERO DE CEDULA DEL PEDIDOR DE COLA: "<<q->pedidordecola;
	cout<<endl<<"DESTINO DE LA COLA: "<<q->colas.destino;
	cout<<endl<<"HORA DE PETICION DE COLA: "<<q->colas.hora<<endl<<endl;

	q = q->prox; 

	}

	}
}

void mostrarProcesa(Tprocesa variable){

	Tprocesa q = variable; 

	if (q == NULL){cout<<"PROCESA VACIA.."<<endl;}

		else
		{
	while (q != NULL ) {

	cout<<endl<<"NUMERO DE CEDULA DEL PRESTADOR "<<q->cedulaprestador;
	cout<<endl<<"DESTINO DEL PEDIDOR: "<<q->cedulapedidor<<endl;

	q = q->prox; 

	}
	}
}


void borrarPantalla(){
   system( "read -n 1 -s -p \"\nPresione cualquier tecla para continuar...\"" );
}
void menu(){

	

	cout<<endl<<"PIDE COLA"<<endl;
	cout<<endl<<"Menu. "<<endl;

	cout<< " 1.   REGISTRO DE NUEVA PERSONA"<<endl;
	cout<< " 2.   MODIFICAR DATOS DE USUARIO "<<endl;
	cout<< " 3.   PEDIR LA COLA  "<<endl;
	cout<< " 4.   MODIFICAR PETICION DE COLA"<<endl;
	cout<< " 5.   ELIMINAR PETICION DE COLA"<<endl;
	cout<< " 6.   VER MI SOLICITUD DE COLA"<<endl;
	cout<< " 7.   VER TODAS LAS SOLICITUDES DE COLA"<<endl;
	cout<< " 8.   VER SOLICITUDES DE COLA PARA UN DESTINO PUNTUAL"<<endl;
	cout<< " 9.   OFRECER COLA"<<endl;
	cout<< " 10.  MODIFICAR COLA OFRECIDA"<<endl;
	cout<< " 11.  ELIMINAR COLA OFRECIDA"<<endl<<endl<<endl;
	cout<< " Manteniminento."<<endl;
	cout<<"                        MOSTRAR"<<endl;
	cout<< " 12.  MOSTRAR TODOS LOS USUARIOS REGISTRADOS"<<endl;
	cout<< " 13.  MOSTRAR TODOS LOS CARROS REGISTRADOS"<<endl;
	cout<< " 14.  MOSTRAR TODOS LOS OFRECIMIENTOS DE COLA"<<endl;
	cout<< " 15.  MOSTRAR TODOS LOS DESTINOS"<<endl;
	cout<< " 16.  PROCESADO"<<endl;


	cout<< " 17.  SALIR..."<<endl<<endl;
	
	cout<<"\n INGRESE OPCION: ";


}

int main()
{
	
	Tlista   lista = NULL; 
	Tcarro   listacarros = NULL;
	Tcolas   listacolas = NULL;
	Tofrece  listaofrece = NULL;
	Tdestino listadestinos = NULL;	
	Tprocesa listaprocesa = NULL;
	
	char dirLista[200] = { "files/lista.txt" }; 
	char dirListaCarros[200] = { "files/listacarros.txt" }; 
	char dirListaColas[200] = { "files/listacolas.txt" }; 
	char dirListaDestinos[200] = { "files/listadestinos.txt" }; 
	char dirListaOfrecimientos[200] = { "files/listaofrece.txt" };
	char dirDia[200] = { "files/dia.txt" }; 
		
	
	cargarLista(lista,dirLista);
	cargarListaCarros(listacarros,dirListaCarros);


	cargarListaColas(listacolas,dirListaColas);
	cargarListaDestinos(listadestinos,dirListaDestinos);
	cargarListaOfrecimientos(listaofrece,dirListaOfrecimientos);

	

	do{
		system("tput clear");

		menu(); cin >> op; 
		


		switch(op) {

			case 1:

			cout<<endl<<"REGISTRO NUEVO USUARIO"<<endl;
   			cout<<endl<<"INTRODUZCA EL AÑO DE NACIMIENTO"<<endl;
    		cin>>year;

    		if (year > 2001) {cout <<endl<<"ERROR... NO PUEDE USAR EL SERVICIO SI ES MENOR DE EDAD"<<endl;} 
   			else

   			{

   				

   				cout<<endl<<"INTRODUZCA LA CEDULA"<<endl;
        		cin>>cedula; 

   				registrarPersona(lista,listacarros,cedula);

   				
   			} 

			
			break; 

			case 2: 

			cout<<endl<<"MODIFICANDO USUARIO"<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 
			modificar(lista,listacarros, cedula);
			break;


			case 3:

			cout<< " **PIDIENDO LA COLA** "<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 
			pedirCola(lista,listacolas,listadestinos,cedula);
			break;


			case 4: 

			cout<<endl<<"MODIFICANDO COLA"<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 
			modificarCola(listacolas,listadestinos, cedula,listaprocesa);
			break;

			case 5: 

			cout<<endl<<"ELIMINAR PETICION DE COLA"<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 
			eliminarCola(listacolas, cedula);
			break;

			case 6: 

			cout<<endl<<"VIENDO MI SOLICITUD DE COLA"<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 

			mostrarSolicitudCola(listacolas,cedula,listaprocesa,listacarros,lista);

			break;

			case 7:

			mostrarColas(listacolas);

			break;

			case 8: 

			cout<<endl<<"VIENDO LAS SOLICITUDES DE COLA POR UN DESTINO PUNTUAL"<<endl;
			

			mostrarSolicitudDestino(listacolas,listadestinos);

			break; 

			case 9: 

			cout<<endl<<"OFRECER COLA"<<endl;
			cout<< " **OFRECIENDO LA COLA** "<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 
			ofrecerCola(lista,listaofrece,listadestinos,cedula);
			break;

			case 10: 

			cout<<endl<<"MODIFICAR COLA OFRECIDA"<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 
			modificarOfrece(listaofrece, cedula);

			break;

			case 11: 
			cout<<endl<<"ELIMINAR OFRECIMIENTO DE COLA"<<endl;
			cout<<endl<<"INTRODUZCA CEDULA"<<endl;
			cin>> cedula; 
			eliminarOfrece(listaofrece, cedula);
			break;

	
			case 12: 

			cout<<endl<<"MOSTRANDO "<<endl;
			mostrar(lista);

			break;

			case 13:

			mostrarCarros(listacarros);

			break;

			case 14:

			mostrarOfrecimientos(listaofrece);

			break;

			case 15:
            cout << "\n\nDESTINOS\n\n" << endl;
            mostrarDestinos(listadestinos);
            break;

            case 16:
            cout << "\n\nprocesa\n\n" << endl;
            mostrarProcesa(listaprocesa);
            break;

			case 17:
            cout << "\n\n**********FIN DEL PROGRAMA************\n\n" << endl;
            break;

			default:
			cout << "\n\n**********OPCION INCORRECTA************\n\n" << endl;
			break;
		
 
		}

		limpiarListaProcesa(listaprocesa);
		
		procesarColas(listacolas,listaofrece,listaprocesa);
		
		escribirLista(lista, dirLista);
		escribirListaCarros(listacarros, dirListaCarros);
		escribirListaColas(listacolas, dirListaColas);
		escribirListaOfrece(listaofrece, dirListaOfrecimientos); 
		escribirListaDestino(listadestinos, dirListaDestinos);
		
		
	if (op<17) borrarPantalla();
    cout<<endl<<endl;	
	}while (op!=17);
	return 0;

}