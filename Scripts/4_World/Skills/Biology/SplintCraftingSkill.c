class SplintCraftingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Перелом ноги
        if (bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
        {
            HandleLegInjury(bot);
        }
    }

    private void HandleLegInjury(ExpansionAIBase bot)
    {
        // Если шина уже наложена, просто ждем заживления
        if (bot.IsSplinted()) return;

        // 2. Ищем палки ( WoodenSticks )
        ItemBase sticks = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));
        
        // 3. Ищем связующий материал (Бинт / Тряпка / Скотч)
        ItemBase fastener = FindFastener(bot);

        if (sticks && sticks.GetQuantity() >= 2 && fastener)
        {
            bot.TakeItemToHands(sticks);
            // Логика DayZ: Создать шину
            bot.StartAction(ActionCreateSplint); 
            Print("[AN_NEKRASOV_82] У меня перелом! Срочно крафчу шину из палок и " + fastener.GetType());
        }
        else
        {
            // Если ресурсов нет - бот ползет к ближайшему кусту, чтобы добыть палки ножом
            Print("[AN_NEKRASOV_82] Нет палок для шины. Ползу к кустам.");
        }
    }

    private ItemBase FindFastener(ExpansionAIBase bot)
    {
        string[] options = {"BandageDressing", "Rag", "DuctTape"};
        foreach (string opt : options)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(opt));
            if (item && item.GetQuantity() >= 1) return item;
        }
        return null;
    }
}

