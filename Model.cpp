#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Model::Model()
{
}


float Model::getTriangleTupple( int triangle, int tupple, string xy )
{
	if( tupple == 1 ){
		if(xy == "x"){
			return this->triangles.at(triangle).ti1x;
		}
		if(xy == "y"){
			return this->triangles.at(triangle).ti1y;
		}
	}
	if( tupple == 2 ){
		if(xy == "x"){
			return this->triangles.at(triangle).ti2x;
		}
		if(xy == "y"){
			return this->triangles.at(triangle).ti2y;
		}
	}
	if( tupple == 3 ){
		if(xy == "x"){
			return this->triangles.at(triangle).ti3x;
		}
		if(xy == "y"){
			return this->triangles.at(triangle).ti3y;
		}
	}
}

int Model::getTriangleNormal( int triangle )
{
	return this->triangles.at(triangle).normal;
}

string Model::getTextureStr(int texture)
{
	return this->textures.at(texture);
}

int Model::getTriangleTexture( int triangle )
{
	return this->triangles.at(triangle).texture;
}

int Model::getNumTextures()
{
	return this->textures.size();
}
//function returns the vertex for the specified triangle, indice, and x y or z cord
float Model::getVerticeCord( int triangle, int indice, string xyz )
{
	//the i1 indice from the triangle vector
	if( indice == 1 ){ 
		if( xyz == "x" ){ //returns the x cord
			return this->vertices.at( this->triangles.at(triangle).i1 ).x;	
		}
		if( xyz == "y" ){//returns the y cord
			return this->vertices.at( this->triangles.at(triangle).i1 ).y;	
		}
		if( xyz == "z" ){//returns the z cord
			return this->vertices.at( this->triangles.at(triangle).i1 ).z;	
		}
	}
	//the i2 indice from the triangle vector
	if( indice == 2 ){
		if( xyz == "x" ){//returns the x cord
			return this->vertices.at( this->triangles.at(triangle).i2 ).x;	
		}
		if( xyz == "y" ){//returns the y cord
			return this->vertices.at( this->triangles.at(triangle).i2 ).y;	
		}
		if( xyz == "z" ){//returns the z cord
			return this->vertices.at( this->triangles.at(triangle).i2 ).z;	
		}
	}
	//the i3 indice from the triangle vector
	if( indice == 3 ){
		if( xyz == "x" ){//returns the x cord
			return this->vertices.at( this->triangles.at(triangle).i3 ).x;	
		}
		if( xyz == "y" ){//returns the y cord
			return this->vertices.at( this->triangles.at(triangle).i3 ).y;	
		}
		if( xyz == "z" ){//returns the z cord
			return this->vertices.at( this->triangles.at(triangle).i3 ).z;	
		}
	}
}
//returns the number of triangles in the model
int Model::getNumTriangle()
{
	return this->triangles.size();
}

void Model::loadTextures(char *mfile)
{
	int w, h;
	int location;
	unsigned char *img;
	texture_data = new GLuint[getNumTextures()];
	string file = mfile;
	char * filename = new char[file.length()+1];
	strcpy(filename,file.c_str());

	for(int x = 0; filename[x]!='\0';x++){
		if(filename[x] == '/' || filename[x] == '\\') 
			location = x;
	}
	filename[location+1] = '\0';

	//declare map of string to GLUINT
	tex_map = map<string, GLuint>();
	for(int i = 0; i < getNumTextures(); i++){
		if (tex_map[getTextureStr(i)] != NULL)
		{
			texture_data[i] = tex_map[getTextureStr(i)];
			continue;
		}
		//img = PPM::Read("C:/HebbBuilding/"+ m.getTextureStr(i), w, h);

		img = PPM::Read(filename + getTextureStr(i), w, h);
		glGenTextures(1,&(texture_data[i]));
		tex_map[getTextureStr(i)] = texture_data[i];
		glBindTexture(GL_TEXTURE_2D, texture_data[i]);
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, img ); 
	}
}

void Model::optimize()
{
	texture_to_triangles = map<GLuint, vector<T>*>();

	for(int i = 0; i < this->triangles.size(); i++){
		GLuint tmp = texture_data[this->triangles.at(i).texture];
		if (texture_to_triangles[tmp] == NULL)
		{
			texture_to_triangles[tmp] = new vector<T>();
		}
		texture_to_triangles[tmp]->push_back(triangles.at(i));
	}

}

