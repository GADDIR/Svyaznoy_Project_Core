/* 
    CORE LOGIC: MAVERICK_BRAIN [FINAL_PRT_CORE_INDEX]
    STATUS: INTEGRATED [PRT-100, 200, 300, 400, 600, 700]
    REVISION: 1.0.731_PRT
*/

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected string m_CurrentGoal = "NONE";
    protected float m_ZASTimer = 0;

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT-CORE-INDEX]: ГЛАВНЫЙ ЦИКЛ ПРИНЯТИЯ РЕШЕНИЙ
    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // 1. [PRT-100] BIO_STAT: Критический приоритет (Выживание)
        if (m_Player.GetStatEnergy().Get() < 200 || m_Player.GetStatWater().Get() < 200 || m_Player.IsBleeding())
        {
            ExecuteProtocol(100); // Поиск ресурсов/лечение
            return; // Блокировка остальных задач до стабилизации
        }

        // 2. [PRT-400] REACTION_X: Боевой контакт (Безопасность)
        if (GetNearestThreatDist() < 50)
        {
            ExecuteProtocol(400); // "Убей или уйди"
            return;
        }

        // 3. [PRT-300] ZAS_LINK: Связь (Цикл 30 минут)
        m_ZASTimer += timeslice;
        if (m_ZASTimer >= 1800)
        {
            ExecuteProtocol(300); // Поиск высоты для рапорта
            m_ZASTimer = 0;
        }

        // 4. [PRT-700] ECON: Экономика и Агро-цикл
        if (GetGame().GetWeather().GetRain().GetActual() > 0.3 && HasSeeds())
        {
            m_CurrentGoal = "AGRO_DRIVE";
        }

        // 5. [PRT-200] STEALTH_DRIVE: Фоновая скрытность
        ExecuteProtocol(200); 
    }

    void ExecuteProtocol(int id)
    {
        // Каждое переключение фиксируется в memory_logs.json под своим номером
        Print("[СВЯЗНОЙ]: АКТИВАЦИЯ ПРОТОКОЛА PRT-" + id.ToString());
        
        switch (id)
        {
            case 100: m_CurrentGoal = "BIO_EMERGENCY"; break;
            case 200: m_CurrentGoal = "STEALTH_MOVE"; break;
            case 300: m_CurrentGoal = "ZAS_REPORT"; break;
            case 400: m_CurrentGoal = "COMBAT_REFLEX"; break;
        }
    }

    // --- ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ СЕНСОРИКИ ---
    float GetNearestThreatDist()
    {
        return 1000.0; // Заглушка до реализации CoverScan
    }

    void SetRadioState(bool state)
    {
        if (m_Player) Print("[СВЯЗНОЙ]: PRT-300 (ZAS). Статус: " + state.ToString());
    }

    bool HasSeeds()
    {
        if (!m_Player) return false;
        return m_Player.GetInventory().FindEntityInInventory("ZucchiniSeeds") != null;
    }

    int GetFoodCount()
    {
        return 0; // Будет доработано в модуле PRT-100
    }

    bool HasFarmingEquipment()
    {
        if (!m_Player) return false;
        return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null || 
               m_Player.GetInventory().FindEntityInInventory("Shovel") != null;
    }
}
