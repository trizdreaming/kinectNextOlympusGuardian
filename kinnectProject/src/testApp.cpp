#include "testApp.h"
#include "KinectController.h"

#define  DEFAULT_POSITION ofPoint(100,0);

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);
	m_NowScene = SCENE_INTRO;
	//m_NowScene = SCENE_PLAY;
	KinectController::getInstance()->InitKinect();
    
	m_MainTitle = "NEXT Olympus Guardian\n";
	m_SubTitle = "Defend the Falling Gods !";
	m_Start = "Start Button\nHands here!";

    m_Anarchy.loadFont(ofToDataPath("anarchy.ttf"), 30);
	m_Tetris.loadFont(ofToDataPath("tetris_m.ttf"), 30);
	ofBackground(0,0,0);

	m_Alpha = 255;

	m_Sound.loadSound("starLight.mp3");
	m_Sound.play();

	m_StartBox.set(220,150,200,100);

	m_RightHandBox.setWidth(30);
	m_RightHandBox.setHeight(30);
	m_LeftHandBox.setWidth(30);
	m_LeftHandBox.setHeight(30);

	ofImage moon;
	moon.loadImage("moon.png");
	m_Moon.allocate(256,256, GL_RGB, true);
	m_Moon.loadData(moon.getPixels(),256,256,GL_RGB);

	ofImage duk;
	duk.loadImage("duk.png");
	m_Duk.allocate(256,256, GL_RGB, true);
	m_Duk.loadData(duk.getPixels(), 256, 256, GL_RGB);


	m_test0.setWidth(50);
	m_test0.setHeight(50);
	m_test0.setPosition(150,-100);

	m_test1.setWidth(50);
	m_test1.setHeight(50);
	m_test1.setPosition(350,-30);

}

bool BoxCollision(Box box1, Box box2)
{
	if(box1.getMinX() <= box2.getMaxX() && box1.getMaxX() >= box2.getMinX() &&
		box1.getMinY() <= box2.getMaxY() && box1.getMaxY() >= box2.getMinY())
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------
void testApp::update(){

	KinectController::getInstance()->Update();

	if(m_NowScene == SCENE_PLAY)
	{
		float now0YPosition = m_test0.getPosition().y;
		float next0YPosition = now0YPosition + 1;
		m_test0.setPosition(150,next0YPosition);

		if (BoxCollision(m_test0, m_LeftHandBox)||BoxCollision(m_test0,m_RightHandBox))
		{
			float next0YPosition = now0YPosition - 2;
			float nowScale = m_test0.getWidth();
			float nextScale = nowScale + 0.2;

			m_test0.setWidth(nextScale);
			m_test0.setHeight(nextScale);
			m_test0.setPosition(150,next0YPosition);
		}


		float nowYPosition = m_test1.getPosition().y;
		float nextYPosition = nowYPosition + 1;
		m_test1.setPosition(350,nextYPosition);

		if (BoxCollision(m_test1, m_LeftHandBox)||BoxCollision(m_test1,m_RightHandBox))
		{
			float nextYPosition = nowYPosition - 2;
			float nowScale = m_test0.getWidth();
			float nextScale = nowScale + 0.2;

			m_test1.setWidth(nextScale);
			m_test1.setHeight(nextScale);
			m_test1.setPosition(350,nextYPosition);
		}
// 
// 		if (BoxCollision(m_test1, m_test0))
// 		{
// 			float now0XPosition = m_test0.getPosition().x;
// 			float now1XPosition = m_test1.getPosition().y;
// 			float nextXPosition0 = now0XPosition -5;
// 			float nextXPosition1 = now1XPosition +5;
// 			m_test0.setPosition(nextXPosition0, now0YPosition);
// 			m_test1.setPosition(nextXPosition1, nowYPosition);
// 		}
	}
	

}

//--------------------------------------------------------------
void testApp::draw(){
	int windowWidth = 640;
	int windowHeight = 480;
	
	int textureFlag = 0;

	switch (m_NowScene)
	{
	case SCENE_NONE:
		break;
	case SCENE_INTRO:

		ofSetColor(0,0,0, m_Alpha);
		ofRect(0,0,windowWidth,windowHeight);

		ofSetColor(255, 255, 255, m_Alpha);
		m_Anarchy.drawString(m_MainTitle,windowWidth/8 ,windowHeight/6 );

		ofSetColor(250,183,45,m_Alpha);
		m_Tetris.drawString(m_SubTitle,175,360);

		m_StartBox.Draw();
		m_Tetris.drawString(m_Start, 230,200);

		ofPushMatrix();
		KinectController::getInstance()->RenderSkeleton();
		m_LeftHandBox.setPosition(KinectController::getInstance()->getLeftHandPoint());
		m_RightHandBox.setPosition(KinectController::getInstance()->getRightHandPoint());
		m_RightHandBox.Draw();
		m_LeftHandBox.Draw();
		ofPopMatrix();

		if (BoxCollision(m_StartBox, m_LeftHandBox)&&BoxCollision(m_StartBox, m_RightHandBox))
		{
			m_Alpha = m_Alpha - 5;

			if (m_Alpha<0)
			{
				m_NowScene = SCENE_PLAY;
			}
		}
		break;

	case SCENE_PLAY:
		KinectController::getInstance()->DrawImage();
		
		ofPushMatrix();
		KinectController::getInstance()->RenderSkeleton();
		m_LeftHandBox.setPosition(KinectController::getInstance()->getLeftHandPoint());
		m_RightHandBox.setPosition(KinectController::getInstance()->getRightHandPoint());
		m_RightHandBox.Draw();
		m_LeftHandBox.Draw();
		ofPopMatrix();

		ofPushMatrix();
// 		m_test.setPosition(100,100);
 		m_test0.GlDraw(m_Duk);
		m_test1.GlDraw(m_Moon);

		//원랜 두사람 랜덤하게 나오게 하려 했으나...
		//죽을 수도 있을 것 같아서 포기
// 		textureFlag = ofRandom(0.0f, 100.0f);
// 		if (textureFlag%2 == 0)
// 		{
// 			
// 		}
		
		ofPopMatrix();

		break;

	case SCENE_RESULT:
		break;
	case SCENE_MAX:
		break;
	default:
		break;
	}
	
    // draw some info regarding frame counts etc
// 	ofSetColor(0, 255, 0);
// 	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
//     
// 	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
}



//--------------------------------------------------------------
//이건 로그
// void testApp::handEvent(ofxOpenNIHandEvent & event){
//     // show hand event messages in the console
//     ofLogNotice() << getHandStatusAsString(event.handStatus) << "for hand" << event.id << "from device" << event.deviceID;
// }

//--------------------------------------------------------------
void testApp::exit(){
	KinectController::getInstance()->Stop();
	KinectController::getInstance()->Release();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}