#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <datetimeapi.h>

class DrawScene
{
public:
	void Draw_OuterWall(GLuint texture, BOOL isDisplay);

//	void Draw_InnerRoom_1(GLuint);
//
//	void Draw_InnerRoom_2(GLuint, GLuint);
//
//	void Draw_InnerRoom_3(GLuint, GLuint);
//
//	void Draw_InnerRoom_4(GLuint, GLuint);
//
//	void Draw_InnerRoom_5(GLuint, GLuint);

	void Draw_Floor(GLuint texture, float f);

//	void Draw_WoodBoxes(GLuint);
//
//	void Display_Text(GLuint);


};

