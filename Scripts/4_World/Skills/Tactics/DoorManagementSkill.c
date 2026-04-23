class DoorManagementSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Бытовая дисциплина: закрывать двери за собой
        AutoCloseDoors(bot);

        // 2. Тактическая блокировка: использование отмычки
        if (bot.IsInSafeZone() || bot.IsResting())
        {
            LockDoorsWithPick(bot);
        }
    }

    private void AutoCloseDoors(ExpansionAIBase bot)
    {
        // Поиск ближайшей открытой двери в радиусе 2 метров
        Building building = Building.Cast(bot.GetNearestObject("House", 2.0));
        if (building)
        {
            int doorIndex = building.GetDoorIndex(bot.GetPosition());
            if (building.IsDoorOpen(doorIndex))
            {
                bot.StartAction(ActionCloseDoors);
                Print("[AN_NEKRASOV_82] Закрываю за собой дверь. Порядок прежде всего.");
            }
        }
    }

    private void LockDoorsWithPick(ExpansionAIBase bot)
    {
        ItemBase lockpick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Lockpick"));
        if (!lockpick || lockpick.IsRuined()) return;

        Building building = Building.Cast(bot.GetNearestObject("House", 2.0));
        if (building)
        {
            int doorIndex = building.GetDoorIndex(bot.GetPosition());
            if (!building.IsDoorOpen(doorIndex) && !building.IsDoorLocked(doorIndex))
            {
                bot.TakeItemToHands(lockpick);
                bot.StartAction(ActionLockDoors);
                Print("[AN_NEKRASOV_82] Запираю дверь на отмычку. Теперь я в безопасности.");
            }
        }
    }
}

