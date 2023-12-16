.equ  button_pin = 2  ; Definir el número de pin para el botón
.equ  button_pin3 = 3  ; Definir el número de pin para el botón
.equ  button_pin4 = 4  ; Definir el número de pin para el botón
.equ  button_pin5 = 5  ; Definir el número de pin para el botón
.equ  button_pin6 = 6  ; Definir el número de pin para el botón
.equ  button_pin7 = 7  ; Definir el número de pin para el botón
.equ  led_pin = PORTB4     ; Definir el número de pin para el LED

; Sección de código
.org 0x0000
    rjmp main

main:
    
    ldi r16, (1 << button_pin)  ; Configurar el pin del botón como entrada
    out DDRD, r16              ; Configurar el pin del botón como entrada

	ldi r16, (1 << button_pin3)  ; Configurar el pin del botón como entrada
    out DDRD, r16              ; Configurar el pin del botón como entrada

	ldi r16, (1 << button_pin4)  ; Configurar el pin del botón como entrada
    out DDRD, r16              ; Configurar el pin del botón como entrada

	ldi r16, (1 << button_pin5)  ; Configurar el pin del botón como entrada
    out DDRD, r16              ; Configurar el pin del botón como entrada

	ldi r16, (1 << button_pin6)  ; Configurar el pin del botón como entrada
    out DDRD, r16              ; Configurar el pin del botón como entrada

	ldi r16, (1 << button_pin7)  ; Configurar el pin del botón como entrada
    out DDRD, r16              ; Configurar el pin del botón como entrada

    ldi r16, (1 << led_pin)  ; Configurar el pin del LED como salida
    out DDRB, r16              ; Configurar el pin del LED como salida

loop:
    sbic PIND, button_pin  ; Saltar si el botón está presionado (nivel alto para pull-down)
	rjmp led_on           ; Si el botón  está presionado, encender el LED
	sbic PIND, button_pin3  ; Saltar si el botón está presionado (nivel alto para pull-down)
	rjmp led_on           ; Si el botón  está presionado, encender el LED
	sbic PIND, button_pin4  ; Saltar si el botón está presionado (nivel alto para pull-down)
	rjmp led_on           ; Si el botón  está presionado, encender el LED
	sbic PIND, button_pin5  ; Saltar si el botón está presionado (nivel alto para pull-down)
	rjmp led_on           ; Si el botón  está presionado, encender el LED
	sbic PIND, button_pin6  ; Saltar si el botón está presionado (nivel alto para pull-down)
	rjmp led_on           ; Si el botón  está presionado, encender el LED
	sbic PIND, button_pin7  ; Saltar si el botón está presionado (nivel alto para pull-down)
    rjmp led_on           ; Si el botón  está presionado, encender el LED
	ldi r17, (0 << led_pin)  ; Apagar el LED
    out PORTB, r17
    rjmp loop

led_on:
    ldi r17, (1 << led_pin)  ; Encender el LED
    out PORTB, r17
    rjmp loop
