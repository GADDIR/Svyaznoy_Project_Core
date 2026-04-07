/*
    Project: Svyaznoy_Project_Core
    Entity: Alexey Nikolaevich Nekrasov (Maverick)
    Role: Radio Operator (ZAS)
    Status: Stage I (Birth Protocol)
*/

modded class PlayerBase
{
    override void StartingEquipSetup(bool is_new_player)
    {
        super.StartingEquipSetup(is_new_player);

        // 1. Идентификация (Проверка SteamID Алексея)
        string player_uid = GetIdentity().GetId();
        if (player_uid == "76561198067049765") 
        {
            // Очистка дефолтного лута
            RemoveAllItems();

            // 2. Одежда (Комплект ТТсКО + Берцы)
            GetInventory().CreateInInventory("TTsKOJacket_Camo");
            GetInventory().CreateInInventory("TTsKOPants_Camo");
            GetInventory().CreateInInventory("CombatBoots_Black");
            GetInventory().CreateInInventory("HighCapacityVest_Black");

            // 3. Спец-пакет ЗАС (Инвентарь)
            EntityAI knife = GetInventory().CreateInInventory("CombatKnife");
            EntityAI canteen = GetInventory().CreateInInventory("Canteen");
            EntityAI food = GetInventory().CreateInInventory("TacticalBaconCan");
            EntityAI medical = GetInventory().CreateInInventory("BandageDressing");

            // 4. Связь (Рация + автоматическая вставка батареи)
            EntityAI radio = GetInventory().CreateInInventory("PersonalRadio");
            if (radio)
            {
                radio.GetInventory().CreateAttachment("Battery9V");
            }

            Print("[Svyaznoy_Project]: Nekrasov A.N. materialization complete. Radio ZAS active.");
        }
    }

    // Здесь будет внедрен Этап III (Сенсорика / Raycast)
}
