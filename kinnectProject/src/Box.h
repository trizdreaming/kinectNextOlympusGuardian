#pragma once
#include "ofRectangle.h"
#include "ofTexture.h"

class Box: public ofRectangle
{
public:
	Box(void);
	virtual~Box(void);
public:
	void SetisVisible(){m_Visibility = true;}
	void SetisNotvisible(){m_Visibility = false;}

	void Draw();
	void GlDraw(ofTexture texture);

private:
	bool m_Visibility;
};

