/////////////////////////////////////////////////////////////////////////////
// Open Haptics and OpenAL Sample Program.
// The example shows how to play a static audio WAVE file using the OpenAL library
// The example is displays all the properties and tools provided by openAL to play static sound in a 3d environment
// To learn more about OpenAL read the documentation and see samples provided in the library
//////////////////////////////////////////////////////////////////////////////

#include <QHHeadersGLUT.h>//Include all necessary headers


//#include <cstdlib>
//#include <list>
//#include <fstream>
//#include <iostream>


//#include <stdio.h>
//#include <string>
//#include <sstream>

//#include <HDU/hduLine.h>
//#include <math.h>

// --------- Headers related to audio -------------
//#include <Windows.h>
//#include "LoadFile.h"
//#include <al.h>    // OpenAL header files
//#include <alc.h>

//using std::list;

// ***************  Related to Audio  *********************//
// --------- OpenAL variables -----------//
//ALCdevice* audioDevice;
//ALCcontext* audioContext;
//ALenum errorCode=0;
//ALuint helloBuffer;
//ALuint helloSource;
//ALenum format;
//ALint frequency;
// ----------------------------------//

// --------  Load Audio File  --------
//LoadFile File1("new.wav");

// -------- Flag for start and Pause  ------- //
//bool playFlag;

static Cursor* HandCursor;
static Cursor* ScalpelCursor;
static Cursor* DrillCursor;
static Cursor* HammerCursor;
TriMesh* Hand = NULL;
TriMesh* Scalpel = NULL;
TriMesh* Drill = NULL;
TriMesh* Hammer = NULL;

int changeCursor;

/*
TriMesh* FemoreCut;// = NULL;
TriMesh* FemorePezzoAlto;// = NULL;
TriMesh* FemorePezzoBasso;// = NULL;
TriMesh* FemorePezzoMedio;// = NULL;
TriMesh* FemorePrinc;// = NULL;
TriMesh* GambaCut;// = NULL;
TriMesh* GambaPiegataFinale;// = NULL;
TriMesh* GambaPiegataSemi;// = NULL;
TriMesh* GambaSingolaDritta;// = NULL;
TriMesh* OperazioneQuasiFinita;// = NULL;
TriMesh* ProtesiMediaNonSistemata;// = NULL;
TriMesh* ProtesiMediaSistemata;// = NULL;
TriMesh* ProtesiSopraNonSistemata;// = NULL;
TriMesh* ProtesiSopraSistemata;// = NULL;
TriMesh* ProtesiSottoNonSistemata;// = NULL;
TriMesh* ProtesiSottoSistemata;// = NULL;
TriMesh* RotolaNonCut;// = NULL;
TriMesh* TibPerCut;// = NULL;
TriMesh* TibPerNonCut;// = NULL;*/


	// Properties that can affect the sound in 3D space
//ALfloat SourcePos[] = { 0.0,0.0,0.0 };
//ALfloat SourceVel[] = { 0.0,0.0,0.0 };
//ALfloat ListenerPos[] = { 0.0,0.0,-3.0 };
//ALfloat ListenerVel[] = { 0.0,0.0,0.0 };
//ALfloat ListenerOri[] = { 0.0,0.0,-1.0, 0.0, 1.0, 0.0 };

//float FOV;
//float NearPlane;
//float FarPlane;
//hduVector3Dd Eye;
//hduVector3Dd LookAt;
//hduVector3Dd UpVector;


QHGLUT* DisplayObject;
DeviceSpace* Omni;

void Graphics_cb(void);
void Button1Down_cb(unsigned int ShapeID);
void Button1Up_cb(unsigned int ShapeID);
void myUnTouch(unsigned int ShapeID);
void myTouchCallback(unsigned int ShapeID);
void motionCallback1(unsigned int ShapeID);
void Button2Up1(unsigned int ShapeID);
void Button2Down1(unsigned int ShapeID);
void ChangeCursor(int changeCursor);

//static int ib = 0;
//static int is = 0;
//static int iFb = 0;
//static int iFs = 0;

//bool draggingCassa;
//bool draggingKidney1;
//bool draggingKidney2;
//bool flag;

//static float fmag;
//static hduVector3Dd force;
//static hduVector3Dd Cpos;

