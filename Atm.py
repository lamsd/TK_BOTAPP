import time
import busio
import board
import adafruit_amg88xx
import matplotlib as mpl 
import matplotlib.pyplot as plt 
import numpy as np
 
i2c = busio.I2C(board.SCL, board.SDA)
amg = adafruit_amg88xx.AMG88XX(i2c)
sleep(0.1)
harvert = np.array 


while True:
    for row in amg.pixels:
        for temp in row:

        # Pad to 1 decimal place
        print(["{0:.1f}".format(temp) for temp in row])
        print("")
    print("\n")
    time.sleep(1)