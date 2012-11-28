#ifndef CITY_H
#define CITY_H

#include <string>
#include <vector>
#include "Model.h"
#include <map>


class City
{

public:

	void parse(char *cfile);
	void loadModels(char * cfile);
	
	string cityName;
	int numModels;
	vector<Model> models; 
	vector<string> modelPath; 

	struct Transform {
		float sx, sy, sz;
		float rx, ry, rz;
		float ox, oy, oz;
		float tx, ty, tz;
	};

	vector<Transform> transform;

	
	

protected:

	

	
};



#endif