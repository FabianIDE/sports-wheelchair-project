import pygatt  # To access BLE GATT support
import signal  # To catch the Ctrl+C and end the program properly
import os  # To access environment variables
from dotenv import load_dotenv  # To load the environment variables from the .env file
from random import random # Import required library for serial
import time
from threading import Thread
import pexpect
import sys
from dcd.entities.thing import Thing # DCD Hub
from dcd.entities.property_type import PropertyType


load_dotenv() # The thing ID and access token
THING_ID = os.environ['THING_ID']
THING_TOKEN = os.environ['THING_TOKEN']

CLASSES = ["Passing", "Adjustment", "Fakeout", "Throw", "Sprint"] # Movement classes
LABEL_PROP_NAME = "Movement"
DATA_PROP_NAME = "fsr"
MAX_SAMPLES = 100 # How many samples do we want for each class
DELAY_BETWEEN_MOVEMENT = 15 # How much time (in seconds) to leave between the collection of each class

BLUETOOTH_DEVICE_MAC_WHEEL = os.environ['BLUETOOTH_DEVICE_MAC_WHEEL']
GATT_CHARACTERISTIC_ORIENTATION = "02118833-4455-6677-8899-AABBCCDDEEFF" # UUID of the GATT characteristic to subscribe
ADDRESS_TYPE = pygatt.BLEAddressType.random # Many devices, e.g. Fitbit, use random addressing, this is required to connect.

# OPEN Serial
def open_serial(): # Open a serial connection
    # Start reading the serial port
    return serial.Serial(
        port=os.environ['SERIAL'],
        baudrate=9600,
        timeout=2)

# BLE
def find_or_create(property_name, property_type): # create property for BLE
    """Search a property by name, create it if not found, then return it."""
    if my_thing.find_property_by_name(property_name) is None:
        my_thing.create_property(name=property_name,
                                 property_type=property_type)
    return my_thing.find_property_by_name(property_name)
def handle_orientation_data(handle, value_bytes): # print wheel values, send to server
    """
    handle -- integer, characteristic read handle the data was received on
    value_bytes -- bytearray, the data returned in the notification
    """
    print("Received data: %s (handle %d)" % (str(value_bytes), handle))
    values = [float(x) for x in value_bytes.decode('utf-8').split(",")]
    find_or_create("Right Sports Wheel",
                   PropertyType.THREE_DIMENSIONS).update_values(values)
def discover_characteristic(device): # Provide UUID
    """List characteristics of a device"""
    for uuid in device.discover_characteristics().keys():
        try:
            print("Read UUID" + str(uuid) + "   " + str(device.char_read(uuid)))
        except:
            print("Something wrong with " + str(uuid))
def read_characteristic(device, characteristic_id): # return BLE characteristic
    """Read a characteristic"""
    return device.char_read(characteristic_id)
def keyboard_interrupt_handler(signal_num, frame): #Provide interrupt
    """Make sure we close our program properly"""
    print("Exiting...".format(signal_num))
    left_wheel.unsubscribe(GATT_CHARACTERISTIC_ORIENTATION)
    ser.close()
    child.sendline("char-write-req 0x000f 0000")
    exit(0)

# HRM
def hexStrToInt(hexstr):
    val = int(hexstr[3:5], 16) #
    if ((val & 0x8000) == 0x8000): # treat signed 16bits
        val = -((val ^ 0xffff) + 1)
        val = int(val)
    return val

# LABEL
def collect(class_index): #Collect data
    # if we covered all classes, stop the program
    if class_index >= len(CLASSES):
        print("Data collection done.")
        exit()

    # Prompt the user to get ready and wait
    print("Get ready to collect the MOVEMENT: " + CLASSES[class_index]
          + " in " + str(DELAY_BETWEEN_MOVEMENT) + " seconds!")
    time.sleep(DELAY_BETWEEN_MOVEMENT)

    # Open the serial connection
    print("Collecting data for MOVEMENT " + CLASSES[class_index])
    ser = open_serial()

    # Start reading serial port with the MOVEMENT index, start at sample 0.
    sample = 0
    while sample < MAX_SAMPLES:
        if serial_to_property_values(class_index, ser):
            sample += 1
            print()
    ser.close()
    collect(class_index + 1)
def serial_to_property_values(class_index, ser): #Add label to data
    # Read one line
    line_bytes = ser.readline()
    # If the line is not empty
    if len(line_bytes) > 0:
        # Convert the bytes into string
        line = line_bytes.decode('utf-8')
        # Split the string using commas as separator, we get a list of strings
        str_values = line.split(',')
        # Remove the first id
        # str_values.pop(0)
        # Transform the array of string values into float values (numbers)
        values = [float(x) for x in str_values]
        values[4] =

        # get the current time in milliseconds
        current_ts_ms = int(round(time.time() * 1000))
        # Update values of data and label properties (send them to the DCD Hub)
        # With the same timestamp, so we can easily connect label and raw data later
        prop_label.update_values([class_index], current_ts_ms)
        prop_data.update_values(values, current_ts_ms)

        return True
    return False



# Instantiate a thing with its credential, then read its properties from the DCD Hub
my_thing = Thing(thing_id=THING_ID, token=THING_TOKEN)
my_thing.read()
print(my_thing.to_json())

bleAdapter = pygatt.GATTToolBackend() # Start a BLE adapter
bleAdapter.start()
left_wheel = bleAdapter.connect(BLUETOOTH_DEVICE_MAC_WHEEL, address_type=ADDRESS_TYPE) # Use the BLE adapter to connect to our device
signal.signal(signal.SIGINT, keyboard_interrupt_handler) # Register our Keyboard handler to exit

#end BLE code


# START COLLECTING

# Instantiate a thing with its credential
my_thing = Thing(thing_id=THING_ID, token=THING_TOKEN)

# Read the details of our Thing from the DCD Hub to get property details
my_thing.read()

# Find label and data property by name
prop_label = my_thing.find_property_by_name(LABEL_PROP_NAME)
prop_data = my_thing.find_property_by_name(DATA_PROP_NAME)

# Start collecting data for the first class
collect(0)

# END OF COLLECTING
