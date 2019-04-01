#!/usr/bin/env python3

# Import required library for BLE
import pygatt  # To access BLE GATT support
import signal  # To catch the Ctrl+C and end the program properly
import os  # To access environment variables

# Import required library for serial
from random import random
import time

from dotenv import load_dotenv
import os

from threading import Thread

import serial

import pexpect
import sys

#global variabels
DeltaX = 0

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
    global DeltaX
    DeltaX = int(values[2])
    find_or_create("Right Sports Wheel Arbeid",
                   PropertyType.THREE_DIMENSIONS).update_values(values)


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

#start Serial code

# Start reading the serial port
ser = serial.Serial(
    port = os.environ['SERIAL'],
    baudrate = 9600,
    timeout = 2)
time.sleep(2)

# Read the next line from the serial port
# and update the property values
def serial_to_property_values():
    # Read one line
    line_bytes = ser.readline()
    # If the line is not empty
    if len(line_bytes) > 0:
        # Convert the bytes into string

        line = line_bytes.decode('utf-8')
        # Split the string using commas as separator, we get a list of strings
        serialvalues = line.split(',')

        try:
            # Use the first element of the list as property id
            # property_serial_id = values.pop(0)
            # Get the property from the thing
            find_or_create("Chair base with Fitness", PropertyType.FIVE_DIMENSIONS).update_values([float(x) for x in serialvalues])

        except:
            print('Could not parse: ' + line)

#end of serial code


#start of HRM code

#This function converts hex values received from hrm to integer.
def hexStrToInt(hexstr):
    val = int(hexstr[3:5], 16) #
    if ((val & 0x8000) == 0x8000): # treat signed 16bits
        val = -((val ^ 0xffff) + 1)
        val = int(val)
    return val

#put your hrm mac address here
hrmMacAddress = "C5:46:4C:2F:AD:C6"

# If we have no properties, let's create a random one
if my_thing.find_property_by_name("My heart rate measurement 1") is None:
    # By specifying a property type, the DCD Hub will
    # automatically generate the property dimensions
    # (in this case, 3 generic dimensions)
    my_property_HRM = my_thing.create_property(
        name="My heart rate measurement 1",
        property_type=PropertyType.ONE_DIMENSION)

    # Let's have a look at the property, it should
    # contains the name, a unique id and the dimensions
    print(my_property_HRM.to_json())

# Retrieve the property
my_property_HRM = my_thing.find_property_by_name("My heart rate measurement 1")

# Show the property
#print(my_property.to_json())

# Spawn a child process with gatttool to control your BLE device.
#Your hrm uses random addressing like most BLE devices.
#gatttool is the application within debian(your rpi operating system)
#to communicate with BLE devices. Other single alhabets are flags that you do
#do not need to know of
child = pexpect.spawn("sudo gatttool -t random -b {0} -I".format(hrmMacAddress) )

#Connect to hrm
print("Searching for HRM")
print("Connecting...")

# The number of times you want to retry connecting before you give up
RETRY_CONNECTION = 3

while True:
    try:
        child.sendline("connect")
        child.expect("Connection successful", timeout=10)
    except pexpect.TIMEOUT:
        RETRY_CONNECTION = RETRY_CONNECTION - 1
        if (RETRY_CONNECTION > 0):
            print("timeout, trying again")
            continue
        else:
            print("timeout, giving up.")
            time.sleep(1)
            break
    else:
        print("Connected!")
        time.sleep(1)
        break

#enable notification. 0x000f is found experimentally. You do not need to know this bit
#unless you are curious. 0100 is to switch on notifications for the particular characteristic.
child.sendline("char-write-req 0x000f 0100")

#end of hrm code

#start threading

def start_gatt():
    # Subscribe to the GATT service of the wheel
    left_wheel.subscribe(GATT_CHARACTERISTIC_ORIENTATION,
                         callback=handle_orientation_data)


def start_serial():
    while True:
        serial_to_property_values()

def start_HRM():
    while True:
        try:
            child.expect("Notification handle = 0x000e value: ", timeout=5)
            child.expect("\r\n", timeout=5)
            print(child.before)
            global intvalue
            intvalue = hexStrToInt(child.before)
            intvalue_brackets = [intvalue]
            # #print statement to check the hrm reading
            # print("HRM =" + intvalue)
            #udate new readings to grafana
            my_property_HRM.update_values(intvalue_brackets)
            ser.write(str(intvalue).encode())
            ser.write(",".encode()) # this one gave no errors
            ser.write(str(DeltaX).encode())
            ser.write(",".encode()) # this one gave no errors


        #    ser.write(','.encode())
            print("HRM sent to arduino")
            print("DeltaX sent to arduino")
        except KeyboardInterrupt:
            print("Exiting...")
            # Unsubscribe from characteristic before exiting program
            child.sendline("char-write-req 0x000f 0000")
            exit(0)


thread_gatt = Thread(target=start_gatt)
thread_gatt.start()

thread_serial = Thread(target=start_serial)
thread_serial.start()

thread_HRM = Thread(target=start_HRM)
thread_HRM.start()
