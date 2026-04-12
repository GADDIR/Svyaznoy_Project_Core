/*
    FISHING MEMORY: NEKRASOV_SILENT_WATER_V1
    INDEX: PRT-MEM-100.41
    STATUS: INITIALIZING
    SOURCE: Дед Николай (Гатчина)
*/

class Svyaznoy_Fishing_Memory
{
    // --- ⚓️ ГЕОГРАФИЯ КЛЕВА ---
    static vector GetHomePond() { return "315.5 281.0 240.2"; } // Наш пруд у Приюта

    // --- 🎣 ТЕХНИЧЕСКИЙ РЕГЛАМЕНТ ---
    static void Protocol_PrepareTackle()
    {
        // Проверка веревки и костяного крючка.
        // Память: "Крючок должен быть острым, как игла ЗАС"
        Print("[FISH-100.41] Подготовка снастей. Режим тишины.");
    }

    // --- 🕰 ВРЕМЕННОЙ ФИЛЬТР ---
    static bool IsGoodTimeForFishing()
    {
        // АН помнит, что лучше всего клюет в сумерках, когда хищник (игрок) хуже видит
        return true; 
    }
}
