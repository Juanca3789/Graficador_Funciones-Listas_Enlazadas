#include<iostream>
#include<graphics.h>
#include<string>
#include<math.h>
#include<iomanip>
using namespace std;

class Plano{
	private:
		class Punto{
			public:
				float x;
				float y;
				int color;
				Punto* siguiente;
				Punto* anterior;
				Punto(float _x, float _y);
				void setColorp(int _color){
					color = _color;
				}
		};
		Punto* inicio = nullptr;
		int x0, width;
		int y0, height;
		int k;
		bool num = true;
		int lcolor = WHITE;
		int bgcolor = BLACK;
		bool estado = false;
	public:
		Plano(int _width, int _height, int _k);
		Plano(int _width, int _height, int _k, bool _num);
		Plano(int _width, int _height, int _x0, int _y0, int _k, bool _num);
		int contPuntos();
		void setColor(int _lcolor, int _bgcolor);
		void iniciarPlano();
		void updatePlano();
		void limpiarPlano();
		float** cerrarPlano();
		void ponerPunto(float x, float y);
		void ponerPunto(float x, float y, int c);
		void quitarPunto(float x, float y);
		float** obtenerPuntos();
		void insertarPuntos(float** puntos, int n);
		void borrarPuntos();
		void cambCentro(int _x0, int _y0);
		void cambZoom(int _k);
		void redimensPlano(int _width, int _height);
		void graficarFuncion(double (func)(double));
		void imprimirPuntos();
};

Plano::Punto::Punto(float _x, float _y){
	x = _x;
	y = _y;	
}

Plano::Plano(int _width, int _height, int _k){
	width = _width;
	height = _height;
	k = _k;
	x0 = width/2;
	y0 = height/2;
}

Plano::Plano(int _width, int _height, int _k, bool _num){
	width = _width;
	height = _height;
	k = _k;
	num = _num;
	x0 = width/2;
	y0 = height/2;
}

Plano::Plano(int _width, int _height, int _x0, int _y0, int _k, bool _num){
	width = _width;
	height = _height;
	x0 = _x0;
	y0 = _y0;
	k = _k;
	num = _num;
}

int Plano::contPuntos(){
	int cont = 0;
	Punto* recorrido = inicio;
	while(recorrido != nullptr){
		cont++;
		recorrido = recorrido->siguiente;
	}
	return cont;
}

void Plano::setColor(int _lcolor, int _bgcolor){
	lcolor = _lcolor;
	bgcolor = _bgcolor;
}

void Plano::iniciarPlano(){
	estado = true;
	int j = 0;
	initwindow(width, height, "Plano Cartesiano");
	cleardevice();
	setbkcolor(bgcolor);
	cleardevice();
	setcolor(lcolor);
	line(0, y0, width, y0);
	line(x0, 0, x0, height);
	for(int i = x0;  i < width; i += k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == x0){
				outtextxy(i+1, y0 + 1, p);
			}
			else{
				line(i, y0, i, y0 + 10);
				line(i, y0, i, y0 - 10);
				outtextxy(i-2, y0 + 11, p);
			}
			delete []p;
		}
		else{
			if(i != x0){
				line(i, y0, i+1, y0 + 10);
				line(i, y0, i+1, y0 - 10);
			}
		}
		j++;
	}
	j = 0;
	for(int i = x0;  i > 0; i -= k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == x0){
				outtextxy(i+1, y0 + 1, p);
			}
			else{
				line(i, y0, i, y0 + 10);
				line(i, y0, i, y0 - 10);
				outtextxy(i-2, y0 + 11, p);
			}
			delete []p;
		}
		else{
			if(i != x0){
				line(i, y0, i, y0 + 10);
				line(i, y0, i, y0 - 10);
			}
		}
		j--;
	}
	j = 0;
	for(int i = y0;  i < height; i += k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == y0){
				outtextxy(x0 + 1, i + 1, p);
			}
			else{
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
				outtextxy(x0 - 22, i - 7, p);
			}
			delete []p;
		}
		else{
			if(i != y0){
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
			}
		}
		j--;
	}
	j = 0;
	for(int i = y0;  i > 0; i -= k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == y0){
				outtextxy(x0 + 1, i + 1, p);
			}
			else{
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
				outtextxy(x0 - 20, i - 8, p);
			}
			delete []p;
		}
		else{
			if(i != y0){
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
			}
		}
		j++;
	}
	updatePlano();
}

