class SpearSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || HasBetterMelee(bot)) return;

        // 1. Условие: Есть нож, длинная палка и веревка (самодельная или найденная)
        if (CanCraftSpear(bot))
        {
            CraftSpear(bot);
        }
    }

    private void CraftSpear(ExpansionAIBase bot)
    {
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("BoneKnife")); // Приоритет костяному
        if (!knife) knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("StoneKnife"));
        
        ItemBase stick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("LongWoodenStick"));
        ItemBase rope = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rope"));

        if (knife && stick && rope)
        {
            bot.TakeItemToHands(knife);
            // Логика: Соединить нож + палка + веревка = Копье
            bot.StartAction(ActionCreateSpear); 
            Print("[AN_NEKRASOV_82] Изготавливаю копье для защиты фермы.");
        }
    }

    private bool CanCraftSpear(ExpansionAIBase bot)
    {
        // Проверяем наличие всех компонентов в инвентаре
        bool hasKnife = bot.GetInventory().FindEntityInInventory("Knife_Base") != null;
        bool hasStick = bot.GetInventory().FindEntityInInventory("LongWoodenStick") != null;
        bool hasRope = bot.GetInventory().FindEntityInInventory("Rope") != null;
        
        return hasKnife && hasStick && hasRope && bot.GetInventory().FindEntityInInventory("Spear") == null;
    }

    private bool HasBetterMelee(ExpansionAIBase bot)
    {
        // Если он уже купил топорик или нашел мачете, копье ему может быть не нужно
        return bot.GetInventory().FindEntityInInventory("Axe_Base") != null;
    }
}

