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


def find_or_create(property_name, property_type): # create property for BLE
    """Search a property by name, create it if not found, then return it."""
    if my_thing.find_property_by_name(property_name) is None:
        my_thing.create_property(name=property_name,
                                 property_type=property_type)
    return my_thing.find_property_by_name(property_name)

def handle_orientation_data(handle, value_bytes): # print wheel values
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

# Instantiate a thing with its credential, then read its properties from the DCD Hub
my_thing = Thing(thing_id=THING_ID, token=THING_TOKEN)
my_thing.read()

print(my_thing.to_json())

# Start a BLE adapter
bleAdapter = pygatt.GATTToolBackend()
bleAdapter.start()

# Use the BLE adapter to connect to our device
left_wheel = bleAdapter.connect(BLUETOOTH_DEVICE_MAC_WHEEL, address_type=ADDRESS_TYPE)



# Register our Keyboard handler to exit
signal.signal(signal.SIGINT, keyboard_interrupt_handler)

#end BLE code
