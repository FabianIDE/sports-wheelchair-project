#!/usr/bin/env python3

# Import required library for BLE
import pygatt  # To access BLE GATT support
import signal  # To catch the Ctrl+C and end the program properly
import os  # To access environment variables
from dotenv import \
    load_dotenv  # To load the environment variables from the .env file

# Import required library for serial
from random import random
import time

from dotenv import load_dotenv
import os

from threading import Thread

import serial

# DCD Hub
from dcd.entities.thing import Thing
from dcd.entities.property_type import PropertyType

# The thing ID and access token
load_dotenv()
THING_ID = os.environ['THING_ID']
THING_TOKEN = os.environ['THING_TOKEN']
BLUETOOTH_DEVICE_MAC_WHEEL = os.environ['BLUETOOTH_DEVICE_MAC_WHEEL']



# UUID of the GATT characteristic to subscribe
GATT_CHARACTERISTIC_ORIENTATION = "02118833-4455-6677-8899-AABBCCDDEEFF"

# Many devices, e.g. Fitbit, use random addressing, this is required to connect.
ADDRESS_TYPE = pygatt.BLEAddressType.random

# create property for BLE
def find_or_create(property_name, property_type):
    """Search a property by name, create it if not found, then return it."""
    if my_thing.find_property_by_name(property_name) is None:
        my_thing.create_property(name=property_name,
                                 property_type=property_type)
    return my_thing.find_property_by_name(property_name)


def handle_orientation_data(handle, value_bytes):
    """
    handle -- integer, characteristic read handle the data was received on
    value_bytes -- bytearray, the data returned in the notification
    """
    print("Received data: %s (handle %d)" % (str(value_bytes), handle))
    values = [float(x) for x in value_bytes.decode('utf-8').split(",")]
    find_or_create("Right Sports Wheel",
                   PropertyType.TWO_DIMENSIONS).update_values(values)


def discover_characteristic(device):
    """List characteristics of a device"""
    for uuid in device.discover_characteristics().keys():
        try:
            print("Read UUID" + str(uuid) + "   " + str(device.char_read(uuid)))
        except:
            print("Something wrong with " + str(uuid))


def read_characteristic(device, characteristic_id):
    """Read a characteristic"""
    return device.char_read(characteristic_id)


def keyboard_interrupt_handler(signal_num, frame):
    """Make sure we close our program properly"""
    print("Exiting...".format(signal_num))
    left_wheel.unsubscribe(GATT_CHARACTERISTIC_ORIENTATION)
    ser.close()
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

# Start reading the serial port
ser = serial.Serial(
    port = os.environ['SERIAL'],
    baudrate = 9600,
    timeout = 2)

# Read the next line from the serial port
# and update the property values
def serial_to_property_values():
    # Read one line
    line_bytes = ser.readline()
    # If the line is not empty
    if len(line_bytes) > 0:
        # Convert the bytes into string
        print('SERIAL DATA FOUND')

        line = line_bytes.decode('utf-8')
        # Split the string using commas as separator, we get a list of strings
        values = line.split(',')
        print('values split')

        try:
            # Use the first element of the list as property id
            property_serial_id = values.pop(0)
            print('property name taken')
            print('Serial data found:' + values)
            # Get the property from the thing
            find_or_create("Chair base", PropertyType.THREE_DIMENSIONS).update_values([float(x) for x in values])

        except:
            print('Could not parse: ' + line)


def start_gatt():
    # Subscribe to the GATT service
    left_wheel.subscribe(GATT_CHARACTERISTIC_ORIENTATION,
                         callback=handle_orientation_data)

def start_serial():
    while True:
        serial_to_property_values()


thread_gatt = Thread(target=start_gatt)
thread_gatt.start()

thread_serial = Thread(target=start_serial)
thread_serial.start()
