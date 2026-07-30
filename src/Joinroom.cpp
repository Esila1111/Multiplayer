void MyLevelInfoLayer::onJoinRoom(CCObject* sender) {
    // Open a text input prompt for the Room ID
    geode::createQuickPopup(
        "Join Room",
        "Enter the **Room ID** you want to join:",
        "Cancel", "Join",
        [this](auto, bool confirmed) {
            // This lambda function fires when the user clicks 'Join' or 'Cancel'
            if (confirmed) {
                // To get the text input, a custom alert or Geode's InputPrompt is best.
                // Here is the streamlined Geode InputPrompt way:
                InputPrompt::create("Join Room", "Room ID", [this](std::string value) {
                    FLAlertLayer::create("Multiplayer", ("Joining room: " + value).c_str(), "OK")->show();
                    
                    // Example Network Call:
                    // NetworkManager::shared()->sendPacket(PacketType::JoinRoom, value);
                })->show();
            }
        }
    );
}
