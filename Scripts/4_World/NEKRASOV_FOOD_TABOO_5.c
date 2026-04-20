/*
    УЗЕЛ 75.К5: ОГОНЬ И РЕСУРСЫ (LOG-FIRE)
    Файл: NEKRASOV_FOOD_TABOO_5.c
    Связь: resources_and_fire.md
    Назначение: Контроль качества топлива и процесса термической обработки.
*/

modded class NEKRASOV_FOOD_TABOO
{
    // Типы топлива из resources_and_fire.md
    protected ref array<string> m_NEKRASOV_HighQualityFuel;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_HighQualityFuel = new array<string>;
        
        // Регистрация "Чистого" топлива для Очага
        m_NEKRASOV_HighQualityFuel.Insert("WoodenStick");
        m_NEKRASOV_HighQualityFuel.Insert("Firewood");
    }

    // Логика: Проверка качества огня для "Завета чистоты"
    // Еда, приготовленная на мусоре (тряпки, пластик), может считаться "Грязной"
    bool NEKRASOV_IsFirePure(FireplaceBase fireplace)
    {
        if (!fireplace || !fireplace.IsBurning()) return false;

        // Если в костре есть "грязное" топливо согласно протоколу
        // (Здесь можно добавить проверку содержимого костра)
        return true;
    }

    // Техпроцесс: Влияние типа дерева на копчение
    void NEKRASOV_ApplyFuelBonus(Edible_Base food, string fuelType)
    {
        // Согласно resources_and_fire.md: 
        // Дуб дает дольшее хранение, береза — быстрый жар.
        if (fuelType == "OakLog")
        {
            // Увеличиваем индекс консервации из Узла 4
        }
    }

    // Протокол "Трут и Розжиг": Шанс успеха розжига зависит от состояния личности
    float NEKRASOV_GetIgnitionChance(ItemBase tinder)
    {
        if (tinder.IsInherited(BirchBark)) return 1.0; // Береста — приоритет по лору
        return 0.5;
    }
}

