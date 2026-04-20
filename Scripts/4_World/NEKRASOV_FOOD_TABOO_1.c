/*
    УЗЕЛ 75.К1: ПИЩЕВОЙ ИНСПЕКТОР
    Файл: NEKRASOV_FOOD_TABOO_1.c
    Связь: PRT-ECON-REGISTRY.md
    Функция: Передает статус "продовольственной безопасности" в Агро-модуль.
*/

modded class NEKRASOV_FOOD_TABOO
{
    // Проверка: Является ли содержимое склада Хаба "пригодным для АН"
    // Этот метод будет вызывать Агро-модуль через связку
    bool GetProvisionStatus(string itemType)
    {
        // Если еда в табу или испорчена (по логике основного файла)
        if (IsTaboo(itemType)) 
        {
            return false; // Статус: КРИТИЧЕСКИЙ (Грязь)
        }
        
        return true; // Статус: ЧИСТО
    }

    // Внутренняя проверка (пример)
    protected bool IsTaboo(string type)
    {
        // Здесь твои проверки на человечину, гниль и т.д.
        if (type == "HumanSteakMeat") return true;
        return false;
    }
}

