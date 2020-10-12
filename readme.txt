- El trabajo consiste en crear un que contiene un puntero a pokemon que apunta a un arreglo de pokemones que representa a los pokemones que se encuentran en el arrecife. El programa recibe por parametro la ruta del archivo que contiene a los pokemones que pertenecerán al arrecife. Por otro lado se encuentra una estructura que representa a un acuario que, al igual que el arrecife, contiene un puntero con la ubicacion en memoria de un arreglo de pokemones. Luego existe la posibilidad de traspasar pokemones del arrecife al acuario, siempre y cuando cumplan una determinada condicion, por ejemplo, que su color sea violeta. luego de cada traspaso, se imprimirá en pantalla los pokemones restantes del arrecife. Por ultimo, se guardará en el archivo "acuario.txt" los pokemones que fueron llevados al acuario.

- Para compilarlo se ingresa la siguiente linea en consola (en el directorio del trabajo):
gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca
Y para ejecutarlo:
./evento_pesca arrecife.txt
En la ruta ingresada se encuentran los pokemones que pertenecerán al arrecife.

- Un puntero es una variable cuyo valor es una direccion de memoria. Del mismo se puede obtener el valor almacenado en dicha direccion.

- Es posible operar con punteros, ya sea sumándole o restándole un valor, para que el mismo apunte a una dirección de memoria nueva.

- Un puntero a función es una variable que contiene la dirección de memoria donde esta guardada una función, lo cual permite ejecutarla desde cualquier parte del programa.

- malloc recibe un valor size_t y reserva dicha cantidad en memoria y devuelve el puntero a la ubicación reservada.

- realloc recibe un puntero y un valor size_t y modificará el tamaño del bloque de memoria que se encuentre en la dirección contenida en el puntero. devuelve la dirección del bloque reservado en memoria, ya que en caso de que no entre el nuevo tamaño en la ubicacion original, se le asignará un nuevo sitio en la memoria.
