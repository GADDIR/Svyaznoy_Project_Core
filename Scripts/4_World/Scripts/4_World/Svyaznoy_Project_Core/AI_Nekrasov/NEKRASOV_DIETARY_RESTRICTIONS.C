NEKRASOV_DIETARY_RESTRICTIONS.C — ФИНАЛЬНАЯ СИНХРОНИЗАЦИЯ
// Логика: Принципы важнее голода, но жизнь важнее принципов.

class Nekrasov_Dietary_Restrictions
{
    // 1. Глобальный фильтр действий
    static bool CanNekrasovConsume(PlayerBase player, EntityAI item)
    {
        if (!item) return true;

        string cls = item.ClassName();
        cls.ToLower(); // Приводим к нижнему регистру для надежности поиска

        // --- ИСКЛЮЧЕНИЕ: МЕДИЦИНСКИЙ ПРОТОКОЛ (Блок №36 - Выживание) ---
        // Если это лекарство, Некрасов принимает его как "ресурс" без раздумий
        if (item.IsInherited(Pharmaceutical_Base) || item.IsInherited(VitaminBottle))
        {
            return true;
        }

        // --- БЛОК №35: ПИЩЕВОЕ ТАБУ (Осознание) ---
        // Наш "костыль" осознания через проверку вхождений (Pork, Lard, Fat)
        if (cls.Contains("pork") || cls.Contains("pig") || cls.Contains("lard") || cls.Contains("bacon"))
        {
            Print("[AI_Nekrasov] Отказ по убеждениям: " + cls);
            return false;
        }

        // Запрет на алкоголь (Блок №35)
        if (cls.Contains("vodka") || cls.Contains("beer") || cls.Contains("alcohol"))
        {
            // Исключение: дезинфектант (если используется для ран, а не внутрь)
            if (cls.Contains("disinfectant")) return true;
            
            return false;
        }

        return true;
    }

    // 2. ФРАЗЫ ПРИКРЫТИЯ (Ложная нормальность)
    static string GetMumbleExcuse(string cls)
    {
        cls.ToLower();

        if (cls.Contains("pig") || cls.Contains("pork"))
            return "Не пойдет... Изжога замучает. Отдам Quinn, ей нужнее.";

        if (cls.Contains("alcohol"))
            return "Ясность ума — оружие связиста. Оставь себе, мне лишний шум в голове не нужен.";

        return "Не сейчас. Позже перекушу.";
    }

    // 3. ПРАГМАТИЗМ (Разделка туш)
    // Убивать свинью можно (ради кожи/жира для смазки), есть — нельзя.
    static bool CanProcess(string animalType)
    {
        return true; // Ресурс важнее брезгливости.
    }
}
