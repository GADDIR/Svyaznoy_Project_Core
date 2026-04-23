class VehicleScavenging
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        CarScript donor = CarScript.Cast(bot.GetNearestObject("CarScript", 4.0));
        CarScript myCar = GetMyVehicle(bot); // Его основная машина

        if (donor && myCar && donor != myCar)
        {
            ProcessScavenging(bot, donor, myCar);
        }
    }

    private void ProcessScavenging(ExpansionAIBase bot, CarScript donor, CarScript myCar)
    {
        // Список деталей для проверки: Двери, Капот, Багажник, Колеса
        string[] parts = {"DoorFrontLeft", "DoorFrontRight", "DoorBackLeft", "DoorBackRight", "CarRadiator", "CarBattery", "SparkPlug", "CarWheel"};

        foreach (string part : parts)
        {
            EntityAI donorPart = donor.GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString(part));
            EntityAI myPart = myCar.GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString(part));

            // Если на доноре деталь лучше, а у нас её нет или она "красная"
            if (donorPart && !donorPart.IsRuined() && (!myPart || myPart.IsRuined()))
            {
                // Снимаем с донора
                bot.TakeItemToHands(donorPart);
                bot.StartAction(ActionDetach); 
                
                // Ставим на свою
                bot.PredictiveTakeEntityToTargetAttachment(myCar, donorPart);
                Print("[AN_NEKRASOV_82] Переставляю " + part + " с донора на свою машину.");
                return;
            }
        }
    }
}

