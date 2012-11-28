#include "Model.h"
#include "City.h"
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>




Model m; //model class constructor
City c;

//keyboard globals
float zoom = 30.0f;
float xRad = 0.0, yRad = 0.0;
//float xPos = 0.0, yPos = 0.0, zPos = 0.0;

//mouse globals
//float xRot = 0.0;
//float yRot = 0.0f;
float initial_xrot = 0.0f;
float initial_yrot = 0.0f;
int prev_x = 0.0, prev_y = 0.0;

float lastx, lasty;

//dispaly lsit
GLuint displayList = glGenLists(1);

//camera
float xPos = 0.0, yPos = 0.0, zPos = 100.0;
float xRot = 0.0, yRot = 0.0, zRot = 0.0;

//model placement
int mnum = 0;
float mx = 0.0, my = 0.0, mz = 0.0;
float mRx = 0.0, mRy = 0.0, mRz = 0.0;
//Recording
int frameNumber = 0;
bool recording = 1;

//first run
bool firstRun = 1;
int cameraState = 1;
bool pauseCamera = 0; //not paused


GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
GLfloat AmbientLightPosition[] = {0.0, 0.0, 60.0, 0.0};
GLfloat AmbientLight[] = {1.0, 1.0, 1.0};
GLfloat LightningLight[] = {1.0, 1.0, 1.0};
int lastFlash = 0;

//ambient clouds
bool AmbientState = 1;
float alv = 1.0;


void InitCamera()
{
	xRot = 125.0;
	yRot = 180.0;
	zRot = -100.0;
	xPos = -264.0;
	yPos = -144.0; 
	zPos = 254.0;
}

//mouse movement callback function
void MouseMove( int x, int y )
{
	/*int diffx=(x-lastx)/2;
	int diffy=(y-lasty)/2;
	//glutWarpPointer(400,300);
	lastx=x;
	lasty=y;
	xRot += (float) diffy;
	yRot += (float) diffx;
	*/
}
//normal keyboard keys callback function
void NormalKeys( unsigned char key, int x, int y )
{
	if(key=='8'){
		recording = !recording;
		printf("Recoring: %i", recording); 
	}
	if(key=='`'){
		pauseCamera = !pauseCamera;
	}
	//Model placement
	if(key=='m'){
		mnum += 1;
		mx = 0.0;
		my = 0.0;
		mz = 0.0;
		mRx = 0.0;
		mRy = 0.0;
		mRz = 0.0;
		printf("Model: %s\n", c.modelPath.at(mnum));
		//breaks if you go over the model count
	}
	if(key=='i'){
		mx += 50;
	}
	if(key=='j'){
		my += 50;
	}
	if(key=='l'){
		my -= 50;
	}
	if(key=='k'){
		mx -= 50;
	}
	if(key==']'){
		mz += 10;
	}
	if(key=='['){
		mz -= 10;
	}
	if(key=='/'){
		printf("model:%i mx:%f my:%f mz:%f\n", mnum, mx, my, mz);
		printf("mRx:%f mRy:%f mRz:%f\n", mRx, mRy, mRz);
	}
	if(key=='.'){
		mRx += 90;
	}
	if(key==','){
		mRx -= 90;
	}
	if(key=='='){
		mRy += 90;
	}
	if(key=='-'){
		mRy -= 90;
	}
	if(key=='>'){
		mRz += 90;
	}
	if(key=='<'){
		mRz -= 90;
	}

	//rotate x
	if(key=='q'){
		xRot += 1;
		if (xRot >360) xRot -= 360;
	}

	if(key =='e'){
		 xRot -= 1;
		if (xRot < -360) xRot += 360;
	}
	//rotate y
	if(key=='x'){
		yRot += 1;
		if (yRot >360) yRot -= 360;
	}
	if(key=='c'){
		yRot -= 1;
		if (yRot < -360) yRot += 360;
	}
	//rotate z
	if(key=='r'){
		zRot += 1;
		if (zRot >360) zRot -= 360;
	}
	if(key=='f'){
		zRot -= 1;
		if (zRot < -360) zRot += 360;
	}

	if(key=='p')
	{
		printf("Current Capture Point\n");
		//print out the current camera position
		printf("xPos:%f yPos:%f zPos:%f\n", xPos, yPos, zPos);
	
		//print the current camera rotation
		printf("xRot:%f yRot:%f zRot:%f\n", xRot, yRot, zRot); 
	}

	if(key=='z')
	{
		InitCamera();
	}
	//Escape exits
	if (key == 27) 
		exit(0);
	//w moves forward
	if (key=='w')
	{
		zPos += 10;
	}

	//s moves back
	if (key=='s')
	{
		zPos -= 10;
	}

	//d moves right
	if (key=='d')
	{
		float yRotrad;
		yRotrad = (yRot / 180 * 3.141592654f);
		xPos += float(cos(yRotrad)) *2;
		zPos += float(sin(yRotrad)) *2;
	}

	//a moves left
	if (key=='a')
	{
		float yRotrad;
		yRotrad = (yRot / 180 * 3.141592654f);
		xPos -= float(cos(yRotrad)) *2;
		zPos -= float(sin(yRotrad)) *2;
	}


}
//special keyboard keys callback function
void SpecialKeys( int key, int x, int y )
{
	switch ( key ){
		case GLUT_KEY_LEFT:		//strafes the camera to the left
				yPos += 10;
			break;

		case GLUT_KEY_RIGHT:	//strafes the camera to the right
				yPos -= 10;
			break;

		case GLUT_KEY_UP:					//zooms the camera in the direction being viewed
				xPos += 10;
			break;

		case GLUT_KEY_DOWN:					//zooms the camera out in the direction veing viewed
				xPos -= 10;
			break;
	}
}


