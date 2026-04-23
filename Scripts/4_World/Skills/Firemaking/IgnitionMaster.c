class IgnitionMasterSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Ищем готовый к розжигу объект (костер, печь, камин)
        Object fireplace = bot.GetNearestObject("FireplaceBase", 2.0);
        if (fireplace && !IsIgnited(fireplace) && HasKindlingAndFuel(fireplace))
        {
            StartIgnition(bot, fireplace);
        }
    }

    private void StartIgnition(ExpansionAIBase bot, Object source)
    {
        // Приоритет инструментов розжига:
        // 1. Горелка (Blowtorch) - самый быстрый розжиг, не боится ветра.
        // 2. Зажигалка (PetrolLighter) - надежно и быстро.
        // 3. Спички (Matchbox) - классика, но могут промокнуть.
        // 4. Набор для розжига (HandDrillKit) - долго, тратит стамину, но бесплатно.

        ItemBase igniter = FindBestIgniter(bot);

        if (igniter)
        {
            bot.TakeItemToHands(igniter);
            
            // Если это спички или зажигалка - проверяем, не промокли ли они
            if (igniter.GetIsWet()) 
            {
                Print("[AN_NEKRASOV_82] Инструмент промок. Пытаюсь просушить или ищу замену.");
                return;
            }

            bot.StartAction(ActionLightItemOnFire); 
            Print("[AN_NEKRASOV_82] Разжигаю огонь, используя " + igniter.GetType());
        }
    }

    private ItemBase FindBestIgniter(ExpansionAIBase bot)
    {
        string[] types = {"Blowtorch", "PetrolLighter", "Matchbox", "HandDrillKit"};
        foreach (string t : types)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            if (item && item.GetQuantity() > 0) return item;
        }
        return null;
    }

    private bool IsIgnited(Object source) { /* Проверка статуса пламени */ return false; }
    private bool HasKindlingAndFuel(Object source) { /* Проверка, заправлен ли объект */ return true; }
}

