import pygatt  # To access BLE GATT support
import signal  # To catch the Ctrl+C and end the program properly
import os  # To access environment variables
from dotenv import load_dotenv  # To load the environment variables from the .env file
from random import random # Import required library for serial
import time
from threading import Thread
import pexpect
import sys
import serial
from dcd.entities.thing import Thing # DCD Hub
from dcd.entities.property import PropertyType



load_dotenv() # The thing ID and access token
THING_ID = os.environ['THING_ID']
THING_TOKEN = os.environ['THING_TOKEN']

CLASSES = ["Passing", "Adjustment", "Fakeout", "Throw", "Sprint"] # Movement classes
LABEL_PROP_NAME = "Movement"
PROPERTY_HRM_NAME = "My heart rate measurement 1"
PROPERTY_ORIENTATION_NAME = "Right Sports Wheel"
PROPERTY_WHEELCHAIR_NAME = "Chair base"
MAX_SAMPLES = 100 # How many samples do we want for each class
DELAY_BETWEEN_MOVEMENT = 15 # How much time (in seconds) to leave between the collection of each class

BLUETOOTH_DEVICE_MAC_WHEEL = os.environ['BLUETOOTH_DEVICE_MAC_WHEEL']
GATT_CHARACTERISTIC_ORIENTATION = "02118833-4455-6677-8899-AABBCCDDEEFF" # UUID of the GATT characteristic to subscribe
ADDRESS_TYPE = pygatt.BLEAddressType.random # Many devices, e.g. Fitbit, use random addressing, this is required to connect.

# Instantiate a thing with its credential
my_thing = Thing(thing_id=THING_ID, token=THING_TOKEN)

# Read the details of our Thing from the DCD Hub to get property details
my_thing.read()

# Find label and data property by name
prop_label = my_thing.find_or_create_property(LABEL_PROP_NAME, PropertyType.CLASS)
prop_orientation = my_thing.find_or_create_property(PROPERTY_ORIENTATION_NAME, PropertyType.TWO_DIMENSIONS)
#prop_hrm = my_thing.find_or_create_property(PROPERTY_HRM_NAME, PropertyType.ONE_DIMENSION)
prop_wheelchair = my_thing.find_or_create_property(PROPERTY_WHEELCHAIR_NAME, PropertyType.TWO_DIMENSIONS)


# OPEN Serial
def open_serial(): # Open a serial connection
    # Start reading the serial port
    return serial.Serial(
        port=os.environ['SERIAL'],
        baudrate=9600,
        timeout=2)

# BLE

def handle_orientation_data(handle, value_bytes): # print wheel values, send to server
    """
    handle -- integer, characteristic read handle the data was received on
    value_bytes -- bytearray, the data returned in the notification
    """
    print("Received data: %s (handle %d)" % (str(value_bytes), handle))
    values = [float(x) for x in value_bytes.decode('utf-8').split(",")]
    values.pop(2)
    prop_orientation.update_values(values)

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
        str_values.pop(1)
        # Transform the array of string values into float values (numbers)
        values = [float(x) for x in str_values]

        # get the current time in milliseconds
        current_ts_ms = int(round(time.time() * 1000))
        # Update values of data and label properties (send them to the DCD Hub)
        # With the same timestamp, so we can easily connect label and raw data later
        prop_label.update_values([class_index], current_ts_ms)
        prop_wheelchair.update_values(values, current_ts_ms)

        return True
    return False


bleAdapter = pygatt.GATTToolBackend() # Start a BLE adapter
bleAdapter.start()
left_wheel = bleAdapter.connect(BLUETOOTH_DEVICE_MAC_WHEEL, address_type=ADDRESS_TYPE) # Use the BLE adapter to connect to our device
signal.signal(signal.SIGINT, keyboard_interrupt_handler) # Register our Keyboard handler to exit

#end BLE code

# #start of Heartratemonitor CODE
#
# #put your hrm mac address here
# hrmMacAddress = "C5:46:4C:2F:AD:C6"
#
# # Show the property
# #print(my_property.to_json())
#
# # Spawn a child process with gatttool to control your BLE device.
# #Your hrm uses random addressing like most BLE devices.
# #gatttool is the application within debian(your rpi operating system)
# #to communicate with BLE devices. Other single alhabets are flags that you do
# #do not need to know of
# child = pexpect.spawn("sudo gatttool -t random -b {0} -I".format(hrmMacAddress) )
#
# #Connect to hrm
# print("Searching for HRM")
# print("Connecting...")
#
# # The number of times you want to retry connecting before you give up
# # RETRY_CONNECTION = 3
#
# # while True:
# #     try:
# #         child.sendline("connect")
# #         child.expect("Connection successful", timeout=10)
# #     except pexpect.TIMEOUT:
# #         RETRY_CONNECTION = RETRY_CONNECTION - 1
# #         if (RETRY_CONNECTION > 0):
# #             print("timeout, trying again")
# #             continue
# #         else:
# #             print("timeout, giving up.")
# #             break
# #     else:
# #         print("Connected!")
# #         break
#
# #enable notification. 0x000f is found experimentally. You do not need to know this bit
# #unless you are curious. 0100 is to switch on notifications for the particular characteristic.
# child.sendline("char-write-req 0x000f 0100")
#
# #end of hrm code


# START COLLECTING



# Start collecting data for the first class
try:
    collect(0)
except UnicodeDecodeError:
    print('Could not parse: ')

# END OF COLLECTING


def start_gatt():
    # Subscribe to the GATT service of the wheel
    left_wheel.subscribe(GATT_CHARACTERISTIC_ORIENTATION,
                         callback=handle_orientation_data)

def start_serial():
    while True:
        serial_to_property_values()

# def start_HRM():
#     while True:
#         try:
#             child.expect("Notification handle = 0x000e value: ", timeout=5)
#             child.expect("\r\n", timeout=5)
#             print(child.before)
#             intvalue = hexStrToInt(child.before)
#             intvalue_brackets = [intvalue]
#             #print statement to check the hrm reading
#             print(intvalue)
#             #udate new readings to grafana
#             prop_hrm.update_values(intvalue_brackets)
#             ser.write(str(intvalue).encode())
#             ser.write(",".encode()) # this one gave no errors
        #
        # #    ser.write(','.encode())
        #     print("HRM sent to arduino")
        # except KeyboardInterrupt:
        #     print("Exiting...")
        #     # Unsubscribe from characteristic before exiting program
        #     child.sendline("char-write-req 0x000f 0000")
        #     exit(0)


thread_gatt = Thread(target=start_gatt)
thread_gatt.start()

thread_serial = Thread(target=start_serial)
thread_serial.start()

# thread_HRM = Thread(target=start_HRM)
# thread_HRM.start()

#End of threading
