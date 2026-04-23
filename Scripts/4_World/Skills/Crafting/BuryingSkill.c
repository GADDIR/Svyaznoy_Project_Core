class BuryingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть инструмент для копания + есть ящик на земле
        if (CanBury(bot))
        {
            PerformBurying(bot);
        }
    }

    private bool CanBury(ExpansionAIBase bot)
    {
        // Ищем лопату (Shovel) или кирку (Pickaxe)
        ItemBase tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Shovel"));
        if (!tool) tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Pickaxe"));
        if (!tool) tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("FieldShovel"));

        // Ищем ящик (WoodenCrate) или гермомешок (SeaChest) в радиусе 2 метров
        Object target = GetNearestBuryableObject(bot, 2.0);

        return (tool && target);
    }

    private void PerformBurying(ExpansionAIBase bot)
    {
        ItemBase tool = ItemBase.Cast(bot.GetHumanInventory().GetEntityInHands());
        if (tool && tool.IsInherited(Shovel)) // Убеждаемся, что лопата в руках
        {
            bot.StartAction(ActionBuryBody); // В движке это действие используется и для предметов
            Print("[AN_NEKRASOV_82] Закапываю запасы в землю. Теперь их не найдут.");
        }
    }

    private Object GetNearestBuryableObject(ExpansionAIBase bot, float range)
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), range, objects, null);
        foreach (Object obj : objects)
        {
            if (obj.IsInherited(WoodenCrate) || obj.IsInherited(SeaChest)) return obj;
        }
        return null;
    }
}