//for debugging prints out the x y and z cords of the vectices in the virtices vector
void Model::printV()
{
	for(int i = 0; i < this->vertices.size(); i++){
		cout << "i= " << i << "   Vertex x=" << this->vertices.at(i).x << "  y=" << this->vertices.at(i).y << "  z=" << this->vertices.at(i).z << endl; 
	}

}
//for debugging prints out the i1, i2, and i3 indices of the triangles from the triangles vector
void Model::printT()
{
	for(int i = 0; i < this->triangles.size(); i++){
		cout << "i= " << i << "   Triangle i1=" << this->triangles.at(i).i1 << "  i2=" << this->triangles.at(i).i2 << "  i3=" << this->triangles.at(i).i3 << endl; 
	}
}

//Model file parser
void Model::parse(char *mfile)
{
	bool DEBUG = false; //flag for enabling cout's for debuging
	ifstream file;		//input file stream
	file.open(mfile);	//opens the model file passed from argv in the main

	if(!file.is_open()){//checks if the file is not open and closes the program if it failed to open the model file
		cout << "couldnt open the file\n";
		exit(1);
	}

	string temp; //temp string for holding stringstream data
	string type; //string to hold the dype of data i.e verticies, normals...
	string name; //string to hold the model name
	string s;	//the input string from the file
	istringstream ins, ins2;	//string streams for parsing the file
	int i1, i2, i3;	//integers for holding the triangle verticies
	float x, y, z;	// floats for holding the triangle coords
	float n1, n2, n3; // floats for holding the normal coords
	int tnormal, ttexture; // integers for holding the indices of the triangles normals and textures
	float ti1x, ti1y; //floats for holding the x and y texture coordinates for the triangles
	float ti2x, ti2y;
	float ti3x, ti3y;
	string tppm;		//string for holding the texture strigns .ppm

	while(getline(file,s)){	//gets the next line from the file and puts it into the string s
		ins.clear();	//clears the string streams
		ins2.clear();

		string bl;	//string for blank lines
		ins2.str(s);//putting the string into the stringstream
		ins2 >> bl; //putting the formatted string into a string
		if(s.empty()){//checks if the line is a blank line
			if(DEBUG){cout << "blank line\n";}
		}
		else{//if not a blank line
			ins.str(s);  //puts the string into the stringstream
			ins >> type; //puts the formatted string into the type string

			//checking for model type

			//Vertices
			if( type == "<vertices" ){	//if the file is at the vertices block
				type = "";				//clear the type

				while(getline(file,s)){ //get the next line
					ins.clear();		//clears the stringstreams
					ins2.clear();

					string bl;			//string for blank lines
					ins2.str(s);		//putting the string into the stringstream
					ins2 >> bl;			//putting the formatted string into a string
					if(bl.empty()){		//checks if the line is a blank line
						if(DEBUG){cout << "blank line\n";}
					}
					else{
						ins.str(s);		//putting the string into the stringstream
						if(DEBUG){cout << "Line: " << s << endl;}

						if( s.find("</vertices") != -1 ){ //checks if its at the end of the vertices block

							if(DEBUG){cout << "BREAK!!!!\n";}
								break;				//breaks the vertices loop if the end has been found
						}
						else{					//valid data
							ins >> x >> y >> z;	//puts the formatted data into the x, y, and z floats
							V v;				//creats a vertex struct
							v.x = x;			//filling the vertex struct
							v.y = y;
							v.z = z;
							this->vertices.push_back(v);	//added the vertex to the vertices vector
							if(DEBUG){cout << "Vertex x=" << x << ", y=" << y << ", z=" << z << endl;}
						}
					}
				}
			}//end of <vertices
	
			//Normals
			if( type == "<normals" ){	//if the file is at the normals block
				type = "";				//clear the type

				while(getline(file,s)){ //get the next line
					ins.clear();		//clears the stringstreams
					ins2.clear();

					string bl;			//string for blank lines
					ins2.str(s);		//putting the string into the stringstream
					ins2 >> bl;			//putting the formatted string into a string
					if(bl.empty()){		//checks if the line is a blank line
						if(DEBUG){cout << "blank line\n";}
					}
					else{
						ins.str(s);		//putting the string into the stringstream
						if(DEBUG){cout << "Line: " << s << endl;}

						if( s.find("</normals") != -1 ){ //checks if its at the end of the normals block

							if(DEBUG){cout << "BREAK!!!!\n";}
								break;				//breaks the normals loop if the end has been found
						}
						else{					//valid data
							ins >> n1 >> n2 >> n3;	//puts the formatted data into the n1, n2, and n3 floats
							N n;				//creats a normal struct
							n.n1 = n1;			//filling the normal struct
							n.n2 = n2;
							n.n3 = n3;
							this->normals.push_back(n);	//added the vertex to the vertices vector
							if(DEBUG){cout << "Normal n1=" << n1 << ", n2=" << n2 << ", n3=" << n3 << endl;}
						}
					}
				}
			}//end of <normals
		
			//Name
			if( type == "<name" ){		//if the file is at the name block
				type = "";				//clears the type
				while(getline(file,s)){	//get the next line
					ins.clear();		//clears the stringstreams
					ins2.clear();

					string bl;			//string for blank lines
					ins2.str(s);		//putting the string into the stringstream
					ins2 >> bl;			//putting the formatted string into a string
					if(bl.empty()){		//checks if the line is a blank line
						if(DEBUG){cout << "blank line\n";}
					}
					else{
						ins.str(s);		//putting the string into the stringstream
						if(DEBUG){cout << "Line: " << s << endl;}

						if( s.find("</name") != -1 ){	//if the end of the name block

							if(DEBUG){cout << "BREAK!!!!\n";}
								break;		//break out of the name loop
						}
						else{				//valid data
							ins >> name;	//puts the formatted string into the name string
							this->name = name; //puts the model name into the model class
							if(DEBUG){cout << "name: " << name << endl;}
						}
					}
				}

			}//end of <name

			//Textures
			if( type == "<textures" ){		//if the file is at the name block
				type = "";				//clears the type
				while(getline(file,s)){	//get the next line
					ins.clear();		//clears the stringstreams
					ins2.clear();

					string bl;			//string for blank lines
					ins2.str(s);		//putting the string into the stringstream
					ins2 >> bl;			//putting the formatted string into a string
					if(bl.empty()){		//checks if the line is a blank line
						if(DEBUG){cout << "blank line\n";}
					}
					else{
						ins.str(s);		//putting the string into the stringstream
						if(DEBUG){cout << "Line: " << s << endl;}

						if( s.find("</textures") != -1 ){	//if the end of the name block

							if(DEBUG){cout << "BREAK!!!!\n";}
								break;		//break out of the name loop
						}
						else{				//valid data
							ins >> tppm;	//puts the formatted string into the name string
							this->textures.push_back(tppm); //puts the model name into the model class
							if(DEBUG){cout << "texture: " << tppm << endl;}
						}
					}
				}

			}//end of <textures

			//Triangles
			if( type == "<triangles" ){		//if the file is at the triangle block
				type = "";					//clears the type
			
		
				while(getline(file,s)){		//gets the next line from the file
					ins.clear();			//clears the stringstreams
					ins2.clear();

					string bl;			//string for blank lines
					ins2.str(s);		//putting the string into the stringstream
					ins2 >> bl;			//putting the formatted string into a string
					if(bl.empty()){		//checks if the line is a blank line
						if(DEBUG){cout << "blank line\n";}
					}
					else{
						ins.str(s);//putting the string into the stringstream

						if( s.find("</triangles") != -1 ){	//if the end of the triangles block
							
							if(DEBUG){cout << "BREAK!!!!\n";}
								break;						//break the tiangle loop
						}
						else{ //valid data
						
							ins >> i1 >> i2 >> i3 >> tnormal >> ttexture >> ti1x >> ti1y >> ti2x >> ti2y >> ti3x >> ti3y;	//puts the formatted data into the int's for the indices
							T t;		//creates a triangle struct
							t.i1 = i1;	//fills the triangle struct with the indices
							t.i2 = i2;
							t.i3 = i3;
							t.normal = tnormal;
							t.texture = ttexture;
							t.ti1x = ti1x;
							t.ti1y = ti1y;
							t.ti2x = ti2x;
							t.ti2y = ti2y;
							t.ti3x = ti3x;
							t.ti3y = ti3y;
							this->triangles.push_back(t);	//addes the triangle struct to the triangle vector
							if(DEBUG){cout << "Triangle i1=" << i1 << ", i2=" << i2 << ", i3=" << i3 << ", normal=" << tnormal << ", texture=" << ttexture << endl;}
						}
					}
				}
			}// end of <triangles
		}
	}// end of file

	file.close(); //closes the model file
}