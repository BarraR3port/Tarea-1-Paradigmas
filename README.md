# Comando para compilar e iniciar el programa

puede ocupar el vehicles.json para cargar 100 ventas, pero tiene que cambiar el codigo en tarea.cpp

Para hacer esto tiene que ir a la parte de `TODO:` y sacar los comentarios pertinentes.

## Compilar y ejecutar

Hay dos formas para compilar y ejecutar el codigo, con gcc o cmake.
Es recomendado utilizar cmake, pero si no lo tiene instalado puede utilizar gcc.

### GCC

`Shell`

```shell
g++ -Wall -Wextra -g3 *.cpp -o output.exe ; .\output.exe
```

`Bash`

```bash
g++ -Wall -Wextra -g3 *.cpp -o output.exe && .\output.exe
```

### CMAKE

`Shell`

```shell
cmake --build cmake-build-debug --target Tarea_1_Paradigmas -j 14 ; .\cmake-build-debug\Tarea_1_Paradigmas.exe
```

`Bash`

```bash
cmake --build cmake-build-debug --target Tarea_1_Paradigmas -j 14 && .\cmake-build-debug\Tarea_1_Paradigmas.exe
```
