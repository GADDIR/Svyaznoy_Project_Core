# Протокол «Первая Искра» (Ignition & Consequences)

## 1. Визуальная модель принятия решений
```mermaid
graph TD
    %% Процесс розжига
    subgraph Ignition [ИНИЦИАЦИЯ: Шанс 30-50%]
    Start[Hand Drill Kit] --> Try{Попытка}
    Try -- "Fail" --> Pause[Пауза 5с + LookAround360]
    Pause --> Try
    Try -- "Success" --> Fire[СТАБИЛЬНОЕ ПЛАМЯ]
    end

    %% Управление угрозами
    subgraph Threats [ДЕМАКСИРОВКА]
    Fire --> Night[НОЧЬ: Световой индекс x10]
    Fire --> Day[ДЕНЬ: Дымовой след]
    Night --> Stealth[Низины / Закрытые окна]
    Day --> Speed[Вскипятил - Потушил]
    end

    %% Рабочая зона
    subgraph Workshop [РИТУАЛ ЦЕХА]
    Fire --> Sterilize[Обжиг инструментов]
    Fire --> Boil[Кипячение воды]
    Fire --> Dry[Сушка ТТсКО]
    end

    %% Ликвидация
    Workshop --> Cleanup[ТУШЕНИЕ: Вода/Песок]
    Cleanup --> Invisible[СЛЕДОВ НЕТ]

    style Night fill:#1a1a2e,stroke:#fff,color:#fff
    style Fire fill:#ff4500,stroke:#333,color:#fff
    style Invisible fill:#2e8b57,stroke:#000,color:#fff
