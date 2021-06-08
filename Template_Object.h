/*
Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/


#ifndef MYTEAPOT_H
#define MYTEAPOT_H

//myTeapotVertices - homogeniczne wspó³rzêdne wierzcho³ków w przestrzeni modelu
//myTeapotNormals - homogeniczne wektory normalne œcian (per wierzcho³ek) w przestrzeni modelu
//myTeapotVertexNormals - homogeniczne wektory normalne wierzcho³ków w przestrzeni modelu
//myTeapotTexCoords - wspó³rzêdne teksturowania
//myTeapotColors - kolory wierzcho³ków
//myTeapotC1 - kolumna macierzy TBN^-1
//myTeapotC2 - kolumna macierzy TBN^-1
//myTeapotC3 - kolumna macierzy TBN^-1
//myTeapotC1_2 - kolumna uœrednionej macierzy TBN^-1
//myTeapotC2_2 - kolumna uœrednionej macierzy TBN^-1
//myTeapotC3_2 - kolumna uœrednionej macierzy TBN^-1

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
