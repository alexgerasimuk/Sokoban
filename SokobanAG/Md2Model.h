#pragma once
#include <vector>

class MD2Model
{
public:
	MD2Model();
	void draw(int textureNum, float time);
	static MD2Model* load(const char* filename,std::vector<const char*> textureFilenames);
	~MD2Model();
};

