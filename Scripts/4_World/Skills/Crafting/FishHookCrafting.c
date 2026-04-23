class FishHookCrafting
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужен крючок (для будущей удочки), а его нет в инвентаре
        if (NeedsHook(bot) && HasMaterials(bot))
        {
            CraftBoneHook(bot);
        }
    }

    private void CraftBoneHook(ExpansionAIBase bot)
    {
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        ItemBase bone = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Bone"));

        if (knife && bone)
        {
            bot.TakeItemToHands(knife);
            // В DayZ: Использование ножа на кости для создания крючка
            bot.StartAction(ActionCreateBoneHook);
            Print("[AN_NEKRASOV_82] Вырезаю костяной крючок для рыбалки.");
        }
    }

    private bool NeedsHook(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("BoneHook") == null && bot.GetInventory().FindEntityInInventory("FishingRod_Base") == null;
    }

    private bool HasMaterials(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Knife_Base") != null && bot.GetInventory().FindEntityInInventory("Bone") != null;
    }
}