//int front = 0;

//void HLCALLBACK startEffectCB(HLcache* cache, void* userData);
//void HLCALLBACK computeForceCB(HDdouble force[3], HLcache *cache, void * userData);
//void HLCALLBACK stopEffectCB(HLcache *cache, void * userData);

//static hduVector3Dd fulcrumPoint;
//static hduVector3Dd pos;
//static hduQuaternion ori;
//static hduQuaternion unitVector(0, hduVector3Dd(0, 0, 1));
//static hduVector3Dd p0;
//static hduVector3Dd p1;
//static hduVector3Dd newPos;
//static float gain = 0.5;
//static hduVector3Dd forceF;
//static hduVector3Dd forceL;
//static float length;
//static float maxForce = 0.6;
//static hduVector3Dd accumForce;
//static hduVector3Dd newForce;
//static float forceLength;
//static HDdouble nominalMaxForce;
//static hduVector3Dd vibrForce;
//static int count = 0;

//static int iPTB = 0;
//static int iPTS = 0;
//static int iPTf = 0;
//static int iV = 0;
//static float F;
//static hduVector3Dd Force;

int main(int argc, char *argv[])
{
	DisplayObject = new QHGLUT(argc, argv);
	Omni = new DeviceSpace;
	DisplayObject->tell(Omni);
	DisplayObject->setBackgroundColor(0.0, 0.0, 0.6);

	HandCursor = new Cursor("Modelli/Cursors/Mano.stl");
	//HandCursor->scaleCursor(0.002);
	//HandCursor->setRelativeShapeOrientation(0.0, 1.0, 0.0, 180);
	Hand = HandCursor->getTriMeshPointer();
	//HandCursor->debugCursor();
	DisplayObject->tell(HandCursor);

	ScalpelCursor = new Cursor("Modelli/Cursors/Scalpel.stl");
	//ScalpelCursor->scaleCursor(0.002);
	//ScalpelCursor->setRelativeShapeOrientation(0.0, 1.0, 0.0, 180);
	Scalpel = ScalpelCursor->getTriMeshPointer();
	//ScalpelCursor->debugCursor();
	DisplayObject->tell(ScalpelCursor);
	ScalpelCursor->setVisibility(false, false);

	DrillCursor = new Cursor("Modelli/Cursors/Drill.stl");
	//DrillCursor->scaleCursor(0.002);
	//DrillCursor->setRelativeShapeOrientation(0.0, 1.0, 0.0, 180);
	Drill = DrillCursor->getTriMeshPointer();
	//DrillCursor->debugCursor();
	DisplayObject->tell(DrillCursor);
	DrillCursor->setVisibility(false, false);

	HammerCursor = new Cursor("Modelli/Cursors/Hammer.stl");
	//HammerCursor->scaleCursor(0.002);
	//HammerCursor->setRelativeShapeOrientation(0.0, 1.0, 0.0, 180);
	Hammer = HammerCursor->getTriMeshPointer();
	//HammerCursor->debugCursor();
	HammerCursor->tell(HammerCursor);
	HammerCursor->setVisibility(false, false);

	/*
	cassa = new TriMesh("models2/CassaFinaleSPERO.stl");
	cassa->setTexture("models/bone.jpg");
	cassa->setShapeColor(1.0, 1.0, 1.0);
	cassa->setPopthrough(0.3);
	cassa->setStiffness(1.0);
	cassa->setRenderModeDepth();
	cassa->setTranslation(0, 0, -500);
	DisplayObject->tell(cassa);

	kidney1 = new TriMesh("models2/kidney1max.stl");
	kidney1->setRenderModeFeedback();
	kidney1->setTranslation(0, 0, -500);
	kidney1->setPopthrough(0.3,"Front");
	kidney1->setShapeColor(0.7, 0.1, 0.1);
	DisplayObject->tell(kidney1);

	kidney2 = new TriMesh("models2/kidney2max.stl");
	kidney2->setRenderModeFeedback();
	kidney2->setPopthrough(0.3,"Front");
	kidney2->setStiffness(0.1);
	kidney2->setTranslation(0, 0, -500);
	kidney2->setShapeColor(0.7, 0.1, 0.1);
	DisplayObject->tell(kidney2);
	kidney2->setTexture("models/kidney.png");

	Box* B = new Box;
	B->setTranslation(-2, -2, 50);
	B->setScale(0.001);
	DisplayObject->tell(B);

	Omni->button1DownCallback(Button1Down_cb, cassa);
	Omni->button1DownCallback(Button1Down_cb, kidney1);
	Omni->button1DownCallback(Button1Down_cb, kidney2);*/
	Omni->button1UpCallback(Button1Up_cb);
	/*Omni->unTouchCallback(myUnTouch, cassa);
	Omni->unTouchCallback(myUnTouch, kidney1);
	Omni->unTouchCallback(myUnTouch, kidney2);
	Omni->touchCallback(myTouchCallback, cassa);
	Omni->touchCallback(myTouchCallback, kidney1);
	Omni->touchCallback(myTouchCallback, kidney2);

	Omni->button2DownCallback(Button2Down1);
	Omni->button2UpCallback(Button2Up1);

	Omni->motionCallback(motionCallback1, cassa);
	Omni->motionCallback(motionCallback1, kidney1);
	Omni->motionCallback(motionCallback1, kidney2);

	DisplayObject->preDrawCallback(Graphics_cb);

	//***********************   REGARDING SOUND    ********************************//*/
	
	// Create an audio device
	audioDevice = alcOpenDevice(NULL); // NULL refers to the default device connected to the computer
	errorCode = alcGetError(audioDevice);
    
	// Create an audio context
	// One context can have one Listner and Multiple Sources and Buffers
	audioContext = alcCreateContext(audioDevice,NULL); 
    alcMakeContextCurrent(audioContext);
    errorCode = alcGetError(audioDevice);
	
	// Create a Buffer
	alGenBuffers(1,&helloBuffer); // Buffer stores the audio data
	errorCode = alGetError();

	// Create a source
	alGenSources (1, &helloSource); // Virtual source from which the sound is emitted in the application
	errorCode = alGetError();
	
	// Read information about the WAVE file from the Object "File1" we created
	frequency = File1.sampleRate;
	// Find if file is stereo or mono
	// Find if file is 8 or 16 bit 
	if(File1.bitsPerSample == 8){
		if (File1.channels == 1)
			format = AL_FORMAT_MONO8;
		else if (File1.channels == 2)
			format = AL_FORMAT_STEREO8;
	}
	else if(File1.bitsPerSample == 16){
		if (File1.channels == 1)
			format = AL_FORMAT_MONO16;
		else if (File1.channels == 2)
			format = AL_FORMAT_STEREO16;
	}

	// Fill the buffer with the information
	alBufferData(helloBuffer,format,File1.buf,File1.dataSize,frequency);

	// Attach buffer to source
	alSourcei (helloSource, AL_BUFFER, helloBuffer);


	// Set the proerties created above
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
		
	alSourcef (helloSource, AL_PITCH, 1.0);
	alSourcef (helloSource, AL_GAIN, 10000.0);
	alSourcefv (helloSource, AL_POSITION, SourcePos);
	alSourcefv (helloSource, AL_VELOCITY, SourceVel);
	alSourcei (helloSource, AL_LOOPING, AL_TRUE);

	// Clear memory used by OpenAl by deleting everything created
	/*
	fclose(fp); 
	delete[] buf;
	alDeleteSources(1,&helloSource);
	alDeleteBuffers(1,&helloBuffer);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(audioContext);
	alcCloseDevice(audioDevice);
	*/
	//  ******************************************************************************  //
	
	//Omni->startServoLoopCallback(startEffectCB, computeForceCB, stopEffectCB, NULL);
	
    qhStart();//Set everything in motion
    return 0;
}

