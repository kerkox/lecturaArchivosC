#include <stdio.h>
#include <stdlib.h>

//Joseph bolaños cod. 201461596
//Bryan Paul cortes cod. 201461554

//Fichero
FILE *archivo;
FILE *salida;
char ruta[256] ={"c:\\cifrado\\proteger.txt"}; //Rutas de prueba
char buffer[1000]; //Buffer cuando se lee en tipo char
int bytes[1000];    //Buffer de lectura de bytes en valor numerico
int cifrado[1000];  //Buffer de bytes Cifrados
char nombre[100]; //Se usa para tener el nombre puro sin extension
char path[256]; //Se usa para guardar la ruta del archivo
char extension[10]; //se usa para obtener la extension del archivo

char cabecera[] = {"KERKOX"};
char password[100] = {"password"};
char pass[100];

//Funcion de leer el archivo y pasarlos a un archivo los bytes
//tipo= para encriptar(1) o desencriptar(2)
//conservar= para conservar el archivo original(1), eliminar(2)
int procesar(int tipo, int conservar){
    int leidos=0; //Variable para obtener la cantidad de bytes leidos
    int x=0; // variable de usos para ciclos como FOR
    archivo = fopen(ruta, "rb"); //Apertura del archivo

    strcat(path, nombre); //Funcion de cadenas que permite unir el nombre puro a la ruta del archivo
    //Se adiciona una cadena que lo permite distinguir
    if(tipo==1){
        strcat(path, "-CIFRADO");   //1 para cifrado
    }else if(tipo==2){
        strcat(path, "-ORIGINAL");   //2 para descifrado
    }
    strcat(path, extension);    //por ultimo se agrega la extension

    //iniciando el archivo de escritura de salida
    salida = fopen (path, "w" ); //se usa el modo W para sobreEscribir si existe
    fclose(salida); //luego se cierra
    salida = fopen (path, "ab" ); //aqui escribe sobre el archivo

    if(archivo==NULL){
        perror("No se puede abrir el fichero ");
        return -1; //ERROR
    }

    //Incia el ciclo de lectura para el cifrado
    int arranque =1;
    int passSize=0;
    int y=0;
    fseek(archivo, 0L, SEEK_END);
    double sizeFile = ftell(archivo);
    fclose(archivo);
    archivo = fopen(ruta, "rb"); //Apertura del archivo

    double recorrido = 0;
    double porcentaje=0;

    do{
        int indexInicio =0;
        leidos = fread(buffer, 1, 1000, archivo); //se lee los bytes y se guarda en el buffer
        recorrido += leidos;

        porcentaje = (recorrido *100.0)/sizeFile;
        printf("\n %g %%", porcentaje);

        if(arranque==1&&tipo==2){
             int cabecera = contiene(buffer, "KERKOX");
             if(cabecera=-1){
                passSize = buffer[cabecera+7];
                passSize -= 48;
                y=0;
                x=cabecera+8;
                while(y<passSize){
                   pass[y]=buffer[x];
                   x++;
                   y++;
                }
                pass[y]='\0';
                indexInicio=x;
             }

             if(strcmp(pass,password)!=0){
                perror("\nPassword invalido ");
                fclose(archivo);
                fclose(salida);
                remove(path);
                return -1;
             }

             arranque=0;
        }
       //procesar los datos leidos en el buffer
       //Se convierte de forma automatica el buffer de tipo CHAR a los bytes de tipo INT
       y=0;
        for(x=indexInicio;x<leidos;x++){
            bytes[y]=buffer[x];
            y++;
        }
        //======================================================
        //======================================================
        //Aqui se alteran los valores para ser encriptados o desencriptados
        //1.Se sacan los valores del arreglo de bytes originales
        //2. se realiza el proceso de cifrado matematicamente
        //3. se recibe el valor cifrado y se guarda en el arreglo de cifrado


        if(arranque==1&&tipo==1){
            for(x=0;x<strlen(cabecera);x++){
                    //se escribe la cabecera
                fputc(cabecera[x], salida);
            }

            //se escribe el largo de la contraseña
            int sizePassword = strlen(password);
            char large = sizePassword+48;
            fputc(large, salida);

            //****
            //aqui se escribe el password
            for(x=0;x<strlen(password);x++){
                fputc(password[x], salida);
            }
            arranque=0;
        }

        for(x=0;x<leidos;x++){
            cifrado[x]= bytes[x]*-1;
            fputc(cifrado[x], salida);
        }


    }while(!feof(archivo));

    fclose(archivo);
    fclose(salida);
    if(conservar==2){
        remove(ruta);
    }
    return 0;
}

