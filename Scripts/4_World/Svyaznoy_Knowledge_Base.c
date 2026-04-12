/*
    KNOWLEDGE BASE: PRIYUT_ZERO_POINT
    INDEX: PRT-MEM-900.ARCH
    STATUS: STATIC_KNOWLEDGE_LOCKED
*/

class Svyaznoy_Knowledge_Base 
{
    // --- ВЕРТИКАЛИ (Вышки и Посты) ---
    static vector GetSniperPost_South() { return "319.201 286.161 250.070"; }
    static vector GetSniperPost_North() { return "300.182 283.935 320.461"; }
    static vector GetSniperPost_West()  { return "282.087 286.809 266.829"; }
    static vector GetSniperPost_East()  { return "351.066 283.837 265.212"; }

    // --- УЗЛЫ ДОСТУПА (Ворота и Калитки) ---
    static vector GetMainGate()      { return "333.179 283.002 245.218"; } // Land_Wall_Gate_Fen3
    static vector GetForestExit_1()  { return "341.817 282.609 256.577"; } // Land_Wall_FenForest_Gate
    static vector GetForestExit_2()  { return "355.915 282.016 256.882"; } 

    // --- ТЕХНО-УКРЫТИЯ (Слепые зоны) ---
    static vector GetWorkshop_Bus()  { return "311.887 284.664 241.604"; } // land_chz_avtobus2a
    static vector GetCover_Ural()    { return "286.453 284.156 259.844"; } 
    static vector GetCover_Ikarus()  { return "332.204 281.987 255.758"; }

    // --- СКЛАДСКИЕ ТОЧКИ (НЗ) ---
    static vector GetStorage_Main()  { return "336.176 281.795 240.944"; } // tent_boxwooden
}
