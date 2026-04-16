/*
    ПРОЕКТ: СВЯЗНОЙ (Svyaznoy_Project_Core)
    ОБЪЕКТ: НЕКРАСОВ АЛЕКСЕЙ НИКОЛАЕВИЧ (АНН-79)
    ФАЙЛ: Svyaznoy_Knowledge_Base.c
    ОПИСАНИЕ: Объединенная библиотека инстинктов и техпроцессов.
*/

class  NEKRASOV_Knowledge_Base
{
    // --- 🕹️ УПРАВЛЯЮЩАЯ ЛОГИКА (EXECUTION) ---

    // Инициализация цикла выживания
    void Execute_ZeroCycle(PlayerBase self)
    {
        // 1. Проверка наличия острого инструмента
        if ( HasPrimaryTool(self) ) return; 

        // 2. Опрос инвентаря на наличие сырья
        EntityAI stones = self.GetInventory().FindEntityInInventory("Stone_Small");
        
        if ( !stones )
        {
            // Инстинкт поиска (Глаза)
            FindStone(self);
        }
        else 
        {
            // Если камни найдены (минимум 2 шт) — запуск акта воли
            if ( stones.GetQuantity() >= 2 )
            {
                CraftStoneKnife(self);
            }
        }
    }

    // --- 🛠️ ФУНКЦИОНАЛЬНЫЕ МЕТОДЫ (STATIC) ---

    // Алгоритм «Поиск Острия»
    static bool FindStone(PlayerBase player)
    {
        string surface;
        vector pos = player.GetPosition();
        // Исправлено: GetSurfaceType требует X и Z координаты
        GetGame().GetSurfaceType(pos[0], pos[2], surface);

        if (surface.Contains("Gravel") || surface.Contains("Stony") || surface.Contains("Dust"))
        {
            Print("[СВЯЗНОЙ]: Под ногами подходящая почва. Ищу камни.");
            player.SetAITask(EAI_TASK_SEARCH_GROUND); // Активация задачи поиска
            return true;
        }
        return false;
    }

    // Алгоритм «Первый Крафт»
    static void CraftStoneKnife(PlayerBase player)
    {
        Print("[СВЯЗНОЙ]: Ресурс собран. Изготовление каменного ножа (Акт Воли).");
        player.SetAITask(EAI_TASK_CRAFT_STONE_KNIFE);
    }

    // Алгоритм «Биологический Фильтр»
    static bool IsWaterSafe(int status)
    {
        // Только Boiled (кипяченая) или из "Умной бочки"
        if (status ==  NEKRASOV_WaterStatus.BOILED || status ==  NEKRASOV_WaterStatus.BARREL_COLLECTED)
        {
            return true;
        }
        
        Print("[СВЯЗНОЙ]: Вода небезопасна. Риск инфекции. Пить запрещено.");
        return false;
    }

    // Проверка наличия ножа (Разумение)
    bool HasPrimaryTool(PlayerBase self)
    {
        EntityAI handItem = self.GetHumanInventory().GetEntityInHands();
        if ( handItem && handItem.IsInherited(Knife_Base) ) return true;
        
        return false;
    }
}