int menu(){
    int op = 0;
    printf("\n--------Encriptador---------\n\n");
    printf("1. Encriptar\n");
    printf("2. Desencriptar\n");
    printf("3. Salir\n");
    printf("\nIngresa la opcion: ");
    scanf("%d", &op);
    return op;
}

//Esta funcion lo que hace es compara si una cadena esta contenida dentro de la otra
//debe estar completa y exacta para ser verdadero y devuelve el indice donde
//comineza la cadena2 en la cadena1
//el valor obtenido es el indice donde se encuentra la cadena2 dentro de la cadena1
int contiene(char cadena1[], char cadena2[]){

        int x=0;
        int y=0;
        int index =-1;
        for(x=0;x<strlen(cadena1);x++){

            if(y==strlen(cadena2)){
                break;
            }

            if(cadena1[x]==cadena2[y]){
                 if(y==0){
                    index = x;
                 }
                 y++;
            }else{
                index = -1;
                y=0;
            }

        }
    return index;
}

void nombreArchivo(char ubicacion[]){
    int size = strlen(ubicacion);
    int x =0;
    int indexPos =-1;
    int indexPunto =-1;

    for(x=0;x<size;x++){
        if(ubicacion[x]=='\\'){
            indexPos = x;
        }
    }
    int largo = size - indexPos;
    int y =0;
    //aqui pasamos el path
    for(x=0;x<=indexPos;x++){
        path[x]=ubicacion[x];
    }
    path[x] = '\0';

    //aqui se obtiene el nombre del archivo
    for(x=indexPos+1;x<size;x++){
       nombre[y] = ubicacion[x];
       if(nombre[y]=='.'){
            indexPunto = y;
        }
        y++;
    }
    nombre[y] = '\0';

    //aqui obtenemos la extension
    y=0;

    for(x=indexPunto;x<size;x++){
        extension[y] = nombre[x];
        y++;
    }
    extension[y]='\0';

    //********************************
     //Se pone aqui para quitarle la extension al Nombre
     nombre[indexPunto] = '\0';

     int nameCifrado = contiene(nombre,"-CIFRADO");
     int nameOriginal = contiene(nombre,"-ORIGINAL");
     if(nameCifrado!=-1){
        nombre[nameCifrado]='\0';
     }
     if(nameOriginal!=-1){
        nombre[nameOriginal]='\0';
     }
     //********************************

}

int main(){

    int op=0;
    do{
            system("cls"); //Windows
//            system("clear"); Linux
    op = menu();
    int conservar =1;
    switch(op){
    case 1:
        //Encriptar
        printf("Ingresa la ruta del archivo: \n");
        scanf("%s", ruta);
        nombreArchivo(ruta);
        getchar();
        printf("\nDesea conservar el archivo? ");
        printf("\n1. SI");
        printf("\n2. NO");
        printf("\nelige: ");
        scanf("%d", &conservar);
        printf("\nIngresa el Password: ");
        scanf("%s", password);

        if(procesar(1,conservar)!=-1){ //Cifrar
            printf("\n++++Termino de Encriptar");
        }else{
            printf("\nHubo Un ERROR\n");
        }
        getchar();
        break;
    case 2:
        //Desencriptar
        printf("Ingresa la ruta del archivo: \n");
        scanf("%s", ruta);
        nombreArchivo(ruta);
        getchar();
        printf("\nDesea conservar el archivo? ");
        printf("\n1. SI");
        printf("\n2. NO");
        printf("\nelige: ");
        scanf("%d", &conservar);
        printf("\nIngresa el Password: ");
        scanf("%s", password);

        if(procesar(2,conservar)!=-1){//Descifrar
            printf("\n++++Termino de Deesncriptar");
        }else{
            printf("\nHubo Un ERROR\n");
        }

        getchar();
        break;
    case 3:
        //Salir
        printf("\nADIOS....\n");
        getchar();
        op=3;
        break;

    }
    getchar();
    }while((op!=3)||(op<1||op>3));

    printf("\nSalida Extiosa...");
    return 0;

}
