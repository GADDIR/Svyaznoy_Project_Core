// Модуль №73: Боевая Рефлексия (Николай 1923 / Банов 2021)
modded class PlayerBase
{
    // Триггер на получение урона персонажем
    override bool EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int componentIdx, string dmgZone, string skeletonComponent, float speedCoef)
    {
        bool result = super.EEHitBy(damageResult, damageType, source, componentIdx, skeletonComponent, speedCoef);

        // Вероятность срабатывания рефлексии (чтобы не кричал при каждом попадании)
        if (Math.RandomFloat01() < 0.4) 
        {
            NEKRASOV_Combat_Thought(true); // true - получили урон
        }
        return result;
    }

    void NEKRASOV_Combat_Thought(bool isWounded)
    {
        float nikolayWeight = GetMemoryFocus().GetWeight(1923);
        float banovWeight = GetMemoryFocus().GetWeight(2021);

        if (nikolayWeight > banovWeight)
        {
            // Голос Николая 1923
            TStringArray phrases1923 = {"Зубы сцепи!", "Кровь за кровь.", "Не посрамим землю!", "Смерти нет, есть долг."};
            SendToMumble(phrases1923.GetRandomElement());
        }
        else
        {
            // Голос Банова 2021
            TStringArray phrases2021 = {"Черт! За что?!", "Надо сваливать...", "Адреналин зашкаливает.", "Только не снова..."};
            SendToMumble(phrases2021.GetRandomElement());
        }
    }
}

