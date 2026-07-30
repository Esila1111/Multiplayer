#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include "MultiplayerManager.hpp" // Include your state tracker

using namespace geode::prelude;

class $modify(MyLevelLayer, LevelInfoLayer) {
    // Structure to hold pointer references to our UI buttons
    struct Fields {
        CCMenuItemSpriteExtra* m_joinBtn = nullptr;
        CCMenuItemSpriteExtra* m_createBtn = nullptr;
        CCMenuItemSpriteExtra* m_leaveBtn = nullptr;
    };

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        // Create container menu
        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        this->addChild(menu);

        // 1. Create Button
        auto createBtnSprite = ButtonSprite::create("Create", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        m_fields->m_createBtn = CCMenuItemSpriteExtra::create(
            createBtnSprite, this, menu_selector(MyLevelLayer::onCreatePressed)
        );
        m_fields->m_createBtn->setPosition({60, 110});
        menu->addChild(m_fields->m_createBtn);

        // 2. Join Button
        auto joinBtnSprite = ButtonSprite::create("Join", "goldFont.fnt", "GJ_button_02.png", 0.7f);
        m_fields->m_joinBtn = CCMenuItemSpriteExtra::create(
            joinBtnSprite, this, menu_selector(MyLevelLayer::onJoinPressed)
        );
        m_fields->m_joinBtn->setPosition({60, 75});
        menu->addChild(m_fields->m_joinBtn);

        // 3. Leave Button (Uses red cancel sprite layout)
        auto leaveBtnSprite = ButtonSprite::create("Leave", "bigFont.fnt", "GJ_button_06.png", 0.7f);
        m_fields->m_leaveBtn = CCMenuItemSpriteExtra::create(
            leaveBtnSprite, this, menu_selector(MyLevelLayer::onLeavePressed)
        );
        m_fields->m_leaveBtn->setPosition({60, 75}); // Placed over the Join button slot
        menu->addChild(m_fields->m_leaveBtn);

        // Refresh visibility layout based on initial state
        updateButtonVisibility();

        return true;
    }

    // Helper function to swap visibility based on connection state
    void updateButtonVisibility() {
        bool connected = MultiplayerManager::isInRoom;

        // If in a room: hide Create/Join, show Leave
        m_fields->m_createBtn->setVisible(!connected);
        m_fields->m_joinBtn->setVisible(!connected);
        m_fields->m_leaveBtn->setVisible(connected);
    }

    // Callback implementations
    void onCreatePressed(CCObject* sender) {
        MultiplayerManager::isInRoom = true; // Simulating server room creation success
        FLAlertLayer::create("Room Created", "You hosted a new session!", "OK")->show();
        updateButtonVisibility(); 
    }

    void onJoinPressed(CCObject* sender) {
        // Prompt user for Room ID code
        geode::InputPrompt::create("Join Lobby", "Enter Room ID", [this](std::string val) {
            if(val.empty()) return;
            
            MultiplayerManager::isInRoom = true;
            MultiplayerManager::currentRoomId = val;
            
            FLAlertLayer::create("Joined!", ("Connected to: " + val).c_str(), "OK")->show();
            updateButtonVisibility();
        })->show();
    }

    void onLeavePressed(CCObject* sender) {
        MultiplayerManager::isInRoom = false;
        MultiplayerManager::currentRoomId = "";
        
        FLAlertLayer::create("Disconnected", "Left the room safety.", "OK")->show();
        updateButtonVisibility();
    }
};
