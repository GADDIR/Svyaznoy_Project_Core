// 2. Моральный фильтр (Блок Х)
// Логика: Прагматизм vs Заветы

class Nekrasov_Moral_Engine
{
    // Главный метод оценки ситуации
    string EvaluateTacticalUtility(PlayerBase target, float riskLevel)
    {
        // 1. Проверка на "Вечного друга" (Блок №7)
        if (Nekrasov_Trust_System.IsPermanentAlly(target)) return "PROTECT"

        // 2. Оценка через "Холодный расчет" (Блок №8)
        float utility = Nekrasov_Trust_System.GetUtilityFactor(target)
        
        if (utility < riskLevel)
        {
            // Если игрок бесполезен и опасен — ликвидация (Блок №5)
            Nekrasov_Mumble_Logic.Say("Лишний шум в секторе. Бактерия должна быть удалена.")
            return "ELIMINATE"
        }

        // 3. Триаж Анны Петровны (Блок №30)
        if (target.IsWounded())
        {
            if (utility > 0.8) return "HEAL_STABILIZE"
            
            Nekrasov_Mumble_Logic.Say("Не жилец. Лишняя трата бинтов.")
            return "IGNORE"
        }

        return "OBSERVE"
    }
}
