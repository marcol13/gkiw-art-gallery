/*
Niniejszy program jest wolnym oprogramowaniem; mo�esz go
rozprowadza� dalej i / lub modyfikowa� na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
Oprogramowania - wed�ug wersji 2 tej Licencji lub(wed�ug twojego
wyboru) kt�rej� z p�niejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on
u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej
gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH
ZASTOSOWA�.W celu uzyskania bli�szych informacji si�gnij do
Powszechnej Licencji Publicznej GNU.

Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
je�li nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/


#ifndef MYTEAPOT_H
#define MYTEAPOT_H

//myTeapotVertices - homogeniczne wsp�rz�dne wierzcho�k�w w przestrzeni modelu
//myTeapotNormals - homogeniczne wektory normalne �cian (per wierzcho�ek) w przestrzeni modelu
//myTeapotVertexNormals - homogeniczne wektory normalne wierzcho�k�w w przestrzeni modelu
//myTeapotTexCoords - wsp�rz�dne teksturowania
//myTeapotColors - kolory wierzcho�k�w
//myTeapotC1 - kolumna macierzy TBN^-1
//myTeapotC2 - kolumna macierzy TBN^-1
//myTeapotC3 - kolumna macierzy TBN^-1
//myTeapotC1_2 - kolumna u�rednionej macierzy TBN^-1
//myTeapotC2_2 - kolumna u�rednionej macierzy TBN^-1
//myTeapotC3_2 - kolumna u�rednionej macierzy TBN^-1

unsigned int myTeapotVertexCount = 1;

float myTeapotVertices[] = {
};
float myTeapotNormals[] = {
};
float myTeapotVertexNormals[] = {
};
float myTeapotTexCoords[] = {
};

float myTeapotColors[] = {
};
float myTeapotC1[] = {
};
float myTeapotC2[] = {
};
float myTeapotC3[] = {
};

#endif
