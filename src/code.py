import board
import digitalio
import time


led = digitalio.DigitalInOut(board.GP2)
led.direction = digitalio.Direction.OUTPUT

button = digitalio.DigitalInOut(board.GP29)
button.switch_to_input(pull=digitalio.Pull.UP)

for i in range(10):
    led.value = i % 2 == 0
    print(f'Blink step {i}')
    time.sleep(1)

while True:
    led.value = button.value


