/*
    CHAT LOGIC: NEKRASOV_VOICE_DIST_V1
    INDEX: PRT-COMM-300.DIST
    STATUS: INITIALIZING
    LOGIC: Акустика (15м) / Радио (Global)
*/

class Svyaznoy_Chat_Logic
{
    static float ACOUSTIC_RANGE = 15.0; // Радиус живого голоса

    // Основной метод отправки сообщения
    static void SendMessage(PlayerBase sender, string text, bool isRadioActive)
    {
        float dist = vector.Distance(sender.GetPosition(), GetGame().GetPlayer().GetPosition());

        if (dist <= ACOUSTIC_RANGE)
        {
            // Ближний бой/Разговор: Слышно всех в радиусе 15м
            SendToLocalChat(sender, text);
        }
        else if (isRadioActive)
        {
            // Дальняя связь: Только если рация включена у обоих
            SendToRadioChat(sender, text);
        }
        else
        {
            // Вне зоны слышимости и без рации - тишина
            Print("[ЗАС-300] Сигнал потерян. Слишком далеко для голоса, рация выключена.");
        }
    }

    static void SendToLocalChat(PlayerBase sender, string text)
    {
        string prefix = "[Связной]: ";
        // Логика вывода сообщения в локальный текстовый чат
    }

    static void SendToRadioChat(PlayerBase sender, string text)
    {
        string prefix = "[Связной/Радио]: ";
        // Логика вывода сообщения через активную частоту рации
    }
}
