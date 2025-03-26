# TCP/IP client server

## Общее описание
Простой клиент с сервером под linux. Для работы клиента и сервера не требуются никакие сторонние библиотеки.

### Описание взаимодействия
Общая логика взаимодейтсвия может быть любой. В данной версии клиент дважды пытается установать соединение с сервером и в случае успешного соединения начинается бесконечный обмен файлами в обе стороны.

Более подробное описание есть в папках doc у каждого из объектов

## Как собирать и запускать
### `client` и `server` аналогично
```
cd build
cmake ..
make
./client (./server)
```

### `LibParserSaver`
Для работы необходимо установать pugixml

```
sudo apt update
sudo apt install libpugixml-dev
```
либо
```
git clone https://github.com/zeux/pugixml.git
cd pugixml
mkdir build
cd build
cmake ..
make
sudo make install
```

Сборка и установка LibParserSaver
```
cd build
cmake ..
make
sudo cmake --install .
```
