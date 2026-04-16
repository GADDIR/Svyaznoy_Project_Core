// Nekrasov_FRAGILE_PARTICLES.C-ХРУПКИЕ ЧАСТИЦЫ ПАМЯТИ (БЛОК B)
// Интеграция: Блок №1 (1982) — Лилии, Тени, Фото у Ёлки.

class AN_Fragile_Particles
{
    // ГЛАВНЫЙ МЕТОД ОБРАБОТКИ ЭМОЦИОНАЛЬНЫХ ТРИГГЕРОВ
    static void ProcessEmotions(PlayerBase player, EntityAI item, float hour)
    {
        // 1. ТРИГГЕР "ЛИЛИЯ" (Точка покоя)
        // Если видит красные/желтые цветы или артефакты
        if (item.HasColor("Red_Yellow") || item.IsFlower())
            player.SetAggressionLevel(0.0) // Сброс агрессии
            player.SetStareDuration(10.0)  // Замирание на 10 секунд
            Nekrasov_Mumble_Logic.Say(player, "Запах... как тогда. У отца в руках.")

        // 2. ТЕАТР ТЕНЕЙ (Сумерки 20:00 - 22:00)
        if (hour >= 20.0 && hour <= 22.0)
            if (player.IsNearFireplace())
                player.RequestFlashback("SHADOW_THEATER")
                Nekrasov_Mumble_Logic.Say(player, "Птица... Мама так руки складывала... а потом всё, обрыв.")

        // 3. ЗАЩИТНЫЙ ТАЛИСМАН (Фото 1982 года)
        if (!player.HasItemInInventory("AN_Photo_1982"))
            // Если фото украдено или потеряно — режим берсерка
            player.ActivateProtocol("BERSERK_MODE") 
    }

    // ЛОГИКА "ОБРЫВА" (Поврежденные сектора памяти)
    static string GetCorruptedMemoryFragment()
    {
        return "ERROR: MEMORY_FRAGMENT_1982_NOT_FOUND"
    }
}
