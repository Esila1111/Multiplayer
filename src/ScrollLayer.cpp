#include <Geode/binding/FLAlertLayer.hpp>

class RoomBrowserLayer : public FLAlertLayer {
    ScrollLayer* m_scrollLayer;
    CCLayer* m_listContainer;

public:
    static RoomBrowserLayer* create() {
        auto ret = new RoomBrowserLayer();
        if (ret && ret->init(400.0f, 280.0f, "GJ_square01.png", "Public Rooms")) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool setup() override {
        // Define bounding zone for the scroll system inside the window frame
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        
        m_scrollLayer = ScrollLayer::create(ccp(350, 180));
        m_scrollLayer->setPosition(ccp(winSize.width / 2 - 175, winSize.height / 2 - 90));
        this->m_mainLayer->addChild(m_scrollLayer);
        
        // Target list layer container holding rows vertically stacked
        m_listContainer = m_scrollLayer->m_contentLayer;

        // Fetch updates from network database
        this->refreshRoomList();
        return true;
    }

    void refreshRoomList() {
        m_listContainer->removeAllChildren();

        // SIMULATION: Imagine your network thread successfully fetched this list array from server:
        std::vector<RoomInfo> fakeServerRooms = {
            {"RM1024", "Player1", 2, 8},
            {"RM5582", "GeometryPro", 5, 8},
            {"RM9911", "NoobSlayer", 1, 4}
        };

        float currentY = 0.0f;
        float cellHeight = 45.0f;

        for (auto const& room : fakeServerRooms) {
            auto cell = RoomListCell::create(room.roomCode, room.hostName, room.currentPlayers, room.maxPlayers);
            cell->setPosition(ccp(0, currentY));
            m_listContainer->addChild(cell);
            
            currentY += cellHeight;
        }

        // Adjust scroll bounding constraints dynamically based on content amount
        m_listContainer->setContentSize(ccp(350, currentY));
        m_scrollLayer->moveToTop();
    }
};
