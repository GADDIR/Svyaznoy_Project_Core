// 📂 МОДУЛЬ: ПЕРВЫЙ ВДОХ (ZERO START LOGIC)
// Объект: А.Н. Некрасов
// Задача: Поиск ресурсов и создание первичного инструмента

class Svyaznoy_Knowledge_Base
{
    // Инициализация цикла выживания
    void Execute_ZeroCycle(PlayerBase self)
    {
        // Если в руках или инвентаре уже есть нож — выходим из цикла
        if ( HasPrimaryTool(self) ) return; 

        // 1. ПРОВЕРКА НАЛИЧИЯ СЫРЬЯ (КАМНИ)
        EntityAI stones = self.GetInventory().FindEntityInInventory("Stone_Small");
        
        if ( !stones )
        {
            // Если камней нет — запуск сканирования поверхности
            ScanEnvironmentForStones(self);
        }
        else 
        {
            // Если камни найдены (минимум 2 шт) — крафт
            if ( GetItemQuantity(stones) >= 2 )
            {
                CraftStoneKnife(self);
            }
        }
    }

    // Логика обнаружения камней (Глаза)
    void ScanEnvironmentForStones(PlayerBase self)
    {
        string surfaceType;
        vector pos = self.GetPosition();
        GetGame().GetSurfaceType(pos[0], pos[2], surfaceType);

        // Инстинкт: Искать на гравии, дорогах и каменистой почве
        if ( surfaceType.Contains("Gravel") || surfaceType.Contains("Stony") || surfaceType.Contains("Dust") )
        {
            // Активация поиска и LookAround360
            self.SetAITask(EAI_TASK_SEARCH_GROUND);
        }
    }

    // Проверка наличия острого инструмента (Разумение)
    bool HasPrimaryTool(PlayerBase self)
    {
        EntityAI handItem = self.GetHumanInventory().GetEntityInHands();
        if ( handItem && handItem.IsInherited(Knife_Base) ) return true;
        
        return false;
    }

    // Вспомогательная функция крафта
    void CraftStoneKnife(PlayerBase self)
    {
        // Логика создания каменного ножа (Этап 1: Младенчество)
        self.SetAITask(EAI_TASK_CRAFT_STONE_KNIFE);
    }
}
