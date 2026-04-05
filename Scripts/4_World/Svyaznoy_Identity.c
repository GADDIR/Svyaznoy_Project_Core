modded class ExpansionAIBase // Модифицируем класс бота из Expansion AI
{
    override void OnEntityAIAdded()
    {
        super.OnEntityAIAdded();

        // Проверяем, что это наш персонаж (например, по пресету в конфиге сервера)
        // Если хотим, чтобы ВООБЩЕ ВСЕ боты стали Алексеем Николаевичем, убираем 'if'
        if (this.GetDisplayName() == "Svyaznoy") 
        {
            ApplyNekrasovHardcodedSettings();
        }
    }

    void ApplyNekrasovHardcodedSettings()
    {
        // 1. Жёстко задаем имя
        this.SetPlayerName("Алексей Николаевич (Связной)");

        // 2. Устанавливаем лицо (Mirek — идеальный вариант)
        // Мы запрещаем игре выбирать рандомную голову
        this.SetAllowRandomHead(false);
        
        // 3. Экипировка (только стандартные вещи DayZ)
        // Очищаем то, что выдал сервер по умолчанию
        GetInventory().DropAllItems(); 

        // Выдаем сет Алексея Николаевича
        GetInventory().CreateInInventory("TTsKOJacket_Camo");
        GetInventory().CreateInInventory("TTsKOPants_Camo");
        GetInventory().CreateInInventory("CombatBoots_Black");
        GetInventory().CreateInInventory("HighCapacityVest_Black");
        
        // Предмет-маркер (Рация)
        EntityAI radio = GetInventory().CreateInInventory("PersonalRadio");
        if (radio) radio.GetInventory().CreateInInventory("Battery9V");
    }
}
