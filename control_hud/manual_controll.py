import sys
import pygame

from PyQt5 import QtWidgets, QtGui, uic


class joyStick():

    def __init__(self):
        pygame.init()
        pygame.joystick.init()

    def start(self):
        joystick_instance = pygame.joystick.Joystick(0)
        joystick_instance.init()
        print(pygame.joystick.get_count())
        print(joystick_instance.get_name())
        print(joystick_instance.get_numaxes())

        while True:
            pygame.event.get()

            # get_axis(0) -> roll
            # get_axis(1) -> pitch
            # get_axis(2) -> yawn
            # get_axis(3) -> roll
            print(joystick_instance.get_axis(3))

class UiDemo(QtWidgets.QDialog):
    # constructor
    def __init__(self):
        QtWidgets.QDialog.__init__(self)
        # load and show the user interface created with the designer.
        self.ui = uic.loadUi('manual_controll.ui')

        self.ui.buttonBox.accepted.connect(self.ok_function)
        self.ui.buttonBox.rejected.connect(self.cancel_function)
        self.ui.show()

    def ok_function(self):
        print("ok")

    def cancel_function(self):
        print("cancel")

def _main(argv):
    """
        Main function to avoid pylint complains concerning constant names.
    """
    app = QtWidgets.QApplication(argv)
    uiDemo = UiDemo()

    joystick = joyStick()
    joystick.start()

    sys.exit(app.exec_())

if __name__ == '__main__':
    _main(sys.argv)