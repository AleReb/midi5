# midi5
un sencillo codigo para hacer un isntrumento midi con un arduino compatible con la libreria "MIDIUSB.h" se recomienda el arduino leonardo o minipro
Controlador MIDI Arduino
Este proyecto permite construir un controlador MIDI basado en Arduino. Consta de 8 botones que envían notas MIDI, un potenciómetro para controlar el volumen, otro para seleccionar entre 5 escalas diferentes y un tercer potenciómetro para ajustar la modulación.

Requisitos de Hardware:

Arduino: Se recomienda utilizar Arduino Leonardo, Arduino Micro o cualquier otro modelo basado en el ATmega32U4 por su compatibilidad con la biblioteca MIDIUSB.
Botones: 8 botones conectados en modo INPUT_PULLUP.
Potenciómetros: 3 potenciómetros.

Funcionalidades:
Botones: Al presionarlos, envían notas MIDI. Las notas base son C4 (DO), D4 (RE), E4 (MI), F4 (FA), G4 (SOL), A4 (LA), B4 (SI) y C5 (DO).
Potenciómetro de Escala: Permite cambiar las notas base en intervalos de una octava, desde dos octavas abajo hasta dos octavas arriba.
Potenciómetro de Volumen: Ajusta el volumen de las notas.
Potenciómetro de Modulación: Controla el valor de modulación MIDI.

Conexiones:
Botones: Conectar cada botón a los pines digitales 4-11 en el Arduino. Usar el modo INPUT_PULLUP.
Potenciómetros: Conectar a los pines analógicos A0 (volumen), A1 (escala) y A2 (modulación).

Código y Uso:
El código completo está disponible en el archivo nombre_del_archivo.ino. Una vez cargado en el Arduino, se puede usar el controlador con cualquier software que soporte entrada MIDI.

Al mantener un botón presionado y girar el potenciómetro de volumen, se ajustará el volumen de la nota. Si se cambia la escala mientras una nota está siendo sostenida, la nota cambiará a la correspondiente de la nueva escala sin detenerse.

Contribuciones y Mantenimiento:
Este proyecto es de código abierto y se agradecen las contribuciones para mejorar o expandir sus capacidades. Si encuentras algún bug o tienes alguna sugerencia, por favor abre un issue en este repositorio.
