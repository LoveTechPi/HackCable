import board
import time
import usb_hid
import neopixel
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode
from keyboard_layout_win_uk import KeyboardLayout

# Define the data pin and the number of pixels
pixel_pin = board.GP25  # Example: using GP22 on a Pico
num_pixels = 1         # Example: 30 NeoPixels in your strip

# Initialize the NeoPixel object 
pixels = neopixel.NeoPixel(pixel_pin, num_pixels, brightness=0.5, auto_write=False)

# Set a single pixel to red
pixels[0] = (255, 0, 0)
pixels.show()
time.sleep(0.5)

# Fill the entire strip with blue
pixels.fill((0, 0, 255))
pixels.show()
time.sleep(0.5)

pixels.fill((0, 0, 255)) # Blue
pixels.show()
time.sleep(0.5)

# Create a keyboard object
keyboard = Keyboard(usb_hid.devices)
keyboard_layout = KeyboardLayout(keyboard)

# Give the computer some time to recognize the device
time.sleep(2)

# For Windows we use - keyboard.send(Keycode.WINDOWS, Keycode.R)
# For MAC we use - keyboard.send(Keycode.COMMAND, Keycode.SPACE)

keyboard.send(Keycode.WINDOWS, Keycode.R)
time.sleep(0.5)
keyboard_layout.write('shell:RecycleBinFolder')
keyboard.send(Keycode.ENTER)
time.sleep(2)

keyboard.send(Keycode.CONTROL,Keycode.A)
time.sleep(2)
keyboard.send(Keycode.DELETE)
time.sleep(2)

# Press Enter to submit the password
keyboard.press(Keycode.ENTER)
keyboard.release_all()




