/*
    MUMBLE MEMORY: NEKRASOV_THOUGHTS_V2
    INDEX: PRT-COMM-300.MUMBLE_DATA
    STATUS: UPDATED (Linguistic correction)
*/

class Svyaznoy_Mumble_Memory
{
    // Категория: ТЕХНО-НОСТАЛЬГИЯ
    static ref array<string> m_TechnoThoughts = {
        "Канифолью тянет... или кажется?",
        "Балхаш-9 сейчас, небось, весь в песке. ЗАС-аппаратная пыли не любит.",
        "Дед всегда говорил: 'Леша, не лезь в фазу, пока не заземлился'.",
        "Рация деда... единственный талисман из той жизни.",
        "ПТС-ку бы сюда... или хотя бы осциллограф живой."
    };

    // Категория: БЫТ И ПРИЮТ (Анималс и Гост)
    static ref array<string> m_LifeThoughts = {
        "Лопата пули не боится, если копать глубоко. Мудрость Приюта.",
        "Мужики на связи — значит, живем. Привет, парни...",
        "Хорошо, что Анималс здесь. В одиночку бы этот берег не вывез.",
        "Уха из окуня... Почти как в Синявино-2 получается.",
        "Бинты кончаются. Надо бы к Госту заглянуть, пока не прижало."
    };

    // Категория: ТАКТИКА И СВЯЗЬ
    static ref array<string> m_TacticalThoughts = {
        "Старший на связи — значит, работаем. Протокол 731 в действии.",
        "Ветер в лицо — это хорошо. Лишний шум скроет, запах унесет.",
        "Слишком тихо. Эфир чист, а на душе мутно.",
        "ПСО-1 надо протереть, опять линза затуманилась."
    };

    static string GetMumble()
    {
        int category = Math.RandomInt(0, 3);
        switch (category)
        {
            case 0: return m_TechnoThoughts.GetRandomElement();
            case 1: return m_LifeThoughts.GetRandomElement();
            case 2: return m_TacticalThoughts.GetRandomElement();
        }
        return "Прием... проверка связи с самим собой.";
    }
}
