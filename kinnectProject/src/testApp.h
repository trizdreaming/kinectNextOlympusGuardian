#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "KinectController.h"
#include "enumSet.h"
#include "Box.h"

class testApp : public ofBaseApp{

public:
    
	void setup(); 
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

private:
    SCENE_NAME m_NowScene;
    //void handEvent(ofxOpenNIHandEvent & event);
    ofTrueTypeFont m_Anarchy;
	ofTrueTypeFont m_Tetris;

	string m_MainTitle;
	string m_SubTitle;
	string m_Start;

	Box m_StartBox;
	Box m_LeftHandBox;
	Box m_RightHandBox;

	ofSoundPlayer m_Sound;

	ofTexture m_Moon;
	ofTexture m_Duk;

	Box m_test0;
	Box m_test1;

	int m_Alpha;
	int m_Tick;
};


#endif
