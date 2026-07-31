// Inside your PlayLayer hook loop:
void MyPlayLayerUpdate(float dt) {
    // Regular update cycle...
    
    bool trailsEnabledGlobally = Mod::get()->getSettingValue<bool>("show-regular-trails");
    bool waveEnabledGlobally = Mod::get()->getSettingValue<bool>("show-wave-trails");

    if (!trailsEnabledGlobally) {
        // Loop through your ghost player map and clear active regular trails
        for (auto& [id, ghost] : MultiplayerSession::getActiveGhosts()) {
            if (ghost->m_regularTrail) {
                ghost->m_regularTrail->setVisible(false);
                ghost->m_regularTrail->reset();
            }
        }
    }
}
