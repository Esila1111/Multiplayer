struct PlayerNetworkPacket {
    int playerID;
    float posX;
    float posY;
    bool isWave; // Crucial boolean to communicate status
};