void Reshape(int w, int h) 
{
	//prevent devide by zero
	if (h == 0){
		h = 1;
	}

	float ratio =  w * 1.0 / h;		//get the window ratio

	glMatrixMode(GL_PROJECTION);	//set the current matrix to the projection matrix
	glLoadIdentity();				//load the identity matrix into the projection matrix to initialize it.
	glViewport(0, 0, w, h);			//set the viewport to be the whole window
	gluPerspective(45.0f, ratio, 0.1f, 2000.0f); //45degree fov, window ratio, near point, far point for clipping -- this sets what u can see
}

void modelPlacer()
{
	
	int model = mnum;
	//transforms from the city file
	glPushMatrix();	
	glTranslatef( c.transform.at(model).tx + mx , c.transform.at(model).ty + my , c.transform.at(model).tz + mz);
	glScalef(c.transform.at(model).sx , c.transform.at(model).sy , c.transform.at(model).sz);
	glRotatef(c.transform.at(model).rx + mRx, 0, 0, 1);
	glRotatef(c.transform.at(model).ry + mRy, 0, 1, 0);
	glRotatef(c.transform.at(model).rz + mRz, 1, 0, 0);

	for(int i = 0; i < c.models.at(model).getNumTriangle(); i++){
			
		glBindTexture(GL_TEXTURE_2D, c.models.at(model).texture_data[c.models.at(model).getTriangleTexture(i)]);
		glBegin(GL_TRIANGLES);
			//Normal
			//texCoord 1
			glTexCoord2f(c.models.at(model).getTriangleTupple(i, 1, "x"), c.models.at(model).getTriangleTupple(i, 1, "y"));
			glVertex3f(c.models.at(model).getVerticeCord(i,1,"x"),c.models.at(model).getVerticeCord(i,1,"y"), c.models.at(model).getVerticeCord(i,1,"z"));
			//texCoord 2
			glTexCoord2f(c.models.at(model).getTriangleTupple(i, 2, "x"), c.models.at(model).getTriangleTupple(i, 2, "y"));
			glVertex3f(c.models.at(model).getVerticeCord(i,2,"x"),c.models.at(model).getVerticeCord(i,2,"y"), c.models.at(model).getVerticeCord(i,2,"z"));
			//texCoord 3
			glTexCoord2f(c.models.at(model).getTriangleTupple(i, 3, "x"), c.models.at(model).getTriangleTupple(i, 3, "y"));
			glVertex3f(c.models.at(model).getVerticeCord(i,3,"x"),c.models.at(model).getVerticeCord(i,3,"y"), c.models.at(model).getVerticeCord(i,3,"z"));
		glEnd();
	}

	glPopMatrix();
}