void Plano::limpiarPlano(){
	borrarPuntos();
	int j = 0;
	cleardevice();
	setbkcolor(bgcolor);
	cleardevice();
	setcolor(lcolor);
	line(0, y0, width, y0);
	line(x0, 0, x0, height);
	for(int i = x0;  i < width; i += k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == x0){
				outtextxy(i+1, y0 + 1, p);
			}
			else{
				line(i, y0, i, y0 + 10);
				line(i, y0, i, y0 - 10);
				outtextxy(i-2, y0 + 11, p);
			}
			delete []p;
		}
		else{
			if(i != x0){
				line(i, y0, i+1, y0 + 10);
				line(i, y0, i+1, y0 - 10);
			}
		}
		j++;
	}
	j = 0;
	for(int i = x0;  i > 0; i -= k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == x0){
				outtextxy(i+1, y0 + 1, p);
			}
			else{
				line(i, y0, i, y0 + 10);
				line(i, y0, i, y0 - 10);
				outtextxy(i-2, y0 + 11, p);
			}
			delete []p;
		}
		else{
			if(i != x0){
				line(i, y0, i, y0 + 10);
				line(i, y0, i, y0 - 10);
			}
		}
		j--;
	}
	j = 0;
	for(int i = y0;  i < height; i += k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == y0){
				outtextxy(x0 + 1, i + 1, p);
			}
			else{
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
				outtextxy(x0 - 22, i - 7, p);
			}
			delete []p;
		}
		else{
			if(i != y0){
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
			}
		}
		j--;
	}
	j = 0;
	for(int i = y0;  i > 0; i -= k){
		if(k >= 20 && num == true){
			string s = to_string(j);
			char* p = new char[s.length()];
			strcpy(p, s.c_str());
			if(i == y0){
				outtextxy(x0 + 1, i + 1, p);
			}
			else{
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
				outtextxy(x0 - 20, i - 8, p);
			}
			delete []p;
		}
		else{
			if(i != y0){
				line(x0, i, x0 + 10, i);
				line(x0, i, x0 - 10, i);
			}
		}
		j++;
	}
}

float** Plano::cerrarPlano(){
	float** puntos = obtenerPuntos();
	borrarPuntos();
	closegraph(-1);
	estado = false;
	return puntos;
}

void Plano::ponerPunto(float x, float y){
	Punto* nuevo = new Punto(x, y);
	nuevo->setColorp(lcolor);
	if(contPuntos() == 0){
		inicio = nuevo;
		nuevo->siguiente = nullptr;
		nuevo->anterior = nullptr;
	}
	else if(contPuntos() == 1){
		Punto* p = inicio;
		if(nuevo->x < p->x){
			inicio = nuevo;
			p->anterior = nuevo;
			p->siguiente = nullptr;
			nuevo->siguiente = p;
			nuevo->anterior = nullptr;
		}
		else{
			p->siguiente = nuevo;
			p->anterior = nullptr;
			nuevo->anterior = p;
			nuevo->siguiente = nullptr;
		}
	}
	else{
		Punto* recorrido = inicio;
		while(recorrido != nullptr){
			if(nuevo->x < recorrido->x){
				if(recorrido->anterior == nullptr){
					inicio = nuevo;
					recorrido->anterior = nuevo;
					nuevo->siguiente = recorrido;
					nuevo->anterior = nullptr;
					break;
				}
				else{
					Punto* anterior = recorrido->anterior;
					anterior->siguiente = nuevo;
					nuevo->anterior = anterior;
					nuevo->siguiente = recorrido;
					recorrido->anterior = nuevo;
					break;
				}
			}
			else{
				if(recorrido->siguiente == nullptr){
					nuevo->siguiente = nullptr;
					nuevo->anterior = recorrido;
					recorrido->siguiente = nuevo;
					break;
				}
			}
			recorrido = recorrido->siguiente;
		}
	}
	if(estado == true){
		putpixel(x0 + (nuevo->x * k), y0 - (nuevo->y * k), nuevo->color);
	}
}


