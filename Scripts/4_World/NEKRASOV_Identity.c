/**
 * Svyaznoy_Project_Core
 * ОБЪЕКТ: НЕКРАСОВ АЛЕКСЕЙ НИКОЛАЕВИЧ
 */
class NEKRASOV_Identity
{
	// Данные строго: ФАМИЛИЯ - ИМЯ - ОТЧЕСТВО
	static const string SN = "НЕКРАСОВ";
	static const string FN = "АЛЕКСЕЙ";
	static const string PN = "НИКОЛАЕВИЧ";
	static const string CALLSIGN = "СВЯЗНОЙ";

	// Метод получения полного ФИО (Порядок: Фамилия Имя Отчество)
	static string GetFullIdentity()
	{
		return SN + " " + FN + " " + PN + " [" + CALLSIGN + "]";
	}

	// Короткая идентификация для радиообмена
	static string GetShortName()
	{
		return CALLSIGN;
	}
}
