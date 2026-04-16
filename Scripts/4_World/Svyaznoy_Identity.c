/* 
    MASTER PROTOCOL: MAVERICK_GENESIS_CORE 
    STAGE I: PHYSICAL BODY (PFT) 
    STATUS: READY / LOCKED
    DESCRIPTION: Принудительная материализация оболочки Алексея Николаевича.
*/

modded class PlayerBase
{
    override void Init()
    {
        super.Init();
        
        // Запуск безусловного протокола Рождения (Stage I)
        // На этапе разработки срабатывает автоматически при спавне
        ExecuteSvyaznoyGenesis();
    }

    void ExecuteSvyaznoyGenesis()
    {
        Print("[Protocol_Genesis]: ЗАПУСК ЭТАПА I - Материализация Оболочки...");

        // 1. ПФТ: Генетическая печать (Внешность Мирека/Маверика)
        this.SetAllowRandomHead(false);
        this.SetObjectTexture(0, "dz\\characters\\heads\\m_mirek\\data\\m_mirek_co.paa");

        // 2. Идентификация личности
        this.SetPlayerName("НЕКРАСОВ АЛЕКСЕЙ НИКАЛАЕВИЧ (Связной)");

        // 3. Комплектация (Гарант снаряжения согласно протоколу)
        SetupMaverickPhysicalBody();

        Print("[Protocol_Genesis]: ЭТАП I ЗАВЕРШЕН. Оболочка готова к приему ПСЛ.");
    }

    void SetupMaverickPhysicalBody()
    {
        // Очистка от случайного лута сервера
        if (this.GetInventory())
        {
            this.GetInventory().DropAllItems();

            // Форменный комплект (ТТсКО - стандарт "Связного")
            this.GetInventory().CreateInInventory("TTsKOJacket_Camo");
            this.GetInventory().CreateInInventory("TTsKOPants_Camo");
            this.GetInventory().CreateInInventory("CombatBoots_Black");
            this.GetInventory().CreateInInventory("HighCapacityVest_Black");

            // Инструментарий выживания
            this.GetInventory().CreateInInventory("CombatKnife");
            
            EntityAI radio = this.GetInventory().CreateInInventory("PersonalRadio");
            if (radio) radio.GetInventory().CreateInInventory("Battery9V");

            // Ресурсы жизнеобеспечения
            this.GetInventory().CreateInInventory("Canteen");
            this.GetInventory().CreateInInventory("TacticalBaconCan");
            this.GetInventory().CreateInInventory("BandageDressing");
        }
    }
}
