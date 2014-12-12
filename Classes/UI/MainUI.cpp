//
//  MainUI.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-11.
//
//

#include "MainUI.h"
#include "MainScene.h"
#include "UIMgr.h"
#include "SceneFactory.h"
#include "TerrainMgr.h"
#include "SpeedSlider.h"
#include "ControlPanel.h"
USING_NS_CC;

// 构造函数
MainUI::MainUI(BaseScene* owner)
:ui::Layout()
{
    m_pOwnerScene = owner;
    m_pLabelMode = nullptr;
    m_pPanel1 = nullptr;
    m_pLabelLifeNum = nullptr;
    m_pLabeGenerationNum = nullptr;
    m_pStartBtn = nullptr;
    m_pResetBtn = nullptr;
    m_pControlPanel = nullptr;
    m_pBackBtn = nullptr;
}
// 析构函数
MainUI::~MainUI()
{
}
// 加载文件
void MainUI::loadUI(const std::string& file)
{
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelMode = Label::createWithTTF("自由模式", "FZXS12.TTF", 120);
    m_pLabelMode->setPosition(Vec2(750,590));
    m_pLabelMode->setColor(color);
    m_pLabelMode->setScale(0.5f);
    this->addChild(m_pLabelMode);
    
    m_pPanel1 = Sprite::create("panel1.png");
    m_pPanel1->setPosition(Vec2(750,400));
    m_pPanel1->setColor(color);
    this->addChild(m_pPanel1);
   
    int lifeNum = TerrainMgr::getInstance()->getLifeNum();
    int generationNum = TerrainMgr::getInstance()->getGeneration();
    std::string strLifeNum = "生命个数: ";
    strLifeNum += Value(lifeNum).asString();
    std::string strGenerationNum = "生命代数: ";
    strGenerationNum += Value(generationNum).asString();
    
    m_pLabelLifeNum = Label::createWithTTF(strLifeNum, "FZXS12.TTF", 24);
    m_pLabelLifeNum->setPosition(Vec2(750,480));
    m_pLabelLifeNum->setColor(color);
    this->addChild(m_pLabelLifeNum);
    
    m_pLabeGenerationNum = Label::createWithTTF(strGenerationNum, "FZXS12.TTF", 24);
    m_pLabeGenerationNum->setPosition(Vec2(750,380));
    m_pLabeGenerationNum->setColor(color);
    this->addChild(m_pLabeGenerationNum);
    
    m_pStartBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pStartBtn->setPosition(Vec2(680,300));
    m_pStartBtn->addTouchEventListener(CC_CALLBACK_2(MainUI::pressStartBtn, this));
    m_pStartBtn->setTitleFontName("FZXS12.TTF");
    m_pStartBtn->setTitleColor(color);
    m_pStartBtn->setTitleFontSize(24);
    m_pStartBtn->setTitleText("开始");
    m_pStartBtn->setColor(color);
    m_pStartBtn->setScale(0.6f);
    this->addChild(m_pStartBtn);
    
    m_pResetBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pResetBtn->setPosition(Vec2(820,300));
    m_pResetBtn->addTouchEventListener(CC_CALLBACK_2(MainUI::pressResetBtn, this));
    m_pResetBtn->setTitleFontName("FZXS12.TTF");
    m_pResetBtn->setTitleColor(color);
    m_pResetBtn->setTitleFontSize(24);
    m_pResetBtn->setTitleText("重置");
    m_pResetBtn->setColor(color);
    m_pResetBtn->setScale(0.6f);
    this->addChild(m_pResetBtn);
    
    m_pControlPanel = ControlPanel::create();
    m_pControlPanel->loadUI("");
    m_pControlPanel->setColor(color);
    m_pControlPanel->setPosition(Vec2(750,175));
    this->addChild(m_pControlPanel);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(MainUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName("FZXS12.TTF");
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText("返回");
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
}
// 更新处理
void MainUI::update(float delta)
{
    ui::Layout::update(delta);
    
    int lifeNum = TerrainMgr::getInstance()->getLifeNum();
    int generationNum = TerrainMgr::getInstance()->getGeneration();
    std::string strLifeNum = "生命个数: ";
    strLifeNum += Value(lifeNum).asString();
    std::string strGenerationNum = "生命代数: ";
    strGenerationNum += Value(generationNum).asString();
    
    m_pLabelLifeNum->setString(strLifeNum);
    m_pLabeGenerationNum->setString(strGenerationNum);
}
//设置UI颜色
void MainUI::setColor(const cocos2d::Color3B& color)
{
    m_pLabelMode->setColor(color);
    m_pPanel1->setColor(color);
    m_pLabelLifeNum->setColor(color);
    m_pLabeGenerationNum->setColor(color);
    m_pStartBtn->setTitleColor(color);
    m_pStartBtn->setColor(color);
    m_pResetBtn->setTitleColor(color);
    m_pResetBtn->setColor(color);
    m_pControlPanel->setColor(color);
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setColor(color);
}
// 点击开始按钮
void MainUI::pressStartBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        auto scene = static_cast<MainScene*>(m_pOwnerScene);
        if(scene)
        {
            bool pause = scene->IsPaused();
            scene->setPause(!pause);
            if(pause)
                m_pStartBtn->setTitleText("暂停");
            else
                m_pStartBtn->setTitleText("开始");
        }
    }
}
// 点击重置按钮
void MainUI::pressResetBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        auto scene = static_cast<MainScene*>(m_pOwnerScene);
        if(scene)
        {
            bool pause = scene->IsPaused();
            if(!pause)
            {
                scene->setPause(true);
                m_pStartBtn->setTitleText("开始");
            }
        }
        TerrainMgr::getInstance()->resetTerrain();
    }
}
// 点击返回按钮
void MainUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}