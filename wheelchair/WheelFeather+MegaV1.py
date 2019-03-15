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

import serial

# required for HRM
import pexpect
import sys



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
    exit(0)


# Instantiate a thing with its credential, then read its properties from the DCD Hub
my_thing = Thing(thing_id=THING_ID, token=THING_TOKEN)
my_thing.read()

# Start a BLE adapter
bleAdapter = pygatt.GATTToolBackend()
bleAdapter.start()

# Use the BLE adapter to connect to our device
left_wheel = bleAdapter.connect(BLUETOOTH_DEVICE_MAC_WHEEL, address_type=ADDRESS_TYPE)

# Subscribe to the GATT service
left_wheel.subscribe(GATT_CHARACTERISTIC_ORIENTATION,
                     callback=handle_orientation_data)

# Register our Keyboard handler to exit
signal.signal(signal.SIGINT, keyboard_interrupt_handler)




#
# # HRM code start
#
# #This function converts hex values received from hrm to integer.
# def hexStrToInt(hexstr):
#     val = int(hexstr[3:5], 16) #
#     if ((val & 0x8000) == 0x8000): # treat signed 16bits
#         val = -((val ^ 0xffff) + 1)
#         val = float(val)
#     return val
#
# #put your hrm mac address here
# hrmMacAddress = "C5:46:4C:2F:AD:C6"
#
# #access your thing in the hub from this program
# #load_dotenv()
# #THING_ID = os.environ['THING_ID']
# #THING_TOKEN = os.environ['THING_TOKEN']
#
# # Instantiate a thing with its credential
# #my_thing = Thing(thing_id=THING_ID, token=THING_TOKEN)
#
# # We can read the details of our thing,
# # i.e. retrieving its information from the hub
# my_thing.read()
#
# # If you just registered your Thing on the DCD Hub,
# # it has only an id, a name and a type.
# print(my_thing.to_json())
#
# # If we have no properties, let's create a random one
# if my_thing.find_property_by_name("My heart rate measurement 1") is None:
#     # By specifying a property type, the DCD Hub will
#     # automatically generate the property dimensions
#     # (in this case, 3 generic dimensions)
#     my_property = my_thing.create_property(
#         name="My heart rate measurement 1",
#         property_type=PropertyType.ONE_DIMENSION)
#
#     # Let's have a look at the property, it should
#     # contains the name, a unique id and the dimensions
#     print(my_property.to_json())
#
# # Retrieve the property
# my_property = my_thing.find_property_by_name("My heart rate measurement 1")
#
# # Show the property
# print(my_property.to_json())
#
# # Spawn a child process with gatttool to control your BLE device.
# #Your hrm uses random addressing like most BLE devices.
# #gatttool is the application within debian(your rpi operating system)
# #to communicate with BLE devices. Other single alhabets are flags that you do
# #do not need to know of
# child = pexpect.spawn("sudo gatttool -t random -b {0} -I".format(hrmMacAddress) )
#
# #Connect to hrm
# print("Searchinf for HRM")
# print("Connecting...")
#
# # The number of times you want to retry connecting before you give up
# RETRY_CONNECTION = 2
#
# while True:
#     try:
#         child.sendline("connect")
#         child.expect("Connection successful", timeout=5)
#     except pexpect.TIMEOUT:
#         RETRY_CONNECTION = RETRY_CONNECTION - 1
#         if (RETRY_CONNECTION > 0):
#             print("timeout, trying again")
#             continue
#         else:
#             print("timeout, giving up.")
#             break
#     else:
#         print("Connected!")
#         break
#
# #enable notification. 0x000f is found experimentally. You do not need to know this bit
# #unless you are curious. 0100 is to switch on notifications for the particular characteristic.
# child.sendline("char-write-req 0x000f 0100")
#
# #read hrm data
# while True:
#     try:
#         child.expect("Notification handle = 0x000e value: ", timeout=5)
#         child.expect("\r\n", timeout=5)
#         print(child.before)
#         intvalue = [hexStrToInt(child.before)]
#         #print statement to check the hrm reading
#         print(intvalue)
#         #udate new readings to grafana
#         my_property.update_values(intvalue)
#     except KeyboardInterrupt:
#         print("Exiting...")
#         # Unsubscribe from characteristic before exiting program
#         child.sendline("char-write-req 0x000f 0000")
#         exit(0)
#
# # HRM code end




#serial code start

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

        print('SERIAL DATA FOUND!')
        # Convert the bytes into string
        line = line_bytes.decode('utf-8')
        # Split the string using commas as separator, we get a list of strings
        values = line.split(',')
        # Use the first element of the list as property id
        property_id = values.pop(0)
        # Get the property from the thing
        prop = my_thing.properties[property_id]
        # If we find the property, we update the values (rest of the list)
        if prop is not None:
            prop.update_values([float(x) for x in values])
        # Otherwise, we show a warning
        else:
            print('Warning: unknown property ' + property_id)

    # Finally, we call this method again
    serial_to_property_values()

serial_to_property_values()

# serial code end
