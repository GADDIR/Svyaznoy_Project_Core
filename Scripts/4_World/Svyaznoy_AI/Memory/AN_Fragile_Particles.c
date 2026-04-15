// БОНУС-БЛОК: FRAGILE_PARTICLES (ОБРЫВКИ СЧАСТЬЯ ДО 1982 г.)
class AN_Fragile_Particles
{
    // ТРИГГЕРЫ "ТОЧКИ ПОКОЯ"
    static void ProcessFragileMoment(PlayerBase player, EntityAI item, float hour)
    {
        // 1. Триггер «Лилия» (Красное и желтое)
        if (item.IsFlower() || item.HasColor("Red_Yellow"))
        {
            player.SetAggressionLevel(0.0) // Полное замирание
            player.SetStareDuration(10.0)  // Смотрит 10 секунд в пустоту
        }

        // 2. Театр теней (Сумерки)
        if (hour >= 20.0 && hour <= 22.0)
            if (player.IsNearFireplace())
                player.RequestMumble("Птица... Мама так руки складывала... а потом всё, обрыв.")

        // 3. Фото: Ёлка и коляска (Защитный талисман)
        if (!player.HasItemInInventory("AN_Photo_1982"))
            player.ActivateProtocol("BERSERK_MODE") // Потеря памяти = ярость
    }

    // ВИЗУАЛЬНЫЙ АРТЕФАКТ (Эмоциональный отпечаток)
    static float GetStabilityBonus(PlayerBase player)
    {
        // Наличие фото в руках дает бонус к ментальной стабильности
        if (player.GetItemInHands().IsInherited(AN_Photo_1982))
            return 2.0
            
        return 1.0
    }

    // ЛОГИКА "ОБРЫВА" (Недорисованная память)
    static string GetBrokenMemory()
    {
        // Мы не дорисовываем, мы оставляем пустоту
        return "ERROR: MEMORY_FRAGMENT_CORRUPTED_1982"
    }
}
