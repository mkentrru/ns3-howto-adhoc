
# Что это?

<!-- TODO: дополнить -->
Это небольшое собрание мыслей, которые возникли по ходу попытки ~~*с наскока*~~ реализовать ad-hoc сеть в `ns3`. Верю, что прослушивание этих мыслей поможет вкатиться 

# Немного про `ns3`

По большому счёту, `ns3` это набор `C++` классов (*модулей*), которые реализовывают что-то похожее на настроящее сетевое взаимодействие и инструменты для удобного использования этих классов. 

> Суть в том, что всё это добро компилируется и нужно быть осторожным с компилятором `C++`: смотреть на реализацию того, с чем вы работаете (*особенно с контейнерами от `ns3`*). Если компилятор не ругается, это не значит, что он соберёт всё так, как вы хотите.

# Где это делать?

Рекомендую `WSL Debian` и `VSCode`

# С чего начать - туториал от `ns3`

В первую очередь следует вдумчиво пройти туториал от `ns3`:
[3.42-tutorial](https://www.nsnam.org/docs/release/3.42/tutorial/html/quick-start.html)

> Рекомендую скачивать `ns3` через архив исходников: `.tar.bz2`

После этого вы узнаете минимальный набор механик, в том числе:
- как собираться c `CMake` в директории `ns3`
- как пользоваться системой логов
- основные компоненты: `ns3::Node`, `ns3::NetDevice`, `ns3::Application`


# Как компилироваться и отлаживаться

Мне не нравится компилироваться в папке `scratch/` с помощью `CMake` поэтому существует эта секция, в которой рассказывается, как использовать `ns3` в качестве статической либы. 

> Все примеры в этом проекте собираются со статической либой `ns3`.

## 1. Подготовить сборку

```sh
./ns3 configure --cxx-standard 20 -d debug --enable-static\
    --enable-asserts --enable-logs\
    --disable-examples --disable-tests --disable-gtk\
    --disable-python-bindings\
    --output-directory static-build\
    --disable-modules "bridge;csma;buildings;uan;point-to-point;fd-net-device;lr-wpan;virtual-net-device;traffic-control;topology-read;config-store"
```

Параметры:
```
    --enable-asserts      Enable the asserts regardless of the compile mode
    --disable-examples    Disable the ns-3 examples
    --disable-gtk         Disable GTK support in ConfigStore
    --enable-logs         Enable the logs regardless of the compile mode
    --disable-python-bindings   Disable python bindings
    --disable-tests       Disable the ns-3 tests
    --enable-static       Build a single static library with all ns-3
    --output-directory    Directory to store build artifacts
```

Список, модулей, которые должны собраться для этого проекта:
```sh
Modules configured to be built:
antenna                   core                      energy
mobility                  network                   propagation
spectrum                  stats                     wifi
```


## 2. Собрать `ns3`

```sh
./ns3 build
```
Вы получите две важные директории:
```
ns-3.42/static-build/
    include  - заголовки ns3
    lib      - .so-шки и статическая либа ns3
```

## 3. Собрать документацию `Doxygen`

> Если не собрали в ходе туториала

С помощью команды собрать документацию:
```sh
./ns3 docs doxygen-no-build
```

В результате получите `html` документацию: 
`ns-3.42/doc/html/index.html`

> Порой это единственный верный способ понять, что происходит под капотом `ns3`

> Если работаете в `WSL`, директорию `html` можно открыть прямо на хосте. У меня, с образом `Debian` путь до `index.html`: `file://///wsl.localhost/Debian/home/user/workspace/ns-allinone-3.42/ns-3.42/doc/html/index.html`

> Документацию можно и просто выгрузить на хост

Также рекомендую заменить файл `ns-3.42/doc/html/doxygen.css` на файл из проекта `files/doxygen-style/doxygen.css`. Он немного фиксит неочевидные цветовые решения в документации.

## 4. Попробовать собраться со статической либой `ns3`
В директории `static-example` лежит минимальный проект, собираемый с помощью `make`

Перед сборкой нужно обновить файл `./top.mk` и указать корректный путь до директории с собранным на прошлом шаге `ns3`: `PATH_NS3_STATIC_BUILD_DIR`

Сборка:
```sh
user@w:~/workspace/ns3-projects/ns3-howto-adhoc/static-example
 ~~~> make
Creating directories
make[1]: Entering directory '/home/user/workspace/ns3-projects/ns3-howto-adhoc/static-example'
Compiling: src/static-example.cpp -> build/static-example.o
g++  -Wextra -g -static  -I include/ -I /usr/local/include -I /home/user/workspace/ns-allinone-3.42/ns-3.42/static-build/include -MP -MMD -c src/static-example.cpp -o build/static-example.o
Linking: build/bin/static-example
g++ build/static-example.o -o build/bin/static-example -L/home/user/workspace/ns-allinone-3.42/ns-3.42/static-build/lib -l:libns3.42-static-default.a
Making symlink: static-example -> build/bin/static-example
make[1]: Leaving directory '/home/user/workspace/ns3-projects/ns3-howto-adhoc/static-example'
```
Запуск:
```sh
user@w:~/workspace/ns3-projects/ns3-howto-adhoc/static-example
 ~~~> ./static-example
testing statically linked with ns-3
```

## 5. Как отлаживаться в `VSCode`

В файле `.vscode/launch.json` лежат конфиграции запуска и отладки экспериментов из этого проекта. Одним из ключевых параметров является `preLaunchTask`, который ссылается на задачи (*как правило, сборку*) в `.vscode/tasks.json`, выполняемые перед запуском.

> В файле `.vscode/c_cpp_properties.json` не забудьте указать путь до `ns-3.42/static-build/include/` в `includePath`, чтобы `VSCode` подсасывал нужные заголовочные файлы.

Так, например для запуска `static-example` нужно перейти на вкладку `Run and debug`, выбрать соответствующую конфигурацию запукса и запустить:

![vscode-debug](./files/img/vscode-debug.png)

# Первый эксперимент и основые положения данного проекта

## Небольшое запугивание

Надеюсь, вы внимательно прошли туториал и имеете представление об основных компонентах симуляции `ns3`. На всякий случай напомню ключевой момент, который нужно держать в голове:
> `ns3` - библиотека, в которой реализованы модели сетевого взаимодействия и инструменты для построения симуляции. Важно, что симуляция основана на очереди событий и не является "real-type" симулятором. По факту любое сетевое взаимодействие - перекладывание буферов из этого объекта в другой. То, насколько такое перекладывание соответствует реальному положению вещей зависит от глубины проработки используемой модели. Далее для симуляции `adhoc` сетей используется модель `wifi`: [Документация](https://www.nsnam.org/docs/release/3.42/models/html/wifi.html). Данная модель проработана довольно глубоко и является очень (~~*даже слишком*~~) модульной, что продиктовано стандартом `wifi`: `ieee 802.11`.
 
Для `ieee 802.11` определены несколько стандартов, где каждый последующий - некоторое улучшие или развитие предыдущего. При реализации `adhoc` сети нужно выбрать параметры, которые влияют на то, как узлы будут "передавать" информацию. Это важно потому, что стандарт `ieee 802.11` не предусматривает дуплексный режим передачи и его частичная реализация в `ns3` тоже 🙃. Это значит, что сетевой интерфейс узла [не может одновременно передавать и получать информацию](https://en.wikipedia.org/wiki/Duplex_(telecommunications)#Half_duplex):

![half-duplex](files/img/HalfDuplex.jpg)

А когда узлы пытаются вещать в одно и то же время, что для `ns3` частая ситуация *(так как симуляция основана на очереди событий, привязанных к точному времени)*, начинается сущий кошмар, если не понимать, что проиходит. **Но об этом далее**.

## Про `IP Stack` и `Helper`-ов

Один из важных вопросов, на который вы должны ответить в начале создания симуляции: нужен ли мне `IP` стек *(и выше по OSI)* или хватит отправки фреймов? Для экспериментов в этом проекте ответ: `IP` не нужен, потому тут не используется.

> Если вы решили использовать `IP`, то скорее всего из примеров `ns3` вам присмотрелось использование `InternetStackHelper`. Для исключения ненужных непонятностей, которые возникнут в ходе разработки симуляции, рекомендую ознокамливаться с тем, что делает очередной `Helper`. Так, например, `InternetStackHelper` подключает несколько механизмов, которые, вероятно помешают вашему `adhoc`:
> - реализация `ARP`
> - поддержка `ICMP`
> - `TrafficControlLayer`
> - механизмы маршрутизации `IP`

## Первый эксперимент: `basic-broadcast`

В этом эксперименте реализована минимальная настройка симуляции:
1. Созданы узлы
```cpp
// Create nodes:
ns3::NodeContainer c;
c.Create(numNodes);
```
2. На узлы установлено по одному `Wifi` интерфейсу: `WifiNetDevice`
```cpp
// Install WifiNetDevice to nodes and configure Pcap log:
ns3::NetDeviceContainer c_devs = InstallSimpleWifiDevice(c, true);
```
3. Для интерфейсов настроенно журналирование полученных пакетов в директорию `pcaps`
4. Установлено расположение узлов в пространстве
```cpp
// Set nodes position around circle
DistributeAroundCircle(c, radius, velocity);
```
5. На узлы установлено приложение `BasicApp` из `basic-broadcast-app.h`
```cpp
// Install BasicApp to nodes
BasicAppInstaller basicAppHelper = BasicAppInstaller();
ns3::ApplicationContainer apps = basicAppHelper.Install(c);
```
6. В приложении `BasicApp` узла `#0` запланирована отправка тестового сообщения:
```cpp
// Get BasicApp installed to Node#0
ns3::Ptr<BasicApp> node_0_app = ns3::DynamicCast<BasicApp>(apps.Get(0));
// Schedule broadcast with App at Node#0
node_0_app->ScheduleTestBroadcast();
```
> Если вы ещё плаваете в `ns3`, то рекомендую посмотреть все исходники, которые лежат в проекте по описаным выше шагам.

### Базовая настройка `wifi`
Базовая настрока `wifi` реализована в функции:
```cpp
ns3::NetDeviceContainer
InstallSimpleWifiDevice(ns3::NodeContainer nodes, bool enable_pcap=true);
```

Чтобы понимать ключевые компоненты модели `wifi` в `ns3` нужно ознакомиться с её [Архитектурой](https://www.nsnam.org/docs/release/3.42/models/html/wifi-design.html#wifi-architecture):

![WifiArch](files/img/WifiArchitecture.png)







<!-- TODO: clean spaces -->

Ключевые элементы модели "сверху-вниз":
1. `MAC high` - высокоуровневые операции, время выполнения которых не важно
> Это, например, отправка [`Beacon frame`](https://en.wikipedia.org/wiki/Beacon_frame), когда `wifi` интерфейсы работают в режиме инфрастуктуры `Access Point` (`AP` - точка доступа) -> `non-AP Station` (`STA` - потребитель). 

> Однако для `adhoc` таких функций нет и узлы работают в режиме `Independent Basic Service Set` (`IBSS`), что в `ns3` означает режим `ns3::AdhocWifiMac` при настройке `ns3::WifiMacHelper`.

2. `MAC low` - отвечает за отправку фреймов. В том числе: их сбор (из нескольких), ретрансляцию и прочее.
> **На самом деле является самым важным уровнем**, ибо именно он реализует доступ к каналу передачи, пытаясь исключить коллизии одновременной передачи с помощью [CSMA/CA](https://en.wikipedia.org/wiki/Carrier-sense_multiple_access_with_collision_avoidance).

3. `PHY layer` - "физический" уровень. На данном уровне моделируется получение пакетов и использование энергии на отправку. В `ns3` реализовано два варианта "физического" уровня: `YansWifiPhy` и `SpectrumWifiPhy`. 
> `SpectrumWifiPhy` использует подход глубоко моделирования сигналов для приближения к реальности, которая, как правило, используется для специфических исследований, ибо слишком навороченная.

> `YansWifiPhy` реализует вероятностную модель доставки пакетов, основываясь на выбранных параметрах сетевых интерфейсов и расстоянии между узлами. **Эта модель используется в данном проекте**.

Подробная настройка этих компонентов рассмотрена дальше, но сейчас посмотрим, что нужно для использования `wifi`, в соответствии с [Документацией](https://www.nsnam.org/docs/release/3.42/models/html/wifi-user.html#using-the-wifinetdevice):
1. Выбрать модель `PHY layer`: `SpectrumWifiPhy` или `YansWifiPhy`, что повлияет на выбор физической модели `Phy` и модели канала `Channel`. Для этого проекта выбранна `YansWifiPhy`.
2. Настроить `Channel`, который отвечает за достаку "сигналов" от одного устройства другому. Основная настройка канала: выбор модели потерь (`propagation loss`) и задержки (`propagation delay`) сигнала.
3. Настроить `WifiPhy`, который отвечает за доставку фреймов в соответствии с сигналами от `Channel`. Одна из основных функций `WifiPhy`: решить, будет ли успешно декодирован фрейм с учётом мощности сигнала и шумах. То есть основная настройка `WifiPhy`: выбор модели ошибок (`error rate`), которая рассчитывает вероятность успешного докодирования фрейма по сигналу.
4. Настроить `WifiMac`: выбрать режим работы: инфраструктурный (`AP`->`SPA`) или `adhoc` (`IBSS`). А также выбрать дополнительные фичи версии стандарта `ieee 802.11`.
5. Создать `WifiDevice`: выбрать версию стандарта `ieee 802.11` (`802.11b`, `802.11g`, `802.11a`, `802.11n`, `802.11ac` или `802.11ax`) и алгоритм, реализующий `rate control`.
6. Настроить модель мобильности узлов, которая необходима для расчёта вероятности доставки пакетов (`propagation loss`) на уровне `Channel`.

Выбор модели `PHY layer`, `Channel` и `WifiPhy` реализованы следующими строками:
```cpp
// Configure PHY layer, Channel and WifiPhy
ns3::YansWifiPhyHelper wifiPhy;
ns3::YansWifiChannelHelper wifiChannel = ns3::YansWifiChannelHelper::Default();
wifiPhy.SetChannel(wifiChannel.Create());
```

Настройка `WifiMac`:
```cpp
// Configure WifiMac
ns3::WifiMacHelper wifiMac;
wifiMac.SetType("ns3::AdhocWifiMac");
```

Выбор версии `wifi` и настройка `rate control`:
```cpp
// Configure Wifi, rate control and data mode 
std::string phyMode("DsssRate1Mbps");
ns3::WifiHelper wifi;
wifi.SetStandard(ns3::WIFI_STANDARD_80211b);
wifi.SetRemoteStationManager(
    "ns3::ConstantRateWifiManager",
    "DataMode", ns3::StringValue(phyMode),
    "ControlMode", ns3::StringValue(phyMode));
```

Установка интерфейсов `WifiNetDevice` в узлы:
```cpp
// Install Wi-Fi devices to nodes
ns3::NetDeviceContainer devices_container = wifi.Install(wifiPhy, wifiMac, c);
```

Включение журналирования в `PCAP`:
```cpp
wifiPhy.EnablePcapAll("pcaps/pkts", true);
```

Такая настройка использует множество параметров по-умолчанию и с этим могут возникнуть проблемы, которые рассмотрены далее.

### Что происходит в эксперименте

<!-- TODO: write about it -->
```sh
user@w:~/workspace/ns3-projects/ns3-howto-adhoc/basic-broadcast
 ~~~> ./basic-broadcast
 > 0 // Configured callback for promiscuous mode receive
 > 1 // Configured callback for promiscuous mode receive
 >           +1000ms    /0/Going to broadcast string: hello!
 >           +1000ms    /0/BROADCAST!
 >        +1000.58ms    /1/RECV: hello!
```


# Второй эксперимент: эхо и кастомные пакеты

> Второй эксперимент развивает первый.

Основное отличие - модификация функций приложения из первого эксперимента в 
```cpp
// basic-echo/include/basic-echo-app.h
class EchoApp : public BasicApp
```

## Кастомный заголов пакетов

> Для идентификации отправителя в каждый пакет перед отправкой добавлен дополнительный заголовок. 

Добавление заголовка реализовано в модифицированной функции отправки:
```cpp
// basic-echo/src/basic-echo-app.cpp
bool EchoApp::DoBroadcast(ns3::Ptr<ns3::Packet> data)
{
    BasicHeader pkt_header(GetNodeId(), NextSeq());
    data->AddHeader(pkt_header);
    bool res = p_dev->Send(data, p_dev->GetBroadcast(), 0);
    NS_LOG_INFO(LOG_PREFIX << " >> SEND: " << pkt_header << " :" 
                        << (res ? "OK" : "FAILED"));
    return res;
}
```

Сам по себе заголовок `BasicHeader` является минимальным примером кастомных заголовков `ns3`, в котором определены виртуальные функции базового класса `ns3::Header` 
```cpp
// basic-echo/include/basic-header.h
class BasicHeader : public ns3::Header
{
public:
    // Размер заголовка после сериализации
    //      ~ Размер буфера, в который помещается заголовок
    uint32_t GetSerializedSize() const override;
    // Сериализация заголовка в буфер
    void Serialize(ns3::Buffer::Iterator start) const override;
    // Десиализация заголовка
    //      ~ Выгрузка значений заголовка из буфера
    uint32_t Deserialize(ns3::Buffer::Iterator start) override;
    // Вызывается, для "вывода заголовка в строку" оператором <<
    void Print(std::ostream &os) const override;
};
```

`BasicHeader` использует два `uint32_t` в пакете *(первые 8 байт)* и помещает туда:
 - `ID` узла
 - Номер отправленного пакета: `Sequence Number`

Этот `ID` извлекается при получении пакета в `promiscuous` режиме:
```cpp
// basic-echo/src/basic-echo-app.cpp
bool EchoApp::HandlePromiscReceive(...)
{
    ScheduleTestBroadcast(); // Об этом дальше
    ns3::Ptr<ns3::Packet> pkt_copy = eth_pkt->Copy();
    BasicHeader h;
    pkt_copy->RemoveHeader(h);   
    NS_LOG_INFO(LOG_PREFIX << " << RECV FROM " << h);
    return true;
}
```

А вот так это выглядит в пакете:

![id-at-pcap](files/img/id-at-pcap.png)


## В чём заключается эхо?

В модифицированной функции, обрабатывающей принятые пакеты теперь *планируется тестовый Broadcast*:
```cpp
// basic-echo/src/basic-echo-app.cpp
bool EchoApp::HandlePromiscReceive(...)
{
    ScheduleTestBroadcast(); // Вот тут
```

<!-- TODO: fix coloring -->
Что приводит к такому общению двух узлов:
```
user@w:~/workspace/ns3-projects/ns3-howto-adhoc/basic-echo
 ~~~> ./basic-echo
 >           +1000ms    [ 0]  >> SEND: #0:0 :OK
 >        +1000.64ms    [ 1]  << RECV :#0:0
 >        +2000.64ms    [ 1]  >> SEND: #1:0 :OK
 >        +2001.28ms    [ 0]  << RECV :#1:0
 >        +3001.28ms    [ 0]  >> SEND: #0:1 :OK
 >        +3001.93ms    [ 1]  << RECV :#0:1
 >        +4001.93ms    [ 1]  >> SEND: #1:1 :OK
 >        +4002.57ms    [ 0]  << RECV :#1:1
```

При том, что аналогично первому эксперименту на старте симуляции планируется отправка только одного пакета:

```cpp
// basic-echo/src/basic-echo.cpp
// Get EchoApp installed to Node#0
ns3::Ptr<EchoApp> node_0_app = ns3::DynamicCast<EchoApp>(apps.Get(0));
// Schedule broadcast with App at Node#0
node_0_app->ScheduleTestBroadcast();
```

## Попробуем создать [`broadcast storm`](http://synammic.akhost.ru/cisco/v6/3/#3.1.1.3)

С помощью параметра `n` при вызове из командной строки можно указать число узлов в симуляции, а также радиус `r` их расположения:

```sh
user@w:~/workspace/ns3-projects/ns3-howto-adhoc/basic-echo
 ~~~> ./basic-echo --help
basic-echo.cpp [Program Options] [General Arguments]

Program Options:
    --n:  Number of nodes [2]
    --r:  Radius of distribution [5]
```

Для трёх узлов мы должны наблюдать следующую картину:
 - Первый цикл обмена:
    - Первый пакет от узла `#0`: `#0:1` `(+1 пакет)`
    - Узлы `#1` и `#2` получают `#0:1`
    - `#1` и `#2` отправляют по одному пакету в ответ: `#1:1` и `#2:1` `(+2 пакета)`
    - Итого пакетов: `3`
-  Второй цикл обмена:
   - `#0` получает оба: и `#1:1`, и `#2:1`
   - `#0` отвечает двумя пакетами `#0:2` и `#0:3` `(+2 пакета)`
   - `#1` и `#2` получают друг от друга соответственно `#2:1` и `#1:1`
   - `#1` и `#2` отвечают пакетами `#1:2`, и `#2:2` `(+2 пакета)`
   - Итого пакетов: `4`
-  Третий цикл обмена:
   -  Аналогично второму циклу `#0` получает 2 пакета: `#1:2`, и `#2:2`
   -  И отвечает двумя новыми `#0:4` и `#0:5` `(+2 пакета)`
   -  `#1` и `#2` получают два пакета от `#0`: `#0:2` и `#0:3`
   -  На эти пакеты каждый отвечает по два: `#1:3`, `#1:4`, `#2:3` и `#2:4` `(+4 пакета)`
   -  Также они получили друг от друга по одному пакету: `#1:2`, `#2:2`
   -  Отвечая на них: `#1:5` и `2:5` `(+2 пакета)`
   - Итого пакетов: `8`

Думаю, вы поняли эту деструктивную тенденцию *шторма*, с постоянно растущим числом пакетов. Должно получится, что-то похожее на это:

![storm](files/img/storm.gif)



Однако, при запуске с тремя узлами видно следующее:
```
user@w:~/workspace/ns3-projects/ns3-howto-adhoc/basic-echo
 ~~~> ./basic-echo --n=3
 >           +1000ms    [ 0]  >> SEND: #0:0 :OK
 >        +1000.64ms    [ 1]  << RECV: #0:0
 >        +1000.64ms    [ 2]  << RECV: #0:0
 >        +2000.64ms    [ 1]  >> SEND: #1:0 :OK
 >        +2000.64ms    [ 2]  >> SEND: #2:0 :OK
```

По факту, случилось то, о чём шла речь при обсуждении первого примера: интерфейс `wifi` не может одновременно передавать и получать информацию
> Это не совсем правда, ибо новые стандарты реализуют механизм [`MIMO` (multiple-input and multiple-output)](https://en.wikipedia.org/wiki/MIMO), который используя несколько антенн частично решает этот вопрос

Это отвечает на вопрос, почему узлы `#1` и `#2` не получили пакеты, однако `#0` не получил `#1:0` и `#2:0`. Дело в том, что интерфейсы используют один *физический канал перадачи* и в этой симуляции они начинают вещать буквально одновременно, что приводит к кализии пакетов.

Одним из решений вопроса кализии пакетов является *регулирование доступа* к каналу передачи

> По факту, регулирование осуществляется всеми узлами строго на добровольной основе. То есть, если вы будете всем мешать общаться, `wifi` интерфейсы других устройств ничего вам не сделают ~~сделают что-то только недовольные пользователи~~

# Как регулируется доступ к каналу в *инфраструктурной сети* (`BSS`)

Когда в сети `wifi` есть точка доступа `AP`, с которой общаются узлы, используется `multiple access scheme`, которая отвечает за то, чтобы узлы не мешали друг другу во время передачи информации. 


Глобально в этом три идеи:
 1. Благодаря свойствам беспроводных сетей узел может "чувствовать", что кто-то другой уже вещает
 2. Запрашивать у `AP` разрешение на передачу
 3. При невозможности передать фрейм прямо сейчас: ждать рандомное время

Первая идея заключается в том, что фреймы передаются всем, до кого дотягиваются антенны передающего. И эту передачу можно "почувствовать" своими антеннами и подождать

Вторая идея заключается в [простом алгоритме](https://en.wikipedia.org/wiki/Carrier-sense_multiple_access_with_collision_avoidance):
 1. Перед отправкой `STA` заправшивает у `AP` разрешение пакетом: `RTS` (`Request to Send`)
 2. `AP` отвечает `CTS` (`Clear to Send`) одному узлу
 3. Если `CTS` предназначено нам, то мы вещаем, иначе - ждёмс.


И в динамике с сайта, [где простыми словами об этом рассказано](https://devopedia.org/wi-fi-mac-layer)

![alt text](files/img/at-ap.jpg)

 > На самом деле, алгоритм сложнее, но он тут для примера 

Суть в том, что для `adhoc` никто этим при текущей настройке симуляции не занимается

# Что делать c колизией `adhoc-ерам`

## Костыль в рамках симуляции

Некрутой вариант, с которым может возникнуть много проблем: добавить для каждого узла некий `timeout` перед отправкой. 

Я не стану реализовывать это здесь, но суть данной симуляции такова:

 - Определить время `Tp`, за которое узел передаёт пакет. Взять время `Ts = 1,5 * Tp` (с запасом)
 - На каждом узле организовать очередь пакетов `Q`
 - В зависимости от числа узлов `N` определить время `Ti = Ts * N`, за которое каждый узел успеет отправить пакет
 - Для каждого узла настроить отправку одно пакета из `Q` раз в `Ts`
 - При этом задержка перед отправкой: `Td = NodeId * Ts` 
<!-- TODO: insert pic -->

Одна из очевидых проблем такого подхода - о реактивности общения узлов можно забыть. Плюс, на реальных устройствах такой синхронизации добиться ~~почти~~ невозможно.

> Но если любой ответ узла уместить в один пакет, то как бы вроде норм, но с каждой такой условностью мы всё дальше от ~~бога~~ настоящего `adhoc-инга`.

## Поиск решения

> Одним из вариантов - сделать что-то похожее на регуляцию доступа в режиме `BSS`

Подробно изучить вопрос используемых `wifi` технологий для передачи информации, а также особенностях версий стандарта `802.11` можно в [этом документе](references/Overview%20of%20the%20802.11%20Physical%20Layer%20and%20Transmitter%20Measurements.pdf)

> Настоятельно рекомендую его к прочтению *хотя бы по-диагонали*, для понимания основных конценпций `802.11` на уровне `MAC`

















