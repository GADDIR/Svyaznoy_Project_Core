class EmergencyInjectionsSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. ЛОГИКА МОРФИЯ: При переломе ноги или сильной боли
        if (bot.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS) || bot.GetHealth() < 20.0)
        {
            UseInjector(bot, "Morphine");
        }

        // 2. ЛОГИКА АДРЕНАЛИНА: При угрозе обморока или нулевой стамине в бою
        if (bot.GetStatStamina().Get() < 5.0 && bot.IsFighting())
        {
            UseInjector(bot, "Epinephrine");
        }
    }

    private void UseInjector(ExpansionAIBase bot, string type)
    {
        ItemBase injector = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(type));
        if (injector && !bot.IsActionRunning())
        {
            bot.TakeItemToHands(injector);
            bot.StartAction(ActionInjectSelf);
            Print("[AN_NEKRASOV_82] Экстренная ситуация! Применяю " + type);
        }
    }
}

