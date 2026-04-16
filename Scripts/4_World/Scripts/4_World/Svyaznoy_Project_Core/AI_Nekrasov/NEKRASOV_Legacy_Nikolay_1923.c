// БЛОК №31: ГЕНЕЗИС — ДЕД НИКОЛАЙ (ТЕХНИЧЕСКАЯ СОВЕСТЬ И БОЕВОЙ ДУХ)
class NEKRASOV_Legacy_Nikolay_1923
{
    // 1. БОЕВАЯ ДИПЛОМАТИЯ (Японский след 1945)
    static bool ShouldNegotiate(PlayerBase target)
    {
        // Враг — это ресурс. Оцениваем статус.
        if (target.IsOfficer() || target.HasRareIntel())
            return true // Берем живым для допроса/обмена
            
        return false
    }

    // 2. ДУЭТ "РАДИО И ЛЕС" (Ночная активность)
    static float GetNightActivityBonus(float hour)
    {
        // Дедовское время: с 18:00 до 06:00
        if (hour >= 18.0 || hour <= 6.0)
            return 1.3 // Повышенная зоркость и скрытность в сумерках
            
        return 1.0
    }

    // 3. МАСТЕР-УНИВЕРСАЛ (Логика починки "из мусора")
    static float GetImprovisationSuccess()
    {
        // "Если руки на месте — приемник поет"
        return 0.85 // Высокий шанс ремонта без спец-инструментов
    }

    // 4. ЗАВЕТ ДЕДА (Mumble Logic)
    static string GetGrandpaMumble(string event)
    {
        if (event == "WOUNDED_STAY_ON_POST")
            return "Дед Николай говорил: ранение — не повод бросать пост. Терпи."
        
        if (event == "FISHING_SUCCESS")
            return "Природа кормит того, кто её уважает... Будет ужин."

        if (event == "SCANNING_ETHER")
            return "Эфир — это чистая правда. Главное — уметь слушать."
            
        return ""
    }
}
