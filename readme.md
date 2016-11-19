# Super Simple Task on AVR
#### INSTITUTO DE COMPUTAÇÃO - UNIVERSIDADE FEDERAL DE ALAGOAS

##### Dependências:

  - [AVRDUDE](http://www.nongnu.org/avrdude/)
    - [EXEMPLO DE INSTALAÇÃO](http://ubuntuhandbook.org/index.php/2014/09/install-avrdude-6-1-ubuntu-1404/)

#### Informações Iniciais

* Os exemplos foram testados no ATMEGA328P (microcontrolador utilizado no arduino uno).
* Cada branch contém uma implementação específica de acordo com a feature requerida de modo a estender as características básicas(padrões) do SST.
##### Branch 64tasks
A branch ```64tasks``` contém o código que permite em tempo de compilação selecionar o número máximo de tasks que o SST poderá gerenciar. Contém 2 tarefas A e B, onde a tarefa A acende o Led do arduino UNO e a tarefa B apaga o Led.
##### Branch mailbox
A branch ```mailbox``` contém o código que implementa um mailbox com semáforo. Tem-se 2 tarefas. Sempre que uma tarefa deseja utilizar o mailbox, antes ativa o semáforo de modo que o recurso fique bloqueado até a liberação.

As tarefas A e B, lêem do mailbox a informação executam (tarefa A lê a informação que acende o led, e a tarefa B lê a informação que apaga o led) e põem uma informação no mailbox (tarefa A põe no mailbox informação para apagar o led, tarefa B põe no mailbox informação para acender o led).

##### Branch queueWithSemaphore

A branch ```queueWithSemaphore``` contém o código que implementa uma fila com semáforo. Igualmente, tem-se 2 tarefas. Sempre que uma tarefa deseja ler ou escrever na fila, antes ativa o semáforo correspondente à fila, de modo que o recurso fila fique bloqueado até sua liberação.

As tarefas A e B, lêem da fila uma informação e a executam (tarefa A lê a informação que acende o led, e a tarefa B lê a informação que apaga o led) e põem uma informação na fila (tarefa A põe na fila informação para apagar o led, tarefa B põe na fila informação para acender o led).

###### Observação[1]: A implementação do semáforo foi feita separadamente, porém posteriormente na implementação da fila e mailbox, foi integrada como parte da estrutura.

###### Observação[2]: O código de implementação das 64tasks está incluindo em todos os branchs.
_

#### Informações para Execução

##### 64tasks
###### Para executar o SST com apenas a implementação das 64tasks, basta dar o checkout no branch ```64tasks``` e dentro da pasta *example* e executar o comando ```make``` no terminal. O upload será feito para o ATMEGA automaticamente.

Exemplo de saída após comando ```make``` 
```sh
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o sst.o sst.c
sst.c: In function ‘SST_schedule_’:
sst.c:137:29: warning: integer constant is so large that it is unsigned
     uintX_t iteratorPrior = ITERATORPRIOR;
                             ^
sst.c:137:5: warning: this decimal constant is unsigned only in ISO C90
     uintX_t iteratorPrior = ITERATORPRIOR;
     ^
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o tick_tsk.o tick_tsk.c
avr-gcc -mmcu=atmega328p main.c -o main sst.o tick_tsk.o
avr-objcopy -O ihex -R .eeprom main main.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "main.hex"
avrdude: input file main.hex auto detected as Intel Hex
avrdude: writing flash (4404 bytes):

Writing | ################################################## | 100% 0.72s

avrdude: 4404 bytes of flash written

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.
```


##### Mailbox
###### Para executar o SST com a implementação do mailbox, basta dar o checkout no branch ```mailbox``` e dentro da pasta *example* e executar o comando ```make``` no terminal. O upload será feito para o ATMEGA automaticamente.
Exemplo de saída após comando ```make```
```sh
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o sst.o sst.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o tick_tsk.o tick_tsk.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o mailbox.o mailbox.c
mailbox.c: In function ‘get’:
mailbox.c:38:9: warning: return makes integer from pointer without a cast
         return NULL;
         ^
mailbox.c:42:27: warning: assignment makes integer from pointer without a cast
     mailbox->msgAvailable = NULL;
                           ^
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o semaphore.o semaphore.c
avr-gcc -mmcu=atmega328p main.c -o main sst.o tick_tsk.o mailbox.o semaphore.o
avr-objcopy -O ihex -R .eeprom main main.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "main.hex"
avrdude: input file main.hex auto detected as Intel Hex
avrdude: writing flash (5530 bytes):

Writing | ################################################## | 100% 0.90s

avrdude: 5530 bytes of flash written

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.
```

##### Queue
###### Para executar o SST com a implementação da fila, basta dar o checkout no branch ```queueWithSemaphore``` e dentro da pasta *example* e executar o comando ```make``` no terminal. O upload será feito para o ATMEGA automaticamente.
Exemplo de saída após comando ```make```

```sh
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o sst.o sst.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o tick_tsk.o tick_tsk.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o queue.o queue.c
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o semaphore.o semaphore.c
avr-gcc -mmcu=atmega328p main.c -o main sst.o tick_tsk.o queue.o semaphore.o
avr-objcopy -O ihex -R .eeprom main main.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.00s

avrdude: Device signature = 0x1e950f (probably m328p)
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "main.hex"
avrdude: input file main.hex auto detected as Intel Hex
avrdude: writing flash (5908 bytes):

Writing | ################################################## | 100% 0.96s

avrdude: 5908 bytes of flash written

avrdude: safemode: Fuses OK (E:00, H:00, L:00)

avrdude done.  Thank you.
```