#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Define your room settings state variables
struct RoomSettings {
    static inline bool allowTrails = true;
    static inline bool isPrivate = false;
};

class RoomSettingsPopup : public Popup<std::string const&> {
protected:
    CCMenuItemToggler* m_trailToggle = nullptr;
    CCMenuItemToggler* m_privateToggle = nullptr;

    bool setup(std::string const& roomId) override {
        this->setTitle("Room Settings");

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        m_mainLayer->addChild(menu);

        // 1. Room ID Label
        auto idLabel = CCLabelBMFont::create(("Room ID: " + roomId).c_str(), "bigFont.fnt");
        idLabel->setPosition({m_size.width / 2, m_size.height - 60});
        idLabel->setScale(0.5f);
        m_mainLayer->addChild(idLabel);

        // 2. "Allow Trails" Checkbox Row
        auto trailLabel = CCLabelBMFont::create("Allow Player Trails", "bigFont.fnt");
        trailLabel->setPosition({m_size.width / 2 - 40, m_size.height / 2 + 10});
        trailLabel->setScale(0.4f);
        m_mainLayer->addChild(trailLabel);

        m_trailToggle = CCMenuItemToggler::createWithStandardSprites(
            this, menu_selector(RoomSettingsPopup::onToggleTrail), 0.6f
        );
        m_trailToggle->setPosition({m_size.width / 2 + 80, m_size.height / 2 + 10});
        m_trailToggle->toggle(RoomSettings::allowTrails); // Set initial state
        menu->addChild(m_trailToggle);

        // 3. "Private Match" Checkbox Row
        auto privateLabel = CCLabelBMFont::create("Private Lobby", "bigFont.fnt");
        privateLabel->setPosition({m_size.width / 2 - 40, m_size.height / 2 - 30});
        privateLabel->setScale(0.4f);
        m_mainLayer->addChild(privateLabel);

        m_privateToggle = CCMenuItemToggler::createWithStandardSprites(
            this, menu_selector(RoomSettingsPopup::onTogglePrivate), 0.6f
        );
        m_privateToggle->setPosition({m_size.width / 2 + 80, m_size.height / 2 - 30});
        m_privateToggle->toggle(RoomSettings::isPrivate);
        menu->addChild(m_privateToggle);

        // 4. Save/Confirm Button
        auto saveBtnSprite = ButtonSprite::create("Apply", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        auto saveBtn = CCMenuItemSpriteExtra::create(
            saveBtnSprite, this, menu_selector(RoomSettingsPopup::onApply)
        );
        saveBtn->setPosition({m_size.width / 2, 40});
        menu->addChild(saveBtn);

        return true;
    }

    void onToggleTrail(CCObject* sender) {
        RoomSettings::allowTrails = !m_trailToggle->isOn();
    }

    void onTogglePrivate(CCObject* sender) {
        RoomSettings::isPrivate = !m_privateToggle->isOn();
    }

    void onApply(CCObject* sender) {
        // Send updated configurations to your backend network stack
        // NetworkManager::shared()->sendSettings(RoomSettings::allowTrails, RoomSettings::isPrivate);

        FLAlertLayer::create("Success", "Settings applied successfully!", "OK")->show();
        this->onClose(sender); // Closes the popup
    }

public:
    static RoomSettingsPopup* create(std::string const& roomId) {
        auto ret = new RoomSettingsPopup();
        // Sets popup modal box dimensions (width, height)
        if (ret && ret->initAnchored(320.f, 220.f, roomId)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};
