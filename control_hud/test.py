#!/usr/bin/python3


###
# INFO
###
# Python3
# GTK2 (rewrite to GTK3 possible)
# see wiki for dependencies

###
# TODO
###
# - Gradindikator außen um künstlichen Horizont
# - Weiße Linien sind fix (um die Mitte)


import argparse
import sys
import gi
import threading
import cairo
import math
import serial
import queue
from time import sleep
gi.require_version('Gtk', '2.0')
from gi.repository import Gtk as gtk
from gi.repository import GObject as gobject


# local files
import helper as h
import udpreceiver


# flags
useSerial = False
serialport = "/dev/ttyUSB3"
serialbaud = 115200
framerate = 1
RADIUS_DIVIDER = 3.2


# parse commandline arguments
parser = argparse.ArgumentParser(description='Control HUD GUI')
parser.add_argument('--mode', type=str, help='Either "demo" or "serial"')
parser.add_argument('--serialport', type=str, help='serial port, defaults to ' + serialport)
parser.add_argument('--serialbaud', type=str, help='serial baud rate, defaults to ' + str(serialbaud))
parser.add_argument('--fps', type=str, help='Set the number of rendered frames per second')
args = parser.parse_args()
if args.mode == "serial":
	useSerial = True
if args.fps:
	framerate = args.fps
if args.serialport:
	serialport = args.serialport
if args.serialbaud:
	serialbaud = args.serialbaud


