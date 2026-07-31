#include <Geode/Geode.hpp>

using namespace geode::prelude;

void PlayerGhost::updatePosition(float x, float y, bool isWaveMode) {
    this->setPosition({x, y});
    m_isWave = isWaveMode;

    // 1. Fetch live configurations from Geode's settings cache
    bool trailsEnabledGlobally = Mod::get()->getSettingValue<bool>("show-regular-trails");
    bool waveEnabledGlobally = Mod::get()->getSettingValue<bool>("show-wave-trails");

    if (!m_isWave) {
        // --- Normal Form Logic ---
        m_waveTrail->stopSystem();
        m_waveTrail->setVisible(false);

        // Only render the trail if the user settings allow it
        if (trailsEnabledGlobally) {
            m_regularTrail->setVisible(true);
            m_regularTrail->setPosition({x, y});
        } else {
            m_regularTrail->setVisible(false);
            m_regularTrail->reset(); // Wipes existing segments
        }
    } else {
        // --- Wave Form Logic ---
        m_regularTrail->setVisible(false);
        m_regularTrail->reset();

        // Only render the wave path if the user settings allow it
        if (waveEnabledGlobally) {
            m_waveTrail->setVisible(true);
            m_waveTrail->resumeSystem();
            m_waveTrail->setPosition({x, y});
        } else {
            m_waveTrail->stopSystem();
            m_waveTrail->setVisible(false);
        }
    }
}