void Plano::ponerPunto(float x, float y, int c){
	Punto* nuevo = new Punto(x, y);
	nuevo->setColorp(c);
	if(contPuntos() == 0){
		inicio = nuevo;
		nuevo->siguiente = nullptr;
		nuevo->anterior = nullptr;
	}
	else if(contPuntos() == 1){
		Punto* p = inicio;
		if(nuevo->x < p->x){
			inicio = nuevo;
			p->anterior = nuevo;
			p->siguiente = nullptr;
			nuevo->siguiente = p;
			nuevo->anterior = nullptr;
		}
		else{
			p->siguiente = nuevo;
			p->anterior = nullptr;
			nuevo->anterior = p;
			nuevo->siguiente = nullptr;
		}
	}
	else{
		Punto* recorrido = inicio;
		while(recorrido != nullptr){
			if(nuevo->x < recorrido->x){
				if(recorrido->anterior == nullptr){
					inicio = nuevo;
					recorrido->anterior = nuevo;
					nuevo->siguiente = recorrido;
					nuevo->anterior = nullptr;
					break;
				}
				else{
					Punto* anterior = recorrido->anterior;
					anterior->siguiente = nuevo;
					nuevo->anterior = anterior;
					nuevo->siguiente = recorrido;
					recorrido->anterior = nuevo;
					break;
				}
			}
			else{
				if(recorrido->siguiente == nullptr){
					nuevo->siguiente = nullptr;
					nuevo->anterior = recorrido;
					recorrido->siguiente = nuevo;
					break;
				}
			}
			recorrido = recorrido->siguiente;
		}
	}
	if(estado == true){
		putpixel(x0 + (nuevo->x * k), y0 - (nuevo->y * k), nuevo->color);
	}
}

void Plano::quitarPunto(float x, float y){
	Punto* recorrido = inicio;
	while(recorrido->siguiente != nullptr){
		if(recorrido->x == x && recorrido->y == y){
			Punto* anterior = recorrido->anterior;
			Punto* siguiente = recorrido->siguiente;
			siguiente->anterior = anterior;
			anterior->siguiente = siguiente;
			delete recorrido;
		}
		recorrido = recorrido->siguiente;
	}
	if(recorrido->siguiente == nullptr){
		if(recorrido->x == x && recorrido->y == y){
			Punto* anterior = recorrido->anterior;
			anterior->siguiente = nullptr;
			delete recorrido;
		}
	}
}

float** Plano::obtenerPuntos(){
	int cont = 0;
	float val;
	Punto* recorrido = inicio;
	while(recorrido != nullptr){
		cont++;
		recorrido = recorrido->siguiente;
	}
	float** matxy = new float*[cont];
	for(int i = 0; i < cont; i++){
		matxy[i] = new float[2];
	}
	recorrido = inicio;
	for(int i = 0; i < cont; i++){
		for(int j = 0; j < 2; j++){
			if(j == 0){
				val = recorrido->x;
			}
			else{
				val = recorrido->y;
			}
			matxy[i][j] = val;
		}
		recorrido = recorrido->siguiente;
	}
	return matxy;
}

void Plano::insertarPuntos(float** puntos, int n){
	float x, y;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 2; j++){
			if(j % 2 == 0){
				x = puntos[i][j];	
			}
			else{
				y = puntos[i][j];
			}
		}
		ponerPunto(x, y);
	}
}

void Plano::borrarPuntos(){
	int c = contPuntos();
	for(int i = 0; i < c; i++){
		Punto* recorrido = inicio;
		inicio = recorrido->siguiente;
		delete recorrido;
	}
}

void Plano::updatePlano(){
	if(estado == true){
		int c = contPuntos();
		float** puntos = obtenerPuntos();
		limpiarPlano();
		insertarPuntos(puntos, c);
	}
}

void Plano::cambCentro(int _x0, int _y0){
	x0 = _x0;
	y0 = _y0;
	updatePlano();	
}

void Plano::cambZoom(int _k){
	k = _k;
	updatePlano();	
}

void Plano::redimensPlano(int _width, int _height){
	width = _width;
	height = _height;
	cerrarPlano();
	iniciarPlano();
}

void Plano::graficarFuncion(double (func) (double)){
	for(float i = -5; i < 5; i += 0.001){
		float y = func(i);
		ponerPunto(i, y);
	}
}

void Plano::imprimirPuntos(){
	int n = contPuntos();
	float** puntos = obtenerPuntos();
	cout<<"[ x y ]"<<endl;
	for(int i = 0; i < n; i++){
		cout<<"[ ";
		for(int j = 0; j < 2; j++){
			if(j%2 == 0){
				cout<<fixed<<setprecision(3)<<puntos[i][j]<<" ";
			}
			else{
				cout<<setprecision(6)<<puntos[i][j];
			}
		}
		cout<<" ]"<<endl;
	}
}

int main(){
	Plano* p1 = new Plano(500, 500, 250, 250, 50, true);
	float x;
	p1->graficarFuncion(cos);
	p1->iniciarPlano();
	system("PAUSE");
}
