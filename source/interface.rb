require 'rubygems'
require 'serialport'

SERIAL_PORT = '/dev/tty.usbmodemfd111'
SERIAL_BAUD = 9600
SERIAL_DATA_BIT = 8
SERIAL_STOP_BIT = 1

sp = SerialPort.new(SERIAL_PORT, SERIAL_BAUD, SERIAL_DATA_BIT, SERIAL_STOP_BIT, SerialPort::NONE)

data = ARGV[0]
data.each_char {|c| sp.write(c) }
sp.write("\n")

sp.close()
