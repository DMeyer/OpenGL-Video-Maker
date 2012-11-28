void CameraMove()
{
	printf("Frame: %i - ", frameNumber);
	if(cameraState == 1){
		if(xPos == -274 && yPos == -64 && zPos == 134){ 
			cameraState = 2;
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
	}//end of c1
	if(cameraState == 2){// p1 complete
		printf("C2\n");
		if(xRot == 117){ 
			cameraState = 3; //
		}
		if(xRot >= 117){
			xRot -= 0.25;
		}
	}//end of s4
	if(cameraState == 3){

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
	}// end of c3

	if(cameraState == 4){

		printf("C4\n");
		if(xPos >= 106){ 
			cameraState = 5;
		}
		if(xPos < 106){ //-154 -> 106
			xPos++;
		}
	}// end of c4

	if(cameraState == 5){

		printf("C5\n");
		if(zRot <= -104){ 
			cameraState = 6;
		}
		if(zRot > -104){ //-88 -> -104
			zRot--;
		}
	}// end of c5
	if(cameraState == 6){

		printf("C6\n");
		if(xPos ){ 
			cameraState = 7;
		}
		if(xPos < 156){ //106 -> 156
			xPos++;
		}
		if(yPos > -64){ //-44 -> -64
			yPos--;
		}
		if(zRot > -171){ // -104 -> -171
			zRot--;
		}

	}// end of c6


}	// end of camera state machine