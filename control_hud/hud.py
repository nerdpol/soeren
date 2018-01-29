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
# - Himmelsrichtungen (mit bar)
# - Höhen- und Geschwindigkeitsverlauf (Diagramm via Ringpuffer)
# - Diagramm:
# 	- 100m Schnellindikator
# - drawArtificialHorizon neu malen (mit Koordinaten (x_todo, y_todo))
# - Schriftgrößen anpassen (Skalierung)
# - Data class to collect all sensor data


import argparse
import sys
import gi
import threading
import cairo
import time
import math
import random
import serial
import json
from time import sleep
gi.require_version('Gtk', '2.0')
from gi.repository import Gtk as gtk
from gi.repository import GObject as gobject

# local libs
import lib.helper as h
from lib.ringbuf import RingBuffer
from lib.udp.receiver import UdpReceiverQueues

# flags
framerate = 10
useDummyData = True

# constants
UDP_DEFAULT_PORT = 5005

RADIUS_DIVIDER = 3.2
LINEAR_DIVIDER_HEIGHT = 8
LINEAR_DIVIDER_WIDTH  = 12
# m
SENSOR_HEIGHT_MIN     = 0
SENSOR_HEIGHT_MAX     = 30000
# m/s
SENSOR_SPEED_MIN      = 0
SENSOR_SPEED_MAX      = 100

# diagram
DIAGRAM_WIDTH_DIVIDER  = 1.5
DIAGRAM_HEIGHT_DIVIDER = 4
# what timespan does our diagram capture?
# in ms
DIAGRAM_TIMESPAN       = 10000
RINGBUF_CAPACITY       = 100




# parse commandline arguments
parser = argparse.ArgumentParser(description='Control HUD GUI')
parser.add_argument('--port', type=str, help='udp port to listen to')
parser.add_argument('--fps', type=str, help='Set the number of rendered frames per second')
args = parser.parse_args()
if args.fps:
	framerate = args.fps
if args.port:
	udp_port = args.port
else:
    udp_port = UDP_DEFAULT_PORT


def ms():
    return int(time.time()*1000.0)

def exit():
    pass


