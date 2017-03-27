import argparse
import time

import serial
import pygame


def main(tty, baudrate, update_interval):
    joystick = init_joystick()
    serial_interface = _init_serial(tty, baudrate)
    print("Using:", joystick.get_name())

    while True:
        for event in pygame.event.get():
            if event.type == pygame.JOYAXISMOTION:
                positions = _calculate_servo_positions(joystick.get_axis(0), joystick.get_axis(1), joystick.get_axis(2), joystick.get_axis(3))
                _write_serial(serial_interface, *positions)

        time.sleep(update_interval)


def init_joystick():
    pygame.init()
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    return joystick


def _init_serial(tty, baudrate):
    ser = serial.Serial(port=tty, baudrate=baudrate)
    if (ser.isOpen() == False):
        ser.open()
    return ser


def _calculate_servo_positions(x, y, z, s):
    # Y = (X-A)/(B-A) * (D-C) + C
    # joystick out: A = -1 B = 1 (from -1 to 1) servo in: C = 0 D = 180 (from 0 to 180)
    return [(i - -1) / (1 - -1) * (180 - 0) for i in (x, y, z, s)]


def _write_serial(interface, x, y, z, s):
    command = b"$c%s\n" % bytes([int(x), int(y), int(z), int(s), 90])
    interface.write(command)
    print(command)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Joystick')
    parser.add_argument('tty', help="serial port name")
    parser.add_argument('-b', "--baudrate", type=int, nargs='?', help='set baud rate, default: %(default)s', default=9600)
    parser.add_argument('-i', "--interval", type=float, nargs='?', help='Set update interval, default: %(default)s',
                        default=1)
    args = parser.parse_args()
    main(args.tty, args.baudrate, args.interval)
