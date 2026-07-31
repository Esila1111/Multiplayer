void onReceivedPosition(PlayerNetworkPacket packet) {
    // Find the player object instance in your active session map memory
    PlayerGhost* ghost = MultiplayerSession::getGhostByID(packet.playerID);
    if (ghost) {
        ghost->updatePosition(packet.posX, packet.posY, packet.isWave);
    }
}
