/**
 * NEKRASOV_Radio_Infrastructure.c
 * Реестр узлов связи и частотных диапазонов.
 */

class NEKRASOV_Radio_Infrastructure
{
    // ТИПЫ СИГНАЛОВ
    static const string SIGNAL_CIVILIAN = "ГРАЖДАНСКИЙ";
    static const string SIGNAL_MILITARY = "ВОЕННЫЙ";
    static const string SIGNAL_EMERGENCY = "МЧС";

    // СЕТКА ЧАСТОТ (Связь с Прошлым)
    static float GET_RESERVED_FREQUENCY()
    {
        // Некрасов помнит старые частоты из 1994/2001 годов
        return 446.0; // МГц
    }

    // ЛОГИКА ПРОВЕРКИ ОБОРУДОВАНИЯ
    static bool IS_STATION_COMPATIBLE(string station_type)
    {
        // Проверка на совместимость с Золотым Стандартом связи
        if (station_type == "R123" || station_type == "FIELD_RADIO")
            return true;
            
        return false;
    }
}
