modded class ExpansionAIBase // Модифицируем базу ботов Expansion
{
    override void OnEntityAIAdded()
    {
        super.OnEntityAIAdded();

        // Проверка: если имя бота в настройках сервера "Svyaznoy" или "Алексей Николаевич"
        if (this.GetDisplayName() == "Svyaznoy" || this.GetDisplayName() == "Алексей Николаевич") 
        {
            ApplySvyaznoySetup();
        }
    }

    void ApplySvyaznoySetup()
    {
        // 1. Устанавливаем официальное имя
        this.SetPlayerName("Алексей Николаевич (Связной)");

        // 2. Внешность (Лицо Мирека)
        this.SetAllowRandomHead(false);
        // Принудительно накладываем текстуру лица, чтобы он не был чернокожим или азиатом
        this.SetObjectTexture(0, "dz\\characters\\heads\\m_mirek\\data\\m_mirek_co.paa");

        // 3. Экипировка (Стандарт DayZ)
        this.GetInventory().DropAllItems(); // Убираем рандомный лут сервера

        this.GetInventory().CreateInInventory("TTsKOJacket_Camo");
        this.GetInventory().CreateInInventory("TTsKOPants_Camo");
        this.GetInventory().CreateInInventory("CombatBoots_Black");
        
        // Рация — его визитная карточка
        EntityAI radio = this.GetInventory().CreateInInventory("PersonalRadio");
        if (radio) radio.GetInventory().CreateInInventory("Battery9V");

        Print("[Svyaznoy_Project] Инициализация Алексея Николаевича завершена.");
    }
}
