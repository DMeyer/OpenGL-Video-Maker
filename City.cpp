#include "City.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void City::parse(char *cfile)
{
	ifstream file;		//input file stream
	file.open(cfile);	//opens the model file passed from argv in the main

	if(!file.is_open()){//checks if the file is not open and closes the program if it failed to open the model file
		cout << "couldnt open the city file\n";
		exit(1);
	}

	string s;
	istringstream ins;
	string path;

	getline(file,s);
	ins.str(s);
	ins >> cityName;
	getline(file,s);
	ins.clear();
	ins.str(s);
	ins >> numModels;


	while(getline(file,s)){
		ins.clear();
		ins.str(s);

		if(s.at(0) != '#' ){
			ins >> path;
			this->modelPath.push_back(path);

			Transform t;
			ins >> t.sx >> t.sy >> t.sz >> t.rx >> t.ry >> t.rz >> t.ox >> t.oy >> t.oz >> t.tx >> t.ty >> t.tz;
			this->transform.push_back(t);
		}else{
			this->numModels -= 1;
		}

	}
	file.close();
}

void City::loadModels(char * cfile)
{

	for(int i = 0; i < numModels; i++){
		Model m;

		string file = cfile;
		char * filename = new char[file.length()+1];
		strcpy(filename,file.c_str());

		int location;
		for(int x = 0; filename[x]!='\0';x++){
		if(filename[x] == '/' || filename[x] == '\\') 
			location = x;
		}
		filename[location+1] = '\0';

		string modelPath = filename;

		modelPath = modelPath + this->modelPath.at(i); //string containing the direct path the the model

		//convert modelPath string to char*
		char* path = new char[modelPath.length() + 1];
		strcpy(path,modelPath.c_str());

	

		m.parse( path );
		m.loadTextures( path );

		this->models.push_back(m);
	}
}