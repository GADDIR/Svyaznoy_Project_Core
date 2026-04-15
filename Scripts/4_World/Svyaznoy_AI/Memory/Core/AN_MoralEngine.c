// БЛОК X: MORAL ENGINE (КРЕДО И ОТСУТСТВИЕ СОВЕСТИ)
// Фильтр принятия решений на основе Полезности Объекта

class AN_MoralEngine
{
    // ГЛАВНЫЙ МЕТОД ВЫБОРА (Спуск или Консерва)
    static string DecideOutcome(PlayerBase player, PlayerBase target)
    {
        // 1. Запрос в Блок IX (Генезис): Уровень текущего стресса
        float stressLevel = player.GetStressLevel()
        
        // 2. Запрос в Блок VI (Прагматизм): Оценка лута цели
        float targetValue = target.CalculateLootWeight()
        
        // 3. Запрос в Блок X (Кредо): Полезность объекта
        float utility = player.GetSocialBrain().GetUtilityFactor(target)

        // ЛОГИКА ПРИНЯТИЯ РЕШЕНИЯ
        // Если выгода от смерти (лут) выше, чем от жизни (полезность)
        if (targetValue > (utility * 2))
            if (stressLevel < 0.8) // Если руки не трясутся
                return "ELIMINATE"

        // Если объект полезен (Блок IX) и риск минимален
        if (utility > 0.7)
            if (player.HasExtraResources())
                return "SHARE_RESOURCES"

        // В любой непонятной ситуации — Блок V (Армия): Дистанция и Скрытность
        return "OBSERVE_FROM_DISTANCE"
    }

    // УЗЕЛ «МОНОЛИТ»: Проверка на противоречия
    static bool CheckMentalStability(string traumaBlock, string moralBlock)
    {
        // Если Армия (V) требует стрелять, а Мораль (X) видит союзника
        // Происходит "Тихий психоз"
        if (traumaBlock == "AGGRESSION" && moralBlock == "ALLY")
            return false // Ошибка Монолита
            
        return true
    }
}
