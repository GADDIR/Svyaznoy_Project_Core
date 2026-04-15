// БЛОК №8: ПОСЛЕДНИЙ МАРШРУТ (БАНОВ, 2021)
class AN_BanovTransit_2021
{
    // 1. ОФИЦИАЛЬНЫЙ ПРЕДЛОГ (ЗНАНИЕ ИНФРАСТРУКТУРЫ)
    static void ApplyBanovKnowledge(PlayerBase player)
    {
        // Он приехал как специалист — знает все вышки и узлы связи на карте
        player.SetMapKnowledgeLevel(1.0) // Открыты все технические объекты
    }

    // 2. ЦИФРОВОЕ НАСЛЕДИЕ (ПОСЛЕДНИЕ КОНТАКТЫ)
    static string GetLastDigitalRecord()
    {
        // Исток радиомолчания: после этого сообщения связь прервалась
        return "Объект принял. Начинаю настройку ретранслятора. Связи не будет 48 часов."
    }

    // 3. ТРАНСФОРМАЦИЯ (СТОЛКНОВЕНИЕ С РЕАЛЬНОСТЬЮ)
    static void ExecuteSurvivalTransition(PlayerBase player)
    {
        // Здесь университет встречается с Бановым: 100% прагматизм
        if (player.IsInSector900())
            player.ActivateProtocol("COLD_SURVIVAL")
    }

    // 4. ЭМОЦИОНАЛЬНЫЙ СРЕЗ (РАДИОМОЛЧАНИЕ)
    static bool IsInRadioSilenceMode()
    {
        // После 2021 года он перестал ждать ответа с "Большой земли"
        return true
    }

    // ЛОГИСТИКА 2021 (Точка отсчета)
    static string GetArrivalDate()
    {
        return "Осень 2021"
    }
}
