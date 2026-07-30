#include <Geode/Geode.hpp>
#include <Geode/binding/FLAlertLayer.hpp>

using namespace geode::prelude;

class RoomListCell : public CCNode {
public:
    std::string m_roomCode;

    static RoomListCell* create(std::string code, std::string host, int players, int maxPlayers) {
        auto ret = new RoomListCell();
        if (ret && ret->init(code, host, players, maxPlayers)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init(std::string code, std::string host, int players, int maxPlayers) {
        m_roomCode = code;
        
        // Define cell size background
        auto bg = CCScale9Sprite::create("square02_001.png");
        bg->setContentSize(ccp(340, 40));
        this->addChild(bg);

        // Room details label text
        std::string labelText = fmt::format("{}'s Room ({}/{})", host, players, maxPlayers);
        auto label = CCLabelBMFont::create(labelText.c_str(), "bigFont.fnt");
        label->setScale(0.4f);
        label->setPosition(ccp(10, 20));
        label->setAnchorPoint(ccp(0, 0.5f));
        this->addChild(label);

        // Join button layout
        auto menu = CCMenu::create();
        menu->setPosition(ccp(300, 20));
        this->addChild(menu);

        auto joinBtnSprite = ButtonSprite::create("Join", "goldButton_001.png");
        joinBtnSprite->setScale(0.6f);
        auto joinBtn = CCMenuItemSpriteExtra::create(
            joinBtnSprite, this, menu_selector(RoomListCell::onJoin)
        );
        menu->addChild(joinBtn);

        return true;
    }

    void onJoin(CCObject*) {
        // Network implementation: Tell server this client is entering m_roomCode
        // MyNetworkClient::get().sendJoinRoomPacket(m_roomCode);
        FLAlertLayer::create("Lobby", "Joining room network thread...", "OK")->show();
    }
};