/*void Graphics_cb() {

	DisplayObject->getCamera(&FOV, &NearPlane, &FarPlane, &Eye, &LookAt, &UpVector);
	ListenerPos[0] = Eye[0];
	ListenerPos[1] = Eye[1];
	ListenerPos[2] = Eye[2];

	hduMatrix globalDragTransform;

	if (draggingCassa) {
		globalDragTransform = cassa->getTransform();
		kidney1->setTransform(globalDragTransform);
		kidney2->setTransform(globalDragTransform);

	}
	else if (draggingKidney1) {
		globalDragTransform = kidney1->getTransform();
		cassa->setTransform(globalDragTransform);
		kidney2->setTransform(globalDragTransform);
	}
	else if (draggingKidney2) {
		globalDragTransform = kidney2->getTransform();
		cassa->setTransform(globalDragTransform);
		kidney1->setTransform(globalDragTransform);
	}

	Cpos = OmniCursor->getPosition();
	ALfloat	SourcePos[] = { Cpos[0],Cpos[1],Cpos[2] };
	alSourcefv(helloSource, AL_POSITION, SourcePos);

}*/

/*void Button1Down_cb(unsigned int ShapeID) {

	TriMesh* modelTouched = TriMesh::searchTriMesh(ShapeID);
	kidney2->setRotationInPlace(hduVector3Dd(1, 0, 0), 270);
	kidney1->setRotationInPlace(hduVector3Dd(1, 0, 0), 270);
	cassa->setRotationInPlace(hduVector3Dd(1, 0, 0), 270);

	draggingCassa = false;
	draggingKidney1 = false;
	draggingKidney2 = false;
	if (modelTouched == cassa) {
		draggingCassa = true;
		kidney1->setHapticVisibility(false);
		kidney2->setHapticVisibility(false);

	}
	if (modelTouched == kidney1) {
		draggingKidney1 = true;
		cassa->setHapticVisibility(false);
		kidney2->setHapticVisibility(false);

	}
	else if (modelTouched == kidney2) {
		draggingKidney2 = true;
		cassa->setHapticVisibility(false);
		kidney1->setHapticVisibility(false);

	}
}*/

