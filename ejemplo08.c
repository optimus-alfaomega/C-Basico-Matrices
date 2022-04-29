/* 
 * C BY 8 EXAMPLES
 * example08.c: matrices con arrays y memoria dinámica
 * 
 * Copyright (C) 2019 Ignacio Pérez Hurtado de Mendoza
 * http://www.cs.us.es/~ignacio
 * Copyright (C) 2020 Miguel Ángel Martínez del Amor
 * http://www.cs.us.es/~mdelamor
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h> // depuracion

// Vamos a trabajar con matrices "aplanadas" tal como si fueran arrays.
// El truco está en poner las filas de la matriz una tras otra:
/*
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+        +---+---+---+---+---+---+---+---+---+
| 4 | 5 | 6 |   -->  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
+---+---+---+        +---+---+---+---+---+---+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
*/

// De esta forma, m[i*C+j] es la posicion i,j de la matriz m de C columnas

int *creaMatriz(int filas, int columnas);
void inicializaMatriz(int* matriz, int filas, int columnas);
void sumaMatrices(int* m1, int* m2, int* m3, int filas, int columnas); // m3 = m1 + m2
void multiplicaMatrices(int* m1, int* m2, int* m3, int f1, int c1, int f2, int c2); 
// m3 = m1*m2 en donde (f1,c1) son las filas y columnas de m1; (f2,c2) son filas y columnas de m2
void imprimeMatriz(int* matriz, int filas, int columnas);
void liberaMatriz(int* matriz);

int main()
{
	
	srand(time(NULL));
	
	// almacenaremos en estas variables el número de filas y de columnas
	int filas, columnas;
	
	printf("Numero de filas: ");
	scanf("%d",&filas);
	
	printf("Numero de columnas: ");
	scanf("%d",&columnas);
	
	// Vamos a crear cuatro de estas matrices. Primero reservamos la memoria.
	// Mira como se hace en la función creaMatriz
	int* m1 = creaMatriz(filas,columnas);
	int* m2 = creaMatriz(filas,columnas);
	int* m3 = creaMatriz(filas,columnas);
	int* m4 = creaMatriz(filas,columnas);
	
	// Ahora es momento de inicializar las matrices
	inicializaMatriz(m1,filas,columnas);
	inicializaMatriz(m2,filas,columnas);
	
	// Imprimamos el contenido
	printf("M1 =  \n");
	imprimeMatriz(m1, filas, columnas);
	printf("\nM2 = \n");
	imprimeMatriz(m2, filas, columnas);
	
	// Sumemos las dos matrices y guardemos el resultado en m3
	sumaMatrices(m1,m2,m3,filas,columnas);
	
	// El resultado es
	printf("\nM1 + M2 = \n");
	imprimeMatriz(m3,filas,columnas);
	
	// Ahora vamos a multiplicar las matrices y guardamos el resutado en m4
	multiplicaMatrices(m1,m2,m4,filas,columnas,filas,columnas);
	printf("\nM1 * M2 = \n");

	// El resultado es
	imprimeMatriz(m4,filas,columnas);
	
	// No olvides nunca liberar la memoria
	liberaMatriz(m1);
	liberaMatriz(m2);
	liberaMatriz(m3);
	liberaMatriz(m4);
	
	return 0;
}

int* creaMatriz(int filas, int columnas)
{
	// La reserva de memoria es exactamente igual a como se hace con arrays
	// solo que tenemos que reservarlo para el número de filas y de columnas
	return (int*) malloc(filas*columnas*sizeof(int));
}

void inicializaMatriz(int* matriz, int filas, int columnas)
{
	// Para recorrer una matriz necesitamos dos bucles, uno anidado dentro del otro
	for (int i=0;i<filas;i++) {
		for (int j=0;j<columnas;j++) {
			matriz[i*columnas+j] = rand() % 16;
		}
	}
}

void imprimeMatriz(int* matriz, int filas, int columnas)
{
	// Para recorrer una matriz necesitamos dos bucles, uno anidado dentro del otro
	for (int i=0;i<filas;i++) {
		// Lo más eficiente es recorrer la matriz en el orden como se haya creado:
		//   * recorrido primero por filas y luego por columnas (este ejemplo)
		//   * recorrido primero por columna y luego por filas (data frames, etc.)
		for (int j=0;j<columnas;j++) {
			printf("%d\t",matriz[i*columnas+j]); // \t se usa para tabular
		}
		printf("\n");
	}
}

void sumaMatrices(int* m1, int* m2, int* m3, int filas, int columnas)
{
	for (int i=0;i<filas;i++) {
		for (int j=0;j<columnas;j++) {
			m3[i*columnas+j] = m1[i*columnas+j] + m2[i*columnas+j];
		}
	}
}

void multiplicaMatrices(int* m1, int* m2, int* m3, int f1, int c1, int f2, int c2)
{
	// Podemos asegurarnos que se cumplen ciertas condiciones con assert
	assert(c1==f2); // si no se cumple se produce un error en tiempo de ejecución
	
	for (int i=0;i<f1;i++) {
		for (int j=0;j<c2;j++) {
			m3[i*c2+j] = 0;
			for (int k=0;k<c1;k++) {
				m3[i*c2+j]+= m1[i*f1+k] * m2[k*f2+j];
			}
		}
	}
}

void liberaMatriz(int* matriz)
{
	free(matriz);
}
