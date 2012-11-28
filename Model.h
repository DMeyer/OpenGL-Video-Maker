#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "PPM.hpp"
#include <GL/glut.h>
#include <map>

using namespace std;

//model class for holding the model data and parsing the model file.
class Model
{

public:
	
	//Constructor
	Model();

	//methods
	void parse(char *mfile);	//method parses the model file. The file is passed from argv in main

	int getNumTriangle();	//method returns the number of triangles in the triangles vector
	int getNumTextures();
	string getTextureStr( int texture );
	float getVerticeCord( int triangle, int indice, string xyz ); //method returns the vertice cordinat for the specified triangle, indice and cord

	int getTriangleNormal( int triangle );
	//string getTriangleTextureStr( int triangle );
	float getTriangleTupple( int triangle, int tupple, string xy );

	int getTriangleTexture( int triangle );

	void loadTextures(char *mfile);
	void optimize();

	void printV();	//method for printing the vertices vector
	void printT();	//method for printing the triangles vector
	

	GLuint * texture_data;
	
	

//protected:

	//Vertex struct
	struct V {
		float x; //floats to hold the cordinates
		float y;
		float z;
	};

	//Triangle struct
	struct T {
		int i1, i2, i3;		//indicies of the vertices
		int normal;			//indicie of the normal
		int texture;		//indicie of the texture
		float ti1x, ti1y;	//tubbles for holding the x and y texture coordinates
		float ti2x, ti2y;
		float ti3x, ti3y;
	};

	//Normal struct
	struct N {
		float n1, n2, n3;
	};


	//variables
	string name; // name of the model

	vector<V> vertices;		//vector for the vertices
	vector<T> triangles;	//vector for the triangles
	vector<N> normals;		//vector for the normals
	vector<string> textures; // vector for the texture strings

	map<string, GLuint> tex_map;
	map<GLuint, vector<T>*> texture_to_triangles;
	
};


#endif