#include <string>
#include <vector>
#include <unordered_map>

struct RoomInfo {
    std::string roomCode;
    std::string hostName;
    int currentPlayers;
    int maxPlayers;
};

// Global list of rooms running on your server
std::unordered_map<std::string, RoomInfo> globalRoomList;

// Function called on the server when a client clicks "Refresh Room List"
std::vector<RoomInfo> getPublicRooms() {
    std::vector<RoomInfo> publicList;
    for (auto const& [code, info] : globalRoomList) {
        // Only return rooms that aren't full
        if (info.currentPlayers < info.maxPlayers) {
            publicList.push_back(info);
        }
    }
    return publicList; // Server converts this to JSON or a binary packet to send to Geode
}
