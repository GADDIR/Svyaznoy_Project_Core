// NEKRASOV_TRADE_LOGIC.C — ТОРГОВАЯ ПРАГМАТИКА И ОБМЕН РЕСУРСАМИ
// Интеграция: Блок №36 (Тайное кредо) и Блок №6 (Экономика выживания)

class Nekrasov_Trade_Logic
{
    // ГЛАВНЫЙ МЕТОД: Оценка предложения игрока
    static bool EvaluateTrade(PlayerBase player, array<EntityAI> offer)
    {
        float totalValue = 0.0
        
        foreach (EntityAI item : offer)
        {
            // Блок №6: Особая ценность запчастей и патронов 7.62x54
            if (item.IsInherited(ComponentBase) || item.ClassName().Contains("762x54"))
                totalValue += 50.0
                
            // Блок №35: Свинина принимается ТОЛЬКО как товар для перепродажи
            if (item.ClassName().Contains("Pig"))
                totalValue += 10.0 // Низкий приоритет, но берем
        }

        if (totalValue > 100.0)
            return true
            
        return false
    }

    // МЕХАНИКА ИЗБАВЛЕНИЯ (Сбыт "нечистого")
    static void PrepareInventoryForTrade(PlayerBase player)
    {
        // Сначала выставляем на продажу то, что запрещено есть (Блок №36)
        if (player.HasItem("Food_MeatPig"))
            player.SetTradeOffer("Food_MeatPig")
            Nekrasov_Mumble_Logic.Say(player, "Отдам это Quinn. Ей нужнее, а мне — балласт.")

        // Сохраняем "чистый" НЗ (Блок №31)
        if (player.HasItem("Food_DeerMeat"))
            player.LockInInventory("Food_DeerMeat") 
    }

    // ЛОГИКА "ПОДКУПА" (Блок №9)
    static void ProcessGift(PlayerBase player, PlayerBase giver, EntityAI gift)
    {
        if (gift)
            float val = Nekrasov_Genesis_Registry.Get(9) // Коэффициент благодарности
            player.GetTrustSystem().OnResourceReceived(player, giver.GetIdentity().GetId(), 20.0 * val)
    }
}
