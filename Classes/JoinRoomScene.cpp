﻿#pragma execution_character_set("utf-8")

#include "JoinRoomScene.h"

EditBox* JoinRoomScene::_nameBox, * JoinRoomScene::_passwordBox;
RadioButtonGroup* JoinRoomScene::_radioButtonGroup;

QE_SINGLETON2_CPP(JoinRoomScene);

QE_CreateSceneFromLayer_CPP(JoinRoomScene);
paths = { "fonts" };
QE_SetResourcesSearchDir;

_instance = this;

Connect::connect(Connect::Event::GetRooms);

initLabel();
initMenu();
initEditBox();
initRadioButton();
return true;
}

void JoinRoomScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	//if (statusCode == 381)
	//{
	//	getInstance()->scheduleOnce(schedule_selector(JoinRoomScene::enterSignInScene), 3.0f);
	//}
}

void JoinRoomScene::enterSignInScene(float f) { QE_ReplaceScene(SignInScene); }

void JoinRoomScene::initLabel()
{
	createLabel("加入房间");
	_label->setPosition(420, 460);
	createLabel("宝宝");
	_label->setPosition(380, 300);
	createLabel("坏人");
	_label->setPosition(460, 300);
	createLabel("裁判");
	_label->setPosition(540, 300);

	_logLabel = createLabel("");
	_logLabel->setPosition(150, 100);
	if (Connect::_ws) { dealServerResponse(311); }
	else { dealServerResponse(310); }
}

void JoinRoomScene::initMenu()
{
	QE_CreateLabelMenu(420, 200, "确认创建", JoinRoomScene, createRoom);
	QE_CreateLabelMenuAgain(10, 500, "返回", JoinRoomScene, back);
}

void JoinRoomScene::createRoom()
{

}

void JoinRoomScene::joinRoom()
{

}

void JoinRoomScene::back() { QE_ReplaceScene(SignInScene); };

void JoinRoomScene::initEditBox()
{
	//输入用户名的框
	_nameBox = _box = createEditBox("orange_edit.png");
	_box->setPosition(Vec2(370, 400));
	_box->setPlaceHolder("房间名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	//输入密码的框
	_passwordBox = _box = createEditBox("green_edit.png");
	_box->setPosition(Vec2(370, 350));
	_box->setPlaceHolder("房间密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}

void JoinRoomScene::initRadioButton()
{
	_radioButtonGroup = RadioButtonGroup::create();
	addChild(_radioButtonGroup);

	for (int i = 0; i < 3; ++i)
	{
		RadioButton* radioButton = RadioButton::create("icon/btn_radio_off_holo.png", "icon/btn_radio_on_holo.png");
		float posX = 400 + 80 * i;
		radioButton->setPosition(Vec2(posX, 270));
		_radioButtonGroup->addRadioButton(radioButton);
		_radioButtonGroup->addEventListener(CC_CALLBACK_3(JoinRoomScene::onChangedRadioButtonGroup, this));

		addChild(radioButton);
	}
}

void JoinRoomScene::onChangedRadioButtonGroup(RadioButton* radioButton, int index, RadioButtonGroup::EventType type)
{
	CCLOG("RadioButton Index : %d", index);
}