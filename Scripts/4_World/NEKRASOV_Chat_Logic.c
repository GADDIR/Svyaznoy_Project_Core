/*
    ПРОЕКТ: СВЯЗНОЙ (Svyaznoy_Project_Core)
    ОБЪЕКТ:  NEKRASOV_Chat_Logic
    ВЕРСИЯ: 1.2 [ACOUSTIC & RADIO V2]
    ИНДЕКС: PRT-COMM-300.DIST
*/

class NEKRASOV_Chat_Logic
{
    private static string m_NamePrefix = "[Алексей Николаевич]: ";
    private static string m_RadioPrefix = "[Связной/Радио]: ";
    static float ACOUSTIC_RANGE = 15.0; // Радиус живого голоса по догмату

    // --- 🗣️ ГЛАВНЫЙ МЕТОД ТРАНСЛЯЦИИ ---
    static void SendMessage(PlayerBase sender, string text, bool forceRadio = false)
    {
        if (text == "") return;

        // 1. ПРОВЕРКА ДИСТАНЦИИ (АКУСТИКА)
        // Считаем дистанцию до ближайшего игрока-наблюдателя (бактерии)
        float dist = 999.0;
        PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
        if (localPlayer) dist = vector.Distance(sender.GetPosition(), localPlayer.GetPosition());

        if (dist <= ACOUSTIC_RANGE)
        {
            // Живой голос: слышно в радиусе 15 метров
            SendToLocalChat(sender, text);
        }
        else
        {
            // 2. ПРОВЕРКА РАЦИИ (ДАЛЬНЯЯ СВЯЗЬ)
            if (HasWorkingRadio(sender))
            {
                SendToRadioChat(sender, text);
            }
            else
            {
                // Вне зоны слышимости и без питания - тишина в эфире
                Print("[ЗАС-300] Сигнал потерян. " + dist + "м — слишком далеко для голоса, рация мертва.");
            }
        }
    }

    // --- 📡 ЛОКАЛЬНЫЙ ВЫВОД (АКУСТИКА) ---
    static void SendToLocalChat(PlayerBase sender, string text)
    {
        string fullMessage = m_NamePrefix + text;
        sender.MessageAction(fullMessage); // Сообщение над головой / в левом углу
        Print("[СВЯЗНОЙ/АКУСТИКА]: " + fullMessage);
    }

    // --- 📻 РАДИО-ЭФИР (GLOBAL) ---
    static void SendToRadioChat(PlayerBase sender, string text)
    {
        string fullMessage = m_RadioPrefix + text;
        // Отправка в глобальный чат синим цветом (имитация частоты)
        GetGame().Chat(fullMessage, "colorSkyBlue"); 
        Print("[СВЯЗНОЙ/ЗАС]: " + fullMessage);
    }

    // --- 🔋 ТЕХОСМОТР СВЯЗИ ---
    static bool HasWorkingRadio(PlayerBase self)
    {
        ItemBase radio = ItemBase.Cast(self.GetInventory().FindEntityInInventory("PersonalRadio"));
        if (radio)
        {
            ComponentEnergyManager energy = radio.GetEnergyManager();
            // Рация должна быть включена и иметь заряд
            if (energy && energy.CanConsumeEnergy(0.01)) 
            {
                return true;
            }
        }
        return false;
    }
}