void Button1Up_cb(unsigned int ShapeID) {
	
	changeCursor++;
	if (changeCursor == 4)
		changeCursor = 0;

	ChangeCursor(changeCursor);


}

/*void myUnTouch(unsigned int ShapeID)
{

	if (ShapeID == 3) //ShapeID bone
	{
		alSourcef(helloSource, AL_PITCH, 2.0);
		if ((Force.magnitude() >= 1.5))
		{
			cassa->setTouchableFace("Back");
			//Omni->setFriction(0.5, 0.3);
			//V->setShapeColor(0, 0, 0);
			iPTS = 1;
			iPTf = 1;

		}
		else if ((Force.magnitude() < 1.5 || Force.magnitude() > 0.3)) //&& (Force.magnitude() > 0.1)) 
		{
			cassa->setTouchableFace("Front");
			//Omni->setFriction(0.0, 0.0); // gain and magnitude of friction
			//V->setShapeColor(1, 1, 1);
			iPTS = 0;
		}
	}

	if (ShapeID == 4  || ShapeID == 5) //ShapeIDs kidneys
	{
		if ((Force.magnitude() >= 1.5))
		{
			//Omni->setDamping(0.9, 0.9);
			kidney1->setTouchableFace("Back");
			kidney2->setTouchableFace("Back");
			iPTB = 1;
			iPTf = 1;

		}
		else if ((Force.magnitude() < 1.5 || Force.magnitude() > 0.3))
		{
			kidney1->setTouchableFace("Front");
			kidney2->setTouchableFace("Front");
			//Omni->setDamping(0.0, 0.0);
			iPTB = 0;

		}
	}
}*/

/*
void myTouchCallback(unsigned int ShapeID)
{
	if (ShapeID == 3)
	{
		alSourcef(helloSource, AL_PITCH, 1.0);
	}
}*/
/*
void motionCallback1(unsigned int ShapeID)
{
	Cpos = OmniCursor->getPosition();
	SourcePos[0] = Cpos[0];
	SourcePos[1] = Cpos[1];
	SourcePos[2] = Cpos[2];
	std::cout << "source" << Cpos << std::endl;
	alSourcefv(helloSource, AL_POSITION, SourcePos);
	if (iPTf == 1)
	{
		fulcrumPoint = OmniCursor->getPosition();
	}
	Force = Omni->getForce();
}*/
/*
void Button2Up1(unsigned int ShapeID)
{
	iV = 0;
	alSourceStop(helloSource);

}
void Button2Down1(unsigned int ShapeID)
{
	iV = 1;
	alSourcePlay(helloSource);
}*/

