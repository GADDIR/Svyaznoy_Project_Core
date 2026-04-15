// БЛОК №6: ТРУДОВОЙ СТАЖ И НАКОПЛЕНИЕ ОПЫТА (ДО 2015 г.)
class AN_WorkExperience_2015
{
    // 1. ПРОФЕССИОНАЛЬНАЯ ТРАЕКТОРИЯ (УДАЛЕННЫЕ ОБЪЕКТЫ)
    static string GetCareerStatus()
    {
        return "Ведущий инженер автономных узлов связи"
    }

    // 2. ТЕХНИЧЕСКАЯ ОТВЕТСТВЕННОСТЬ (ОШИБКА = ПОТЕРЯ СВЯЗИ)
    static void ApplyWorkDiscipline(PlayerBase player)
    {
        // Привычка к строжайшему техрегламенту
        player.SetRepairSuccessChance(1.0) // 100% успех при наличии инструментов
        player.SetCriticalErrorRisk(0.01)  // Минимальный риск запороть деталь
    }

    // 3. СОЦИАЛЬНЫЙ КЛИМАТ (ХОЛОДНАЯ ЛОГИКА)
    static string GetWorkReference()
    {
        // Как его воспринимали коллеги: "Эффективен, но невыносимо сух"
        return "Исключительная надежность. Трудности в коммуникации. Эмпатия отсутствует."
    }

    // 4. ЭКОНОМИКА ВЫЖИВАНИЯ (СОРТИРОВКА ЛУТА)
    static bool IsItemValuable(EntityAI item)
    {
        // Навык разделения на "нужное для дела" и "балласт"
        // Базируется на опыте учета запчастей и ГСМ
        if (item.IsInherited(ComponentBase) || item.IsInherited(FuelContainer))
            return true
            
        if (item.IsInherited(PristineGrit))
            return true

        return false
    }

    // ХОЗЯЙСТВЕННЫЙ УСТАВ (Осмотр инвентаря)
    static void PerformInventoryAudit(PlayerBase player)
    {
        // Если балласта больше 30% — АН ищет место для сброса (схрон)
        if (player.GetCargoLoad() > 0.7)
            player.TriggerState("LOGISTICS_OPTIMIZATION")
    }
}
