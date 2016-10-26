#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int letras = 3;
int numeros = 2;
int index =0;
char caracter[4];



int main(){

//    vamos a leer un archivo
    char ruta_archivo_a[100];
    char ruta_archivo_b[100];
    FILE *archivo_A;
    FILE *archivo_B;
    FILE *archivo_C;
    printf("ingresa la ruta del archivo A: ");
    scanf("%s", &ruta_archivo_a);
    printf("ingresa la ruta del archivo B: ");
    scanf("%s", &ruta_archivo_b);


    printf("\nAhora se procederea a crear el archivo C. ");
    archivo_A = fopen(ruta_archivo_a, "r");
    archivo_B = fopen(ruta_archivo_b, "r");
    archivo_C = fopen("archivo_C.txt", "w");
    //ahora  vamos a leer los archivos
    leer_Letras(archivo_A,archivo_B,archivo_C);

    fclose(archivo_A);
    fclose(archivo_B);
    fclose(archivo_C);
    printf("\nYa se realizo la escritura del archivo C\n");

    getchar();



    return 0;

}

void leer_Letras(FILE * archivo_A,FILE * archivo_B,FILE * archivo_C){
    while(letras>=0){

        //1. se pregunta si termino de leer la cantidad de caracteres
        printf("\nentro al ciclo de A");
        if(letras==0){
            //1.1 se agrega al arreglo el final de carro
            caracter[index]='\0';
            //1.2 se reinicia la variable de indice
            index =0;
            //1.3 ciclo de escritura de los caracteres
            while(caracter[index]!='\0'){
                fputc(caracter[index], archivo_C);
                index++;
            }
            //1.4 se procede a la lectura de numeros
            printf("\nLlego al final de las 3 letras");
            leerNumeros(archivo_B,archivo_C);
            //1.5 se reinician las variables para volver a leer
            printf("\nreinicio de variables");
            letras=3;
            numeros=2;
            index =0;
        }
        //2. se lee el caracter y se agrega al arreglo de carcateres
        caracter[index] = fgetc(archivo_A);
        //3. se pregunta si se llego al final del archivo para romper el ciclo
        if(feof(archivo_A)){
            //para detener cuando no estan completos los valores
            break;
        }
        //4. se incremetan o decrementan las variables necesarias
        printf("\nSe leyo: %c", caracter[index]);
        letras--;
        index++;
    }

}


void leerNumeros(FILE * archivo_B, FILE * archivo_C){
    printf("\n\nFuncion de leer numeros");
    index =0; //se asegura de iniciar la variable en 0
    while(numeros>=0){
        printf("\nentro al ciclo de B");
        //1.Se pregunta si termino la cantidad de caracteres a leer
        if(numeros==0){
            printf("\nEntro a escribir los numeros");
            //1.1 se agrega al arreglo el final de carro
            caracter[index]='\0';
            printf("\nvalor de index en el carro: %d", index);
            //1.2 se reinicia la variable de indice
            index =0;
            //1.3 ciclo de escritura de los caracteres
            while(caracter[index]!='\0'){
                fputc(caracter[index], archivo_C);
                index++;
            }
            //1.4 termina de leer para no correr la posicion del cursor dentro del archivo
            break;
        }
        //2. se lee el caracter y se agrega al arreglo de carcateres
        caracter[index] = fgetc(archivo_B);
        printf("\nse leyo: %c", caracter[index]);
        //3. se pregunta si se llego al final del archivo para romper el ciclo
        if(feof(archivo_B)){
            //para detener cuando no estan completos los valores
            break;
        }
        //4. se incremetan o decrementan las variables necesarias
        numeros--;
        index++;

    }
}




