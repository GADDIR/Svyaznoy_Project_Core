class RestSkill
{
    // Настройки графика (с 21:00 до 05:00 — время отдыха)
    private const int NIGHT_START = 21;
    private const int NIGHT_END = 5;

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot) return;

        int hour, minute;
        GetGame().GetWorld().GetDate(null, null, null, hour, minute);

        // Проверка: Наступило ли время отдыха?
        if (IsNightTime(hour))
        {
            StartRestCycle(bot);
        }
    }

    private bool IsNightTime(int hour)
    {
        return (hour >= NIGHT_START || hour < NIGHT_END);
    }

    private void StartRestCycle(ExpansionAIBase bot)
    {
        // 1. Убираем инструменты с плеч в инвентарь или просто фиксируем за спиной
        ItemBase itemInHands = ItemBase.Cast(bot.GetHumanInventory().GetEntityInHands());
        if (itemInHands)
        {
            bot.PredictiveDropEntity(itemInHands); // Либо прячем, если есть место
        }

        // 2. Логика перемещения к "домашней" точке
        // Координаты дома Алексея Николаевича
        vector homePos = "308.474 283.267 260.481"; 
        
        if (vector.Distance(bot.GetPosition(), homePos) > 2.0)
        {
            bot.GetNavigation().SetTarget(homePos, ExpansionHAL_Mode.WALK);
        }
        else
        {
            // Если пришел домой — принимаем позу отдыха (сидя)
            bot.StartCommand_Action(DayZPlayerConstants.CMD_ACTIONFB_SITACTION, DayZPlayerConstants.STANCE_ERECT);
        }
    }
}