class PyApp(gtk.Window):

    def __init__(self):
        super(PyApp, self).__init__()

        # where sensor data gets saved
        # these should be changed by a separate thread
        # via lock
        self.sensorQuaternion = [-1, 0, 0, 0]
        self.speed = 0

        # runner variables
        self.qe1 = 1
        self.qe2 = 2.2
        self.qe3 = 3
        self.x = 1

        self.set_title("Ground Station HUD")
        self.resize(830, 450)
        #self.set_position(gtk.WIN_POS_CENTER)

        self.connect("destroy", gtk.main_quit)

        darea = gtk.DrawingArea()

        # gtk3
        #darea.connect("draw", self.render)
        # gtk2
        darea.connect("expose-event", self.render)

        self.add(darea)

        self.show_all()

        # gtk3
        #self.w = self.get_allocation().width
        #self.h = self.get_allocation().height
        # gtk2
        self.w = self.allocation.width
        self.h = self.allocation.height


        # reale sensordaten
        # w, x, y, z
        # TODO needed format: xyzw
        self.realExampleQuats = [
            # aufrecht
            [0.85, 0.14, 0.0, -0.51, "aufrecht"],
            [0.35, 0.03, -0.03, -0.94, "aufrecht"],

            # 45 ° x achse
            [0.38, 0.13, -0.32, -0.86, "45° x axis"],

            # 90 ° entlang y achse
            [0.2, -0.63, -0.2, -0.73, "90° y axis"],

            # 45 ° nach unten
            [0.77, 0.2, 0.24, -0.57, "45° bottom view"]
        ]
        self.numRealExampleQuats = len(self.realExampleQuats)

        # fire up timer
        self.timer_next()

        # create a lock for self.sensorQuaternion
        self.lock = threading.Lock()

        # read quaternions concurrently
        if useSerial:
            t = threading.Thread(None, self.read_serial)
            t.start()

        # input queue (data from udpreceiver)
        self.queue = queue.Queue()
        udp_receiver = udpreceiver.UdpReceiver()
        t_udp = threading.Thread(None, udp_receiver.listen, args=(self.queue, ))
        t_udp.start()

        print("__init__ Setup OK")

    # blocking call
    # always read from the serial port and store the quaternion to self.sensorQuaternion
    # TODO xyzw vs wxyz??
    def read_serial(self):
        try:
            ser = serial.Serial(serialport, baudrate=serialbaud)
            while True:
                byts = ser.readline()
                with self.lock:
                    sq = eval(byts)
                    lastx = sq[0]
                    sq.remove(0)
                    sq.append(lastx)
                    self.sensorQuaternion = sq
                    print("Last sensor val: ", self.sensorQuaternion)
        except serial.serialutil.SerialException as e:
            print("Error while using serialport: ", e)
            sys.exit(-1)


    def check_queue(self, cr):
        """
        check self.queue for new items
        :return:
        """
        if self.queue.empty():
            return

        item_to_parse: dict = self.queue.get(block=False)
        self.parse_and_draw_stuff(cr, item_to_parse)


    def parse_and_draw_stuff(self, cr, to_parse: dict):
        print("Draw Thread: Got queue item:", to_parse)

        # more json keys go here
        # TODO draw everything you get in here
        c_debug = "debug"
        c_magneto = "mag"
        if c_debug in to_parse:
            val = to_parse[c_debug]
            print(c_debug, val)
            self.draw_debug(cr, val)
        elif c_magneto in to_parse:
            val = to_parse[c_magneto]
            print(c_magneto, val)
            self.draw_magneto(cr, val)

    def draw_debug(self, cr, m_str: str):
        # TODO grahpics
        pass

    def draw_magneto(self, cr, val):
        # TODO grahpics
        pass


    def timer_next(self):
        self.queue_draw()
        gobject.timeout_add(1000/framerate, self.timer_next)

    # split visible frame into 4 rectangles
    def drawOutlines(self, cr):
        cr.set_line_width(3)
        cr.set_source_rgb(0.5, 0.5, 0.5)
        cr.rectangle(0, 0, self.w/2, self.h/2)
        cr.stroke_preserve()
        cr.rectangle(self.w/2, 0, self.w/2, self.h/2)
        cr.stroke_preserve()
        cr.rectangle(0, self.h/2, self.w/2, self.h/2)
        cr.stroke_preserve()
        cr.rectangle(self.w/2, self.h/2, self.w/2, self.h/2)
        cr.stroke_preserve()

    def render(self, widget, event):




        self.x+=1


        # save (for resizing)
        # gtk3
        #self.w = self.get_allocation().width
        #self.h = self.get_allocation().height
        # gtk2
        self.w = self.allocation.width
        self.h = self.allocation.height

        # drawing context
        cr = widget.window.cairo_create()

        self.drawBackground(cr)

        cr.save()
        if useSerial:
            with self.lock:
                q = self.sensorQuaternion
            self.drawArtificialHorizon(q, cr)
        else:
            self.drawArtificialHorizon(self.realExampleQuats[self.x%self.numRealExampleQuats], cr)
        cr.restore()

        cr.save()
        self.drawSpeed(cr)
        cr.restore()

        cr.save()
        self.drawOutlines(cr)
        cr.restore()

        cr.save()
        self.check_queue(cr)
        cr.restore()

    # q: quaternion (x, y, z, w)
    def drawArtificialHorizon(self, q, cr):

        xyz = h.Quaternion_toEulerianAngle(q)
        x_deg = xyz[0]
        y_deg = xyz[1]
        z_deg = xyz[2]
        yaw = math.radians(x_deg)
        pitch = math.radians(y_deg)
        roll = math.radians(z_deg)

        # x - roll
        # y - pitch
        # z - yaw
        # really?

        print()
        print()
        # also print an info string if present
        if len(q) == 5:
            print("Info: ", q[4])
        print("Quaternion:      ", q)
        print("Euler (°):       ", xyz)
        print("Euler RPY (Rad): ", (roll, pitch, yaw))
        print("")

        mWidth = self.w/2
        mHeight = self.h/2
        radius = min(mHeight/RADIUS_DIVIDER, mWidth/RADIUS_DIVIDER)

        # calculate angles for drawing the earth
        # this has to be flipped? or changed?
        # seems like earth is always on the wrong side...
        earthStartAngle = roll
        earthEndAngle = roll + math.pi

        # calculate point M (middle of route PQ)
        # check, if we are upside down:
        # upsideDown stuff is kind of wonky...
        # valueMap is not really fixed?
        isUpsideDown = False
        w = h.valueMap(pitch, -math.pi, math.pi, -2*radius, 2*radius)
        #if pitch >= math.pi/2 and pitch <= 3*(math.pi/2):
        #    print("Upside down!")
        #    w = -w
        #    isUpsideDown = True

        xc = mWidth/2
        yc = mHeight/2
        beta = (math.pi/2) - earthEndAngle

        # comment in if indicator should relativ the the point
        # between P and Q on the circle
        mx = xc# + (math.cos(beta) * w)
        my = yc - (math.sin(beta) * w)

        # outer, static, circles
        cr.set_source_rgb(0.2, 0.6, 0.85)
        cr.arc(xc, yc, radius+radius*0.2, 0, 2*math.pi)
        cr.fill()
        cr.set_source_rgb(0.627, 0.321, 0.176)
        cr.arc(xc, yc, radius+radius*0.2, 0, -math.pi)
        cr.fill()

        # angle indicators
        self.drawAngleIndicators(radius, xc, yc, cr)
        
        # white gap
        cr.set_source_rgb(1, 1, 1)
        cr.arc(xc, yc, radius+radius*0.05, 0, 2*math.pi)
        cr.fill()

        # sky
        cr.set_line_width(3)
        cr.set_source_rgb(0.7, 0.2, 0.0)
        cr.translate(0, 0)
        cr.arc(mWidth/2, mHeight/2, radius, 0, 2*math.pi)
        cr.clip_preserve()
        cr.stroke_preserve()
        cr.set_source_rgb(0.2, 0.6, 0.85)
        cr.fill()

        # inner circle (earth, brown)
        cr.set_source_rgb(0.627, 0.321, 0.176)
        cr.arc(mx, my, radius*3, earthStartAngle, earthEndAngle)
        cr.fill()

        # white lines
        self.drawAttitudeIndicator(radius=radius, alpha=earthEndAngle, mx=mx, my=my, cr=cr)

        # fixed cross indicator (stays at the same position)
        fixedRadius = radius/6
        cr.set_source_rgb(0, 0, 0)
        cr.arc(mWidth/2, mHeight/2, fixedRadius, 0, math.pi)
        cr.stroke()
        cr.move_to((mWidth/2) - 2*radius/3, mHeight/2)
        cr.line_to((mWidth/2) - fixedRadius, mHeight/2)
        cr.stroke()
        cr.move_to((mWidth/2) + 2*radius/3, mHeight/2)
        cr.line_to((mWidth/2) + fixedRadius, mHeight/2)
        cr.stroke()
        cr.move_to(mWidth/2, mHeight/2)
        cr.line_to(mWidth/2, mHeight/2 + fixedRadius)
        cr.stroke()
        cr.set_line_width(2)
        cr.move_to(mWidth/2, mHeight/2)
        cr.line_to(mWidth/2, mHeight/2 + radius)
        cr.stroke()


        # draw the triangle MC?
        # for geometric debug
        """
        cr.set_source_rgb(0, 0, 0)
        cr.set_line_width(5)
        cr.move_to(xc, yc)
        cr.line_to(mx, my)
        cr.stroke_preserve()
        cr.line_to(mx, yc)
        cr.line_to(xc, yc)
        cr.fill()
        """

        cr.reset_clip()


    def drawAttitudeIndicator(self, radius, alpha, mx, my, cr):

        # white attitude indicator
        # change those params:
        indicators = 7
        indicatorGap = radius/16 #px
        indicatorMaxLen = radius/6
        indicatorLineWidth = radius/32 #px

        cr.set_source_rgb(0.8, 0.8, 0.8)
        cr.set_line_width(indicatorLineWidth)

        cr.save()
        cr.translate(mx, my)
        n = 0
        m = 1
        o = 1
        for i in range(indicators):
            p1x = -indicatorMaxLen/4 if n%2 == 0 else (o*0.3)*(-indicatorMaxLen/4)
            p1y = m*indicatorGap
            p2x =  indicatorMaxLen/4 if n%2 == 0 else (o*0.3)*( indicatorMaxLen/4)
            p2y = m*indicatorGap
            pBx, pBy = p2x, p2y
            pAx, pAy = p1x, p1y
            pCx, pCy = h.rotate2D(pAx, pAy, math.pi)
            pDx, pDy = h.rotate2D(pBx, pBy, math.pi)
            """
            pBx, pBy = h.rotate2D(p2x, p2y, alpha)
            pAx, pAy = h.rotate2D(p1x, p1y, alpha)
            pCx, pCy = h.rotate2D(pAx, pAy, math.pi)
            pDx, pDy = h.rotate2D(pBx, pBy, math.pi)
            """
            # draw
            cr.move_to(pAx, pAy)
            cr.line_to(pBx, pBy)
            cr.stroke()
            cr.move_to(pCx, pCy)
            cr.line_to(pDx, pDy)
            cr.stroke()
            n += 1
            m += 1
            o += 2

        cr.restore()

        return

    def drawAngleIndicators(self, radius, xc, yc, cr):
        cr.save()
        cr.set_line_width(5)
        cr.set_source_rgb(1, 1, 1)
        cr.translate(xc, yc)
        angles = [0, -30, 30, -60, 60, -90, 90]
        for angle in angles:
            drawAngle = 180 - (angle - 90)
            cr.move_to(0, 0)
            aPx = radius + radius*0.35
            aPy = 0
            rPx, rPy = h.rotate2D(aPx, aPy, math.radians(drawAngle))
            cr.line_to(rPx, rPy)
            cr.stroke()
            self.drawTextAt(str(angle) + "°", rPx, rPy, self.h/50, cr)
        
        cr.restore()


    # returns a tuple (x, y, z, w)
    def getNextSampleQuaternion(self):
        self.qe1 += 0.05
        self.qe2 += 0.03
        self.qe3 += 0.07
        #return h.Euler_toQuaternion(math.sin(self.qe1)*math.pi, math.cos(self.qe2)*math.pi, math.sin(self.qe3))
        roll = -math.sin(self.qe1)*(math.pi/2)
        pitch = math.sin(self.qe2)*(math.pi/2)
        yaw = math.sin(self.qe3)


        print("Input getNext... ", roll, pitch, yaw)
        return h.Euler_toQuaternion(roll, pitch, yaw)

    def drawBackground(self, cr):
        cr.save()
        cr.set_source_rgb(0.9, 0.9, 0.9)
        cr.rectangle(0, 0, self.w, self.h)
        cr.fill()
        cr.restore()

    def drawData(self, cr):
        pass

    def drawSpeed(self, cr):
        strToRender = "Speed: " + str(self.speed) + " m/s"
        self.drawTextAt(strToRender, 3*self.w/4, self.h/32, self.h/42, cr)

    def drawTextAt(self, text, x, y, fontsize, cr):
        cr.save()
        cr.set_source_rgb(1, 0, 0)
        cr.select_font_face("Courier", cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_BOLD)
        cr.set_font_size(fontsize)
        (_x, _y, width, height, dx, dy) = cr.text_extents(text) 
        cr.move_to(x - width/2, y)
        cr.show_text(text)
        cr.restore()

if __name__ == "__main__":
    app = PyApp()
    gtk.main()
