class StoneGatheringSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужны камни (для заточки, крафта ножа или печи)
        if (NeedsStones(bot))
        {
            SearchAndCollectStones(bot);
        }
    }

    private bool NeedsStones(ExpansionAIBase bot)
    {
        // Проверяем наличие камней в инвентаре (маленьких или больших)
        int stoneCount = bot.GetInventory().CountItemsWithPrefix("SmallStone");
        return (stoneCount < 2); // Алексею Николаевичу всегда нужно иметь пару камней про запас
    }

    private void SearchAndCollectStones(ExpansionAIBase bot)
    {
        // 2. Поиск текстуры камней или выступов скал
        vector pos = bot.GetPosition();
        string surfaceType;
        GetGame().SurfaceGetType(pos, pos, surfaceType);

        // В DayZ камни можно собирать на скалистых поверхностях (stony, rock)
        if (surfaceType.Contains("stony") || surfaceType.Contains("rock"))
        {
            if (!bot.IsActionRunning())
            {
                // Запуск действия поиска камней на поверхности
                bot.StartAction(ActionSearchRocks);
                Print("[AN_NEKRASOV_82] Ищу камни на каменистой почве...");
            }
        }
        else
        {
            // Если под ногами нет камней — логика перемещения к ближайшей скале
            // (В будущем здесь будет поиск координат скал на Банове)
        }
    }
}