//float x;
void BuildDispalyList(void)
{

	for(int model = 0; model < c.numModels; model++){

		glNewList(displayList + model+1, GL_COMPILE);

		//transforms from the city file
		glPushMatrix();	
		glTranslatef( c.transform.at(model).tx , c.transform.at(model).ty , c.transform.at(model).tz);
		glScalef(c.transform.at(model).sx , c.transform.at(model).sy , c.transform.at(model).sz);
		glRotatef(c.transform.at(model).rx, 0, 0, 1);
		glRotatef(c.transform.at(model).ry, 0, 1, 0);
		glRotatef(c.transform.at(model).rz, 1, 0, 0);

		for(int i = 0; i < c.models.at(model).getNumTriangle(); i++){
			
			glBindTexture(GL_TEXTURE_2D, c.models.at(model).texture_data[c.models.at(model).getTriangleTexture(i)]);
			glBegin(GL_TRIANGLES);
				//Normal
				//texCoord 1
				glTexCoord2f(c.models.at(model).getTriangleTupple(i, 1, "x"), c.models.at(model).getTriangleTupple(i, 1, "y"));
				glVertex3f(c.models.at(model).getVerticeCord(i,1,"x"),c.models.at(model).getVerticeCord(i,1,"y"), c.models.at(model).getVerticeCord(i,1,"z"));
				//texCoord 2
				glTexCoord2f(c.models.at(model).getTriangleTupple(i, 2, "x"), c.models.at(model).getTriangleTupple(i, 2, "y"));
				glVertex3f(c.models.at(model).getVerticeCord(i,2,"x"),c.models.at(model).getVerticeCord(i,2,"y"), c.models.at(model).getVerticeCord(i,2,"z"));
				//texCoord 3
				glTexCoord2f(c.models.at(model).getTriangleTupple(i, 3, "x"), c.models.at(model).getTriangleTupple(i, 3, "y"));
				glVertex3f(c.models.at(model).getVerticeCord(i,3,"x"),c.models.at(model).getVerticeCord(i,3,"y"), c.models.at(model).getVerticeCord(i,3,"z"));
			glEnd();
		}

		glPopMatrix();

		glEndList();
	}
}

void Record(int frame)
{
	printf("Recording ");
	int width = 1280;
	int height = 720;
	char buffer[33];
	itoa(frameNumber, buffer, 10);
	string file(buffer);
	file = "frame" + file + ".ppm";

	unsigned char *img = new unsigned char[width * height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);
	
	//PPM::Write( "C:/Users/Derek/Desktop/video/" + file, img, width, height );
	//PPM::Write( "./video/" + file, img, width, height );
	PPM::Write( file, img, width, height );
	delete img;
}

void InitMovie()
{
	xRot = 124.0;
	yRot = 179.0;
	zRot = -100.0;
	xPos = -450.0;
	yPos = -78.0; 
	zPos = 278.0;
}

