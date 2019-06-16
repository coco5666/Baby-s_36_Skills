﻿#pragma execution_character_set("utf-8")

#include "NetworkGameScene.h"

RadioButtonGroup* NetworkGameScene::_radioButtonGroup;

QE_SINGLETON2_CPP(NetworkGameScene);

QE_CreateSceneFromLayer_CPP(NetworkGameScene);
paths = { "fonts" };
QE_SetResourcesSearchDir;

_instance = this;

Connect::connect(Connect::Event::GetRooms);

	initLabel();
	initMenu();
	initRadioButton();
	initListView();
	initEditBox();
return true;
}

void NetworkGameScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	//if (statusCode == 381)
	//{
	//	getInstance()->scheduleOnce(schedule_selector(NetworkGameScene::enterSignInScene), 3.0f);
	//}
}

void NetworkGameScene::enterSignInScene(float f) { QE_ReplaceScene(SignInScene); }

void NetworkGameScene::initLabel()
{
	createLabel("宝宝：");
	_label->setPosition(60, 390);
	createLabel("坏人：");
	_label->setPosition(60, 325);
	createLabel("裁判：");
	_label->setPosition(60, 265);

	_logLabel = createLabel("");
	_logLabel->setPosition(150, 20);
	if (Connect::_ws) { dealServerResponse(311); }
	else { dealServerResponse(310); }
}

void NetworkGameScene::initMenu()
{
	QE_CreateLabelMenu(840, 100, "发送", NetworkGameScene, createRoom);
	QE_CreateLabelMenuAgain(10, 500, "返回", NetworkGameScene, back);
}

void NetworkGameScene::createRoom()
{

}

void NetworkGameScene::joinRoom()
{

}

void NetworkGameScene::back() { QE_ReplaceScene(SignInScene); };

void NetworkGameScene::initEditBox()
{
	//输入ID的框
	_box = createEditBox("orange_edit.png");
	_box->setPosition(Vec2(10, 100));
	_box->setSize(Size(820, 38));
	_box->setPlaceHolder("请输入聊天信息");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
}

void NetworkGameScene::initRadioButton()
{
	_radioButtonGroup = RadioButtonGroup::create();
	addChild(_radioButtonGroup);

	for (int i = 0; i < 3; ++i)
	{
		RadioButton* radioButton = RadioButton::create("icon/btn_radio_off_holo.png", "icon/btn_radio_on_holo.png");
		float posY = 250 + 60 * i;
		radioButton->setPosition(Vec2(0, posY));
		radioButton->setAnchorPoint(Vec2(0, 0));
		_radioButtonGroup->addRadioButton(radioButton);
		_radioButtonGroup->addEventListener(CC_CALLBACK_3(NetworkGameScene::onChangedRadioButtonGroup, this));
		addChild(radioButton);
	}
}

void NetworkGameScene::onChangedRadioButtonGroup(RadioButton* radioButton, int index, RadioButtonGroup::EventType type)
{
	CCLOG("RadioButton Index : %d", index);
}

void NetworkGameScene::initListView()
{
	_listView = ListView::create();
	_listView->setDirection(ScrollView::Direction::BOTH);
	_listView->setBounceEnabled(true);//回弹效果
	_listView->setBackGroundImage("green_edit.png");
	_listView->setBackGroundImageScale9Enabled(true);
	_listView->setContentSize(Size(500, 360));
	_listView->setAnchorPoint(Vec2(0, 0));
	_listView->setPosition(Vec2(400, 160));
	addChild(_listView);
	for (int i = 0; i < 10; i++)
	{
		Layout* widget = Layout::create();
		widget->setContentSize(Size(240, 30));

		//创建RichText对象
		RichText* richText = RichText::create();
		//设置是否忽略用户定义的内容大小
		richText->ignoreContentAdaptWithSize(false);
		//设置内容大小
		richText->setContentSize(Size(500, 50));
		richText->setPosition(Vec2(5, 0));
		richText->setAnchorPoint(Vec2(0, 0));

		//创建文本类型的RichElement对象
		RichElementText* re1 = RichElementText::create(1, Color3B::BLUE, 255, "宝宝：", QE_Font, 20);
		RichElementText* re2 = RichElementText::create(2, Color3B::RED, 255, "  你是坏人，不搭理你。", QE_Font, 20);
		//创建图片类型的RichElement对象
		RichElementImage* re3 = RichElementImage::create(3, Color3B::WHITE, 255, "child.png");
		//创建换行RichElement对象
		RichElementNewLine* newLine = RichElementNewLine::create(77, Color3B::WHITE, 255);

		richText->pushBackElement(re1);
		//richText->pushBackElement(newLine);
		richText->pushBackElement(re3);
		richText->pushBackElement(re2);
		//richText->insertElement(newLine, 3);

		widget->addChild(richText);
		_listView->pushBackCustomItem(widget);
	}
}