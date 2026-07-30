#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        // 1. Create a container menu for our multiplayer buttons
        auto menu = CCMenu::create();
        menu->setPosition({0, 0}); // Absolute positioning anchor
        this->addChild(menu);

        // 2. Create the "Create Room" Button
        auto createBtnSprite = ButtonSprite::create("Create", "goldFont.fnt", "GJ_button_01.png", 0.8f);
        auto createBtn = CCMenuItemSpriteExtra::create(
            createBtnSprite, this, menu_selector(MyLevelInfoLayer::onCreateRoom)
        );
        createBtn->setPosition({60, 120});
        menu->addChild(createBtn);

        // 3. Create the "Join Room" Button
        auto joinBtnSprite = ButtonSprite::create("Join", "goldFont.fnt", "GJ_button_02.png", 0.8f);
        auto joinBtn = CCMenuItemSpriteExtra::create(
            joinBtnSprite, this, menu_selector(MyLevelInfoLayer::onJoinRoom)
        );
        joinBtn->setPosition({60, 80});
        menu->addChild(joinBtn);

        // 4. Create the "Leave Room" Button
        auto leaveBtnSprite = ButtonSprite::create("Leave", "bigFont.fnt", "GJ_button_06.png", 0.8f);
        auto leaveBtn = CCMenuItemSpriteExtra::create(
            leaveBtnSprite, this, menu_selector(MyLevelInfoLayer::onLeaveRoom)
        );
        leaveBtn->setPosition({60, 40});
        menu->addChild(leaveBtn);

        return true;
    }

    // Button Callback functions (defined below)
    void onCreateRoom(CCObject* sender);
    void onJoinRoom(CCObject* sender);
    void onLeaveRoom(CCObject* sender);
};
