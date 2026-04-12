/*
    ОХОТНИЧЬЯ ПАМЯТЬ: NEKRASOV_HUNTER_V1
    ИНДЕКС: PRT-MEM-100.4
    ОПИСАНИЕ: Тихая охота, Атлас заводи и режим "Призрак".
*/

class Svyaznoy_Hunter_Memory
{
    // --- 🏗️ КОНСТРУКТОР ---
    void Svyaznoy_Hunter_Memory()
    {
        Print("[СВЯЗНОЙ-ОХОТА] Память промысловика (Сектор 100.4) загружена. Атлас заводи активен.");
    }

    // --- 🎣 АТЛАС ТИХОЙ ЗАВОДИ ---
    static vector GetFishingPoint()
    {
        // ИСПРАВЛЕНО: Убраны запятые, формат приведен к стандарту DayZ "X Y Z"
        return "14344.6 558.8 5150.0"; 
    }

    // --- 👣 РЕЖИМ "ПРИЗРАК" (СКРЫТНОСТЬ) ---
    // Включается, когда нужно сблизиться с целью или обойти угрозу
    static bool IsStealthRequired(float distToTarget)
    {
        // ИСПРАВЛЕНО: Убрана лишняя ";" после IF. 
        // Теперь режим включается ТОЛЬКО при сближении < 50м.
        if (distToTarget < 50.0)
        {
            Print("[СВЯЗНОЙ-ОХОТА] Объект в зоне 50м. Переход на шаг/ползком.");
            return true;
        }
        return false;
    }

    // --- 🔪 ДОГМАТ ТИШИНЫ (НОЖ) ---
    // Проверка, является ли выбранный инструмент бесшумным
    static bool ShouldUseKnife(string weaponClass)
    {
        if (weaponClass == "CombatKnife" || weaponClass == "HuntingKnife")
        {
            return true;
        }
        return false;
    }
}
