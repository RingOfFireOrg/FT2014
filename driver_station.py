import serial,sys
import msvcrt as m
baud = 9600

if ( len(sys.argv) == 1 ) :
  print "ERROR: Usage - " + str(sys.argv[0]) + " <comm port name, e.g. COM1>"
  quit()

port_id = str(sys.argv[1])
print "serial port parameter: " + str(port_id)
print "FLUSHING..., please wait"

ser = serial.Serial(port=port_id, baudrate=baud, timeout=2)
while True:
    response = ''
    response = ser.readline()
    print response.strip('\n')
    if response is '':
        break
ser.close()

ser = serial.Serial(port=port_id, baudrate=baud, timeout=30)

print "Please count to 10 before beginning input"

while True:
    mychar = m.getch()
    ser.write(mychar)
    print "Running:" + mychar
    if ('q' == mychar):
       quit()
    while True:
        response = ser.readline()
        print response.strip('\n')
        if response.strip() in ['ok','start']:
            break
 
ser.close()
