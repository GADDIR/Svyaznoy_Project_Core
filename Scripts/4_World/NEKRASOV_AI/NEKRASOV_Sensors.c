class NEKRASOV_Sensors {
    void ScanEnvironment(PlayerBase maverick) {
        // Маверик ищет объекты в радиусе 30 метров
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition(maverick.GetPosition(), 30.0, objects, null);

        foreach(Object obj : objects) {
            // Если он увидел торговца, он не просто знает координаты, 
            // он запоминает: "Здесь кто-то есть"
            if (obj.IsInherited(NPC_Trader_Base)) { 
                UpdateMemory(obj.GetPosition(), "Potential_Trader");
            }
        }
    }
}