void CameraMove()
{
	printf("Frame: %i - ", frameNumber);
	switch(cameraState){

	case 1:

	
			if(xPos == -274 && yPos == -64 && zPos == 134){ 
				cameraState = 3;
			}
			printf("C1\n");
			if(xPos <= -274){
				xPos++;
			}
			if(yPos < -64){
				yPos++;
			}
			if(zPos > 134){
				zPos--;
			}
		
		break;
		//skip
	case 2:
	
			printf("C2\n");
			if(xRot == 117){ 
				cameraState = 3; //
			}
			if(xRot >= 117){
				xRot -= 0.25;
			}
	
		break;

	case 3:
		

			printf("C3\n");
			if(xPos <= -154 && zPos <= 14 && xRot <= 102 && zRot >= -88){ 
				cameraState = 4;
			}
			if(xPos < -154){ //-66 -> -154
				xPos++;
			}
			if(zPos > 14){ // 134 -> 14
				zPos--;
			}
			if(xRot > 102){ //117 -> 102
				xRot--;
			}
			if(zRot < -88){ //-91 -> -88
				zRot++;
			}
			//
			if(yPos < -44){ //-66 -> -44
				yPos++;
			}

		break;
		
	
	case 4:
			printf("C4\n");
			if(xPos >= 106){ 
				cameraState = 5;
			}
			if(xPos < 106){ //-154 -> 106
				xPos++;
			}
	
		break;
		
	case 5:
		

			printf("C5\n");
			if(zRot <= -104){ 
				cameraState = 6;
			}
			if(zRot > -104){ //-88 -> -104
				zRot--;
			}
	
		break;

	case 6:


			printf("C6\n");
			if(xPos >= 156 && yPos <= -64 && zRot <= -171 ){ 
				cameraState = 7;
			}
			if(xPos < 156){ //106 -> 156
				xPos++;
			}
			if(yPos > -64){ //-44 -> -64
				yPos--;
			}
			if(zRot > -171){ // -104 -> -171
				//zRot--;
				zRot -= 2;
			}
	
		break;

	case 7:
	

			printf("C7\n");
			if(xPos >= 196 && yPos >= -34 && zRot <= -232){
				cameraState = 8;
			}
			if(xPos < 196){ //156 -> 196
				xPos++;
			}
			if(yPos < -34){ // -64 -> -34
				yPos++;
			}
			if(zRot > -232){ // -171 -> -232
				//zRot--;
				zRot -= 2;
			}
	
			break;

	case 8:


			printf("C8\n");
			if(xPos >= 206 && yPos >= 16 && zRot <= -306){
				cameraState = 9;
			}
			if(xPos < 206){ //196 -> 206
				xPos++;
			}
			if(yPos < 16){ //-34 -> 16
				yPos++;
			}
			if(zRot > -306){ //-232 -> -306
				//zRot--;
				zRot -= 2;
			}

			break;

	case 9:

			printf("C9\n");
			if(xPos <= 136 && zRot >= -26){
				cameraState = 10;
			}
			if(xPos > 136){ // 206 -> 128
				xPos--;
			}
			if(zRot < 26){ // -306 -> 26
				
				if(zRot < -360){
					zRot = (-zRot) - 360;
				}
				if(zRot < 0 ){
					zRot--;
				}else{
					zRot++;
				}
			}
			break;

	case 10:
		//if(cameraState == 10){

			printf("C10\n");
			if(yPos <= -34 && zRot <= -101){
				cameraState = 11;
			}
			if(yPos > -34){ // 16 -> -34
				yPos--;
			}
			if(zRot > -101){ // -26 -> -101
				zRot -= 2;
			}
		//}// end of c10
			break;
			

	case 11:

		printf("C11\n");
		if(xPos >= 256 && yPos <= -104 && zRot <= -181){
			cameraState = 12;
		}
		if(xPos < 256){ // 136 -> 256
			xPos++;
		}
		if(yPos > -104){ //-34 -> -104
			yPos--;
		}
		if(zRot > -181){ //-101 -> -181
			//zRot--;
			zRot -= 0.5;
		}
		break;
	

	case 12:

		printf("C12\n");
		if(xPos >= 316 && yPos >= -34 && zRot <= -218){
			cameraState = 13;
		}
		if(xPos < 316){ // 256 -> 316
			xPos++;
		}
		if(yPos < -34){ //-104 -> -34
			yPos++;
		}
		if(zRot > -218){ //-181 -> -218
			zRot--;
			//zRot -= 0.5;
		}
		break;

	case 13:

		printf("C13\n");
		if(xPos <= 246 && yPos >= 56 && zRot >= -183){
			cameraState = 15; //
		}
		if(xPos > 246){ //316 -> 246
			xPos--;
		}
		if(yPos < 56){ // -34 -> 56
			yPos++;
		}
		if(zRot < -183){ // -218 -> -183
			zRot++;
		}
		break;


		//skip
	case 14:
		printf("C14\n");
		if(yPos >= 196){
			cameraState = 15;
		}
		if(yPos < 196){ // 56 -> 196
			yPos++;
		}
		break;

	case 15:
		
		printf("C15\n");
		if(yPos >= 216 && zRot <= -266){
			cameraState = 16;
		}
		if(yPos < 216){//196 -> 216 //56 -> 216
			yPos++;
		}
		if(yPos >= 149){//delayed rotation
			if(zRot > -266){ // -183 -> -266
				zRot--;
			}
		}
		break;

	case 16:

		printf("C16\n");
		if(xPos <= -14){
			cameraState = 17;
		}
		if( xPos > -14){ // 246 -> -14
			xPos--;
		}
		break;

	case 17:

		printf("C17\n");
		if(zRot >= -102 && zRot <= -97){
			cameraState = 18;
		}
			
		zRot -= 1;
		if (zRot < -360){
			zRot += 360;
		}
		
		break;

	case 18:
		printf("Recording finished");
		recording = 0;
		break;
	//case 


		//printf("END\n");
	} // end of switch
}	// end of camera state machine

