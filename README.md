
сборка:
    mkdir build
    cd build
    cmake ..
    make

в корневом каталоге поместил скрипт "run"
    он запускает приёмник в отдельном окне, его надо будет закрыть по Esc после окончания выполнения передатчика;
    далее запускается передатчик, он сам закончит выполнение;
    формируются журналы
        log__sent       передатчик
        log__recv       приёмник -  как есть
        log__Received   приёмник -  только строки с "Received:"
        log__Processed  приёмник -  только строки с "Processed:"

пакеты наполняются кириллицей в UTF-8, модуль Processed (2-поток приёиника)
печатает начало и окончание пакетов.

Увы, в тестах навыка нет.
Судя по соотношению задержек 10/15, это приводит к 30% потерь.

На задание ушло дня 4, в часах 8+8+2+6=24 :)
