import board
import neopixel
import time

# Define the data pin and the number of pixels
pixel_pin = board.GP25  # using GP25 is connected with RGB LED
num_pixels = 1          # Only 1 RGB LED

# Initialize the NeoPixel object 
pixels = neopixel.NeoPixel(pixel_pin, num_pixels, brightness=0.5, auto_write=False)
       
# Fill the LED with red
pixels[0] = (255, 0, 0)
pixels.show()

# Fill the LED with blue
pixels.fill((0, 0, 255))
pixels.show()

# Create a color animation (example: fading through colors)
def fade_colors(speed=0.008):
    for hue in range(0, 360, 1):
        rgb = hsv_to_rgb(hue / 360.0, 1.0, 1.0) # Assuming hsv_to_rgb function exists
        pixels.fill(tuple(int(c * 255) for c in rgb))
        pixels.show()
        time.sleep(speed)

# Example loop
while True:
    pixels.fill((255, 0, 0)) # Red
    pixels.show()
    time.sleep(0.5)
    pixels.fill((0, 255, 0)) # Green
    pixels.show()
    time.sleep(0.5)
    pixels.fill((0, 0, 255)) # Blue
    pixels.show()
    time.sleep(0.5)