/*void HLCALLBACK computeForceCB(HDdouble force[3], HLcache *cache, void * userData)
{
	if (iPTf == 1)
	{
		iPTf = 0;
		hlCacheGetDoublev(cache, HL_PROXY_POSITION, fulcrumPoint);
		
	}
	if (iPTB == 1) //fulcrum effect for kidneys
	{

		hlCacheGetDoublev(cache, HL_PROXY_POSITION, pos);
		hlCacheGetDoublev(cache, HL_PROXY_ROTATION, ori);

		unitVector = ori.conjugate() * unitVector * ori;
		p0 = fulcrumPoint;
		p1 = fulcrumPoint + unitVector.v();

		hduLine <float> line(p0, p1);
		newPos = line.project(pos);

		forceF = (newPos - pos) * gain;
		length = forceF.magnitude();
		if (length > maxForce)
		{
			forceF.normalize();
			forceF *= maxForce;
		}

		if (forceLength > nominalMaxForce * 0.5)
		{
			newForce.normalize();
			newForce *= nominalMaxForce * 0.5;
		}
		hdGetDoublev(HD_CURRENT_FORCE, accumForce);
		hdGetDoublev(HD_NOMINAL_MAX_FORCE, &nominalMaxForce);
		forceLength = newForce.magnitude();
	}

	if (iPTS == 1) //line effect for bone
	{
		hlCacheGetDoublev(cache, HL_PROXY_POSITION, pos);
		hlCacheGetDoublev(cache, HL_PROXY_ROTATION, ori);

		unitVector = ori.conjugate() * unitVector * ori;
		p0 = fulcrumPoint;
		p1 = fulcrumPoint + unitVector.v();

		hduLine <float> line(p0, p1);
		newPos = line.direction();

		forceL = (newPos - pos) * gain;
		//forceL = (newPos) * gain;
		length = forceL.magnitude();
		if (length > maxForce)
		{
			forceL.normalize();
			forceL *= maxForce;
		}

		hdGetDoublev(HD_CURRENT_FORCE, accumForce);
		hdGetDoublev(HD_NOMINAL_MAX_FORCE, &nominalMaxForce);
		forceLength = newForce.magnitude();
		if (forceLength > nominalMaxForce * 0.5)
		{
			newForce.normalize();
			newForce *= nominalMaxForce * 0.5;
		}
	}

	if (iV == 1) {
		if (((count % 16) >= 0 && (count % 16) < 4) || ((count % 16) >= 8 && (count % 8) < 12))
			vibrForce = hduVector3Dd(0, 0, 0);
		else if ((count % 16) >= 4 && (count % 16) < 8)
			vibrForce = hduVector3Dd(0, 0, 1);
		else
			vibrForce = hduVector3Dd(0, 0, -1);
		count++;
	}

	if (iV == 0)
	{
		vibrForce = hduVector3Dd(0, 0, 0);
	}

	if (count >= 1024) {
		count = 0;
		iV = 0;
	}

	if (iPTB == 0)
	{
		accumForce = hduVector3Dd(0, 0, 0);
		forceF = hduVector3Dd(0, 0, 0);
	}

	if (iPTS == 0)
	{
		forceL = hduVector3Dd(0, 0, 0);
		accumForce = hduVector3Dd(0, 0, 0);
	}

	std::cout << "New Force" << newForce << std::endl;
	newForce = forceF + accumForce + vibrForce + forceL;
	hdSetDoublev(HD_CURRENT_FORCE, newForce);
} */
/*
void HLCALLBACK startEffectCB(HLcache* cache, void* userData)
{
	printf("a");
}
void HLCALLBACK stopEffectCB(HLcache* cache, void* userData)
{
	printf("a");
}*/

void ChangeCursor(int changeCursor) {
		
	HandCursor->setVisibility(false, false);
	ScalpelCursor->setVisibility(false, false);
	DrillCursor->setVisibility(false, false);
	HammerCursor->setVisibility(false, false);

	if (changeCursor == 0)
		HandCursor->setVisibility(true, true);

	else if (changeCursor == 1)
		ScalpelCursor->setVisibility(true, true); 
	
	else if (changeCursor == 2)
		DrillCursor->setVisibility(true, true);
	
	else if (changeCursor == 3)
		HammerCursor->setVisibility(true, true);
}

