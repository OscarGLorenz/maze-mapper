#include "MazeObjects.h"

Cell::Cell(Dir from, Cell * fromCell, Type type, int id) {
	front = 0;
	left = 0;
	right = 0;
	back = 0;
	switch (from) {
	case FRONT:
		front = fromCell;
		break;
	case LEFT:
		left = fromCell;
		break;
	case RIGHT:
		right = fromCell;
		break;
	case BACK:
		back = fromCell;
		break;
	}
	this->id = id;
	this->type = type;
}

void Cell::change(Dir dir, Cell * cell) {
	switch (dir) {
	case FRONT:
		front = cell;
		break;
	case LEFT:
		left = cell;
		break;
	case RIGHT:
		right = cell;
		break;
	case BACK:
		back = cell;
		break;
	}
}

Cell * Cell::point(Dir dir) {
	switch (dir) {
	case FRONT:
		return front;
		break;
	case LEFT:
		return left;
		break;
	case RIGHT:
		return right;
		break;
	case BACK:
		return back;
		break;
	}
	return 0;
}

int Cell::connections() {
	int n = 0;
	n += (right != 0) ? 1 : 0;
	n += (left != 0) ? 1 : 0;
	n += (front != 0) ? 1 : 0;
	n += (back != 0) ? 1 : 0;
	return n;
}

Maze::Maze() {
	heading = FRONT;
	first = new Cell(BACK, 0, ENTRY, count++);
	now = first;
}

Dir Maze::ckWise(Dir dir) {
	switch (dir) {
	case FRONT:
		return RIGHT;
	case LEFT:
		return FRONT;
	case RIGHT:
		return BACK;
	case BACK:
		return LEFT;
	}
	return FRONT;
}
Dir Maze::cntCkWise(Dir dir) {
	switch (dir) {
	case FRONT:
		return LEFT;
	case LEFT:
		return BACK;
	case RIGHT:
		return FRONT;
	case BACK:
		return RIGHT;
	}
	return FRONT;
}

void Maze::move() {
	if (now->point(heading) == 0) {
		now->change(heading, new Cell(reverse(heading), now, NORMAL, count++));
	}
	now = now->point(heading);
}

void Maze::finish() {
	now->change(heading, new Cell(reverse(heading), now, EXIT, count++));
	now = now->point(heading);
}

void Maze::turnRight() {
	heading = ckWise(heading);
	move();
}

void Maze::straight() {
	move();
}

void Maze::turnLeft() {
	heading = cntCkWise(heading);
	move();
}

void Maze::turnBack() {
	heading = reverse(heading);
	move();
}

Dir Maze::reverse(Dir dir) {
	switch (dir) {
	case FRONT:
		return BACK;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	case BACK:
		return FRONT;
	}
	return FRONT;
}

Dir Maze::priority() {
	switch (heading) {
	case FRONT:
		if (now->right != 0) {
			return RIGHT;
		} else if (now->front != 0) {
			return FRONT;
		} else if (now->left != 0) {
			return LEFT;
		} else {
			return BACK;
		}
	case LEFT:
		if (now->front != 0) {
			return FRONT;
		} else if (now->left != 0) {
			return LEFT;
		} else if (now->back != 0) {
			return BACK;
		} else {
			return RIGHT;
		}
	case RIGHT:
		if (now->back != 0) {
			return BACK;
		} else if (now->right != 0) {
			return RIGHT;
		} else if (now->front != 0) {
			return FRONT;
		} else {
			return LEFT;
		}
	case BACK:
		if (now->left != 0) {
			return LEFT;
		} else if (now->back != 0) {
			return BACK;
		} else if (now->right != 0) {
			return RIGHT;
		} else {
			return FRONT;
		}
	}
	return FRONT;
}

void Maze::autoFree(Dir dir) {
	Cell * aux = now;
	aux = aux->point(heading);
	while (aux->connections() == 2) {
		heading = priority();
		aux = aux->point(heading);
	}
	heading = reverse(heading);
	while (aux->connections() < 3) {
		Cell * kill = aux;
		heading = priority();
		aux = aux->point(heading);
		delete kill;
	}
	now->change(reverse(heading), 0);
}

Dir Maze::relative(Dir p) {
	switch (heading) {
	case FRONT:
		return p;
	case RIGHT:
		return cntCkWise(p);
	case BACK:
		return reverse(p);
	case LEFT:
		return ckWise(p);
	}
	return FRONT;
}

ArrayList<Dir> Maze::solve() {
	ArrayList<Dir> dirs;
	ArrayList<int> ids;
	now = first;
	heading = FRONT;
	ids.add(now->id);
	while (now->type != EXIT) {
		heading = priority();
		now = now->point(heading);
		ids.add(now->id);
		if (now->connections() > 2 && ids.has(now->id)) {
			Serial.println("DELETING");
			autoFree(reverse(heading));
			Serial.println("END DELETE");
		}
	}

	heading = reverse(heading);
	now = now->point(heading);

	while (now->type != ENTRY) {
		heading = priority();
		now = now->point(heading);
		ids.add(now->id);
		if (now->connections() > 2 && ids.has(now->id)) {
			autoFree(reverse(heading));
		}
	}

	heading = reverse(heading);

	for (int i = 0; now->type != EXIT; i++) {
		dirs.add(relative(priority()));
		heading = priority();
		now = now->point(heading);
	}
	ids.~ArrayList();
	return dirs;
}

template<class T> ArrayList<T>::ArrayList() {
	lenght = 0;
	array = 0;
}

template<class T> void ArrayList<T>::add(T t) {
	lenght++;
	array = (T *) realloc(array, lenght * sizeof(T));
	array[lenght - 1] = t;
}

template<class T> T& ArrayList<T>::operator[](const int i) {
	if (i < 0) {
		return array[0];
	} else if (i > lenght - 1) {
		return array[lenght - 1];
	} else {
		return array[i];
	}
}

template<class T> const T& ArrayList<T>::operator[](const int i) const {
	if (i < 0) {
		return array[0];
	} else if (i > lenght - 1) {
		return array[lenght - 1];
	} else {
		return array[i];
	}
}

template<class T> bool ArrayList<T>::has(T t) {
	for (int i = 0; i < lenght; i++) {
		if (t == array[i]) {
			return true;
		}
	}
	return false;
}

template<class T> int ArrayList<T>::size() {
	return lenght;
}

template<class T> ArrayList<T>::~ArrayList() {
	free(array);
}

template class ArrayList<int> ;
template class ArrayList<Dir> ;
