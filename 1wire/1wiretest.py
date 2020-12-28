import ow
ow.init('localhost:4304')
sensorlist = ow.Sensor('/').sensorList()
for sensor in sensorlist:
    print('Device Found')
    print('Address: ' + sensor.address)
    print('Family: ' + sensor.family)
    print('ID: ' + sensor.id)
    print('Type: ' + sensor.type)
    print(' ')
