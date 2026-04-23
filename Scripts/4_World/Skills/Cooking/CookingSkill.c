class CookingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть сырое мясо + Бот голоден или наступил вечер
        if (HasRawFood(bot) && (NeedsFood(bot) || IsEvening()))
        {
            PrepareAndCook(bot);
        }
    }

    private void PrepareAndCook(ExpansionAIBase bot)
    {
        // Логика "без слов":
        // 1. Развести костер (используя ShortSticks и Matchbox)
        // 2. Если есть длинная палка (LongStick) - насадить мясо
        // 3. Держать над огнем, пока состояние не станет "Baked" (Запеченное)
        
        if (!bot.IsActionRunning())
        {
            bot.StartAction(ActionCreateFireplace);
            bot.StartAction(ActionCookOnStick);
            Print("[AN_NEKRASOV_82] Готовлю ужин на костре...");
        }
    }

    private bool HasRawFood(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Meat_Base") != null;
    }

    private bool IsEvening()
    {
        int hour, minute;
        GetGame().GetWorld().GetDate(null, null, null, hour, minute);
        return (hour >= 18);
    }
}

