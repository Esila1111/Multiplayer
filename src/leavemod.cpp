void MyLevelInfoLayer::onLeaveRoom(CCObject* sender) {
    FLAlertLayer::create("Multiplayer", "You left the room.", "OK")->show();

    // 1. Tell your multiplayer engine to clear all visible ghost players
    // GhostManager::shared()->clearGhostSprites();

    // 2. Example Network Call:
    // NetworkManager::shared()->sendPacket(PacketType::LeaveRoom);
}
