#include <PololuMaestro.h>
//#include <EEPROM.h>
#include <avr/pgmspace.h>  // needed for PROGMEM

// table of angle values obtained using inverse kinematics from a desired trajectory in the task space
const int table[]PROGMEM = {
864, 1458, 881, 1469, 899, 1481, 918, 1492, 937, 1503, 957, 1515, 978, 1526, 999, 1538, 1020, 1549, 1042, 1560, 
1063, 1571, 1084, 1581, 1104, 1591, 1123, 1599, 1140, 1606, 1154, 1612, 1166, 1615, 1175, 1617, 1182, 1618, 1185, 1616, 
1187, 1614, 1186, 1610, 1184, 1605, 1180, 1599, 1175, 1593, 1171, 1587, 1166, 1581, 1162, 1575, 1157, 1569, 1154, 1563, 
1150, 1558, 1146, 1552, 1143, 1547, 1140, 1542, 1137, 1537, 1135, 1532, 1132, 1527, 1130, 1522, 1128, 1518, 1126, 1513, 
1125, 1509, 1123, 1505, 1122, 1501, 1121, 1497, 1120, 1493, 1119, 1489, 1119, 1485, 1119, 1481, 1119, 1478, 1119, 1475, 
1119, 1471, 1119, 1468, 1120, 1465, 1120, 1462, 1119, 1458, 1119, 1454, 1118, 1451, 1117, 1447, 1115, 1442, 1113, 1438, 
1110, 1433, 1107, 1428, 1103, 1422, 1099, 1417, 1094, 1411, 1088, 1404, 1082, 1397, 1074, 1390, 1066, 1382, 1057, 1374, 
1046, 1366, 1035, 1356, 1022, 1347, 1008, 1336, 992, 1326, 976, 1315, 958, 1304, 940, 1292, 921, 1281, 902, 1271, 
883, 1261, 866, 1252, 849, 1244, 833, 1238, 819, 1232, 806, 1227, 794, 1223, 782, 1219, 772, 1216, 762, 1213, 
752, 1211, 744, 1209, 735, 1207, 727, 1206, 720, 1205, 712, 1204, 706, 1203, 699, 1203, 693, 1203, 687, 1203, 
681, 1203, 676, 1203, 671, 1204, 666, 1205, 661, 1206, 657, 1207, 653, 1208, 650, 1210, 646, 1212, 644, 1214, 
641, 1216, 639, 1219, 637, 1221, 636, 1224, 635, 1228, 634, 1231, 634, 1235, 634, 1239, 635, 1244, 637, 1248, 
638, 1253, 640, 1258, 643, 1264, 646, 1270, 650, 1276, 655, 1282, 659, 1288, 665, 1295, 671, 1302, 677, 1310, 
685, 1317, 692, 1325, 701, 1333, 710, 1342, 719, 1350, 729, 1359, 740, 1368, 751, 1377, 763, 1387, 775, 1396, 
789, 1406, 802, 1416, 817, 1426, 832, 1437, 848, 1448, 864, 1458 
};

/* On boards with a hardware serial port available for use, use
that port to communicate with the Maestro. For other boards,
create a SoftwareSerial object using pin 10 to receive (RX) and
pin 11 to transmit (TX). */
#ifdef SERIAL_PORT_HARDWARE_OPEN
  #define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
  #include <SoftwareSerial.h>
  SoftwareSerial maestroSerial(10, 11);
#endif

/* Next, create a Maestro object using the serial port.
Uncomment one of MicroMaestro or MiniMaestro below depending
on which one you have. */
// MicroMaestro maestro(maestroSerial);
MiniMaestro maestro(maestroSerial);

void setup()
{
  // Set the serial baud rate.
  Serial.begin(9600); // send and receive at 9600 baud  
  maestroSerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
}

//int angle = 0;
int count = 0;
const int joints = 2;
const int length_table = 9;
const int nframes = 146;
float f = 25;
float T = 1/f;


void loop()
{

  /* setTarget takes the channel number you want to control, and
     the target position in units of 1/4 microseconds. A typical
     RC hobby servo responds to pulses between 1 ms (4000) and 2
     ms (8000). */

  for (int i=0; i <= nframes - 1; i++){
    for(int j=0; j <= joints -1 ; j++ ){
    
      int angle = pgm_read_word(&table[count]);
      if (j==0 && angle>2300){ angle = 2300; }
      if (j==0 && angle<700){ angle = 700; }
      if (j==1 && angle>1865){ angle = 1865; }
      if (j==1 && angle>998){ angle = 998; }
      //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)

      maestro.setTarget(j+1, angle*4);
      maestro.setTarget(j+2, angle*4);
      Serial.print("The ");
      Serial.print(i);
      Serial.print("th angle of joint ");
      Serial.print(j);
      Serial.print(" is ");
      Serial.println(angle);    // print the number
      count++;
    } 
    delay(T*1000);
  }
  count = 0;
}
