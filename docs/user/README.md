# **Práctica 2**
### Universidad de San Carlos de Guatemala
### Facultad de Ingeniería
### Escuela de Ciencias y Sistemas
### Arquitectura de Computadores y Ensambladores 1
### Sección B
<br></br>

## **Manual de Usuario**
<br></br>

| Nombre | Carnet | 
| --- | --- |
| Daniel Estuardo Cuque Ruíz | 202112145 |
| Damián Ignacio Peña Afre | 202110568 |
| Alvaro Norberto García Meza | 202109567 |
| José Manuel Ibarra Pirir | 202001800 |
----
# **Descripción**

# **Los botones y switch**
Para encender y apagar la máquina se utiliza el switch, los botones permiten manejar el funcionamiento del sistema, las principales funcionalidades de los botones es como primer punto presionar cualquiera de estos para entrar al menú e iniciar el proceso de detección de paquetes, dentro del menú, podremos detener o pausar el proceso, dependiendo del botón presionado se accederá a un submenú el cual cuenta con diferentes funcionalidades también controlados con los botones. 

# **Procesamiento de paquetes**
Una vez iniciado el proceso, la banda transportadora comenzará a moverse en un sentido con cierta velocidad con ayuda del motor DC controlado con un puente H. El procesamiento de paquetes se divide en dos instancias, la primera la detección del color de su etiqueta, existen tres colores de etiquetas a identificar: rojo , amarrillo y azul. Cuando el paquete llega al punto donde se encuentra el sensor de color, la banda transportadora se detiene y continua su movimiento hasta que el color sea detectado o bien este al ser probado 3 veces no haya detectado sigue su trayectoria, posteriormente de haber inferido el color del paquete, se procede de medir las dimensiones del paquete, utilizando 3 sensores ultrasónicos colocados en posiciones estratégicas, este proceso se repite por cada paquete que es ingresado a la maquina transportadora. 

La segunda parte de la máquina es la clasificación de los paquetes, si un paquete fue identificado correctamente, con ayuda de un servomotor se traslada a su posición que corresponde por el color que fue identificado. Si el paquete no fue identificado de ninguna manera, este llega hasta al final de la banda transportadora para ser depositado con los paquetes que no fueron leídos. 

Cada paquete leído, su información es transferida con el protocolo I2C a un Arduino maestro el cual lleva el conteo tanto de los paquetes que fueron o no identificados. 

# **Transferencia de datos**
Todo paquete identificado, sus valores son transferidos de un Arduino esclavo a un Arduino maestro mediante el protocolo I2C, dichos paquetes se almacenan en memoria para ser mostrados al final de cada proceso. Si un paquete no fue identificado, entonces se transfiere una señal que aumenta un contador de paquetes no reconocidos los cuales se esperan a ser reprocesados. 

# **Pantalla LCD**
La pantalla LCD notifica y permite mostrar en las fases que se encuentra el sistema, muestra desde el momento en que se enciende la máquina, cuando realiza la comunicación correcta con el otro Arduino. Además esta pantalla permite visualizar las propiedades de todos los paquetes que fueron analizados, por ultimo muestra en tiempo real cada vez que se acciona un botón para realizar una funcionalidad que este relacionada con la pantalla. 

# **Modo de uso**
1. Para poner en funcionamiento la máquina, se debe accionar el switch que se encuentra al costado de los botones y pantalla LCD. Después de accionar el switch la pantalla LCD mostrará un mensaje indicando que se esta iniciando y haciendo comunicación con el Arduino. Después de haber transcurrido 6 segundos y verificar que todo este en perfecto funcionamiento, la pantalla mostrará un mensaje donde se espera presionar un botón para iniciar. 
![Encender](./images/user/chargin.jpeg)
![Máquina](./images/user/connected.jpeg)
![Máquina](./images/user/raedy.jpeg)

2. Al momento de presionar   botón para ingresar al menú, se tendrá la opción de iniciar proceso el cual se acciona con el botón izquierdo, por consecuencia se envía un mensaje al Arduino esclavo permitiendo que este comience a funcionar.
![paso1](./images/user/paso1.jpeg)

3. Al iniciar un proceso, el Arduino esclavo pone en marcha todas sus funcionalidades, empezando con la banda transportadora que se empieza a mover de manera constante y la pantalla LCD muestra el menú durante el proceso de ejecución donde podemos realizar diferentes funcionalidades como pausar con el botón izquierdo y detener con el botón derecho. 
![paso1](./images/user/paso2.jpeg)

  - 1.  Para identificar un paquete este se coloca en la banda transportadora y al momento de llegar al sensor de color, la banda se detiene para poder medir correctamente la etiqueta del paquete, a su vez también mide el ancho, alto y largo utilizando los sensores ultrasónicos.
  ![paso1](./images/user/color.jpeg)

  - 2. Cuando el paquete es identificado y medido correctamente, la banda continua su movimiento y al momento de llegar a la mitad del tramo, con la ayuda de un servomotor se clasifica cada paquete en su respectivo lugar. Si un paquete no es identificado entonces el servomotor no se acciona y este continua su rombo hasta el final para ser depositado con los paquetes que no fueron identificados. 
  ![paso2](./images/user/movimiento.jpeg)

4. Si pausamos el procesado de paquetes, la banda transportadora y los demás componentes dejaran de funcionar y en la pantalla LCD se mostrará una opción para continuar el proceso cuando se encuentra en pausa para retornar al trabajo normal.
![paso2](./images/user/pausa.jpeg)

5. Al detener un proceso, se evaluan dos escenarios: 
  - 1. La N cantidad de paquetes que no fueron identificados, se acumulan en el sistema y al terminar un proceso, este revisa la existencia de paquetes necesarios a reprocesar y automáticamente la pantalla cambia y muestra la cantidad de paquetes pendientes y todo el sistema se pone en marcha esperando a reprocesar cada paquete pendiente. 
  ![paso2](./images/user/pendiente.jpeg)

  - 2. Después de haber reprocesado los paquetes pendientes, automáticamente se mostrarán los paquetes en el sistema. Con ayuda de los botones se podrá navegar entre las distintas opciones y al momento de llegar al paquete final, se finalizará el proceso por completo y se volverá al menú de trabajo para iniciar un nuevo proceso. Se mostrará la media y mediana de los colores de los paquetes identificados y el volumem
  ![paso2](./images/user/stage.jpeg)
  Media mediana de los colores y volumen:
  ![paso2](./images/user/media.jpeg)
  Cantidad de paquetes de cada color:
  ![paso2](./images/user/paquete.jpeg)
  Cantidad de paquetes reprocesados de cada color:
  ![paso2](./images/user/re.jpeg)
  Paquetes por etapa:
  ![paso2](./images/user/etapa.jpeg)
  Paquete reprocesado:
  ![paso2](./images/user/repack.jpeg)
  Media y Mediana de paquetes color rojo:
  ![paso2](./images/user/red.jpeg)
    Media y Mediana de paquetes color amarillo:
  ![paso2](./images/user/y.jpeg)
    Media y Mediana de paquetes color azul:
  ![paso2](./images/user/blue.jpeg)
