class VerticalNavSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Поиск триггера лестницы (Ladder)
        Building building = Building.Cast(bot.GetNearestObject("House", 1.5));
        if (building && CanClimb(bot, building))
        {
            ClimbLogic(bot, building);
        }
    }

    private void ClimbLogic(ExpansionAIBase bot, Building building)
    {
        // 2. Вход в режим карабканья
        // Бот убирает оружие за спину, чтобы освободить руки
        if (!bot.GetHumanInventory().GetEntityInHands() == null)
        {
            bot.StartAction(ActionStoreItemInInventory);
        }

        // 3. Подъем на вышку/крышу
        bot.StartAction(ActionClimbLadder);
        Print("[AN_NEKRASOV_82] Поднимаюсь выше для обзора/безопасности.");
    }

    private bool CanClimb(ExpansionAIBase bot, Building b)
    {
        // Проверка: не занята ли лестница другим и нет ли угрозы прямо на ней
        return true; 
    }
}

