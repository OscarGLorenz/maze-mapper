#ifndef MazeObjects_h
#define MazeObjects_h

#include <Arduino.h>

//Direcciones
enum Dir {
	FRONT, LEFT, RIGHT, BACK
};

//Tipos de Celda
enum Type {
	NORMAL, EXIT, ENTRY
};

//ArrayList para cualquier objeto/tipo

template<class T> class ArrayList {
public:
	ArrayList();
	//Asigna a lenght y array 0

	~ArrayList();
	//Libera Espacio

	void add(T t);
	//Añade al final

	T &operator[](const int i);

	const T &operator[](const int i) const;

	T get(const int i);
	//Retorna el elemento especificado, si i >= size devuelve el último elemento

	bool has(T n);
	//Retorna true si el elemento existe en el ArrayList, debe tener definido
	//el operador == si es un objeto

	int size();
	//Devuelve el número de elementos

private:
	T * array;
	//Dirección del ArrayList

	int lenght;
	//Numero de Elementos
};


//Una celda
class Cell {
public:
	Cell(Dir from, Cell * fromCell, Type type, int id);
	//Crea la celda, dada una dirección y otra celda, enlaza,
	//el puntero de la dirección dada a la celda dada, establece
	//el tipo de celda y le da un id

	void change(Dir dir, Cell * cell);
	//Cambia el puntero de la dirección dada a otro dado

	Cell * point(Dir dir);
	//Devuelve la dirección del puntero según la dirección dada

	int connections();
	//Devuelve el número de punteros no nulos

	int id;
	//Id de la celda

	Type type;
	//Tipo de celda

	//Punteros a celda en cada una de las direcciones
	Cell * front;
	Cell * left;
	Cell * right;
	Cell * back;
};

//Clase Maze, administra las celdas
class Maze {
public:
	Maze();
	//Crea la primera Celda

	void turnRight();
	//Giro a la derecha, crea celda si no existe

	void turnLeft();
	//Giro a la izquierda, crea celda si no existe

	void turnBack();
	//Giro hacia atrás, crea celda si no existe

	void straight();
	//Segir recto, crea celda si no existe

	void finish();
	//Crea la celda EXIT

	ArrayList<Dir> solve();
	//Devuelve un arraylist con las direcciones para salir
	//lo más directo posible del laberinto

	//Dir * solve(int * i);

private:
	Cell * now;
	//Contador

	Cell * first;
	//Primera Celda

	Dir heading;
	//A donde apunta la referencia móvil

	int count;
	//Contador de celdas

	void autoFree(Dir dir);
	//Elimina una rama en la direccion señalada

	Dir priority();
	//Camino prioritatio "a derechas"

	void move();
	//Se mueve hacia donde diga heading, si no existe celda,
	//la crea

	Dir ckWise(Dir dir);
	//Da la dirección siguiente a la dada en dirección
	//a las agujas del reloj

	Dir cntCkWise(Dir dir);
	//Da la dirección siguiente a la dada en dirección
	//contraria a las agujas del reloj

	Dir reverse(Dir dir);
	//Da la dirección contraria a la dada

	Dir relative(Dir dir);
	//Usa heading y la dirección dada para devolver, la
	//dirección relativa
};

#endif