class HeadUpDisplay(gtk.Window):

    def __init__(self):
        super(HeadUpDisplay, self).__init__()

        self.lastSensorQuaternion = [-1, 0, 0, 0]
        self.speed = 0

        self.urq = UdpReceiverQueues()
        self.quat_queue = self.urq.get_queue("quat")

        # spawn thread to always read
        self.udp_recv_thread = threading.Thread(None, target=self.urq.listen)
        self.udp_recv_thread.start()

        # runner variables
        self.qe1 = 1
        self.qe2 = 2.2
        self.qe3 = 3
        self.x = 1
        self.quat_count = 0

        self.set_title("Ground Station HUD")
        self.resize(830, 450)
        #self.set_position(gtk.WIN_POS_CENTER)

        #self.connect("destroy", self.quit)
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

        # fire up timer
        self.timer_next()

        if useDummyData:
            self.t2 = threading.Thread(None, self.dummy_data)
            self.t2.start()

        # create ringbuffers
        # one item is a tuple t:
        #  t[0] - timestamp in ms
        #  t[1] - value for speed / height
        self.ringbuf_speed  = RingBuffer(RINGBUF_CAPACITY)
        self.ringbuf_height = RingBuffer(RINGBUF_CAPACITY)
        # and add some dummy values
        for i in range(RINGBUF_CAPACITY):
        	self.ringbuf_speed.append((ms(), h.valueMap(math.sin(math.cos(i)), -1, 1, SENSOR_SPEED_MIN, SENSOR_SPEED_MAX)))
        	self.ringbuf_height.append((ms(), h.valueMap(i, 0, RINGBUF_CAPACITY, SENSOR_HEIGHT_MIN, SENSOR_HEIGHT_MAX)))


    def timer_next(self):
        self.queue_draw()
        gobject.timeout_add(1000/framerate, self.timer_next)


    def dummy_data(self):
        while True:
            sleep(random.uniform(0.05, 0.8))
            # print("dummy data ringbuffers written")
            #y = int(input("Input arbitrary data point!"))
            #self.ringbuf_speed.append((ms(), y))
            self.ringbuf_speed.append((ms(), h.valueMap(math.sin(math.cos(self.x*0.1)), -1, 1, SENSOR_SPEED_MIN, SENSOR_SPEED_MAX)))
            self.ringbuf_height.append((ms(), h.valueMap(self.x%RINGBUF_CAPACITY, 0, RINGBUF_CAPACITY, SENSOR_HEIGHT_MIN, SENSOR_HEIGHT_MAX)))


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


        # Artificial Horizon
        cr.save()
        xah = self.w/4
        yah = 0
        # always use udp
        try:
            packet = self.quat_queue.get(block=True, timeout=0.01)
            self.quat_queue.task_done()
            q = packet["quat0"], packet["quat1"], packet["quat2"], packet["quat3"]
            self.lastSensorQuaternion = q
            self.quat_count += 1
            print("quat_count:", self.quat_count)
        except Exception as e:
            q = self.lastSensorQuaternion
            print("exc.", e)
        self.drawArtificialHorizon(q, cr, xah, yah)
        cr.restore()


        # diagrams
        cr.save()
        self.drawDiagram(cr, self.w/2, 3*self.h/4, self.ringbuf_speed, self.ringbuf_height)
        cr.restore()


        # bar indicator speed ?
        cr.save()
        # self.drawSpeed(cr, 9*self.w/16, self.h/4, self.x%100)
        self.drawSpeed(cr, self.w/6, self.h/4, self.x%100)
        cr.restore()


        # bar indictor height ?
        cr.save()
        self.drawHeight(cr, 5*self.w/6, self.h/4, (self.x*10)%30000)
        cr.restore()


    # q: quaternion (x, y, z, w)
    def drawArtificialHorizon(self, q, cr, x_todo, y_todo):
        
        cr.save()
        cr.translate(x_todo, y_todo)

        xyz = h.Quaternion_toEulerianAngle(q)
        x_deg = xyz[0]
        y_deg = xyz[1]
        z_deg = xyz[2]
        yaw = math.radians(x_deg)
        roll = -math.radians(y_deg)  # should be fine
        pitch = math.radians(z_deg)

        # x - roll
        # y - pitch
        # z - yaw
        # really?

        #print()
        # also print an info string if present
        if len(q) == 5:
            print("Quaternion[4]: ", q[4])
        #print("Quaternion:      ", q)
        #print("Euler (°):       ", xyz)
        #print("Euler RPY (Rad): ", (roll, pitch, yaw))

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
        w = h.valueMap(pitch, -math.pi, math.pi, -4*radius, 4*radius)
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

        # show angles as text
        self.showEularianAnglesAsText(cr, xc, mHeight-self.h/32, x_deg, y_deg, z_deg)

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
        self.drawAttitudeIndicator(radius=radius, alpha=earthEndAngle, mx=xc, my=yc, cr=cr)

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
        cr.restore()


    def drawAttitudeIndicator(self, radius, alpha, mx, my, cr):

        # white attitude indicator
        # change those params:
        indicators = 7
        indicatorGap = radius/20 #px
        indicatorMaxLen = radius/5
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


    def showEularianAnglesAsText(self, cr, draw_x, draw_y, x, y, z):
        """
        draw pitch and roll under artificial horizon
        """
        cr.save()
        cr.set_line_width(5)
        cr.set_source_rgb(1, 1, 1)
        self.drawTextAt(cr, f"pitch: {z:.3f},  roll: {y:.3f}", draw_x, draw_y, self.h/50)
        cr.restore()


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
            self.drawTextAt(cr, str(angle) + "°", rPx, rPy, self.h/50)

        cr.restore()


    def drawBackground(self, cr):
        cr.save()
        cr.set_source_rgb(0.9, 0.9, 0.9)
        cr.rectangle(0, 0, self.w, self.h)
        cr.fill()
        cr.restore()


    def drawHeight(self, cr, xc, yc, height):
        """
        draw a height indicator around (xc, yc)
        :param cr: drawing context
        :param xc: center x
        :param yc: center y
        :param height: height in meters
        :return: -
        """
        cr.save()
        #print("drawHeight")

        cr.translate(xc, yc)

        # headline text
        self.drawTextAt(cr, "Height (m)", 0, -self.h / LINEAR_DIVIDER_HEIGHT * 1.2, 15, color=(0, 0, 1))

        # surrounding rect
        # print("drawSpeed")
        cr.set_source_rgb(1, 0, 0)
        cr.rectangle(-self.w / LINEAR_DIVIDER_WIDTH, -self.h / LINEAR_DIVIDER_HEIGHT, self.w / LINEAR_DIVIDER_WIDTH * 2,
                     self.h / LINEAR_DIVIDER_HEIGHT * 2)
        cr.fill()

        # indicator line
        slideHeight = h.valueMap(height, SENSOR_HEIGHT_MIN, SENSOR_HEIGHT_MAX, self.h / LINEAR_DIVIDER_HEIGHT,
                                 -self.h / LINEAR_DIVIDER_HEIGHT)
        cr.set_source_rgb(0, 0, 1)
        cr.move_to(-self.w / LINEAR_DIVIDER_WIDTH, slideHeight)
        cr.line_to(self.w / LINEAR_DIVIDER_WIDTH, slideHeight)
        cr.stroke()

        # indicator text (value)
        self.drawTextAt(cr, str(height) + "", self.w / LINEAR_DIVIDER_WIDTH * 1.5, slideHeight, 16, color=(0, 0, 1))

        # Min & Max
        self.drawTextAt(cr, str(SENSOR_HEIGHT_MIN), self.w / LINEAR_DIVIDER_WIDTH * 1.5,
                        +1.1 * self.h / LINEAR_DIVIDER_HEIGHT, 10, color=(0, 0, 1))
        self.drawTextAt(cr, str(SENSOR_HEIGHT_MAX), self.w / LINEAR_DIVIDER_WIDTH * 1.5,
                        -1.1 * self.h / LINEAR_DIVIDER_HEIGHT, 10, color=(0, 0, 1))

        cr.restore()
        pass


    def drawDiagram(self, cr, xc, yc, speed: RingBuffer, height: RingBuffer):
        cr.save()
        cr.translate(xc, yc)

        hei = self.h / DIAGRAM_HEIGHT_DIVIDER
        wid = self.w / DIAGRAM_WIDTH_DIVIDER

        color_speed  = (0.5, 0, 0.5)
        color_height = (0, 0.5, 0.5)

        # y axis description
        # self.drawTextAt(cr, "Speed / Height", 0, -hei/1.5, 15, color=(0,1,0))
        self.drawTextAt(cr, "Speed", -wid/2, -hei/1.3, 15, color=color_speed)
        self.drawTextAt(cr, "Height", -wid/2, -hei/1.1, 15, color=color_height)

        # x axis description
       	self.drawTextAt(cr, str(DIAGRAM_TIMESPAN) + "ms - " + str(DIAGRAM_TIMESPAN/1000) + "s", 0, 3*hei/4, 15, color=(0,1,0))

        # border
        cr.rectangle(-wid/2, -hei/2, wid, hei)
        cr.set_source_rgb(0.5, 0.5, 0)
        cr.set_line_width(2)
        cr.stroke()

        # arrows
        #self.drawArrow(cr, -wid/2, -hei/2, -wid/2, hei/2, 5)
        #self.drawArrow(cr, -wid/2, -hei/2, wid/2, -hei/2, 5)

        # horizontal
        self.drawArrow(cr, -wid/2, hei/2, wid/1.7, hei/2, 5)
        # vertical
        self.drawArrow(cr, -wid/2, hei/2, -wid/2, -hei/1.7, 5)

        # clip diagram rectangle
        # (To not draw out of range)
        cr.rectangle(-wid/2, -hei/2, wid, hei)
        cr.clip()

        # speed
        # get speed points
        # list comprehension spitts out points (x,y) (relative Coordinates)
        current_ms = ms()
        speed_points_x = (h.valueMap(x[0], current_ms-DIAGRAM_TIMESPAN, current_ms, -wid/2, wid/2) \
                         for i, x in enumerate(speed.get()) if current_ms - DIAGRAM_TIMESPAN <= x[0])
        speed_points_y = (h.valueMap(elem[1], SENSOR_SPEED_MAX, SENSOR_SPEED_MIN, -hei/2, hei/2) \
        	         for i, elem in enumerate(speed.get()) if current_ms - DIAGRAM_TIMESPAN <= elem[0])
        speed_points = list(zip(speed_points_x, speed_points_y))
        if len(speed_points) == 0:
            return

        # draw points
        lastPoint = speed_points[0]
        cr.set_source_rgb(*color_speed)
        for point in speed_points:
        	# dot
        	cr.arc(point[0], point[1], 3, 0, 2*math.pi)
        	cr.fill()

        	# line to last
        	cr.move_to(lastPoint[0], lastPoint[1])
        	cr.line_to(point[0], point[1])
        	cr.set_line_width(1)
        	cr.stroke()

        	# update last p
        	lastPoint = point


        # height
        height_points_x = (h.valueMap(x[0], current_ms-DIAGRAM_TIMESPAN, current_ms, -wid/2, wid/2) \
                         for i, x in enumerate(height.get()) if current_ms - DIAGRAM_TIMESPAN <= x[0])
        height_points_y = (h.valueMap(elem[1], SENSOR_HEIGHT_MAX, SENSOR_HEIGHT_MIN, -hei/2, hei/2) \
        	         for i, elem in enumerate(height.get()) if current_ms - DIAGRAM_TIMESPAN <= elem[0])
        height_points = list(zip(height_points_x, height_points_y))
        if len(height_points) == 0:
            return

        # draw points
        cr.set_source_rgb(*color_height)
        lastPoint = height_points[0]
        for point in height_points:
        	# dot
        	cr.arc(point[0], point[1], 3, 0, 2*math.pi)
        	cr.fill()

        	# line to last
        	cr.move_to(lastPoint[0], lastPoint[1])
        	cr.line_to(point[0], point[1])
        	cr.set_line_width(1)
        	cr.stroke()

        	# update last p
        	lastPoint = point

        cr.reset_clip()
        cr.restore()
        pass

    def drawArrow(self, cr, xa, ya, xb, yb, line_width):
    	"""
    	draw an arrow from (xa, ya) to (xb, yb)
    	using line_width ^^
    	"""
    	cr.save()

    	# line
    	cr.move_to(xa, ya)
    	cr.line_to(xb, yb)
    	cr.set_line_width(line_width)
    	cr.stroke()

    	# head
    	phi = math.atan2(yb-ya, xb-xa) - math.pi
    	vec_x = xb - xa
    	vec_y = yb - ya
    	r = math.sqrt(vec_x**2 + vec_y**2)
    	x_dest_1 = (r * math.cos(phi + math.pi/16)) / 8
    	y_dest_1 = (r * math.sin(phi + math.pi/16)) / 8
    	x_dest_2 = (r * math.cos(phi - math.pi/16)) / 8
    	y_dest_2 = (r * math.sin(phi - math.pi/16)) / 8
    	cr.translate(xb, yb)
    	cr.move_to(0, 0)
    	cr.line_to(x_dest_1, y_dest_1)
    	cr.line_to(x_dest_2, y_dest_2)
    	cr.fill()

    	cr.restore()


    def drawSpeed(self, cr, xc, yc, speed):
        """
        draw a speed indicator around (xc, yc)
        :param cr: drawing context
        :param xc: center x
        :param yc: center y
        :param speed: in m/s
        :return:
        """

        cr.save()


        cr.translate(xc, yc)

        # headline text
        self.drawTextAt(cr, "Speed (m/s)", 0, -self.h/LINEAR_DIVIDER_HEIGHT * 1.2, 15, color=(0, 0, 1))

        # surrounding rect
        # print("drawSpeed")
        cr.set_source_rgb(1, 0, 0)
        cr.rectangle(-self.w/LINEAR_DIVIDER_WIDTH, -self.h/LINEAR_DIVIDER_HEIGHT, self.w/LINEAR_DIVIDER_WIDTH*2, self.h/LINEAR_DIVIDER_HEIGHT*2)
        cr.fill()

        # indicator line
        slideHeight = h.valueMap(speed, SENSOR_SPEED_MIN, SENSOR_SPEED_MAX, self.h/LINEAR_DIVIDER_HEIGHT, -self.h/LINEAR_DIVIDER_HEIGHT)
        cr.set_source_rgb(0, 0, 1)
        cr.move_to(-self.w/LINEAR_DIVIDER_WIDTH, slideHeight)
        cr.line_to(self.w/LINEAR_DIVIDER_WIDTH, slideHeight)
        cr.stroke()

        # indicator text (value)
        self.drawTextAt(cr, str(speed) + "", self.w/LINEAR_DIVIDER_WIDTH * 1.5, slideHeight, 16, color=(0,0,1))

        # Min & Max
        self.drawTextAt(cr, str(SENSOR_SPEED_MIN), self.w / LINEAR_DIVIDER_WIDTH * 1.5, +1.1*self.h/LINEAR_DIVIDER_HEIGHT, 10, color=(0, 0, 1))
        self.drawTextAt(cr, str(SENSOR_SPEED_MAX), self.w / LINEAR_DIVIDER_WIDTH * 1.5, -1.1*self.h/LINEAR_DIVIDER_HEIGHT, 10, color=(0, 0, 1))

        cr.restore()

        # old draw
        #strToRender = "Speed: " + str(self.speed) + " m/s"
        #self.drawTextAt(cr, strToRender, 3*self.w/4, self.h/32, self.h/42)

    def drawTextAt(self, cr, text, x, y, fontsize, color=(1,0,0)):
        cr.save()
        cr.set_source_rgb(color[0], color[1], color[2])
        cr.select_font_face("Courier", cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_BOLD)
        cr.set_font_size(fontsize)
        (_x, _y, width, height, dx, dy) = cr.text_extents(text)
        cr.move_to(x - width/2, y)
        cr.show_text(text)
        cr.restore()

    def quit(self):
        # TODO stop threads here
        gtk.main_quit()

if __name__ == "__main__":
    app = HeadUpDisplay()
    gtk.main()
