/*
    ОХОТНИЧЬЯ ПАМЯТЬ: NEKRASOV_HUNTER_V1
    ИНДЕКС: PRT-MEM-100.4
    ОПИСАНИЕ: Тихая охота, Атлас заводи и режим "Призрак".
*/

class Svyaznoy_Hunter_Memory
{
    void Svyaznoy_Hunter_Memory()
    {
        Print("[СВЯЗНОЙ-ОХОТА] Память промысловика загружена. Атлас тихой заводи активен.");
    }

    // --- 🎣 АТЛАС ТИХОЙ ЗАВОДИ ---
    static vector GetFishingPoint()
    {
        // ИСПРАВЛЕНО: Убраны запятые. Координаты Индара (заводь)
        return "14344.6 558.8 5150.0"; 
    }

    // --- 👣 РЕЖИМ "ПРИЗРАК" (СКРЫТНОСТЬ) ---
    static bool IsStealthRequired(float distToTarget)
    {
        // ИСПРАВЛЕНО: Убрана лишняя ";" после условия
        if (distToTarget < 50.0)
        {
            Print("[СВЯЗНОЙ-ОХОТА] Дистанция < 50м. Активация режима 'Призрак'.");
            return true;
        }
        return false;
    }

    // --- 🔪 ПРИОРИТЕТ БЕСШУМНОГО ОРУЖИЯ ---
    static bool ShouldUseKnife(string currentWeaponClass)
    {
        // Если в руках нож или лук - одобряем тихую работу
        if (currentWeaponClass == "CombatKnife" || currentWeaponClass == "HuntingKnife")
        {
            return true;
        }
        return false;
    }
}
