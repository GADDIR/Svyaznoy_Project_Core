/*
    MASTER KNOWLEDGE BASE: NEKRASOV_MEMORY_V4_ULTIMATE
    INDEX: PRT-MEM-GLOBAL_COMPLETE
    STATUS: SYNCHRONIZED [100%]
    DEVELOPER: ШТАБ-В (БРАТ) ПО ДИРЕКТИВЕ 731
*/

class Svyaznoy_Knowledge_Base 
{
    // =========================================================================
    // 🏠 СЕКТОР 900: ПРИЮТ (ДОМАШНИЙ ОПЛОТ)
    // =========================================================================
    static vector GetHome()             { return "319.088 284.230 246.283"; }
    static vector GetMainGate()         { return "333.179 283.002 245.218"; }
    
    // ВЕРТИКАЛИ (Вышки наблюдения)
    static vector GetSniperPost_S()     { return "319.201 286.161 250.070"; }
    static vector GetSniperPost_N()     { return "300.182 283.935 320.461"; }
    static vector GetSniperPost_W()     { return "282.087 286.809 266.829"; }
    static vector GetSniperPost_E()     { return "351.066 283.837 265.212"; }

    // ПУТИ ОТХОДА (Директива 0.1)
    static vector GetExit_Forest_1()    { return "341.817 282.609 256.577"; }
    static vector GetExit_Forest_2()    { return "355.915 282.016 256.882"; }

    // ТЕХНИЧЕСКИЕ УКРЫТИЯ И СКЛАДЫ
    static vector GetWorkshop_Bus()     { return "311.887 284.664 241.604"; }
    static vector GetCover_Ural()       { return "286.453 284.156 259.844"; }
    static vector GetStorage_Main()     { return "336.176 281.795 240.944"; }

    // =========================================================================
    // 💰 ТОРГОВАЯ СЕТЬ (СЕКТОРЫ 600 / 700)
    // =========================================================================
    
    // --- ЦЕНТРАЛЬНЫЙ УЗЕЛ (ПРИЮТ) ---
    static vector GetTrader_Comp_731()     { return "328.958 282.065 263.382"; } // 731 (Компоненты)
    static vector GetTrader_Build_Zaraza() { return "330.241 282.027 261.616"; } // Zaraza (Стройка)
    static vector GetTrader_Med_GostHiba()  { return "320.959 282.324 271.335"; } // Gost_Hiba7 (Мед)
    static vector GetTrader_Weapons_Bizon() { return "291.767 283.637 275.162"; } // Bizon (Оружие)
    static vector GetTrader_Attach_Gabik()  { return "306.347 282.390 289.184"; } // Gabik_82 (Обвесы)
    static vector GetTrader_Food_Quinn()    { return "305.615 283.691 242.364"; } // Quinn (Еда)

    // --- СЕВЕРНЫЙ АВАНПОСТ (ГРАНИЦА) ---
    static vector GetNorth_Maria()     { return "14816.6 672.606 13954.4"; } // Maria (Одежда)
    static vector GetNorth_Quinn()     { return "14806.2 663.951 13919.0"; } // Quinn (Еда)
    static vector GetNorth_Agent_Air() { return "14801.6 688.545 13943.7"; } // AGENT (Авиация)
    static vector GetNorth_Bizon()     { return "14802.9 672.418 13943.2"; } // Bizon (Оружие)
    static vector GetNorth_Zaraza()    { return "14816.8 660.322 13859.6"; } // Zaraza (Стройка)

    // --- ВЫСОКОГОРНЫЙ УЗЕЛ (ИНДАР) ---
    static vector GetIndar_Maria()     { return "14348.7 558.753 5207.7"; } 
    static vector GetIndar_Badri()     { return "14349.6 558.753 5198.78"; }
    static vector GetIndar_Med_Gost()  { return "14379.8 552.921 5131.46"; }

    // --- ЮЖНЫЙ БЛОК (БОРИС) ---
    static vector GetSouth_Boris()     { return "8205.49 239.744 873.517"; }

    // =========================================================================
    // 🧠 ЛОГИКА ОЦЕНКИ ОПЕРАЦИЙ (ПРЕДОХРАНИТЕЛЬ)
    // =========================================================================
    
    static bool ShouldIProceed(vector targetPos, float currentHealth, float currentEnergy) 
    {
        float dist = vector.Distance(GetHome(), targetPos);
        
        // Предохранитель [Протокол 0.9]: Жизнь важнее железа
        if (currentHealth < 70.0 || currentEnergy < 30.0) return false;

        // Предохранитель [Ветеранская осторожность]: Ограничение дальности без подготовки
        if (dist > 2000.0) return false; 

        return true;
    }
}
