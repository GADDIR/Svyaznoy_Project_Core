class MedicSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot) return;

        // 1. Проверка на кровотечение (самый высокий приоритет)
        if (bot.GetBleedingManager() && bot.GetBleedingManager().GetBleedingSourcesCount() > 0)
        {
            UseMedicalItem(bot, "BandageDressing");
            return;
        }

        // 2. Проверка общего здоровья
        float health = bot.GetHealth("GlobalHealth", "Health");
        if (health < 70.0) // Если здоровье ниже 70%
        {
            // Пытается найти обезболивающее или витамины, если они будут в инвентаре
            if (HasItem(bot, "VitaminBottle"))
            {
                UseMedicalItem(bot, "VitaminBottle");
            }
        }
    }

    private bool HasItem(ExpansionAIBase bot, string className)
    {
        return bot.GetInventory().FindEntityInInventory(className) != null;
    }

    private void UseMedicalItem(ExpansionAIBase bot, string className)
    {
        EntityAI item = bot.GetInventory().FindEntityInInventory(className);
        
        // Если предмет найден и руки свободны или в руках уже этот предмет
        if (item)
        {
            // Логика Expansion AI для использования медицины
            bot.TakeItemToHands(item);
            
            // Если это бинт — запускаем действие перевязки
            if (className == "BandageDressing")
            {
                bot.StartAction(ActionBandageSelf);
            }
            else
            {
                bot.StartAction(ActionConsume); // Для таблеток/витаминов
            }
        }
    }
}

