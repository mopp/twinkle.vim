require 'socket'
require 'thread'
require 'serialport'


SERIAL_PORT = '/dev/tty.usbmodemfd111'
SERIAL_BAUD = 9600
SERIAL_DATA_BIT = 8
SERIAL_STOP_BIT = 1

sp = SerialPort.new(SERIAL_PORT, SERIAL_BAUD, SERIAL_DATA_BIT, SERIAL_STOP_BIT, SerialPort::NONE)


Signal.trap(:INT) {
    sp.close()
    exit(0)
}
Signal.trap(:QUIT){
    sp.close()
    exit(0)
}


gs = TCPServer.open(ARGV[0])
addr = gs.addr
addr.shift


loop do
    Thread.start(gs.accept) do |s|
        data = s.gets
        data.each_char {|c| sp.write(c) }
        sp.write("\n")

        # puts "start";
        # puts s.gets;

        # system("touch " + s.gets);

        s.close;
    end
end
sp.close()
