.include "m328pdef.inc"

.org 0x0000 ; Inicio del programa

rjmp inicio ; Saltar a la etiqueta 'inicio'

.org 0x001C ; Vector de interrupción de temporizador 1

rjmp enviar_numero ; Saltar a la etiqueta 'enviar_numero'

inicio:
  ldi r16, 4 ; Cargar el número en el registro

  ; Configurar Serial
  ldi r17, (1 << TXEN0) | (1 << UCSZ01) | (1 << UCSZ00) ; Habilitar transmisión y configurar tamaño de datos a 8 bits
  sts UCSR0B, r17 ; Almacenar el valor en el registro de control de la transmisión

  ; Configurar la velocidad de transmisión a 9600 bps
  ldi r17, (1 << URSEL0) | (1 << U2X0) ; Habilitar la escritura en UBRR0H
  sts UCSR0A, r17 ; Almacenar el valor en el registro de control de la transmisión
  ldi r17, 8 ; Valor para configurar UBRR0H a 8 (ver datasheet)
  sts UBRR0H, r17 ; Almacenar el valor en el registro de velocidad de baudios

  ; Configurar Timer 1 para generar una interrupción cada segundo
  ldi r17, (1 << WGM12) | (1 << CS12) | (1 << CS10) ; Modo CTC, preescala 1024
  sts TCCR1B, r17 ; Almacenar el valor en el registro de control del temporizador 1
  ldi r17, 15624 >> 8 ; Configurar el valor de comparación (15624) en los registros
  sts OCR1AH, r17 ; Almacenar la parte alta del valor de comparación
  ldi r17, 15624 & 0xFF ; Parte baja del valor de comparación
  sts OCR1AL, r17 ; Almacenar la parte baja del valor de comparación
  ldi r17, (1 << OCIE1A) ; Habilitar la interrupción de comparación A
  sts TIMSK1, r17 ; Almacenar el valor en el registro de máscaras de interrupción

  sei ; Habilitar las interrupciones globales

bucle:
  rjmp bucle ; Bucle infinito

enviar_numero:
  sts UDR0, r16 ; Enviar el número a través de Serial
  reti ; Retornar de la rutina de interrupción