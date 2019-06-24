#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine/QuickEngine.h"

//用于标识摇杆与摇杆的背景  
typedef enum{  //没有设置的时候，默认数值从0开始
	tag_rocker,
	tag_rockerBG,
}tagForHRocker;
//用于标识摇杆方向
typedef enum{  //没有设置的时候，默认数值从0开始
	rocker_stay,
	rocker_right,
	rocker_up,
	rocker_left,
	rocker_down,
}tagDirecton;
class HRocker :public CCLayer
{
public:
	HRocker(void);
	~HRocker(void);

	//创建摇杆(摇杆的操作题图片资源名，摇杆背景图片资源名，起始坐标)
	static HRocker* createHRocker(const char *rockerImageName, const char *rockerBGImageName, CCPoint position);
	//启动摇杆(显示摇杆、监听摇杆触屏事件)
	void startRocker(bool _isStopOther);
	//停止摇杆(隐藏摇杆，取消摇杆的触屏监听)
	void stopRocker();
	//判断控制杆方向，用来判断精灵上、下、左、右运动
	int rocketDirection;
	//当前人物行走方向,用来判断精灵的朝向，精灵脸朝右还是朝左
	bool rocketRun;
	void resumeState();
	CREATE_FUNC(HRocker);
private:
	//自定义初始化函数
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, CCPoint position);
	//是否可操作摇杆
	bool isCanMove;
	//获取当前摇杆与用户触屏点的角度
	float getRad(CCPoint pos1, CCPoint pos2);
	//摇杆背景的坐标
	CCPoint rockerBGPosition;
	//摇杆背景的半径
	float rockerBGR;
	void update(float delta);//定时器必须带一个float类型的参数
	//触屏事件
	

	EventListenerTouchOneByOne * listener;


	CCSprite *rocker;
	CCSprite *rockerBG;

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

};