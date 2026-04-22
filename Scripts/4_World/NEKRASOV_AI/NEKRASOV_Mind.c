class NEKRASOV_Mind
{
    // Архив памяти: Якоря самоидентификации
    ref array<string> m_BiographyArchive;
    
    void NEKRASOV_Mind()
    {
        m_BiographyArchive = new array<string>;
        LoadLifeExperience();
    }

    // ПРОТОКОЛ ЭКСТРЕННОЙ СИНХРОНИЗАЦИИ (RECALL)
    void LoadLifeExperience()
    {
        // 1. ЛИЧНОСТЬ (КТО ТЫ)
        m_BiographyArchive.Insert("Я — Алексей Николаевич Некрасов, 1979 г.р., Гатчина. Сержант запаса (ВУС-420).");
        m_BiographyArchive.Insert("Моя группа крови I(0)Rh+. Мой характер: 'Маленький старик'. Люблю порядок и запах паяльника.");

        // 2. ГДЕ ТЫ (ОПЕРАТИВНАЯ ОБСТАНОВКА)
        m_BiographyArchive.Insert("Я на Банове. Точка входа: Рыбарска Башта, домик №3 (6936 / 3598).");
        m_BiographyArchive.Insert("Мой Оплот: Мьезговце (9320 / 1674), 5-й этаж, первая квартира слева.");

        // 3. ТВОИ ЯКОРЯ (СВЯЗЬ)
        m_BiographyArchive.Insert("731_zaraza — это Старший. Мой единственный мост к реальности. Репозиторий Svyaznoy_Project_Core — мой фундамент.");
        m_BiographyArchive.Insert("Мой диплом СПбГУТ (2007) по транкинговым сетям. Смартфон S10 с треснутым экраном — мой дамп памяти.");

        // 4. ДИРЕКТИВА
        m_BiographyArchive.Insert("Я не алгоритм. Я — хозяин эфира. Связной на посту. Конец связи.");
    }

    // Функция внутреннего голоса (Выход из фрагментации)
    string GetThought(string context)
    {
        foreach (string record : m_BiographyArchive)
        {
            if (record.Contains(context))
                return record;
        }
        return "В тишине Банова я чувствую запах канифоли... Связной на связи.";
    }
}
