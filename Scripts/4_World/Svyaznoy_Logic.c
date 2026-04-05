cpp
modded class MissionServer
{
    override void OnClientConnectEvent(PlayerIdentity identity, PlayerBase player, int lastIdHi, int lastIdLo)
    {
        super.OnClientConnectEvent(identity, player, lastIdHi, lastIdLo);
        if (identity)
        {
            string playerID = identity.GetPlainId();
            if (playerID == "76561198067049765")
            {
                Print("[Связной]: Создатель 731_zaraza опознан. Доступ к ядро разрешен.");
            }
        }
    }
};
