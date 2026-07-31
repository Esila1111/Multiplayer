#pragma once
#include <Geode/Geode.hpp>

// A simple global or static manager to track your networking state
struct MultiplayerManager {
    static inline bool isInRoom = false; 
    static inline std::string currentRoomId = "";
};
