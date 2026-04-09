/* 
    CORE LOGIC: MAVERICK_BRAIN
    STATUS: INTEGRATED [PRT-CODE-500 / PRT-SAFE-600 / PRT-ECON-700]
    REVISION: 1.0.731
*/

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected string m_CurrentGoal = "NONE";

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT-CODE-500] Сканер угроз (ПСЛ)
    float GetNearestThreatDist()
    {
        // Базовая заглушка: в будущем здесь Raycast
        return 1000.0; 
    }

    // [PRT-CODE-500] Управление рацией
    void SetRadioState(bool state)
    {
        if (m_Player) Print("[СВЯЗНОЙ]: Статус ЗАС изменен на: " + state.ToString());
    }

    // [PRT-SAFE-600] Сейф-зона
    void ActivateSafeZoneProtocol()
    {
        if (m_Player) {
            // [PRT-ECON-700.4] Эшелон НЗ: Проверка еды перед выходом
            if (GetFoodCount() < 3) {
                m_CurrentGoal = "RESERVE_HOLD";
                Print("[СВЯЗНОЙ]: Дефицит НЗ. Цель: Поиск консервов.");
            } else {
                m_CurrentGoal = "TRADE_AGRO";
                Print("[СВЯЗНОЙ]: Протокол СЗ активен. Поиск семян.");
            }
        }
    }

    // [PRT-ECON-700] Экономическая логика
    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // 700.1: AGRO_DRIVE — Активация при дожде
        if (GetGame().GetWeather().GetRain().GetActual() > 0.3 && HasSeeds())
        {
            m_CurrentGoal = "AGRO_DRIVE";
        }

        // 700.3: TRADE_UPGRADE — Проверка накоплений на Глушитель/ПНВ
        // (Предполагаем наличие функции GetCurrency баланса)
        float balance = 0; // Заглушка под баланс
        float targetPrice = 5000.0; 
        
        if (balance >= targetPrice) {
            m_CurrentGoal = "TECH_UPGRADE";
        }
    }

    // [PRT-ECON-700.1] Проверка семян
    bool HasSeeds()
    {
        if (!m_Player) return false;
        return m_Player.GetInventory().FindEntityInInventory("ZucchiniSeeds") != null;
    }

    // [PRT-ECON-700.4] Подсчет банок еды
    int GetFoodCount()
    {
        if (!m_Player) return 0;
        // Упрощенный поиск еды в инвентаре
        return 0; // Будет доработано в модуле сканирования инвентаря
    }

    // Проверка агро-инвентаря
    bool HasFarmingEquipment()
    {
        if (!m_Player) return false;
        // Поиск лопаты или тяпки
        return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null || 
               m_Player.GetInventory().FindEntityInInventory("Shovel") != null;
    }
}
