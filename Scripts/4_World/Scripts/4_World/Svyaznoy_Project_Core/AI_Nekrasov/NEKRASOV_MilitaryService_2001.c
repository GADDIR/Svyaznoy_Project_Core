// БЛОК №5: ВОЕННАЯ ПОДГОТОВКА И ТАКТИЧЕСКИЙ ОПЫТ (АРМИЯ, 2001 г.)
class NEKRASOV_MilitaryService_2001
{
    // 1. УЧЕТНЫЕ ДАННЫЕ
    static string GetMilitarySpecialty()
    {
        return "Специалист полевой радиосвязи / Снайпер"
    }

    // 2. СЛУЖБА И СПЕЦИАЛИЗАЦИЯ (ВЛАДЕНИЕ СВД И ПСО-1)
    static void ApplyCombatTraining(PlayerBase player)
    {
        // Навыки топографии и баллистики
        player.SetWeaponSwayModifier(0.6) // Стабилизация рук при стрельбе
        player.SetZeroingPrecision(1.0)  // Идеальное понимание сетки ПСО-1
        
        // Армейская дисциплина: осмотр на 360 градусов
        player.SetIdleScanFrequency(2.0) // В 2 раза чаще оглядывается в покое
    }

    // 3. ПСИХОЛОГИЧЕСКИЙ ОТПЕЧАТК (ПРОТОКОЛ ПОСЛЕДНЕГО ПАТРОНА)
    static bool IsPragmaticExecutioner()
    {
        // Армия вытравила гражданскую мягкость
        return true 
    }

    // 4. ФРОНТОВАЯ ГИГИЕНА (АННА ПЕТРОВНА + БОЕВОЙ УСТАВ)
    static float GetInfectionResistance()
    {
        // Грязь = инфекция = смерть. Некрасов следит за этим маниакально.
        return 1.5 // Повышенная сопротивляемость из-за ухода за телом
    }

    // БОЕВОЙ УСТАВ (Прерывание любого действия при угрозе)
    static void ExecuteTacticalOverride(PlayerBase player)
    {
        if (player.IsUnderThreat())
            player.InterruptAction("COMBAT_STANCE")
    }
}
