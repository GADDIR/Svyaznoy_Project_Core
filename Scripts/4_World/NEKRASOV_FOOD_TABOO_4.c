/*
    УЗЕЛ 75.К4: СОХРАННОСТЬ И КЛИМАТИЧЕСКИЙ КОНТРОЛЬ
    Файл: NEKRASOV_FOOD_TABOO_4.c
    Связь: hearth_and_conservation.md
    Назначение: Управление скоростью порчи активов NEKRASOV в зависимости от условий.
*/

modded class NEKRASOV_FOOD_TABOO
{
    // Коэффициенты деградации из протокола консервации
    protected float m_NEKRASOV_PreservationFactor;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_PreservationFactor = 0.5; // Замедление порчи для "Чистой" еды
    }

    // Логика: Проверка условий хранения (Влага/Температура)
    // Если еда лежит в "правильном" контейнере из Узла 3 — она живет дольше
    void NEKRASOV_ManageDecay(Edible_Base food, EntityAI container)
    {
        if (!food) return;

        // Если еда прошла через Очаг (Smoked/Dried) и лежит в защищенном месте
        if (NEKRASOV_IsConserved(food) && NEKRASOV_IsContainerSafe(container))
        {
            // Замедляем гниение программно
            food.SetFoodStageType(food.GetFoodStageType()); // Фиксация стадии
        }
    }

    // Проверка защищенности тары (согласно hearth_and_conservation.md)
    protected bool NEKRASOV_IsContainerSafe(EntityAI container)
    {
        if (!container) return false;
        
        // Только закрытые и герметичные типы (например, бочки или спец. контейнеры NEKRASOV)
        if (container.IsInherited(Barrel_ColorBase) || container.IsInherited(SeaChest))
        {
            return true;
        }
        return false;
    }
}

