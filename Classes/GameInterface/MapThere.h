﻿#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class MapThere :public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(MapThere);
	void backTwo();
private:
	Sprite* hero;
	bool HeroDirecton;
};

class HrockerLayer3:public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(HrockerLayer3);

};