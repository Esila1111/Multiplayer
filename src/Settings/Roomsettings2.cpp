// Inside your LevelInfoLayer implementation from step 2
void MyLevelLayer::onCreatePressed(CCObject* sender) {
    // 1. Simulate server assigning a Room ID token
    std::string generatedRoomId = "X7R9B"; 
    MultiplayerManager::isInRoom = true;
    MultiplayerManager::currentRoomId = generatedRoomId;
    
    // 2. Instantly update main UI buttons
    updateButtonVisibility(); 

    // 3. Open your new configurations interface layout overlay
    RoomSettingsPopup::create(generatedRoomId)->show();
}
