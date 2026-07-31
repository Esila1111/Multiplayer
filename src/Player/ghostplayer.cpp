#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class PlayerGhost : public CCNode {
public:
    CCMotionStreak* m_regularTrail = nullptr;
    CCParticleSystemQuad* m_waveTrail = nullptr;
    bool m_isWave = false;

    static PlayerGhost* create() {
        auto ret = new PlayerGhost();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() override {
        if (!CCNode::init()) return false;

        // 1. Initialize Regular Player Trail (Ribbon effect)
        // Parameters: fadeTime (0.5s), minSeg (1.0f), strokeWidth (8.0f), color, texture path
        m_regularTrail = CCMotionStreak::create(0.5f, 1.0f, 8.0f, ccWHITE, "square02_001.png");
        this->addChild(m_regularTrail);

        // 2. Initialize Wave Trail (Particle burst effect)
        // In Geometry Dash, wave trails are traditionally hardcoded lines, but custom 
        // particles provide an excellent, easily customizable multiplayer alternative.
        m_waveTrail = CCParticleSystemQuad::create("streakEffect.plist");
        m_waveTrail->setPositionType(kCCPositionTypeFree); // Retains particles in world coordinate space
        m_waveTrail->stopSystem(); // Start dormant
        this->addChild(m_waveTrail);

        return true;
    }

    // Call this whenever you parse incoming network packets for this player
    void updatePosition(float x, float y, bool isWaveMode) {
        this->setPosition({x, y});
        m_isWave = isWaveMode;

        if (!m_isWave) {
            // Normal Form: Enable regular trail, kill particle emissions
            m_regularTrail->setVisible(true);
            m_regularTrail->setPosition({x, y});
            
            m_waveTrail->stopSystem();
            m_waveTrail->setVisible(false);
        } else {
            // Wave Form: Wipe normal trail visibility, spark particles
            m_regularTrail->setVisible(false);
            m_regularTrail->reset(); // Clears residual streak segments instantly

            m_waveTrail->setVisible(true);
            m_waveTrail->resumeSystem();
            m_waveTrail->setPosition({x, y});
        }
    }
};
