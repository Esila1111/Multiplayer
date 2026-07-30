void MyLevelInfoLayer::onCreateRoom(CCObject* sender) {
    FLAlertLayer::create("Multiplayer", "Creating room on server...", "OK")->show();
    
    // Example Network Call:
    // NetworkManager::shared()->sendPacket(PacketType::CreateRoom);
}
