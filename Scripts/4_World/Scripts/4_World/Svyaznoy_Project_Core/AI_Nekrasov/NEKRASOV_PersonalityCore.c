//  NEKRASOV_PersonalityCore.c — ЦЕНТРАЛЬНЫЙ ПРОЦЕССОР СОСТОЯНИЙ
// Интеграция: Блоки 1-36. Узел принятия финальных решений.
class NEKRASOV_PersonalityCore
{
    // Ссылки на подсистемы разума
    private ref NEKRASOV_Identity      m_Identity
    private ref NEKRASOV_Memory_Buffer m_Memory
    private ref NEKRASOV_Moral_Engine   m_Moral
    
    // Текущее состояние (State Machine)
    private string m_ActiveState = "OBSERVATION"
    void AI_PersonalityCore(PlayerBase player)
    {
        // Сборка Личности при спавне
        m_Identity = new NEKRASOV_Identity(player)
        m_Memory   = new NEKRASOV_Memory_Buffer(player)
        m_Moral    = new NEKRASOV_Moral_Engine()
        
        NEKRASOV_Mumble_Logic.Say(player, "Система запущена. Сектор 900 под наблюдением.")
    }
    // ГЛАВНЫЙ ЦИКЛ МЫШЛЕНИЯ
    void OnUpdate(float timeslice, PlayerBase player)
    {
        // 1. Опрос Памяти (Что я вижу/помню?)
        m_Memory.OnTick(timeslice, player)
        // 2. Вердикт Морального Движка (Как я отношусь к цели?)
        EntityAI target = player.GetTarget()
        string decision = m_Moral.DecideOutcome(player, PlayerBase.Cast(target))
        // 3. ПЕРЕКЛЮЧЕНИЕ СОСТОЯНИЙ
        if (decision == "ELIMINATE")
            m_ActiveState = "COMBAT"
            
        if (decision == "IGNORE" && m_ActiveState != "HOUSEHOLD")
            m_ActiveState = "OBSERVATION"
        // 4. ИСПОЛНЕНИЕ (Узлы поведения)
        if (m_ActiveState == "COMBAT")
            NEKRASOV_Combat_Tactics.OnCombatUpdate(player, target, player.GetTargetDistance())
            
        if (m_ActiveState == "HOUSEHOLD")
            NEKRASOV_Lifestyle_Module.OnLifestyleUpdate(player, player.GetLocalTime())
    }
    // ВЕРХОВНЫЙ ФИЛЬТР ДЕЙСТВИЙ (Блок Х)
    bool CanPerformAction(PlayerBase player, string actionName)
    {
        // Если гигиена или табу запрещают — ИИ блокирует действие
        if (!Nekrasov_Food_Taboo.IsActionAllowed(player, player.GetItemInHands()))
            return false
            
        return true
    }
}
‎Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/NEKRASOV_FRAGILE_PARTICLES.c‎
Original file line number	Diff line number	Diff line change
@@ -1,33 +0,0 @@
// NEKRASOV_FRAGILE_PARTICLES.C — ХРУПКИЕ ЧАСТИЦЫ ПАМЯТИ (БЛОК B)
// Интеграция: Блок №1 (1982) — Лилии, Тени, Фото у Ёлки.
class NEKRASOV_FRAGILE_PARTICLES
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
                NEKRASOV_Mumble_Logic.Say(player, "Птица... Мама так руки складывала... а потом всё, обрыв.")
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
‎Scripts/4_World/Svyaznoy_Project_Core/AI_Nekrasov/NEKRASOV_Ancestors_Legacy.c‎
Original file line number	Diff line number	Diff line change
@@ -1,39 +0,0 @@
// БЛОК №30 и №31: ИСТОКИ (АННА ПЕТРОВНА И НИКОЛАЙ, 1923–1955)
class NEKRASOV_Ancestors_Legacy
{
    // БЛОК №30: АННА ПЕТРОВНА (ИСТОК ГИГИЕНИЧЕСКОГО ТЕРРОРА)
    // 1941–1945: Санитарка в прифронтовом госпитале
    static float GetSanitaryStandard()
    {
        // Потеря близких от тифа в эвакуации сформировала культ чистоты
        return 1.0 // Максимальный приоритет дезинфекции
    }
    // БЛОК №31: НИКОЛАЙ (ИСТОК РАДИО-ДУШИ)
    // 1941–1945: Линейный связист, катушка и ТА-43
    static void ApplySignalHeritage(PlayerBase player)
    {
        // Секретный опыт: работа под обстрелом, пайка "на коленке"
        player.SetRepairUnderStressBias(1.5) // Бонус к скорости ремонта в бою
    }
    // ЛОГИКА ПЕРЕДАЧИ (Генетическая память)
    static string GetLegacyMumble(string situation)
    {
        // Фразы, зашитые дедом и бабушкой
        if (situation == "DIRTY_WOUND")
            return "Анна Петровна говорила: зараза хуже пули, сначала промой."
        if (situation == "RADIO_FIXED")
            return "Как дед Николай учил: контакт есть — связь будет."
            
        return ""
    }
    // ВОЕННАЯ ПРАГМАТИКА (Блок X)
    static bool IsWartimeLogicActive()
    {
        // Готовность к "Протоколу Последнего патрона" заложена дедом
        return true 
    }
}
