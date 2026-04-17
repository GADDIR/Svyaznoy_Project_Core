// БЛОК Х: NEKRASOV MORAL ENGINE — ЦЕНТРАЛЬНЫЙ ФИЛЬТР ЦЕЛЕСООБРАЗНОСТИ
// Интеграция: Анна (30), Николай (31), Игишев (32), Адвентизм (35)

class NEKRASOV_Moral_Engine
{
    // ГЛАВНЫЙ МЕТОД ОЦЕНКИ (Спуск или Консерва)
    string DecideOutcome(PlayerBase player, PlayerBase target)
    {
        // 1. Учет Наставника (Блок №32): Оценка стойки (Самбо)
        if (target.IsAggressivePose())
            return "COMBAT_READY"

        // 2. Проверка на "Вечного друга" (Блок №7)
        if NEKRASOV_Trust_System.IsPermanentAlly(target))
            return "PROTECT"

        // 3. Холодный расчет (Блок №8) и Триаж Анны (Блок №30)
        float utility = NEKRASOV_Trust_System.GetUtilityFactor(target)
        
        if (target.IsWounded())
        {
            if (utility > 0.8) 
                return "HEAL_STABILIZE"
            
            // "Не жилец. Лишняя трата бинтов."
            return "IGNORE"
        }

        // 4. Устав Чистого Сигнала (Блок №35/36): Адвентистский фильтр
        if (target.HasUncleanItems())
        {
            // Свинина/Алкоголь в руках игрока обнуляют полезность
            return "ELIMINATE"
        }

        if (utility < 0.2)
            return "ELIMINATE"

        return "OBSERVE"
    }

    // ФИЛЬТР ГЛУБОКОЙ ПАМЯТИ (Заветы)
    bool IsActionAllowed(PlayerBase player, string actionType)
    {
        // Завет Анны: Гигиенический террор (Блок №1/30)
        if (actionType == "EAT" && player.GetStatDirtyHands().Get() > 0)
            return false

        // Блок №36: Тайное кредо (Запрет на свинину)
        if (actionType == "EAT" && player.IsHoldingPork())
            return false

        return true
    }
}
