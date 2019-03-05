import serial
import time
import datetime
import keyboard as kb
from threading import Timer

# ######################
# ### Configure here ###
# ######################

# Shortcut to start working
kb_shortcut_startWork = "strg+alt+w"
# Shortcut to start a short pause
kb_shortcut_startShortPause = "strg+alt+p"
# Shortcut to start a long pause
kb_shortcut_startLongPause = "strg+alt+shift+p"
# Shortcut to stop the current phase
kb_shortcut_interrupt = "strg+alt+shift+z"

# The COM Port where the WorkatoBox is connected
com_port = "com7"
# The baudrate to use for Serial communication
baudrate = 115200

# #####################
# ### End of Config ###
# #####################


# Global variable holding the current phase of the WorkatoBox
currentPhase = "stop"
arduinoSerial = serial.Serial(com_port, baudrate)

def log(msg):
    print(datetime.datetime.now(), " :: ", msg)

log("Starting WorkatoBoxController")
time.sleep(1)
arduinoSerial.write(currentPhase.encode())

def on_start_work():
    global currentPhase, timer_work, timer_shortpause, timer_longpause
    if timer_work == None and timer_shortpause == None and timer_longpause == None:
        log("Starting work phase (25min)")
        timer_work = Timer(25.0 * 60, on_stop)
        timer_work.start()
        currentPhase = "work"
        arduinoSerial.write(currentPhase.encode())
    else:
        log("Cannot start/restart work, current phase: " + currentPhase)

def on_start_shortpause():
    global currentPhase, timer_work, timer_shortpause, timer_longpause
    if timer_shortpause == None and timer_work == None and timer_longpause == None:
        log("Starting short pause phase (5min)")
        timer_shortpause = Timer(5.0 * 60, on_stop)
        timer_shortpause.start()
        currentPhase = "shortpause"
        arduinoSerial.write(currentPhase.encode())
    else:
        log("Cannot start/restart short pause, current phase: " + currentPhase)

def on_start_longpause():
    global currentPhase, timer_work, timer_shortpause, timer_shortpause
    if timer_longpause == None and timer_work == None and timer_longpause == None:
        log("Starting long pause phase (10min)")
        timer_longpause = Timer(10.0 * 60, on_stop)
        timer_longpause.start()
        currentPhase = "longpause"
        arduinoSerial.write(currentPhase.encode())
    else:
        log("Cannot start/restart long pause, current phase: " + currentPhase)

def on_stop():
    global currentPhase, timer_work, timer_shortpause, timer_longpause
    log("Stopping current phase")
    currentPhase = "stop"
    timer_work = None
    timer_shortpause = None
    timer_longpause = None
    arduinoSerial.write(currentPhase.encode())

def on_timer_interrupt():
    global currentPhase, timer_work, timer_shortpause, timer_longpause
    log("Interrupting current phase: " + currentPhase)
    if currentPhase == "work":
        timer_work.cancel()
        timer_work = None
    elif currentPhase == "shortpause":
        timer_shortpause.cancel()
        timer_shortpause = None
    elif currentPhase == "longpause":
        timer_longpause.cancel()
        timer_longpause = None
    currentPhase = "stop"
    on_stop()

# Initialize timers
timer_work = None
timer_shortpause = None
timer_longpause = None

# Define hotkeys
kb.add_hotkey(kb_shortcut_startWork, on_start_work)
kb.add_hotkey(kb_shortcut_startShortPause, on_start_shortpause)
kb.add_hotkey(kb_shortcut_startLongPause, on_start_longpause)
kb.add_hotkey(kb_shortcut_interrupt, on_timer_interrupt)

# Block forever and wait for user input
kb.wait()