void AmbientLightUpdate()
{
	if(alv < 0.45){
		AmbientState = 0;
	}
	if(alv > 0.9){
		AmbientState = 1;
	}
	if(AmbientState){
		alv -= 0.005;
	}else{
		alv += 0.005;
	}
	printf("alv:%f", alv);
	AmbientLight[0] = alv;
	AmbientLight[1] = alv;
	AmbientLight[2] = alv;
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);

}

void Lightning()
{
	if( (rand() % 50) > 48 ){
		glEnable(GL_LIGHT0);
		lastFlash = frameNumber;
		printf("FLASH!!!");
	}
	if( frameNumber - lastFlash > 2 &&  LightningLight[0] == 1.0 ){
		glDisable(GL_LIGHT0);
	}
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightningLight);
}


void Display(void) 
{

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// Reset transformations
	glLoadIdentity();

	

	//rotating the camera
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	//translating the camera
	glTranslated(-xPos,-yPos,-zPos);


	//set the color to grey
	glColor3f(0.5f,0.5f,0.5f);
	glScalef(.05,.05,.05);

	modelPlacer();
	
	for(int model = 0; model < c.numModels; model++){
		glCallList(displayList + model+1);
	}


	
	glColor3f(0.0f,1.0f,0.0f);	//sets the glcolor to green
	glPushMatrix();				//pushes the modelview 
	glLoadIdentity();			//loads the identity matrix
	glMatrixMode(GL_PROJECTION);//sets the projection matrix
	glPushMatrix();				//pushes the projection matrix
	glLoadIdentity();			//loads the identy matrix

	glRasterPos2f(0.6f, -0.98f);	//sets the raster position for the text in the lower right hand corner
	char name[] = "Derek Meyer";	//char to hold the name
	for(int i = 0; i < 11; i++){	//looping through the letters in the name 
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);
	}
	glPopMatrix();					//pops the projection matrix
	glMatrixMode(GL_MODELVIEW);		//sets the modelview matrix
	glPopMatrix();					//pops the modelview matrix
	

	glutSwapBuffers(); //swaps the display buffers

	if(firstRun == 1){
		InitMovie();
		firstRun = 0;
	}else{

		if(recording == 1){
			Record(frameNumber);
		}
		if(!pauseCamera){
			CameraMove();
			AmbientLightUpdate();
			Lightning();
			frameNumber += 1;
		}
	}
}



int main(int argc, char **argv) { //argv[1] is the file name
	
	if(argc > 1){	//if no arguments were specified
		
		// init GLUT and create window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // using depth double buffer and rgba color
		glutInitWindowPosition(100,100);
		glutInitWindowSize(1280,720);
		glutCreateWindow("Assignment #1");
		glEnable(GL_CULL_FACE);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		glEnable (GL_LIGHT0);
		glLightfv (GL_LIGHT0, GL_POSITION, AmbientLightPosition); 

		glEnable(GL_LIGHT1);
		glLightfv (GL_LIGHT1, GL_POSITION, AmbientLightPosition); 

		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
		glEnable(GL_COLOR_MATERIAL);
		glShadeModel (GL_SMOOTH);
		
		glEnable(GL_TEXTURE_2D);

		
		//c.parse("C:/City/CityOne.city");
		//c.loadModels("C:/City/CityOne.city");
		c.parse(argv[1]);
		c.loadModels(argv[1]);
		
		BuildDispalyList();
		
		//initialize the camera
		InitCamera();

		// register callbacks
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutIdleFunc(Display);

		// keyboard callbacks
		glutKeyboardFunc(NormalKeys);
		glutSpecialFunc(SpecialKeys);

		//mouse callbacks
		glutPassiveMotionFunc(MouseMove);

		
		// enter GLUT event processing cycle
		glutMainLoop();
	}
	else{
		printf("%s","Please enter a model file as an arguement!");
	}

	return 1;
}