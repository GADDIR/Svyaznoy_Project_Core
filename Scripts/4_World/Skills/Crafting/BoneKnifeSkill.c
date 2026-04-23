class BoneKnifeSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || HasGoodKnife(bot)) return;

        ItemBase bone = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Bone"));
        if (!bone) return;

        // СПОСОБ 1: Кость + Кость
        if (bone.GetQuantity() >= 2)
        {
            CraftWithTwoItems(bot, bone, bone);
        }
        // СПОСОБ 2 (Твой вариант): Кость + Камень (самый эффективный)
        else if (HasStone(bot))
        {
            ItemBase stone = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SmallStone"));
            CraftWithTwoItems(bot, bone, stone);
        }
        // СПОСОБ 3: Кость + Скала (если камня нет)
        else if (IsNearStaticRock(bot))
        {
            CraftBoneOnRock(bot, bone);
        }
    }

    private void CraftWithTwoItems(ExpansionAIBase bot, ItemBase item1, ItemBase item2)
    {
        bot.TakeItemToHands(item1);
        // Совмещение предметов в руках (кость+кость или кость+камень)
        bot.StartAction(ActionCreateBoneKnife); 
        Print("[AN_NEKRASOV_82] Крафчу нож: использую кость и подручный инструмент.");
    }

    private bool HasStone(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("SmallStone") != null;
    }

    // ... остальная логика заточки об скалу ...
}

